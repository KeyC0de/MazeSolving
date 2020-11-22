CC = gcc
CFLAGS = -std=c99 -Wall
OBJECTS = maze_ekpa.o queueLlistImpl.o fileWorking.o myMath.o

target : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o maze

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean :
	rm -f maze maze.exe $(OBJECTS)
	del maze maze.exe $(OBJECTS)