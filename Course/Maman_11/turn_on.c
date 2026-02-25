/*
 * Name: Liad Firouz
 * ID: 209187699
 * File: turn_on.c
 * Description: A program that takes a 32-bit integer and turns on its 17th bit
 * (index 16) without altering any other bits.
 */

#include <stdio.h>

#define TOTAL_BITS 32
#define MASK (1L << 16)

long turn_on(long num);
void printByte(long num);

int main(void)
{
    long num = 0, new_num = 0;

    printf("Enter a number: ");
    scanf("%ld", &num);

    printf("\nThe original number:\nBase 2: ");
    printByte(num);
    printf("Base 10: %ld\n", num);

    new_num = turn_on(num);

    if (num == new_num)
    {
        printf("\nNo change occurred\n");
    }
    else
    {
        printf("\nA change occurred\n");
        printf("The number after change:\nBase 2: ");
        printByte(new_num);
        printf("Base 10: %ld\n", new_num);
    }

    return 0;
}

/*
 * Function: turn_on
 * -----------------
 * Turns on the 17th bit (index 16) of a given long integer.
 * If the bit is already turned on, the number remains unchanged.
 * * num: The original number inputted by the user.
 * * returns: The modified number with the 17th bit turned on.
 */

long turn_on(long num)
{
    num |= MASK;
    return num;
}

/*
 * Function: printByte
 * -------------------
 * Prints the binary representation of a 32-bit number.
 * Traverses from the most significant bit (index 31) to the
 * least significant bit (index 0).
 * * num: The number to be printed in binary format.
 */
void printByte(long num)
{
    int i = 0;
    int currentBit = 0;

    for (i = TOTAL_BITS - 1; i >= 0; i--)
    {
        currentBit = (num >> i) & 1;
        printf("%d", currentBit);
    }

    printf("\n");
}