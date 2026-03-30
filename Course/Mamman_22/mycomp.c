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

/* Helper function prototype */
complex *get_var(char name, complex *vars[]);

int main(void)
{
    /* * Variable Declarations
     * Placed strictly at the top of the block to comply with ANSI C89.
     */
    complex A = {0, 0}, B = {0, 0}, C = {0, 0}, D = {0, 0}, E = {0, 0}, F = {0, 0};
    complex *vars[6], *target, *target2;

    char line[MAX], command[MAX], extra[MAX];
    char varName, varName2;
    double n1, n2;
    int args;

    /* Initialize the pointer map for O(1) variable access via ASCII math */
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
        if (sscanf(line, "%s", command) < 1)
            continue;

        /* --- Command Routing & Parsing --- */
        if (strcmp(command, "stop") == 0)
        {
            /* Check if user typed garbage after the stop command */
            args = sscanf(line, "%s %s", command, extra);
            if (args == 2)
                printf("Extraneous text after end of command\n");

            else
                break; /* Exit the program */
        }

        else if (strcmp(command, "read_comp") == 0)
        {
            /* Expects: string, char, comma, double, comma, double */
            args = sscanf(line, "%s %c , %lf , %lf %s", command, &varName, &n1, &n2, extra);

            if (args == 5)
                printf("Extraneous text after end of command\n");

            else if (args != 4)
                printf("Missing parameter\n");
            else
            {
                target = get_var(varName, vars);
                if (target != NULL)
                    read_comp(target, n1, n2);
            }
        }

        else if (strcmp(command, "print_comp") == 0)
        {
            /* Expects: string, char */
            args = sscanf(line, "%s %c %s", command, &varName, extra);

            if (args == 3)
                printf("Extraneous text after end of command\n");

            else if (args != 2)
                printf("Missing parameter\n");

            else
            {
                target = get_var(varName, vars);
                if (target != NULL)
                    print_comp(*target);
            }
        }

        else if (strcmp(command, "add_comp") == 0)
        {
            /* Expects: string, char, comma, char */
            args = sscanf(line, "%s %c , %c %s", command, &varName, &varName2, extra);

            if (args == 4)
                printf("Extraneous text after end of command\n");

            else if (args != 3)
                printf("Missing parameter\n");
            else
            {
                target = get_var(varName, vars);
                target2 = get_var(varName2, vars);
                if (target != NULL && target2 != NULL)
                    add_comp(*target, *target2);
            }
        }

        else if (strcmp(command, "sub_comp") == 0)
        {
            args = sscanf(line, "%s %c , %c %s", command, &varName, &varName2, extra);

            if (args == 4)
                printf("Extraneous text after end of command\n");

            else if (args != 3)
                printf("Missing parameter\n");
            else
            {
                target = get_var(varName, vars);
                target2 = get_var(varName2, vars);
                if (target != NULL && target2 != NULL)
                    sub_comp(*target, *target2);
            }
        }

        else if (strcmp(command, "mult_comp_real") == 0)
        {
            /* Expects: string, char, comma, double */
            args = sscanf(line, "%s %c , %lf %s", command, &varName, &n1, extra);

            if (args == 4)
                printf("Extraneous text after end of command\n");

            else if (args != 3)
                printf("Missing parameter\n");
            else
            {
                target = get_var(varName, vars);
                if (target != NULL)
                    mult_comp_real(*target, n1);
            }
        }

        else if (strcmp(command, "mult_comp_img") == 0)
        {
            args = sscanf(line, "%s %c , %lf %s", command, &varName, &n1, extra);

            if (args == 4)
                printf("Extraneous text after end of command\n");

            else if (args != 3)
                printf("Missing parameter\n");
            else
            {
                target = get_var(varName, vars);
                if (target != NULL)
                    mult_comp_img(*target, n1);
            }
        }

        else if (strcmp(command, "mult_comp_comp") == 0)
        {
            args = sscanf(line, "%s %c , %c %s", command, &varName, &varName2, extra);

            if (args == 4)
                printf("Extraneous text after end of command\n");

            else if (args != 3)
                printf("Missing parameter\n");
            else
            {
                target = get_var(varName, vars);
                target2 = get_var(varName2, vars);
                if (target != NULL && target2 != NULL)
                    mult_comp_comp(*target, *target2);
            }
        }

        else if (strcmp(command, "abs_comp") == 0)
        {
            args = sscanf(line, "%s %c %s", command, &varName, extra);

            if (args == 3)
                printf("Extraneous text after end of command\n");

            else if (args != 2)
                printf("Missing parameter\n");
            else
            {
                target = get_var(varName, vars);
                if (target != NULL)
                    abs_comp(*target);
            }
        }

        else
            printf("Undefined command name\n");
    }
    return 0;
}

/*
 * get_var:
 * Maps a character ('A' to 'F') to the corresponding complex variable pointer.
 * Returns NULL and prints an error if the character is out of bounds.
 */
complex *get_var(char name, complex *vars[])
{
    if (name >= 'A' && name <= 'F')
        /* Calculate array index using ASCII subtraction */
        return vars[name - 'A'];

    printf("Undefined complex variable\n");
    return NULL;
}
