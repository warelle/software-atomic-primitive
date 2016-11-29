CC    = gcc
CFLAGS=-Wall -Wextra -O3 -std=c11
OBJ   = dcss.o

all: main.c $(OBJ)
	$(CC) $(CFLAGS) -o main $^

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.o
	rm main
