/*
 * FILE: 	dxshm.c
 * PROJECT: 	Hoochamacallit System - A3
 * PROGRAMMER: 	Gerritt Hooyer
 * FIRST VER.: 	2022-03-07
 * DESCRIPTION:	The header file for the drshm.c file
 */

/* DEPENDENCIES */
#include <signal.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../Common/inc/mlstruct.h"
#include "../../Common/inc/common.h"
#include "../../Common/inc/logger.h"

/* CONSTANTS */
#define SHM_NOT_FOUND -1
#define SHM_FLAG 0
#define MAX_ATTEMPTS 100
#define SLEEP_TIME 10

#define WOD_MIN 0
#define WOD_MAX 20

#define DO_NOTHING_0    0
#define KILL_DC01_0     1
#define KILL_DC03_0     2
#define KILL_DC02_0     3
#define KILL_DC01_1     4
#define KILL_DC03_1     5
#define KILL_DC02_1     6
#define KILL_DC04_0     7
#define DO_NOTHING_1    8
#define KILL_DC05_0     9
#define DEL_MSGQ_0      10
#define KILL_DC01_2     11
#define KILL_DC06_0     12
#define KILL_DC02_2     13
#define KILL_DC07_0     14
#define KILL_DC03_2     15
#define KILL_DC08_0     16
#define DEL_MSGQ_1      17
#define KILL_DC09_0     18
#define DO_NOTHING_2    19
#define KILL_DC10_0     20

/*
 * FUNCTION      : getML()
 * DESCRIPTION   : Gets a masterlist using shared memory created by
 *                 the DR subsystem.
 * PARAMETERS    : N/A
 * RETURNS       : MasterList* | mlptr | A pointer to the shared memory
 *                 for the master list.
 */
MasterList *getML()
{
    MasterList *mlptr = NULL;
    key_t shmKey = ftok(".", 16535);
    int attempts = 0;
    int shmid = SHM_NOT_FOUND;

    // We can now check if we successfully got the key
    if (shmKey != SHM_NOT_FOUND)
    {
        // First, let's enter a while loop
        while (1)
        {
            // If so, we can try to get the id
            shmid = shmget(shmKey, sizeof(MasterList), SHM_FLAG);
            // Increment the counter
            attempts++;
            // Now let's check if we actually got it
            if (shmid == SHM_NOT_FOUND)
            {
#if defined DEBUG
                    printf("shared memory id not found : %d / %d attempts...\n", attempts, MAX_ATTEMPTS);
                    printf("Sleeping for 10 seconds...\n");
#endif
                // If the ID wasn't found, we need to sleep for 10 seconds
                sleep(SLEEP_TIME);
            }
            else
            {
                // shmid != SHM_NOT_FOUND, we can break out of the loop
                break;
            }
            // If the attempts counter == MAX_ATTEMPTS
            // we also need to break out
            if (attempts == MAX_ATTEMPTS)
            {
                break;
            }
        }
        // Now, let's check again that our ID was found (could be -1 after 100 attempts)
        if (shmid != SHM_NOT_FOUND)
        {
            mlptr = (MasterList *)shmat(shmid, NULL, SHM_FLAG);
#if defined DEBUG
                printf("mlptr = %lX\n", (long)mlptr);
#endif
        }
    }

    return mlptr;
}

/*
 * FUNCTION      : killDC(DCInfo* dc)
 * DESCRIPTION   : Kills a DC if possible using the DCInfo
 * PARAMETERS    : DCInfo* | dc | A pointer to the DC based on the WoD action
 * RETURNS       : N/A
 */
void killDC(DCInfo *dc)
{
    // Check if the DC was in the list
    if (dc != NULL)
    {
        // Then check if we're good to kill the process
        if (kill(dc->dcProcessID, 0))
        {
            // If valid, we can kill the process
            kill(dc->dcProcessID, SIGKILL);
        }
        // Then set DC to NULL
        dc=NULL;
    }
    else
    {
#if defined DEBUG
            printf("DC Entry not found.\n");
#endif
    }
}

/*
 * FUNCTION      : wheelOfDestruction(MasterList* mlptr)
 * DESCRIPTION   : Picks a random action from the WoD and executes it.
 * PARAMETERS    : MasterList* | mlptr | A pointer to the shared memory
 *                 for the master list.
 *                 int | actionID | The ID for the action
 * RETURNS       : N/A
 */
void wodAction(int actionID, MasterList *mlptr)
{
    DCInfo *dc = NULL;
    switch (actionID)
    {
    // Do nothing
    case DO_NOTHING_0:
    case DO_NOTHING_1:
    case DO_NOTHING_2:
        break;
    // Kill DC-01
    case KILL_DC01_0:
    case KILL_DC01_1:
    case KILL_DC01_2:
        // Get a reference to the DC
        dc = &(mlptr->dc[DC01]);
        // Then log the event
        logDX(dc,actionID,1);
        // Then try to kill the process
        killDC(dc);
        break;
    // Kill DC-02
    case KILL_DC02_0:
    case KILL_DC02_1:
    case KILL_DC02_2:
        // Get a reference to the DC
        dc = &(mlptr->dc[DC02]);
        // Then log the event
        logDX(dc,actionID,2);
        // Then try to kill the process
        killDC(dc);
        break;
    // Kill DC-03
    case KILL_DC03_0:
    case KILL_DC03_1:
    case KILL_DC03_2:
        // Get a reference to the DC
        dc = &(mlptr->dc[DC03]);
        // Then log the event
        logDX(dc,actionID,3);
        // Then try to kill the process
        killDC(dc);
        break;
    // Kill DC-04
    case KILL_DC04_0:
        // Get a reference to the DC
        dc = &(mlptr->dc[DC04]);
        // Then log the event
        logDX(dc,actionID,4);
        // Then try to kill the process
        killDC(dc);
        break;
    // Kill DC-05
    case KILL_DC05_0:
        // Get a reference to the DC
        dc = &(mlptr->dc[DC05]);
        // Then log the event
        logDX(dc,actionID,5);
        // Then try to kill the process
        killDC(dc);
        break;
    // Kill DC-06
    case KILL_DC06_0:
        // Get a reference to the DC
        dc = &(mlptr->dc[DC06]);
        // Then log the event
        logDX(dc,actionID,6);
        // Then try to kill the process
        killDC(dc);
        break;
    // Kill DC-07
    case KILL_DC07_0:
        // Get a reference to the DC
        dc = &(mlptr->dc[DC07]);
        // Then log the event
        logDX(dc,actionID,7);
        // Then try to kill the process
        killDC(dc);
        break;
    // Kill DC-08
    case KILL_DC08_0:
        // Get a reference to the DC
        dc = &(mlptr->dc[DC08]);
        // Then log the event
        logDX(dc,actionID,8);
        // Then try to kill the process
        killDC(dc);
        break;
    // Kill DC-09
    case KILL_DC09_0:
        // Get a reference to the DC
        dc = &(mlptr->dc[DC09]);
        // Then log the event
        logDX(dc,actionID,9);
        // Then try to kill the process
        killDC(dc);
        break;
    // Kill DC-10
    case KILL_DC10_0:
        // Get a reference to the DC
        dc = &(mlptr->dc[DC10]);
        // Then log the event
        logDX(dc,actionID,10);
        // Then try to kill the process
        killDC(dc);
        break;
    }
}

/*
 * FUNCTION      : wheelOfDestruction(MasterList* mlptr)
 * DESCRIPTION   : Picks a random action from the WoD and executes it.
 * PARAMETERS    : MasterList* | mlptr | A pointer to the shared memory
 *                 for the master list.
 * RETURNS       : N/A
 */
void wheelOfDestruction(MasterList *mlptr)
{
    int actionID = -1;
    int msgQueueID = MSG_QUEUE_NOT_FOUND;
    int sleepTime = 0;
    // First, let's check for the existence of the msg queue
    key_t msgKey = ftok(MSG_QUEUE_PATH, IPC_ID);
    srand(time(NULL));
    // Seed the random number generator
    while (1)
    {
        // Then use the msgKey to check for the existance of the queue
        if ((msgQueueID = msgget(msgKey, 0)) == MSG_QUEUE_NOT_FOUND)
        {
#if defined DEBUG
                printf("Message queue not found.\n");
#endif
            // Create the log entry
            logDXMsg("DX detexted that msgQ is gone = assuming DR/DCs done");
            // Exit if it's not available
            break;
        }
        // Generate the action
        actionID = (rand() % (WOD_MAX - WOD_MIN) + WOD_MIN);
        // Check if the 'destroy queue' option was selected
        if(actionID == DEL_MSGQ_0 || actionID == DEL_MSGQ_1)
        {
            // Then destroy the queue if needed
            msgctl(msgQueueID,IPC_RMID,NULL);
            // Then log the message
            logDXMsg("DX deleted the msgQ - the DR/DCs can't talk anymore - exiting");
            // Then break the loop
            break;
        }
        else
        {
            // Otherwise, run the action
            wodAction(actionID, mlptr);
            // Then sleep for the random amount of time
            sleepTime = (rand() % (SLEEP_MAX - SLEEP_MIN) + SLEEP_MIN);
            sleep(sleepTime);
        }
        
    }
}
