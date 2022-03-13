/*
* FILE: 	mlstruct.h
* PROJECT: 	Hoochamacallit System - A3
* PROGRAMMER: 	Gerritt Hooyer and Nathan Domingo
* FIRST VER.: 	2022-03-09
* DESCRIPTION:	Structs related to the function of the system.
*/
#ifndef MLSTRUCT_H_
#define MLSTRUCT_H_
/* DEPENDENCIES */
#include <time.h>

/* CONSTANTS */
#define MAX_DC_ROLES 10

/* DEFINITIONS */
typedef struct
{
    pid_t dcProcessID;
    time_t lastTimeHeardFrom;
} DCInfo;

typedef struct
{
    long type;
    int msgQueueID;
    int numberOfDCs;
    DCInfo dc[MAX_DC_ROLES];
} MasterList;
#endif