# FILE : makefile
# PROJECT : 
# PROGRAMMER : Nathan Domingo & Gerritt Hooyer
# FIRST VER: 2022-03-07
# DESCRIPTION : The makefile for the DR.

#
# this makefile will compile and and all source
# found in the "dr" directory.  This represents a sample
# development directory structure and project
# 


# FINAL BINARY Target
./bin/dr : ./obj/dr.o ./obj/drshm.o ./obj/drmsg.o
	cc ./obj/dr.o ./obj/drshm.o ./obj/drmsg.o -o ./bin/dr
#
# =======================================================
#                     Dependencies
# =======================================================                     
./obj/dr.o : ./src/dr.c ./inc/drshm.h ./inc/drmsg.h ../Common/inc/logger.h
	cc -c ./src/dr.c -o ./obj/dr.o

./obj/drshm.o : ./src/drshm.c ./inc/drshm.h ../Common/inc/logger.h ../Common/inc/mlstruct.h
	cc -c ./src/drshm.c -o ./obj/drshm.o
	
./obj/drmsg.o : ./src/drmsg.c ./inc/drmsg.h ../Common/inc/logger.h
	cc -c ./src/drmsg.c -o ./obj/drmsg.o

#
# =======================================================
# Other targets
# =======================================================                     
all : ./bin/dr

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	


