#
# this makefile will compile and and all source
# found in the "dx" directory.  This represents a sample
# development directory structure and project
# 


# FINAL BINARY Target
./bin/dx : ./obj/dx.o ./obj/dxshm.o
	cc ./obj/dx.o ./obj/dxshm.o -o ./bin/dx
#
# =======================================================
#                     Dependencies
# =======================================================                     
./obj/dx.o : ./src/dx.c ./inc/dxshm.h
	cc -c ./src/dx.c -o ./obj/dx.o

./obj/dxshm.o : ./src/dxshm.c ./inc/dxshm.h
	cc -c ./src/dxshm.c -o ./obj/dxshm.o

#
# =======================================================
# Other targets
# =======================================================                     
all : ./bin/dx

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	


