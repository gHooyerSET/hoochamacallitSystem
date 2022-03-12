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
#include <sys/msg.h>
#include "../../Common/inc/logger.h"

/* CONSTANTS */
#define CURRENT_FOLDER "." // Folder for message queue location

/*
* FUNCTION      : getMK()
* DESCRIPTION   : Gets a key for the message queue
* PARAMETERS    : N/A
* RETURNS       : key_t | message key 
*/    
key_t getMk()
{
    key_t message_key = ftok (MSG_QUEUE_PATH, IPC_ID);
    if (message_key == -1)
    {
        logError("Message key failure");
        return -1;
    }
    else
    {
        return message_key;
    }
}

/*
* FUNCTION      : get_mid()
* DESCRIPTION   : Gets a message queue ID, creates one if it DNE
* PARAMETERS    : key_t | message key 
* RETURNS       : int mid | message queue id
*/  
int get_mid(key_t message_key)
{
    int mid = -1;

    // If mid DNE create one
    if((mid = msgget(message_key, 0)) == -1)
    {
        mid = msgget (message_key, IPC_CREAT | 0660); 
        if (mid == -1) 
        { 
            logError("mid creation error");
        } 
    }
    else
    {
        // Delete and create one
        msgctl (mid, IPC_RMID, NULL);
        mid = msgget (message_key, IPC_CREAT | 0660); 
        if (mid == -1) 
        { 
            logError("mid creation error");
        } 
    }

    return mid;
}