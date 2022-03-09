/* CONSTANTS */
#define DEBUG 1
#define MSG_OK 0
#define MSG_HYDR_PRS_FAIL 1
#define MSG_SFTY_BTN_FAIL 2
#define MSG_NO_RAW_MAT 3
#define MSG_TEMP_OUT_OF_RANGE 4
#define MSG_OPRTR_ERR 5
#define MSG_MCHN_OFFLN 6

/* DEFINITIONS */
typedef struct 
{
    long msgType;
    pid_t pid;
} msg;

