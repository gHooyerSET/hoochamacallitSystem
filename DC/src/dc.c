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

#if defined DEBUG
printf("message queue ID %d\n", msgQueueID);
#endif

    // Once attached to the message queue, send OK message
    sendOKMsg(msgQueueID);

#if defined DEBUG
printf("Sending ok message");
#endif

    // Then start sending random messages (will exit on Offline being sent)
    sendRandMsgStart(msgQueueID);

#if defined DEBUG
printf("Sending random message");
#endif

    // Exit
    return 0;
}
