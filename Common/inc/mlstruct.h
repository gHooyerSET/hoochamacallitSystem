/* DEPENDENCIES */
#include <time.h>

/* CONSTANTS */
#define MAX_DC_ROLES 10

/* DEFINITIONS */
typedef struct
{
    pid_t dcProcessID;
    time_t lastTimeHeardFrom;
} DCInfo;

typedef struct
{
    long type;
    int msgQueueID;
    int numberOfDCs;
    DCInfo dc[MAX_DC_ROLES];
} MasterList;
