# Compiler settings
CC = gcc
CFLAGS = -Wall -ansi -pedantic

# The final executable
seek: seek.o 
	$(CC) $(CFLAGS) seek.o -o seek 

# Rule for compiling the main file
seek.o: seek.c
	$(CC) $(CFLAGS) -c seek.c


# Cleanup rule
clean:
	rm -f *.o seek