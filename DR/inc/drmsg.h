/*
* FILE: 	drmsg.h
* PROJECT: 	Hoochamacallit System - A3
* PROGRAMMER: 	Gerritt Hooyer and Nathan Domingo
* FIRST VER.: 	2022-03-07
* DESCRIPTION:	The header file for the drmsg.c file
*/

#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h> 

/* DEPENDENCIES */
#define MSGQ_BAD_ID -1

/* PROTOTYPES */
key_t getMk();
int get_mid(key_t message_key);