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
void set_mac_address(unsigned char address[],bowler4_header *h);
void calculate_checksum(bowler4_header *h);
unsigned char check_mac_address(unsigned char address[],bowler4_header *h);

char verify_checksum(bowler4_header *h);

#define setDirection(a)		(a | 0x80)	
#define setAsync(a)			(a | 0x40)
#define setState(a)			(a | 0x20)

#define clearDirection(a)		(a & 0x7f)	
#define clearAsync(a)			(a & 0xbf)
#define clearState(a)			(a & 0xdf)

#define setPriority(p,a)		((p & 0x1f)+a)

#define testDirection(a)	(a & 0x80)	
#define testAsync(a)		(a & 0x40)	
#define testState(a)		(a & 0x20)

#define getPriority(a)		(a & 0x1f)	

#endif
