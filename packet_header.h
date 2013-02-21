#ifndef packet_HEADER_H
#define packet_HEADER_H


typedef struct {
	unsigned char version;
	unsigned char mac[6];
	unsigned char affect;
	unsigned char RESERVED;
	unsigned char payloadType;
	unsigned char payloadLength;
	unsigned char headerChecksum;	
} bowler4_header_fields;


typedef union{
	bowler4_header_fields fields;
	unsigned char bytes[12];
} bowler4_header;

void printHeader(bowler4_header h);
void set_mac_address(char address[],bowler4_header *h);
void calculate_checksum(bowler4_header *h);

char verify_checksum(bowler4_header *h);

#endif
