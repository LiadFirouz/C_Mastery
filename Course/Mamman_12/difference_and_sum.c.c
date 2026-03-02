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
    int num1 = 0, num2 = 0, result1 = 0, result2 = 0;
    while(scanf("%d %d", &num1, &num2) != EOF){
        printf("For %d, %d", num1, num2);
        findDifferenceAndSum(&result1, &result2, num1, num2);
    }


    return 0;
}

void findDifferenceAndSum (int *result1, int *result2, int num1, int num2){

}