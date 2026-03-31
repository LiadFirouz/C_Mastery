/*
 * mycomp.c
 * * The main interactive shell for the complex number calculator.
 * Responsible for command routing, string parsing, and robust input validation.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "complex.h"

#define MAX 100
#define TRUE 1
#define FALSE 0

/* Helper function prototype */
void skip_spaces(char **p);
int isValidCommand(char *command);
complex *get_var(char name, complex *vars[]);

int main(void)
{
    /* * Variable Declarations
     * Placed strictly at the top of the block to comply with ANSI C89.
     */
    complex A = {0, 0}, B = {0, 0}, C = {0, 0}, D = {0, 0}, E = {0, 0}, F = {0, 0};
    complex *vars[6], *target;

    char line[MAX], command[MAX], extra[MAX];
    /*char varName, varName2;
    double n1, n2;*/
    int args;

    char *p;
    int offset;
    /*char *endptr;*/

    /* Initialize the pointer map for O(1) variable access via ASCII math*/
    vars[0] = &A;
    vars[1] = &B;
    vars[2] = &C;
    vars[3] = &D;
    vars[4] = &E;
    vars[5] = &F;

    /* The Main Command Loop */
    while (1)
    {
        printf("Enter command: ");
        /* Safe input reading to prevent buffer overflow */
        if (fgets(line, MAX, stdin) == NULL)
        {
            break; /* Handle EOF */
        }

        printf("You entered: %s", line);

        /* Extract the command verb. Skip empty lines (Ghost line fix). */
        if (sscanf(line, "%s%n", command, &offset) < 1)
            continue;

        if (isValidCommand(command) == FALSE)
            continue;

        p = line + offset;

        /* --- Command Routing & Parsing ---*/
        if (strcmp(command, "stop") == 0)
        {
            /* Check if user typed garbage after the stop command*/
            args = sscanf(line, "%s %s", command, extra);
            if (args == 2)
                printf("Extraneous text after end of command\n");

            else
                break; /* Exit the program*/
        }

        else if (strcmp(command, "read_comp") == 0)
        {
        }

        else if (strcmp(command, "print_comp") == 0)
        {
            skip_spaces(&p);
            if (*p == ',')
            {
                printf("Illegal comma\n");
                continue;
            }

            if (*p == '\0' || *p == '\n')
            {
                printf("Missing parameter\n");
                continue;
            }

            target = get_var(*p++, vars);
            if (target == NULL)
                continue;

            skip_spaces(&p);
            if (*p != '\n' && *p != '\0')
            {
                printf("Extraneous text after end of command\n");
                continue;
            }

            print_comp(*target);
        }

        else if (strcmp(command, "add_comp") == 0)
        {
        }

        else if (strcmp(command, "sub_comp") == 0)
        {
        }

        else if (strcmp(command, "mult_comp_real") == 0)
        {
        }

        else if (strcmp(command, "mult_comp_img") == 0)
        {
        }

        else if (strcmp(command, "mult_comp_comp") == 0)
        {
        }

        else if (strcmp(command, "abs_comp") == 0)
        {
            skip_spaces(&p);
            if (*p == ',')
            {
                printf("Illegal comma\n");
                continue;
            }

            if (*p == '\0' || *p == '\n')
            {
                printf("Missing parameter\n");
                continue;
            }

            target = get_var(*p++, vars);
            if (target == NULL)
                continue;

            skip_spaces(&p);
            if (*p != '\n' && *p != '\0')
            {
                printf("Extraneous text after end of command\n");
                continue;
            }

            abs_comp(*target);
        }

        else
            printf("Undefined command name\n");
    }

    return 0;
}

void skip_spaces(char **p)
{
    while (**p == ' ' || **p == '\t')
        (*p)++;
}

/*
 * isValidCommand:
 * Validates if the given string matches any of the system's known commands.
 * Uses a lookup table (array) for scalable and clean command verification.
 * * Parameters:
 * command - The command string extracted from the user's input.
 * * Returns:
 * 1 (True) if the command is valid, 0 (False) otherwise.
 */
int isValidCommand(char *command)
{
    /* Lookup table containing all legal operations in the system */
    char *valid_commands[] = {
        "read_comp", "print_comp", "add_comp", "sub_comp",
        "mult_comp_real", "mult_comp_img", "mult_comp_comp",
        "abs_comp", "stop"};
    int i = 0;

    /* * Safely calculate the number of elements in the array.
     * Total array size (bytes) divided by the size of a single pointer.
     */
    int num_elements = sizeof(valid_commands) / sizeof(valid_commands[0]);

    /* Scan the lookup table for an exact string match */
    for (i = 0; i < num_elements; i++)
        if (strcmp(command, valid_commands[i]) == 0)
            return TRUE; /* Match found - valid command */

    printf("Undefined command name\n");
    return FALSE;
}

/*
 * get_var:
 * Maps a character ('A' to 'F') to the corresponding complex variable pointer.
 * Returns NULL and prints an error if the character is out of bounds.
 */
complex *get_var(char name, complex *vars[])
{
    if (name >= 'A' && name <= 'F')
        return vars[name - 'A'];

    printf("Undefined complex variable\n");
    return NULL;
}
