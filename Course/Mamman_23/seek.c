/*
 * Name: Liad Firouz
 * ID: 209187699
 * File: seek.c
 * ============================================================================
 * Description: A program that receives a positive integer 'n' and a list of
 * filenames as command-line arguments. It iterates through the
 * files, navigates directly to the n-th character of each file,
 * and prints the filename along with the character's decimal
 * ASCII value. If a file cannot be opened or is shorter than
 * 'n' characters, an appropriate error message is displayed,
 * and the program safely continues to the next file.
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define MIN_ARGS 3

/* Function prototypes */
void processFile(FILE *fptr, char *filename, int n);
int isNumberOfArgsValid(int n);
int isNPositive(int n);

/* * Main function.
 * Receives a number 'n' and a list of filenames via command line arguments.
 * It opens each file, navigates to the n-th character, and prints its ASCII value.
 */
int main(int argsN, char *args[])
{
    int n = 0, i = 2;
    FILE *fptr;

    /* Check if the minimum required number of arguments was provided */
    if (isNumberOfArgsValid(argsN) == FALSE)
        return 1;

    /* Convert the second argument (the character offset) from string to integer */
    n = atoi(args[1]);

    /* Validate that 'n' is a strictly positive integer */
    if (isNPositive(n) == FALSE)
        return 1;

    /* Iterate over all the provided filenames starting from index 2 */
    for (i = 2; i < argsN; i++)
    {
        /* Attempt to open the file in read-only mode */
        fptr = fopen(args[i], "r");

        /* If the file doesn't exist or cannot be opened, print an error and skip to the next */
        if (fptr == NULL)
        {
            fprintf(stderr, "Error: Cannot open file %s\n", args[i]);
            continue;
        }

        /* Process the successfully opened file */
        processFile(fptr, args[i], n);

        /* Close the file to prevent memory leaks */
        fclose(fptr);
    }
    return 0;
}

/*
 * Navigates directly to the n-th character (n-1 offset) using fseek.
 * If the file is shorter than n, it prints an error.
 * Otherwise, it prints the filename and the decimal ASCII value of the character.
 */
void processFile(FILE *fptr, char *filename, int n)
{
    int c;

    /* Move the file pointer to the (n-1) position from the start of the file */
    fseek(fptr, n - 1, SEEK_SET);

    /* Read the character at the new pointer position */
    c = fgetc(fptr);

    /* Check if the pointer reached the End Of File (i.e., the file is too short) */
    if (c == EOF)
    {
        printf("Error: %s - file is too short.\n", filename);
        return;
    }

    /* Print the filename and the ASCII value of the character */
    printf("%s - %d\n", filename, c);
}

/*
 * Validates the total number of command line arguments.
 * Returns TRUE if valid, FALSE otherwise.
 */
int isNumberOfArgsValid(int n)
{
    if (n < MIN_ARGS)
    {
        printf("Error: Not enough arguments.\n");
        return FALSE;
    }
    return TRUE;
}

/*
 * Validates that the requested character position is strictly positive (> 0).
 * Returns TRUE if valid, FALSE otherwise.
 */
int isNPositive(int n)
{
    if (n <= 0)
    {
        printf("Error: the number must be greater than zero.\n");
        return FALSE;
    }
    return TRUE;
}