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
#include "../../Common/inc/logger.h"

/* CONSTANTS */
#define SHM_NOT_FOUND -1
#define SHM_FLAG 0
#define MAX_ATTEMPTS 100
#define SLEEP_TIME 0.1
#define KEY_ML 16535
#define DEBUG 1

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

printf("ML Start\n");


    MasterList* mlptr = NULL;
    key_t shmKey = ftok(".", 16535);
    int attempts = 0;
    int shmid = SHM_NOT_FOUND;

#if defined DEBUG
printf("Before ML Key Found\n");
#endif

    if(shmKey != SHM_NOT_FOUND)
    {

#if defined DEBUG
printf("ML Key Found\n");
#endif

        shmid = shmget(shmKey,sizeof(MasterList),(IPC_CREAT | 0660));

        if(shmid != SHM_NOT_FOUND)
        {
            mlptr = (MasterList *)shmat(shmid,NULL,SHM_FLAG);
            
#if defined DEBUG
printf("ML Created\n");
#endif
            if(mlptr == NULL)
            {
                logError("Master list memory block creation failure");
                printf("mlptr = %lX\n",(long)mlptr);
            }
        }
    }

    return mlptr;
}

/*
* FUNCTION      : deleteDC()
* DESCRIPTION   : Deletes a DC from array and rearranges array
* PARAMETERS    : DCInfo dc[MAX_DC_ROLES] 
*               : int numberOfDCs
*               : int dcToDelete
* RETURNS       : int retCode | 0 for success, -1 for failure
*/
int deleteDC(DCInfo dc[], int numberOfDCs, int dcToDelete)
{
    if(dcToDelete < 0 || dcToDelete > numberOfDCs)
    {
        logError("Invalid DC selected for deletion");
        return -1;
    }
    else
    {
        for(int i = dcToDelete - 1; i < numberOfDCs - 1; i++)
        {
            dc[i] = dc[i + 1];
        }
        numberOfDCs--;
        return 0;
    }
}