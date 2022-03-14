#ifndef LOGGER_H_
#define LOGGER_H_
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
#include "./mlstruct.h"

/* CONSTANTS */
#define LOG_PATH_DC "../../tmp/dataCreator.log"
#define LOG_PATH_DM "../../tmp/dataMonitor.log"
#define LOG_PATH_DX "../../tmp/dataCorruptor.log"
#define LOG_PATH_ERROR "../../tmp/error.log"
#define MSG_BUFFER_SIZE 256
#define MSG_STATUS_BUFFER_SIZE 64
#define TIME_BUFFER_SIZE 24
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

    char logTime[TIME_BUFFER_SIZE];
    strftime(logTime, TIME_BUFFER_SIZE, "%x %X", localtime(&(time_t){time(NULL)}));
    
    // Create log message
    snprintf(logMsg, MSG_BUFFER_SIZE, "\n[%s] : ERROR - %s \n", logTime, eventMsg);

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

    char logTime[TIME_BUFFER_SIZE];
    strftime(logTime, TIME_BUFFER_SIZE, "%x %X", localtime(&(time_t){time(NULL)}));

    snprintf(logMsg, MSG_BUFFER_SIZE, "[%s] : DC [%2d] - MSG SENT - Status %d (%s)\n", logTime, msgSent.pid, msgSent.status, discription[msgSent.status]);

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
static void logDR(msg msgSent, const char* eventMsg, const char* eventType, int dcNum)
{
    const char* discription[] = {
        "Everything is OKAY", "Hydraulic Pressure Failure", "Safety Button Failure", 
        "No Raw Material in the Process", "Operating Temperature Out of Range", "Operator Error", 
        "Machine is Off-line"
    };

    char logMsg[MSG_BUFFER_SIZE];

    char logTime[TIME_BUFFER_SIZE];
    strftime(logTime, TIME_BUFFER_SIZE, "%x %X", localtime(&(time_t){time(NULL)}));
    
    snprintf(logMsg, MSG_BUFFER_SIZE, "[%s] : DC-[%2d] [%d] %s - %s - Status %d (%s)\n", logTime, dcNum, msgSent.pid, eventMsg, eventType, msgSent.status, discription[msgSent.status]);
    
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

    char logTime[TIME_BUFFER_SIZE];
    strftime(logTime, TIME_BUFFER_SIZE, "%x %X", localtime(&(time_t){time(NULL)}));
    
    snprintf(logMsg, MSG_BUFFER_SIZE, "[%s] : All DCs have gone offline or terminated - DR TERMINATING\n", logTime);
    
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
* FUNCTION      : logDX()
* DESCRIPTION   : Creates a DX log
* PARAMETERS    : DCInfo dc | The data creator being terminated
*               : int actionID | The action ID
*               : int dcID | The ID of the data creator
* RETURNS       : NA
*/
static void logDX(DCInfo* dc, int actionID, int dcID)
{
    char logMsg[MSG_BUFFER_SIZE];

    char logTime[TIME_BUFFER_SIZE];
    strftime(logTime, TIME_BUFFER_SIZE, "%x %X", localtime(&(time_t){time(NULL)}));

    // Create the log message
    sprintf(logMsg,"[%s] : WOD Action %2d - DC-%2d [%d] TERMINATED\n",logTime,actionID,dcID,dc->dcProcessID);

#if defined DEBUG
printf("WoD action: %s\n", logMsg);
#endif
    
    // Write to file
    FILE* fp;
    fp = fopen(LOG_PATH_DX, "a");
    if(fp == NULL)
    {
        printf("dataCorruptor.log could not be opened");
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
static void logDXMsg(const char* msgText)
{
    char logMsg[MSG_BUFFER_SIZE];

    char logTime[TIME_BUFFER_SIZE];
    strftime(logTime, TIME_BUFFER_SIZE, "%x %X", localtime(&(time_t){time(NULL)}));

    // Create the log message
    sprintf(logMsg,"[%s] : %s\n",logTime,msgText);
    
    // Write to file
    FILE* fp;
    fp = fopen(LOG_PATH_DX, "a");
    if(fp == NULL)
    {
        printf("dataCorruptor.log could not be opened");
    }
    fprintf(fp, "%s", logMsg);

    fclose(fp);
}
#endif