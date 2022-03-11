/*
* FILE: 	logger.h
* PROJECT: 	Hoochamacallit System - A3
* PROGRAMMER: 	Gerritt Hooyer and Nathan Domingo
* FIRST VER.: 	2022-03-09
* DESCRIPTION:	Logger functions for Hoochamacallit System
*/
/* DEPENDENCIES */
#include <time.h>
#include <stdio.h>
#include "./common.h"

/* CONSTANTS */
#define LOG_PATH_DC "/tmp/dataCreator.log"
#define LOG_PATH_DM "/tmp/dataMonitor.log"
#define LOG_PATH_DX "/tmp/dataCorruptor.log"
#define MSG_BUFFER_SIZE 128
#define MSG_STATUS_BUFFER_SIZE 64
#define MAX_STATUS 7

/* Definitions */
typedef struct {
    char discription[MAX_STATUS][MSG_STATUS_BUFFER_SIZE]
    {
        "Everything is OKAY", "Hydraulic Pressure Failure", "Safety Button Failure", 
        "No Raw Material in the Process", "Operating Temperature Out of Range", "Operator Error", 
        "Machine is Off-line"
    };
}MsgStatus;

/*
* FUNCTION      : logDC()
* DESCRIPTION   : Creates a DC log
* PARAMETERS    : msg msgSent | Message info
* RETURNS       : NA
*/
void logDC(msg msgSent)
{
    MsgStatus msgStatus;
    char logMsg[MSG_BUFFER_SIZE];

    time_t time_ptr;
    time(&time_ptr);

    char* logTime = asctime(localtime(&time_ptr));
    
    snprintf(logMsg, MSG_BUFFER_SIZE, "[%s] : DC [%d] - MSG SENT - Status %d (%s)", logTime, msgSent.pid, msgSent.status, msgStatus.discription[msgSent.status]);
}

/*
* FUNCTION      : logDR()
* DESCRIPTION   : Creates a DR log
* PARAMETERS    : msg msgSent | Message info
*               : char* eventMsg | Event message string
* RETURNS       : NA
*/
void logDR(msg msgSent, const char* eventMsg)
{
    MsgStatus msgStatus;
    char logMsg[MSG_BUFFER_SIZE];

    time_t time_ptr;
    time(&time_ptr);

    char* logTime = asctime(localtime(&time_ptr));
    
    snprintf(logMsg, MSG_BUFFER_SIZE, "[%s] : DC-[%2d] [%d] %s - MSG RECEIVED - Status %d (%s)", msgSent.status, logTime, msgSent.pid, eventMsg , msgSent.status, msgStatus.discription[msgSent.status]);
}