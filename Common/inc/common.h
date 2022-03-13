/* CONSTANTS */
#define DEBUG 1
#define IPC_ID 16534
#define MSG_QUEUE_NOT_FOUND -1
#define MSG_QUEUE_PATH "/tmp"
#define MSG_OK 0
#define MSG_HYDR_PRS_FAIL 1
#define MSG_SFTY_BTN_FAIL 2
#define MSG_NO_RAW_MAT 3
#define MSG_TEMP_OUT_OF_RANGE 4
#define MSG_OPRTR_ERR 5
#define MSG_MCHN_OFFLN 6

#define DC01 0
#define DC02 1
#define DC03 2
#define DC04 3
#define DC05 4
#define DC06 5
#define DC07 6
#define DC08 7
#define DC09 8
#define DC10 9

/* DEFINITIONS */
typedef struct 
{
    long type;
    int status;
    pid_t pid;
} msg;

/*typedef struct 
{
    int logID;
    char* logMsg;
} logEntry;*/

