#include <sys/types.h>
#include <sys/ipc.h>
#include "../../Common/inc/common.h"

#define SLEEP_TIME 10

int getMsgQueue()
{
    int msgQueueID = 0;
    key_t msgKey = ftok(MSG_QUEUE_PATH,IPC_ID);

    // Make sure the key was valid
    if (msgKey != MSG_QUEUE_NOT_FOUND)
    {
        // Create an infinite loop
        while(1)
        {
            // Get the queue ID using the key
            msgQueueID = msgget(msgKey, 0);
            // If it's valid, break out of the loop.
            if(msgQueueID != MSG_QUEUE_NOT_FOUND)
            {
                // Break out of the loop
                break;
            }
            else
            {
                // Otherwise, we sleep for 10 s
                sleep(SLEEP_TIME);
            }
        }
    }
    
    return msgQueueID;
}

