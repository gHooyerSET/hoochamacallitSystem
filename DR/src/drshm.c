/*
* FILE: 	drshm.c
* PROJECT: 	Hoochamacallit System - A3
* PROGRAMMER: 	Gerritt Hooyer
* FIRST VER.: 	2022-03-07
* DESCRIPTION:	Functions related to shared memory in the DR
*               subsystem.
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

    if(shmKey != SHM_NOT_FOUND)
    {
        shmid = shmget(shmKey,sizeof(MasterList),(IPC_CREAT | 0660));

        if(shmid != SHM_NOT_FOUND)
        {
            mlptr = (MasterList *)shmat(shmid,NULL,SHM_FLAG);
            
            if(DEBUG == 1)
            {
                printf("mlptr = %lX\n",(long)mlptr);
            }
        }
    }

    return mlptr;
}