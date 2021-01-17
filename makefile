CFLAGS= -Wall

all: frequency 

frequency:frequency.c
	gcc $(CFLAGS) frequency.c  -o frequency

.PHONY: clean all

clean:
	rm -f *.o frequency 