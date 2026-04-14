#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define MIN_ARGS 3

int isNumberOfArgsValid(int n);
int isNPositive(int n);

int main(int argsN, char *args[])
{
    int n = 0, i = 2;

    /* checkout the argsN > 2 */
    if (isNumberOfArgsValid(argsN) == FALSE)
        return 1;

    n = atoi(args[1]);
    if (isNPositive(n) == FALSE)
        return 1;

    for (i = 2; i < argsN; i++)
    {
    }
}

int isNumberOfArgsValid(int n)
{
    if (n < MIN_ARGS)
    {
        printf("Error: Not enough arguments.\n");
        return FALSE;
    }
    return TRUE;
}

int isNPositive(int n)
{
    if (n <= 0)
    {
        printf("Error: the number must be greater than zero.\n");
        return FALSE;
    }
    return TRUE;
}