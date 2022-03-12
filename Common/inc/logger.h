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
#define LOG_PATH_DC "../../tmp/dataCreator.log"
#define LOG_PATH_DM "../../tmp/dataMonitor.log"
#define LOG_PATH_DX "../../tmp/dataCorruptor.log"
#define LOG_PATH_ERROR "../../tmp/error.log"
#define MSG_BUFFER_SIZE 128
#define MSG_STATUS_BUFFER_SIZE 64
#define MAX_STATUS 7

/*
* FUNCTION      : logError()
* DESCRIPTION   : Creates an Error log
* PARAMETERS    : char* eventMsg | Event message string
* RETURNS       : NA
*/
static void logError(const char* eventMsg)
{
    char logMsg[MSG_BUFFER_SIZE];

    time_t time_ptr;
    time(&time_ptr);
    char* logTime = asctime(localtime(&time_ptr));
    
    // Create log message
    snprintf(logMsg, MSG_BUFFER_SIZE, "[%s] : ERROR - %s ", logTime, eventMsg);

    // Write to file
    FILE* fp;
    fp = fopen(LOG_PATH_ERROR, "a");
    if(fp == NULL)
    {
        printf("error.log could not be opened");
    }
    fprintf(fp, "%s", logMsg);

    fclose(fp);
}

/*
* FUNCTION      : logDC()
* DESCRIPTION   : Creates a DC log
* PARAMETERS    : msg msgSent | Message info
* RETURNS       : NA
*/
static void logDC(msg msgSent)
{
    const char* discription[] = {
        "Everything is OKAY", "Hydraulic Pressure Failure", "Safety Button Failure", 
        "No Raw Material in the Process", "Operating Temperature Out of Range", "Operator Error", 
        "Machine is Off-line"
    };

    char logMsg[MSG_BUFFER_SIZE];

    time_t time_ptr;
    time(&time_ptr);

    char* logTime = asctime(localtime(&time_ptr));
    
    snprintf(logMsg, MSG_BUFFER_SIZE, "[%s] : DC [%d] - MSG SENT - Status %d (%s)", logTime, msgSent.pid, msgSent.status, discription[msgSent.status]);

    // Write to file
    FILE* fp;
    fp = fopen(LOG_PATH_DC, "a");
    if(fp == NULL)
    {
        printf("error.log could not be opened");
    }
    fprintf(fp, "%s", logMsg);

    fclose(fp);
}

/*
* FUNCTION      : logDR()
* DESCRIPTION   : Creates a DR log
* PARAMETERS    : msg msgSent | Message info
*               : char* eventMsg | Event message string
* RETURNS       : NA
*/
static void logDR(msg msgSent, const char* eventMsg, const char* eventType)
{
    const char* discription[] = {
        "Everything is OKAY", "Hydraulic Pressure Failure", "Safety Button Failure", 
        "No Raw Material in the Process", "Operating Temperature Out of Range", "Operator Error", 
        "Machine is Off-line"
    };

    char logMsg[MSG_BUFFER_SIZE];

    time_t time_ptr;
    time(&time_ptr);

    char* logTime = asctime(localtime(&time_ptr));
    
    snprintf(logMsg, MSG_BUFFER_SIZE, "[%s] : DC-[%2d] [%d] %s - %s - Status %d (%s)", logTime, msgSent.status, msgSent.pid, eventMsg, eventType, msgSent.status, discription[msgSent.status]);
    
    // Write to file
    FILE* fp;
    fp = fopen(LOG_PATH_DM, "a");
    if(fp == NULL)
    {
        printf("error.log could not be opened");
    }
    fprintf(fp, "%s", logMsg);

    fclose(fp);
}

/*
* FUNCTION      : logDRTerminate()
* DESCRIPTION   : Creates a DR termination log
* PARAMETERS    : NA
* RETURNS       : NA
*/
static void logDRTerminate()
{
    char logMsg[MSG_BUFFER_SIZE];

    time_t time_ptr;
    time(&time_ptr);

    char* logTime = asctime(localtime(&time_ptr));
    
    snprintf(logMsg, MSG_BUFFER_SIZE, "[%s] : All DCs have gone offline or terminated - DR TERMINATING", logTime);
    
    // Write to file
    FILE* fp;
    fp = fopen(LOG_PATH_DM, "a");
    if(fp == NULL)
    {
        printf("error.log could not be opened");
    }
    fprintf(fp, "%s", logMsg);

    fclose(fp);
}