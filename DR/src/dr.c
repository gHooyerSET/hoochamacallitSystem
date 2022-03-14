/*
* FILE: 	dr.c
* PROJECT: 	Hoochamacallit System - A3
* PROGRAMMER: 	Gerritt Hooyer
* FIRST VER.: 	2022-03-07
* DESCRIPTION:	The body of main() in the dr portion
*		of the hoochamacallit system.
*/

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
#define SLEEP_TIME_PRE_MSG_REC 15
#define SLEEP_TIME 1.5
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

#if defined DEBUG
printf("mlptr = getML()");
fflush (stdout);
#endif

    // Create Master List
    mlptr = getML();

#if defined DEBUG
printf("%p\n", mlptr);
fflush (stdout);
#endif

    if(mlptr == NULL)
    {

#if defined DEBUG
printf("Master list error\n");
fflush (stdout);
#endif
        //Error
        logError("Master list error");
    }

    // Sleep 15s
    sleep(SLEEP_TIME_PRE_MSG_REC);

    /******************************** Main loop ********************************/
    while(true)
    {
        
#if defined DEBUG
printf("Waiting to receive msg\n");
fflush (stdout);
#endif
        // Sleep 15s
        sleep(SLEEP_TIME);
        // Receive message
        msgrcv(queueID, &msg, msgSize, 1, 0);

        //int numOfDCs = mlptr->numberOfDCs;
        
#if defined DEBUG
printf("DCs in ML: %d\n", mlptr->numberOfDCs);
fflush (stdout);
#endif

#if defined DEBUG
printf("Received message\n");
//printf("Received message from %d", msg.pid);
fflush (stdout);
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
                logDR(msg, "updated in the master list", "MSG RECEIVED", i);

#if defined DEBUG
printf("updated in the master list\n");
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
            }
            else
            {
                // Add to ML
                DCInfo newDC;
                newDC.dcProcessID = msg.pid;
                newDC.lastTimeHeardFrom = time(&time_ptr);

                // Log success
                logDR(msg, "added to the master list", "NEW DC", mlptr->numberOfDCs);

                mlptr->dc[mlptr->numberOfDCs] = newDC;
                mlptr->numberOfDCs++;

#if defined DEBUG
printf("added to the master list\n");
printf("DCs in ML: %d\n", mlptr->numberOfDCs);
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

#if defined DEBUG
printf("Removing DC %d Process %d from master-list\n\n", i, mlptr->dc[i].dcProcessID);
fflush (stdout);
for(int i = 0; i < mlptr->numberOfDCs; i++)
{
    printf("ML DC[%d] Process [%d]\n", i, mlptr->dc[i].dcProcessID);
    fflush (stdout);
}
#endif
                    // Delete DC
                    deleteDC(mlptr, i);

#if defined DEBUG
printf("After delete\n\n");
fflush (stdout);
for(int i = 0; i < mlptr->numberOfDCs; i++)
{
    printf("ML DC[%d] Process [%d]\n", i, mlptr->dc[i].dcProcessID);
    fflush (stdout);
}
#endif

                    // Log
                    logDR(msg, "has gone OFFLINE", "Removing from master-list", i);
                    mlptr->numberOfDCs--;
                }
            }
        }

        // Has it been 35s since we last heard from any machine?
        // Find DC index
        for(int i = 0; i < mlptr->numberOfDCs; i++)
        {
            int lastHeardTime = time(&time_ptr) - mlptr->dc[i].lastTimeHeardFrom;

#if defined DEBUG
printf("id = %d lastHeardTime: %d\n", mlptr->dc[i].dcProcessID, lastHeardTime);
fflush (stdout);
#endif

            if(lastHeardTime >= LAST_HEARD_CUTOFF_TIME)
            {

#if defined DEBUG
printf("Timeout = %d: Removing id = %d  from master-list\n", lastHeardTime, mlptr->dc[i].dcProcessID);
fflush (stdout);
#endif

                // Delete DC
                DCInfo* newDCArray = mlptr->dc;
                deleteDC(mlptr, i);
                // Log
                logDR(msg, "has gone OFFLINE from timeout", "Removing from master-list", i);
                mlptr->numberOfDCs--;
            }
        }

        // Number of machines in zero?
        if(mlptr->numberOfDCs <= 0)
        {

#if defined DEBUG
printf("numberOfDc=%d <= 0\n", mlptr->numberOfDCs);
fflush (stdout);
#endif

            logDRTerminate();

            // Remove queue and free memory
            msgctl(queueID, IPC_RMID, NULL);
            key_t shmKey = ftok(".", 16535);
            shmctl(shmget(shmKey,sizeof(MasterList),(IPC_CREAT | 0660)), IPC_RMID, NULL);

            return 0;
        }

        // Sleep 1.5s
        sleep(SLEEP_TIME);
    }
    return 0;
}
