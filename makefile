CFLAGS=-pedantic -ansi -O2 -Wall -g
OBJS=$(patsubst %.c,%.o,$(wildcard *.c))
LIBS=

prot: $(OBJS)
	$(CC) $(CFLAGS) -o prot $(OBJS) $(LIBS) 

do: prot
	./prot

clean: 
	rm prot *.o 

