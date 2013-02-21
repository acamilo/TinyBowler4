#include "packet_header.h"

void set_mac_address(char address[],bowler4_header *h){
	int i; for (i=0; i<6; i++) h->fields.mac[i]=address[i];
}

void calculate_checksum(bowler4_header *h){
	int i; for (i=0; i<(sizeof(h->bytes)-1); i++) h->fields.headerChecksum+=h->bytes[i];
}

char verify_checksum(bowler4_header *h){
	unsigned char checksum;
	int i; for (i=0; i<(sizeof(h->bytes)-1); i++) checksum+=h->bytes[i];
	if (h->fields.headerChecksum==checksum) return 1;
	else return 0;
}

void printHeader(bowler4_header h){
	int i;
		printf("\n\n[");
	for(i=0; i<sizeof(h.bytes); i++){
		if (i==(sizeof(h.bytes)-1)) printf("%02x",h.bytes[i]);
		else printf("%02x,",h.bytes[i]);
	}
	printf("]\n\n");
}


