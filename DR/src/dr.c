/*
* FILE: 	dr.c
* PROJECT: 	Hoochamacallit System - A3
* PROGRAMMER: 	Gerritt Hooyer
* FIRST VER.: 	2022-03-07
* DESCRIPTION:	The body of main() in the dr portion
*		of the hoochamacallit system.
*/
#define DEBUG 1

/* DEPENDENCIES */
#include "../inc/drshm.h"
#include "../inc/drmsg.h"
#include "../../Common/inc/logger.h"

#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/shm.h>

/* CONSTANTS */
#define SLEEP_TIME 2
#define LAST_HEARD_CUTOFF_TIME 35

int main()
{
    // Queue and ML variables
    int queueID = 0;
    MasterList* mlptr = NULL;
    msg msg;
    int msgSize = sizeof(msg) - sizeof(long);

    // Time variables
    time_t time_ptr;
    time(&time_ptr);

    // Check for and create message queue
    queueID = get_mid(getMk());

#if defined DEBUG
printf("message queue ID %d\n", queueID);
fflush (stdout);
#endif

    // Create Master List
    mlptr = getML();
    if(mlptr == NULL)
    {

#if defined DEBUG
printf("Master list error\n");
#endif
        //Error
        logError("Master list error");
    }

    /******************************** Main loop ********************************/
    while(true)
    {

#if defined DEBUG
logError("Start looping\n");
int i = 0;
printf("Looping: %d\n", i++);
fflush (stdout);
#endif
	printf("Sleeping for %d(s)",SLEEP_TIME);
        // Sleep 15s
        sleep(SLEEP_TIME);

        // Receive message
        msgrcv(queueID, &msg, msgSize, 1, 0);

#if defined DEBUG
printf("Received message from %d", msg.pid);
#endif

        // Check ML, does machineID exist?
        bool mid_exists = false;
        for(int i = 0; i < mlptr->numberOfDCs; i++)
        {
            // If it exists update entry
            if(msg.pid == mlptr->dc[i].dcProcessID)
            {
                mid_exists = true;
                mlptr->dc->lastTimeHeardFrom = time(&time_ptr);
                logDR(msg, "updated in the master list", "MSG RECEIVED");

#if defined DEBUG
printf("updated in the master list");
fflush (stdout);
#endif

            }
        }
        // If it DNE, create entry
        if(mid_exists == false)
        {
            // Error check for going over our Max DC limit 
            if((mlptr->numberOfDCs + 1) >= MAX_DC_ROLES)
            {
                // Log error
                logError("DC number overflow");

#if defined DEBUG
printf("DC number overflow");
fflush (stdout);
#endif

            }
            else
            {
                // Add to ML
                DCInfo newDC;
                newDC.dcProcessID = msg.pid;
                newDC.lastTimeHeardFrom = time(&time_ptr);

                mlptr->dc[mlptr->numberOfDCs] = newDC;
                mlptr->numberOfDCs++;
                // Log success
                logDR(msg, "added to the master list", "NEW DC");

#if defined DEBUG
printf("DC number overflow");
fflush (stdout);
#endif

            }
        }

        // Does message status equal 6?
        if(msg.status == MSG_MCHN_OFFLN)
        {
            // Find DC index
            for(int i = 0; i < mlptr->numberOfDCs; i++)
            {
                if(msg.pid == mlptr->dc[i].dcProcessID)
                {
                    // Delete DC
                    DCInfo* newDCArray = mlptr->dc;
                    deleteDC(newDCArray, mlptr->numberOfDCs, i);
                    // Log
                    logDR(msg, "has gone OFFLINE", "Removing from master-list");

#if defined DEBUG
printf("Removing from master-list");
fflush (stdout);
#endif

                }
            }
        }

        // Has it been 35s since we last heard from any machine?
        // Find DC index
        for(int i = 0; i < mlptr->numberOfDCs; i++)
        {
            if((mlptr->dc[i].lastTimeHeardFrom - time(&time_ptr)) >= LAST_HEARD_CUTOFF_TIME)
            {
                // Delete DC
                DCInfo* newDCArray = mlptr->dc;
                deleteDC(newDCArray, mlptr->numberOfDCs, i);
                // Log
                logDR(msg, "has gone OFFLINE", "Removing from master-list");

#if defined DEBUG
printf("Removing from master-list");
fflush (stdout);
#endif

            }
        }

        // Number of machines in zero?
        if(mlptr->numberOfDCs <= 0)
        {

#if defined DEBUG
printf("Machines are zero\n");
fflush (stdout);
#endif

            logDRTerminate();
            // Remove queue and free memory
            msgctl(queueID, IPC_RMID, (struct msqid_ds *)NULL);
            shmdt (mlptr);
        }
    }
    return 0;
}
