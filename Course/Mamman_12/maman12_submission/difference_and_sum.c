/*
 * Name: Liad Firouz
 * ID: 209187699
 * File: difference_and_sum.c
 * Description: A program that calculate two numbers and update the value
 */

#include <stdio.h>
#include <stdlib.h>

/* Macro definitions for sum and absolute difference, fully parenthesized for safety */
#define SUM(a, b) (((a) + (b)))
#define DIFF(a, b) (((a) > (b)) ? ((a) - (b)) : ((b) - (a)))

/* Function prototypes */
void findDifferenceAndSum(int *diff, int *sum, int num1, int num2);
int saveArray(int num1, int num2, int **arr, int *count);

int main(void)
{
    /* Variable declarations complying with ANSI C standard (top of block) */
    int i = 0, num1 = 0, num2 = 0, diff = 0, sum = 0, count = 0;
    int *arr = NULL;

    printf("Please enter 2 number for diffrence and sum:\n");

    /* Read pairs of integers until End Of File (EOF) is reached */
    while (scanf("%d %d", &num1, &num2) != EOF)
    {
        printf("For %d, %d:\n", num1, num2);

        /* Attempt to save the array dynamically. If allocation fails (returns 1), handle error */
        if (saveArray(num1, num2, &arr, &count) == 1)
        {
            /* Free previously allocated memory to prevent memory leaks before exiting */
            free(arr);
            return 1;
        }

        /* Calculate values using the function (passing by reference) */
        findDifferenceAndSum(&diff, &sum, num1, num2);
        printf("using function diff: %d, sum: %d\n", diff, sum);

        /* Calculate values using the preprocessor macros */
        printf("using macros diff: %d, sum: %d\n\n", DIFF(num1, num2), SUM(num1, num2));
    }

    printf("The list:\n");

    /* Iterate through the dynamically allocated array and print the saved pairs */
    for (i = 0; i < count; i += 2)
    {
        printf("%d, %d\n", arr[i], arr[i + 1]);
    }

    /* Free the dynamically allocated array before successful program termination */
    free(arr);
    return 0;
}

/* Calculates the sum and absolute difference, storing results in the provided pointers */
void findDifferenceAndSum(int *diff, int *sum, int num1, int num2)
{
    *sum = num1 + num2;
    *diff = (num1 > num2) ? (num1 - num2) : (num2 - num1);
}

/* * Dynamically expands the array to store the new pair of numbers.
 * Returns 0 on success, 1 on memory allocation failure.
 */
int saveArray(int num1, int num2, int **arr, int *count)
{
    /* Reallocate memory using a temporary pointer to protect existing data on failure */
    int *temp = realloc(*arr, (*count + 2) * sizeof(int));

    if (temp != NULL)
    {
        /* Allocation successful: update pointer, store values, and increment count */
        *arr = temp;
        (*arr)[*count] = num1;
        (*arr)[*count + 1] = num2;
        (*count) += 2;
    }
    else
    {
        /* Allocation failed: report error (original array is preserved) */
        printf("Error: Memory allocation failed!\n");
        return 1;
    }
    return 0;
}