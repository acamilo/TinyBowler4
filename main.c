#include <stdio.h>
#include "packet_header.h"
#include "packet_payload.h"
#include "bowler.h"
#include "fifo.h"
#include "main.h"



void main()
{
	int i=0;
	char mymac[6]={0x74,0xf7,0x26,0x00,0x00,0x01};
	unsigned char data[]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x04,0x74,0xf7,0x26,0x00,0x00,0x01,0x65,0x00,0x00,0x0a,0x05,0x00,0x01,0x02,0x03,0x05,0x06,0x07,0x08,0x09};

	bowler4_header bh;
	for (i=0; i<sizeof(bowler4_header); i++) bh.bytes[i]=0;
	bh.fields.version=0x04;
	bh.fields.affect=setPriority(5,setState(setAsync(bh.fields.affect)));
	bh.fields.payloadLength=10;
	bh.fields.payloadType=0;


	set_mac_address(mymac,&bh);
	calculate_checksum(&bh);
	printf("Verify?\t%d\n",verify_checksum(&bh));
	printf("Verify?\t%d\n",verify_checksum(&bh));
printf("%X\n",check_mac_address(mymac,&bh) );
	printHeader(bh);


	V4MicroParser_state parser;
	parser.state=align;
	parser.macaddr=&mymac;
	fifoInit(&parser.fifo);
	fifoPrint(&parser.fifo);

	for (i=0; i<sizeof(data); i++){
 		fifoPush(&parser.fifo,data[i]);
		int delta=parser.fifo.inPointer;
		printf("Pushing:\t%i\n",i);
		/*fifoPrint(&parser.fifo);*/
		runParserSM(&parser);
		if (parser.fifo.inPointer!=delta) {printf("\nNew Contents of FIFO:");fifoPrint(&parser.fifo);}

		printf("===================\n");
		

	}
		/* fifoPull(&fifo,15); */
		/* fifoPrint(&fifo); */
}


