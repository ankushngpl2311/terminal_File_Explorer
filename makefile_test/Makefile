# -*- MakeFile -*-

#target: dependencies
#	action

drive: drive.o sum.o
	gcc drive.o sum.o -o drive

drive.o: drive.c sum.h
	gcc -c drive.c

sum.o: sum.c
	gcc -c sum.c 

clear:
	rm *.o drive
