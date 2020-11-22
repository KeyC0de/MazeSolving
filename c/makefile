CC = gcc
CFLAGS = -std=c99 -Wall
OBJECTS = maze_ekpa.o queueLlistImpl.o fileWorking.o myMath.o

target : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o Erotima7_M1485

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean :
	rm -f Erotima7_M1485 Erotima7_M1485.exe $(OBJECTS)
