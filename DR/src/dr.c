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

    // Create Master List
    mlptr = getML();

    if(mlptr == NULL)
    {
        //Error
        logError("Master list error");
    }

    // Sleep 15s
    sleep(SLEEP_TIME_PRE_MSG_REC);

    /******************************** Main loop ********************************/
    while(true)
    {
        // Sleep 15s
        sleep(SLEEP_TIME);

        // Check for and create message queue
        //queueID = get_mid(getMk());

        // Receive message
        msgrcv(queueID, &msg, msgSize, 1, 0);

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
                    deleteDC(mlptr, i);

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

            if(lastHeardTime >= LAST_HEARD_CUTOFF_TIME)
            {
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
