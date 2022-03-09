/*
* FILE: 	dxshm.c
* PROJECT: 	Hoochamacallit System - A3
* PROGRAMMER: 	Gerritt Hooyer
* FIRST VER.: 	2022-03-07
* DESCRIPTION:	The header file for the drshm.c file
*/

/* DEPENDENCIES */
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include "../../Common/inc/mlstruct.h"
#include "../../Common/inc/common.h"

/* CONSTANTS */
#define SHM_NOT_FOUND -1
#define SHM_FLAG 0
#define MAX_ATTEMPTS 100
#define SLEEP_TIME 0.1

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
