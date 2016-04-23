CFLAGS=-pedantic -ansi -O2 -Wall -g
OBJS=$(patsubst %.c,%.o,$(wildcard *.c))
LIBS=

gerevendas: $(OBJS)
	$(CC) $(CFLAGS) -o gerevendas $(OBJS) $(LIBS) 

do: gerevendas
	./gerevendas

clean: 
	rm gerevendas *.o 

