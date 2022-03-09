/*
* FILE: 	drmsg.c
* PROJECT: 	Hoochamacallit System - A3
* PROGRAMMER: 	Gerritt Hooyer and Nathan Domingo
* FIRST VER.: 	2022-03-09
* DESCRIPTION:	Functions relating to the message que used for the Hoochamacallit System
*/

/* DEPENDENCIES */
#include <sys/types.h> 
#include <sys/ipc.h> 
 

/* CONSTANTS */
#define CURRENT_FOLDER "." // Folder for message queue location
#define KEY_ID 'A' // Application suite ID

/*
* FUNCTION      : getMK()
* DESCRIPTION   : Gets a key for the message queue
* PARAMETERS    : N/A
* RETURNS       : key_t | message key 
*/    
key_t GetMk()
{
    key_t message_key = ftok (CURRENT_FOLDER, KEY_ID);
}