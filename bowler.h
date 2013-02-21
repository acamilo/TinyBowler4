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
#endif
