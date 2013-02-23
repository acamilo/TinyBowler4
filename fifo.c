#include "fifo.h"

/*
In this FIFO, i opted to use a different approach then the buf[], int in, int out, approach.
This FIFO is optimized for packets.

The functions you can use are push,peek,pull

element 0 in the buffer is always the first element in this fifo.
 push adds an nth element into the buffer, when the buffer is full this element is discarded.

 peek allows you to peek into the buffer but does not remove the bytes.

 pull removes and discards bytes from the FIFO and shifts the rest fo the bytes 
	forward n number of bytes such that the n+1th byte is now the 0th byte.

If you pull a section of information equivelent to the contents of the buffer no copying
is done and the pointer just moves to the beginning of the buffer.

When a packet comes in it's bytes are placed onto the buffer. The packet state machine then
waits for the buffer to fill to the size of a header or greater and then PEEKS a headers worth of data.
A pointer to the data is returned to the SM and parsed as a packet. when the SM is done it PULLS 
a header's worth of bytes. So if everything is aligned, the buffer is not really there...

IF there is a packet problem, the SM can PEEK into the buffer looking for the next 0x04,
discard the "junk bytes" by doing a PULL and then starting over.

everything stays in that buffer. there is no copying or shuffling of data from one buffer to
another and the memory footprint of the parser is that buffer and the parser state.

The size of the buffer can be tuned based on the size of the packets expected. If a typical packet is 20
bytes then the buffer can be pretty small.

TX of packets can be done using "templates" in flash. no need to use up precious precious ram.

*/

unsigned char fifoPeek(NR_fifo *f, unsigned char position){
if (position<sizeof(f->buffer)) return f->buffer[position];
return 0;
}

unsigned char *fifoPeek_array(NR_fifo *f, unsigned char count, unsigned char position){
if ((position+count) <= f->inPointer) return &f->buffer[position];
return 0;
}



unsigned char fifoPush(NR_fifo *f, unsigned char value){
	if (f->inPointer<sizeof(f->buffer)){
		f->buffer[f->inPointer++]=value;
		return 1;
	}
return 0;
}

unsigned char fifoPull(NR_fifo *f,unsigned char bytes){
	int i=0,j=0;
	if (bytes!=0 && (f->inPointer)>=bytes){
		for (i=bytes; i<(f->inPointer); i++) f->buffer[j++]=f->buffer[i];
		f->inPointer -= bytes;
	}
		
return 0;
}

void fifoInit(NR_fifo *f){
	int i=0;	
	for (i=0; i<sizeof(f->buffer); i++) f->buffer[i]=0x00;
	f->inPointer=0;
}

void fifoPrint(NR_fifo *f){
	int i=0;	
	printf("\n\033[32;1mFIFO State of\033[0m [%x]\n",(unsigned int)f);
	printf("\tPointer:\t%i\n",f->inPointer);
	printf("\tBuffer:\t[ ");
	printf("\033[32m");
	for (i=0; i<sizeof(f->buffer); i++){
		if (i>f->inPointer) printf("\033[31m");
		if (i==f->inPointer) printf("\033[34m");
		printf("%02X",f->buffer[i]);
		if (i==f->inPointer) printf("\033[0m");
		if (i==(sizeof(f->buffer)-1)) printf("\033[0m ]\n\n");
		else  printf(",");
	}
 	printf("\033[0m");

}
