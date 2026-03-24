/*Exercise 2-8. Write a function rightrot(x,n) that 
returns the value of the integer x rotated
to the right by n positions. */

#include <stdio.h>

unsigned int rightrot(unsigned int x, int n);

int main(void){
    unsigned int x = 0;
    int n = 0;

    printf("Enter a number: x=");
    scanf("%u", &x);

    printf("n=");
    scanf("%d", &n);

    printf("The rotate num is: %u", rightrot(x, n));
}

unsigned int rightrot(unsigned int x, int n){
    int totalBits = sizeof(x) * 8;
    unsigned int droppedBits = x & ~(~0 << n);
    unsigned int rotateLeft = droppedBits << (totalBits - n);
    unsigned int rotateRight = x >> n;

    return rotateLeft | rotateRight;
}
