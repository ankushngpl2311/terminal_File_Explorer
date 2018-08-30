# -*- MakeFile -*-

#target: dependencies
#	action

CC=g++
#all:  homepage ver_overflow


#ver_overflow:ver_overflow.o cursor_move.o list.o
#$(CC) ver_overflow.o cursor_move.o list.o -o ver_overflow

homepage: homepage.o termios1.o list.o
	$(CC) homepage.o termios1.o list.o -o homepage




homepage.o: homepage.cpp functions.h
	$(CC) -c homepage.cpp

termios1.o: termios1.cpp
	$(CC) -c termios1.cpp

list.o: list.cpp
	$(CC) -c list.cpp

#cursor_move.o: cursor_move.cpp
#$(CC) -c cursor_move.cpp

#ver_overflow.o: ver_overflow.cpp functions.h
#$(CC) -c ver_overflow.cpp 


clear:
	rm *.o homepage