CC=gcc
CFLAGS=-Wall -Wextra -Werror -lm -pedantic


# %: ./src/%.c
# 	$(CC) -o ./bin/$@ $^ $(CFLAGS)

guiao04: main.o inc.o
    gcc -o ./bin/guiao04 guiao04.o functions.o $(CFLAGS)

guiao04.o: guiao04.c functions.h
    gcc -c main.c $(CFLAGS)

functions.o: functions.c functions.h 
    gcc -c inc.c $(CFLAGS)