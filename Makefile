# -*- MakeFile -*-

#target: dependencies
#	action

CC=g++
homepage: homepage.o termios1.o list.o
	$(CC) homepage.o termios1.o list.o -o homepage

homepage.o: homepage.cpp functions.h
	$(CC) -c homepage.cpp

termios1.o: termios1.cpp
	$(CC) -c termios1.cpp

list.o: list.cpp
	$(CC) -c list.cpp

clear:
	rm *.o homepage