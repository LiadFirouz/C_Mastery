/*
 * Name: Liad Firouz
 * ID: 209187699
 * File: remove_blanks.c
 * Description: A program that takes a given text from the user and deletes all the spaces in it.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define STRING_LEN 256

void remove_blanks(char *string);

int main(void)
{
    char string[STRING_LEN];

    while (fgets(string, STRING_LEN, stdin) != NULL)
    {
        string[strcspn(string, "\n")] = '\0';
        printf("The Input string:\n\"%s\"\n", string);
        remove_blanks(string);
        printf("The string at the end of the function:\n\"%s\"\n\n\n", string);
    }
    return 0;
}

/*
 * Function: remove_blanks
 * -------------------
 * Iterates through a string and removes all whitespace characters 
 * (spaces, tabs, newlines) by shifting valid characters to the left.
 * Modifies the string in-place.
 * * *string: A pointer to the null-terminated string to be processed.
 */

void remove_blanks(char *string)
{
    int writeIndex = 0, readIndex = 0;

    printf("The string as received by the function:\n\"%s\"\n", string);

    for (readIndex = 0; string[readIndex] != '\0'; readIndex++)
    {
        if (!(isspace(string[readIndex])))
        {
            string[writeIndex] = string[readIndex];
            writeIndex++;
        }
    }

    string[writeIndex] = '\0';
}
