#ifndef bowler_H
#define bowler_H
#include "fifo.h"


typedef enum {
	align,
	pailoadWait,
	RPC
} SM_State;

#define BUFFERLEN 32
typedef struct {
	NR_fifo fifo;
	SM_State state;
} V4MicroParser_state;

void printParserState(V4MicroParser_state *s);
char runParserSM(V4MicroParser_state *s);

#define DEBUG
/* SM Hooks */
#ifdef DEBUG

	#define HOOK_SM_ALIGN(s)			printf("V4MicroParser[%X]: State: ALIGN \n",s);
	#define HOOK_SM_ALIGN_ENOUGHBYTES(s)		printf("V4MicroParser[%X]:\tHave %d bytes Attempting to parse\n",s,sizeof(bowler4_header_fields));
	#define HOOK_SM_ALIGN_XSUMMATCH(s)		printf("V4MicroParser[%X]:\tValid Packet!\n",s);
	#define HOOK_SM_ALIGN_COURRUPTDATA(s,b)		printf("V4MicroParser[%X]:\tPacket is not valid. Discarded %d bytes\n",s,b);

	#define HOOK_SM_PAYLOADWAIT(s)

	#define HOOK_SM_PAYLOADWAIT(s)


#else

	#define HOOK_SM_ALIGN(s)
	#define HOOK_SM_ALIGN_ENOUGHBYTES(s)
	#define HOOK_SM_ALIGN_XSUMMATCH(s)
	#define HOOK_SM_ALIGN_COURRUPTDATA(s,b)

	#define HOOK_SM_PAYLOADWAIT(s)

	#define HOOK_SM_PAYLOADWAIT(s)
#endif

#endif
