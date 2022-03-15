CC=gcc
CFLAGS=-I

pnorm: pnorm.c
	$(CC) -o pnorm pnorm.c

clean:
	rm -rf pnorm *.o 
