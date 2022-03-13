# FILE : makefile
# PROJECT : 
# PROGRAMMER : Nathan Domingo & Gerritt Hooyer
# FIRST VER: 2022-03-07
# DESCRIPTION : The makefile for the DC.

#
# this makefile will compile and and all source
# found in the "dc" directory.  This represents a sample
# development directory structure and project
# 

# FINAL BINARY Target
./bin/dc : ./obj/dc.o ./obj/dcmsg.o
	cc ./obj/dc.o ./obj/dcmsg.o -o ./bin/dc
#
# =======================================================
#                     Dependencies
# =======================================================                     
./obj/dc.o : ./src/dc.c ./inc/dcmsg.h
	cc -c ./src/dc.c -o ./obj/dc.o

./obj/dcmsg.o : ./src/dcmsg.c ./inc/dcmsg.h
	cc -c ./src/dcmsg.c -o ./obj/dcmsg.o

#
# =======================================================
# Other targets
# =======================================================                     
all : ./bin/dc

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	


