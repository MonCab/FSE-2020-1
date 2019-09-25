LD = ld 
AS = as 
ASFLAGS_THUMB = -mthumb-interwork
LDFLAGS_THUMB = --thumb-entry=_start

CC = gcc
CFLAGS = -O2 -Wall
LFLAGS =


all:	uart


uart:	uart.o
	$(LD) $(LDFLAGS) -o uart uart.o

uart.o:	uart.s
	$(AS) $(ASFLAGS) -o uart.o uart.s


submit:	uart.s Makefile README
	tar -czvf P4_FSEsubmit.tar.gz uart.s Makefile README

clean:	
	rm -f *~ *.o uart