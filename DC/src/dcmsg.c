/*
 * FILE: 	dcmsg.c
 * PROJECT: 	Hoochamacallit System - A3
 * PROGRAMMER: 	Gerritt Hooyer
 * FIRST VER.: 	2022-03-07
 * DESCRIPTION:	The functions related to the MsgQ for the DC.
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../../Common/inc/common.h"
#include "../../Common/inc/logger.h"

#define SLEEP_TIME 10

/*
 * FUNCTION      : getMsgQueue()
 * DESCRIPTION   : Sends the OK message.
 * PARAMETERS    : N/A
 * RETURNS       : int msgQueueID | The ID of the msg q
 */
int getMsgQueue()
{
    int msgQueueID = 0;
    key_t msgKey = ftok(MSG_QUEUE_PATH, IPC_ID);

    // Make sure the key was valid
    if (msgKey != MSG_QUEUE_NOT_FOUND)
    {
        // Create an infinite loop
        while (1)
        {
            // Get the queue ID using the key
            msgQueueID = msgget(msgKey, 0);
            // If it's valid, break out of the loop.
            if (msgQueueID != MSG_QUEUE_NOT_FOUND)
            {
                // Break out of the loop
                break;
            }
            else
            {
#if defined DEBUG
                printf("Message Queue Not Found\nSleeping for %d(s)\n", SLEEP_TIME);
                fflush(stdout);
#endif
                // Otherwise, we sleep for 10 s
                sleep(SLEEP_TIME);
            }
        }
    }

    return msgQueueID;
}

/*
 * FUNCTION      : getMsgSize()
 * DESCRIPTION   : Sends the OK message.
 * PARAMETERS    : N/A
 * RETURNS       : int msgSize | The size of the msg struct - size of long
 */
int getMsgSize()
{
    int msgSize = sizeof(msg) - sizeof(long);
    return msgSize;
}

/*
 * FUNCTION      : sendOKMsg(int msgQueueID)
 * DESCRIPTION   : Sends the OK message.
 * PARAMETERS    : int msgQueueID | The ID for the msg q
 * RETURNS       : N/A
 */
void sendOKMsg(int msgQueueID)
{
    // Declare our variables
    msg m;
    int msgSize = 0;
    // Set the message contents
    m.type = 1;
    m.status = MSG_OK;
    m.pid = getpid();
    // Get the size of the msg
    msgSize = getMsgSize();
    // Attempt to send to the message.
    if (msgsnd(msgQueueID, &m, msgSize, 0) != 0)
    {
#if defined DEBUG
        printf("OK Message failed to send.\n");
        fflush(stdout);
#endif
    }
    else
    {
#if defined DEBUG
        printf("OK Message sent : QueueID: %d PID : %d.\n", msgQueueID, m.pid);
        fflush(stdout);
#endif
        // Create the log entry
        logDC(m);
    }
}

/*
 * FUNCTION      : sendRandMsgStart(int msgQueueID)
 * DESCRIPTION   : Sends a random message.
 * PARAMETERS    : int msgQueueID | The ID for the msg q
 * RETURNS       : N/A
 */
void sendRandMsgStart(int msgQueueID)
{
    // Declare our variables
    int status = 0;
    int msgSize = 0;
    int sleepTime = 0;
    // Set the message contents
    msg m;
    m.pid = getpid();
    m.type = 1;

    // Get the message size
    msgSize = getMsgSize();

    // Seed the RNG
    srand(time(NULL));

    while (1)
    {
        // Generate the message status
        status = (rand() % (MSG_MCHN_OFFLN + 1));
        // Set the message status
        m.status = status;
        // Attempt to send the message to the queue
        if (msgsnd(msgQueueID, &m, msgSize, 0) != 0)
        {
#if defined DEBUG
            printf("Random message failed to send.\n");
#endif
        }
        else
        {
            // Create the log entry
            logDC(m);
        }
        // If the offline message was sent, break the loop.
        if (status == MSG_MCHN_OFFLN)
        {
#if defined DEBUG
            printf("Random message sent : QueueID: %d. MSG Code: %d\n", msgQueueID, m.status);
#endif
            break;
        }
        else
        {
            sleepTime = (rand() % (SLEEP_MAX + 1 - SLEEP_MIN) + SLEEP_MIN);
#if defined DEBUG
            printf("Sleeping for %d(s)\n", sleepTime);
#endif
            sleep(sleepTime);
        }
    }
}
