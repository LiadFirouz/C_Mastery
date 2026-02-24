#include <stdio.h>

#define TOTAL_BITS 32
#define MASK (1L << 16)

long turn_on (long num);
void printByte(long num);

int main(void){

    long num = 0, new_num = 0;

    printf("Enter a number:");
    scanf("%ld", &num);

    printf("The original number: Base 2: ");
    printByte(num);
    printf("Base 10: %ld\n", num);

    new_num = turn_on(num);

    if (num == new_num) {
        printf("No change occurred\n");
    } else {
        printf("A change occurred\n");
        printf("The number after change: Base 2: ");
        printByte(new_num);
        printf("Base 10: %ld\n", new_num);
    }
    
    return 0;
}

long turn_on(long num){
    num |= MASK;
    return num;
}

void printByte(long num){
    int i = TOTAL_BITS - 1;
    int currentBit = 0; 

    for(i; i >= 0; i--){
        currentBit = (num >> i) & 1;
        printf("%d", currentBit);
    }
    printf("\n");
}