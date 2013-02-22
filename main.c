#include <stdio.h>
#include "packet_header.h"
#include "packet_payload.h"
#include "bowler.h"
#include "fifo.h"



void main()
{
	int i=0;
	char mymac[6]={0x74,0xf7,0x26,0x00,0x00,0x01};

	V4MicroParser_state parser;
	parser.state=align;
	fifoInit(&parser.fifo);
	fifoPrint(&parser.fifo);

	for (i=0; i<37; i++){
 		fifoPush(&parser.fifo,(unsigned char)i);
		runParserSM(&parser);
		/*fifoPrint(&parser.fifo);*/
		

	}
		/* fifoPull(&fifo,15); */
		/* fifoPrint(&fifo); */
}


