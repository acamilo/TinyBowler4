#include <stdio.h>
#include "packet_header.h"
#include "packet_payload.h"
#include "bowler.h"
#include "fifo.h"



void main()
{
	int i=0;
	char mymac[6]={0x74,0xf7,0x26,0x00,0x00,0x01};

	NR_fifo fifo;
	fifoInit(&fifo);
	fifoPrint(&fifo);

	for (i=0; i<37; i++){
 		fifoPush(&fifo,(unsigned char)i);
		fifoPrint(&fifo);
		printf("Result of fifoPeek_array(&fifo,12,2):\t%X",fifoPeek_array(&fifo,12,2));

	}
		fifoPull(&fifo,15);
		fifoPrint(&fifo);
}


