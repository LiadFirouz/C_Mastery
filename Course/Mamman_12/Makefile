# Variables 
CC = gcc
CFLAGS = -Wall -ansi -pedantic

# The default target that builds everything
all: difference_and_sum

# Target for difference_and_sum
difference_and_sum: difference_and_sum.c
	$(CC) $(CFLAGS) difference_and_sum.c -o difference_and_sum

# Clean up the executable
clean:
	rm -f difference_and_sum