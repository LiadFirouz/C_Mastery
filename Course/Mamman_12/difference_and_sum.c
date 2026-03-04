/*
 * Name: Liad Firouz
 * ID: 209187699
 * File: difference_and_sum.c
 * Description: A program that calculate two numbers and update the value
 */

#include <stdio.h>
#include <stdlib.h>

#define SUM(a, b) (((a) + (b)))
#define DIFF(a, b) (((a) > (b)) ? ((a) - (b)) : ((b) - (a)))

void findDifferenceAndSum(int *diff, int *sum, int num1, int num2);
void saveArray(int num1, int num2, int **arr, int *count);

int main(void)
{
    int i = 0, num1 = 0, num2 = 0, diff = 0, sum = 0, count = 0;
    int *arr = NULL;

    printf("Please enter 2 number for diffrence and sum:\n");

    while (scanf("%d %d", &num1, &num2) != EOF)
    {
        printf("For %d, %d:\n", num1, num2);
        saveArray(num1, num2, &arr, &count);
        findDifferenceAndSum(&diff, &sum, num1, num2);
        printf("using function diff: %d, sum: %d\n", diff, sum);
        printf("using macros diff: %d, sum: %d\n\n", DIFF(num1, num2), SUM(num1, num2));
    }

    printf("The list:\n");

    for (i = 0; i < count; i += 2)
    {
        printf("%d, %d\n", arr[i], arr[i + 1]);
    }
    free(arr);
    return 0;
}

void findDifferenceAndSum(int *diff, int *sum, int num1, int num2)
{
    *sum = num1 + num2;
    *diff = (num1 > num2) ? (num1 - num2) : (num2 - num1);
}

void saveArray(int num1, int num2, int **arr, int *count)
{
    int *temp = (int *)realloc(*arr, (*count + 2) * sizeof(int));

    if (temp != NULL)
    {
        *arr = temp;
        (*arr)[*count] = num1;
        (*arr)[*count + 1] = num2;
        (*count) += 2;
    }

    else
        printf("Error: Memory allocation failed!\n");
}
