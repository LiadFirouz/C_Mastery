/* Write a program to print a histogram of the frequencies of different characters
in its input. */

#include <stdio.h>

#define LOWEST ' '
#define HIGHEST '~'

int main()
{
    int c, i, k, height = 0;
    int array[HIGHEST - LOWEST + 1] = {0};

    while ((c = getchar()) != EOF)
    {
        if (LOWEST <= c && c <= HIGHEST)
        {
            ++array[c - LOWEST];
            if (array[c - LOWEST] > height)
                height = array[c - LOWEST];
        }
    }

    for (i = height; i > 0; i--)
    {
        printf("%2d| ", i);

        for (k = 0; k <= HIGHEST - LOWEST; k++)
        {
            if (array[k] >= i)
                printf("#");
            else
                printf(" ");
        }
        printf("\n");
    }

    printf("  +-");
    for (i = 0; i <= HIGHEST - LOWEST; ++i)
        printf("-");
    printf("\n");

    printf("    ");
    for (i = 0; i <= HIGHEST - LOWEST; ++i)
        printf("%c", i + LOWEST);
    printf("\n\n");

    return 0;
}