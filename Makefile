all: main

main: main.o packet_header.o packet_payload.o bowler.o fifo.o
	colorgcc -ansi main.o packet_header.o packet_payload.o bowler.o fifo.o -o main

main.o:
	colorgcc -ansi -c main.c
fifo.o:
	colorgcc -ansi -c fifo.c

bowler.o:
	colorgcc -ansi -c bowler.c

packet_header.o:
	colorgcc -ansi -c packet_header.c

packet_payload.o:
	colorgcc -ansi -c packet_payload.c

clean:
	rm *.o
