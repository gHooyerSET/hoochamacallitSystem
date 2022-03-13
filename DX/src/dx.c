/*
 * FILE: 	dx.c
 * PROJECT: 	Hoochamacallit System - A3
 * PROGRAMMER: 	Gerritt Hooyer
 * FIRST VER.: 	2022-03-07
 * DESCRIPTION:	The body of main() in the dx portion
 *		of the hoochamacallit system.
 */

#include "../inc/dxshm.h"
#include "../../Common/inc/common.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


void randSleep();

int main()
{
	// First, we can try to get the master list shared memory pointer
	MasterList *mlptr = getML();
	// Now we need to check that we actually got the ptr
	if (mlptr != NULL)
	{
		// First, let's sleep for a random length of time
		randSleep();
		// Then we can start the wheel of destruction
		wheelOfDestruction(mlptr);
	}
	
	// Detach from the shared memory before exiting
	shmdt(mlptr);

#if defined DEBUG
		printf("Exiting...\n");
#endif
	return 0;
}

/*
* FUNCTION      : randSleep()
* DESCRIPTION   : Sleeps the system for a random amount of time
*				  between SLEEP_MIN and SLEEP_MAX in seconds.  
* PARAMETERS    : N/A
* RETURNS       : N/A
*/
void randSleep()
{
	// Step 1: Seed the RNG
	srand(time(NULL));
	// Then generate our random number within the range
	int sleepTime = (rand() % (SLEEP_MAX - SLEEP_MIN) + SLEEP_MIN);
	// Debug message, turn off via common.h
#if defined DEBUG
		printf("Sleeping for %d(s)\n", sleepTime);
#endif
	// Then sleep for that amount of time
	sleep(sleepTime);
}
