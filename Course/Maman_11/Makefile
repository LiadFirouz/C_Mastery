# Variables 
CC = gcc
CFLAGS = -Wall -ansi -pedantic

# The default target that builds everything
all: remove_blanks turn_on

# Target for Question 1
remove_blanks: remove_blanks.c
	$(CC) $(CFLAGS) remove_blanks.c -o remove_blanks

# Target for Question 2
turn_on: turn_on.c
	$(CC) $(CFLAGS) turn_on.c -o turn_on

# Clean up both executables
clean:
	rm -f remove_blanks turn_on