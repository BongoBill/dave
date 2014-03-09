CC = /usr/bin/cc
CFLAGS = -g -I.
all :  daveTest.exe billTest.exe
billTest.exe : billTest.c SDO.h  SDOqueue.h
	${CC} -o $@ -g testSDOqueue.c
daveTest.exe : daveTest.c SDO.h  SDOqueue.h
	${CC} -o $@ -g daveTest.c
clean : rm daveTest.exe billTest.exe
