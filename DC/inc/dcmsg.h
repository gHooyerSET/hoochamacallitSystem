/*
 * FILE: 	dcmsg.c
 * PROJECT: 	Hoochamacallit System - A3
 * PROGRAMMER: 	Gerritt Hooyer
 * FIRST VER.: 	2022-03-07
 * DESCRIPTION:	Heaer file for MsgQ related functions for the DC.
 */
int getMsgQueue();
void sendOKMsg(int msgQueueID);
void sendRandMsgStart(int msgQueueID);
int getMsgSize();