# Compiler settings
CC = gcc
CFLAGS = -Wall -ansi -pedantic
LDFLAGS = -lm

# The final executable
mycomp: mycomp.o complex.o
	$(CC) $(CFLAGS) mycomp.o complex.o -o mycomp $(LDFLAGS)

# Rule for compiling the main file
mycomp.o: mycomp.c complex.h
	$(CC) $(CFLAGS) -c mycomp.c

# Rule for compiling the math engine
complex.o: complex.c complex.h
	$(CC) $(CFLAGS) -c complex.c

# Cleanup rule
clean:
	rm -f *.o mycomp