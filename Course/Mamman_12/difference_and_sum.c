/*
 * Name: Liad Firouz
 * ID: 209187699
 * File: difference_and_sum.c
 * Description: A program that calculate two numbers and update the value
 */

#include <stdio.h>

#define SUM(a, b) (((a) + (b)))
#define DIFF(a,b)  (((a)>(b))?((a)-(b)) : ((b)-(a)))

void findDifferenceAndSum (int *result1, int *result2, int num1, int num2);


int main(){
    int num1 = 0, num2 = 0, diff = 0, sum = 0;


    printf("Please enter 2 number for diffrence and sum:");

    while(scanf("%d %d", &num1, &num2) != EOF){
        printf("For %d, %d", num1, num2);
        findDifferenceAndSum(&diff, &sum, num1, num2);
    }


    return 0;
}

void findDifferenceAndSum (int *diff, int *sum, int num1, int num2){
    *sum = num1 + num2;
    *diff = (num1 > num2)? (num1 - num2): (num2- num1);
}