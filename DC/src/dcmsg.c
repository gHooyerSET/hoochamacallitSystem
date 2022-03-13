#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../../Common/inc/common.h"

#define SLEEP_TIME 10

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
                if (DEBUG)
                {
                    printf("Message Queue Not Found\nSleeping for %d(s)\n", SLEEP_TIME);
                    fflush (stdout);
                }
                // Otherwise, we sleep for 10 s
                sleep(SLEEP_TIME);
            }
        }
    }

    return msgQueueID;
}


int getMsgSize()
{
    int msgSize = sizeof(msg) - sizeof(long);
    return msgSize;
}

void sendOKMsg(int msgQueueID)
{
    msg m;
    int msgSize = 0;
    m.type = 1;
    m.status = MSG_OK;
    m.pid = getpid();

    msgSize = getMsgSize();

    if (!msgsnd(msgQueueID, &m, msgSize, 0))
    {
        if (DEBUG)
        {
            printf("OK Message failed to send.\n");
            fflush (stdout);
        }
    }
    else
    {
        if (DEBUG)
        {
            printf("OK Message sent : QueueID: %d.\n", msgQueueID);
            fflush (stdout);
        }
    }
}

void sendRandMsgStart(int msgQueueID)
{
    int status = 0;
    int msgSize = 0;

    msg m;
    m.pid = getpid();
    m.type = 1;

    // Get the message size
    msgSize = getMsgSize();

    srand(time(NULL));

    while (1)
    {
        // Generate the message status
        status = (rand() % (MSG_OK - MSG_MCHN_OFFLN) + MSG_OK);
        // Set the message status
        m.status = status;
        // Attempt to send the message to the queue
        if (!msgsnd(msgQueueID, &m, msgSize, 0))
        {
            if (DEBUG)
            {
                printf("OK Message failed to send.\n");
            }
        }
        // If the offline message was sent, break the loop.
        if (status == MSG_MCHN_OFFLN)
        {
            if (DEBUG)
            {
                printf("random message sent.\n");
            }
            break;
        }
    }
}

