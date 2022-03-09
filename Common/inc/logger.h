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
#define LOG_PATH_DC "../tmp/dataCreator.log"
#define LOG_PATH_DM "../tmp/dataMonitor.log"
#define LOG_PATH_DX "../tmp/dataCorruptor.log"
#define BUFFER_SIZE 128

/*
* FUNCTION      : logDC()
* DESCRIPTION   : Creates a DC log
* PARAMETERS    : int | pId | The PID of the DC
*               : int | status | The status of the DC
* RETURNS       : NA
*/
void logDC(msg msgSent)
{
    char logMsg[BUFFER_SIZE];

    time_t time_ptr;
    time(&time_ptr);

    char* logTime = asctime(localtime(&time_ptr));
    
    snprintf(logMsg, BUFFER_SIZE, "[%s] : DC [%d] - %s - %s", );
}
