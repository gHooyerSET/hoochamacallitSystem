#
# this makefile will compile and and all source
# found in the "dr" directory.  This represents a sample
# development directory structure and project
# 


# FINAL BINARY Target
./bin/dr : ./obj/dr.o ./obj/drshm.o
	cc ./obj/dr.o ./obj/drshm.o -o ./bin/dr
#
# =======================================================
#                     Dependencies
# =======================================================                     
./obj/dr.o : ./src/dr.c ./inc/drshm.h
	cc -c ./src/dr.c -o ./obj/dr.o

./obj/drshm.o : ./src/drshm.c ./inc/drshm.h
	cc -c ./src/drshm.c -o ./obj/drshm.o

#
# =======================================================
# Other targets
# =======================================================                     
all : ./bin/dr

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	


