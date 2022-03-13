/*
 * FILE: 	dc.c
 * PROJECT: 	Hoochamacallit System - A3
 * PROGRAMMER: 	Gerritt Hooyer
 * FIRST VER.: 	2022-03-07
 * DESCRIPTION:	The main body for the DC.
 */
#include "../inc/dcmsg.h"
#include <unistd.h>
#include <stdio.h>
#include "../../Common/inc/common.h"

int main()
{
    // Initialize the msgQueueId variable
	int msgQueueID = MSG_QUEUE_NOT_FOUND;
    
    // Get the queue ID
    msgQueueID = getMsgQueue();

    // Once attached to the message queue, send OK message
    sendOKMsg(msgQueueID);

    // Then start sending random messages (will exit on Offline being sent)
    sendRandMsgStart(msgQueueID);

    // Exit
    return 0;
}
