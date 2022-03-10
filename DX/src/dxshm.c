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
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../Common/inc/mlstruct.h"
#include "../../Common/inc/common.h"

/* CONSTANTS */
#define SHM_NOT_FOUND -1
#define SHM_FLAG 0
#define MAX_ATTEMPTS 100
#define SLEEP_TIME 0.1

#define WOD_MIN 0
#define WOD_MAX 20

/*
* FUNCTION      : getML()
* DESCRIPTION   : Gets a masterlist using shared memory created by
*                 the DR subsystem.  
* PARAMETERS    : N/A
* RETURNS       : MasterList* | mlptr | A pointer to the shared memory
*                 for the master list.
*/
MasterList* getML()
{
    MasterList* mlptr = NULL;
    key_t shmKey = ftok(".",16535);
    int attempts = 0;
    int shmid = SHM_NOT_FOUND;

    // We can now check if we successfully got the key
    if(shmKey != SHM_NOT_FOUND)
    {
        // First, let's enter a while loop
        while(1)
        {
            // If so, we can try to get the id
            shmid = shmget(shmKey,sizeof(MasterList),SHM_FLAG);
            //Increment the counter
            attempts++;
            //Now let's check if we actually got it
            if(shmid == SHM_NOT_FOUND)
            {
                if(DEBUG)
                {
                    printf("shared memory id not found : %d / %d attempts...\n",attempts,MAX_ATTEMPTS);
                    printf("Sleeping for 10 seconds...\n");
                }
                //If the ID wasn't found, we need to sleep for 10 seconds
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
        if(shmid != SHM_NOT_FOUND)
        {
            mlptr = (MasterList *)shmat(shmid,NULL,SHM_FLAG);
            if(DEBUG)
            {
                printf("mlptr = %lX\n",(long)mlptr);
            }
        }
    }

    return mlptr;
}

/*
* FUNCTION      : wheelOfDestruction(MasterList* mlptr)
* DESCRIPTION   : Picks a random action from the WoD and executes it.
* PARAMETERS    : MasterList* | mlptr | A pointer to the shared memory
*                 for the master list.
* RETURNS       : N/A
*/
void wheelOfDestruction(MasterList* mlptr)
{
    int actionID = -1;
    // First, let's check for the existence of the msg queue
    key_t msgKey = ftok(MSG_QUEUE_PATH,IPC_ID);
    
    
        srand(time(NULL));
        // Seed the random number generator
        while(1)
        {
            // Then use the msgKey to check for the existance of the queue
            if (msgget(msgKey,0) == MSG_QUEUE_NOT_FOUND)
            {
                // Exit if it's not available
                break;
            }
            // Generate the action
            actionID = (rand() % (WOD_MAX - WOD_MIN) + WOD_MIN);
            // Then run the action
            wodAction(actionID, mlptr);
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
void wodAction(int actionID, MasterList* mlptr)
{
    DCInfo* dc = NULL;
    switch(actionID)
    {
        //Do nothing
        case 0:
        case 8:
        case 19:
            break;
        // Kill DC-01
        case 1:
        case 4:
        case 11:
            //Get a reference to the DC
            dc = &(mlptr->dc[DC01]);
            //Then try to kill the process
            killDC(dc);
            break;
        //Kill DC-02
        case 3:
        case 6:
        case 13:
            //Get a reference to the DC
            dc = &(mlptr->dc[DC02]);
            //Then try to kill the process
            killDC(dc);
            break;
        //Kill DC-03
        case 2:
        case 5:
        case 15:
            //Get a reference to the DC
            dc = &(mlptr->dc[DC03]);
            //Then try to kill the process
            killDC(dc);
            break;
        //Kill DC-04
        case 7:
            //Get a reference to the DC
            dc = &(mlptr->dc[DC04]);
            //Then try to kill the process
            killDC(dc);
            break;
        //Kill DC-05
        case 9:
            //Get a reference to the DC
            dc = &(mlptr->dc[DC05]);
            //Then try to kill the process
            killDC(dc);
            break;
        //Kill DC-06
        case 12:
            //Get a reference to the DC
            dc = &(mlptr->dc[DC06]);
            //Then try to kill the process
            killDC(dc);
            break;
        //Kill DC-07
        case 14:
            //Get a reference to the DC
            dc = &(mlptr->dc[DC07]);
            //Then try to kill the process
            killDC(dc);
            break;
        //Kill DC-08
        case 16:
            //Get a reference to the DC
            dc = &(mlptr->dc[DC08]);
            //Then try to kill the process
            killDC(dc);
            break;
        //Kill DC-09
        case 18:
            //Get a reference to the DC
            dc = &(mlptr->dc[DC09]);
            //Then try to kill the process
            killDC(dc);
            break;
        //Kill DC-10
        case 20:
            //Get a reference to the DC
            dc = &(mlptr->dc[DC10]);
            //Then try to kill the process
            killDC(dc);
            break;        
    }
}

/*
* FUNCTION      : killDC(DCInfo* dc)
* DESCRIPTION   : Kills a DC if possible using the DCInfo
* PARAMETERS    : DCInfo* | dc | A pointer to the DC based on the WoD action
* RETURNS       : N/A
*/
void killDC(DCInfo* dc)
{
    //Check if the DC was in the list
    if (dc != NULL)
    {
        //Then check if we're good to kill the process
        if(kill(dc->dcProcessID,0))
        {
            // If valid, we can kill the process
            kill(dc->dcProcessID,SIGKILL);
        }
    }
}