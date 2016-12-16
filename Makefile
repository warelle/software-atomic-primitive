CC    = gcc
CFLAGS=-Wall -Wextra -g -O3 -std=c11
OBJ   = dcas.o dcss.o

all: main.c $(OBJ)
	$(CC) $(CFLAGS) -o main $^

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.o
	rm main
