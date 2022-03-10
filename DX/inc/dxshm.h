/*
* FILE: 	drshm.h
* PROJECT: 	Hoochamacallit System - A3
* PROGRAMMER: 	Gerritt Hooyer
* FIRST VER.: 	2022-03-07
* DESCRIPTION:	The header file for the drshm.c file
*/

/* DEPENDENCIES */
#include "../../Common/inc/mlstruct.h"

/* PROTOTYPES */
MasterList* getML();
void wheelOfDestruction(MasterList* mlptr);
void wodAction(int actionID, MasterList* mlptr);
void killDC(DCInfo* dc);