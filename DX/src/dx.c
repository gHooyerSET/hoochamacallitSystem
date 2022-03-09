/*
* FILE: 	dx.c
* PROJECT: 	Hoochamacallit System - A3
* PROGRAMMER: 	Gerritt Hooyer
* FIRST VER.: 	2022-03-07
* DESCRIPTION:	The body of main() in the dx portion
*		of the hoochamacallit system.
*/

#include "../inc/dxshm.h"
#include <stdio.h>

int main()
{
	//First, we can try to get the master list shared memory pointer
	MasterList* mlptr = getML();
	// Now we need to check that we actually got the ptr
	if(mlptr != NULL)
	{
		
	}

	return 0;
}
