#ifndef fifo_H
#define fifo_H

#define FIFOSIZE 32

typedef struct{
	unsigned char buffer[FIFOSIZE];
	unsigned char inPointer;
} NR_fifo;

unsigned char fifoPeek(NR_fifo *f, unsigned char position);
unsigned char *fifoPeek_array(NR_fifo *f, unsigned char count, unsigned char position);

unsigned char fifoPush(NR_fifo *f,  unsigned char value);
unsigned char fifoPull(NR_fifo *f,unsigned char bytes);


void fifoPrint(NR_fifo *f);
#endif
