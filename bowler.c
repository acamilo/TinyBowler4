#include "bowler.h"
#include "packet_header.h"
#include "packet_payload.h"


char runParserSM(V4MicroParser_state *s){

	switch(s->state){
		case align: 
			HOOK_SM_ALIGN(s);
			/* Do we have a packet header's worth of bytes */
			if (s->fifo.inPointer>=sizeof(bowler4_header_fields)){
				bowler4_header *h = fifoPeek_array(&s->fifo,sizeof(bowler4_header),0);
				HOOK_SM_ALIGN_ENOUGHBYTES(s);
				/* Is the packet valid? Does it start with 0x04 and have a valid checksum? */
				if (h->fields.version==0x04 & verify_checksum(h)){
					HOOK_SM_ALIGN_XSUMMATCH(s);
					/* valid packet. go to next state */
					s->state=pailoadWait;
				} else {
					
					/* Try to re-align by looking for 0x04. */
					unsigned char i=0;
					for (i=1; i<(s->fifo.inPointer); i++) if (fifoPeek(&s->fifo,i)==0x04) break;
					HOOK_SM_ALIGN_COURRUPTDATA(s,i);
					/* Pull off junk bytes before the newly found 4 (or pull em all off cause 4 was not found) */							
					fifoPull(&s->fifo,i);
					
				}

			}	
			break;
		case pailoadWait:  printf("PailoadWait..\n"); s->state=align; break;
		case RPC:  printf("RPC..\n"); s->state=align;   break;
	
	}
}


void printParserState(V4MicroParser_state *s){

}
