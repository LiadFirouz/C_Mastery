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
complex *extract_single_arg(char **p, complex *vars[]);
int check_illegal_comma(char c);
int check_missing_parameter(char c);
int check_extraneous_text(char c);
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
    double n1;    char *endptr;*/
    int args;
    char *p;
    int offset;

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
            target = extract_single_arg(&p, vars);
            if (target != NULL)
            {
                print_comp(*target);
            }
        }

        else if (strcmp(command, "add_comp") == 0)
        {
        }

        else if (strcmp(command, "sub_comp") == 0)
        {
        }

        else if (strcmp(command, "mult_comp_real") == 0)
        {
            /*target = extract_double_arg(&p, vars, &n1);
            if (target != NULL)
            {
                mult_comp_real(*target, n1);
            }*/
        }

        else if (strcmp(command, "mult_comp_img") == 0)
        {
        }

        else if (strcmp(command, "mult_comp_comp") == 0)
        {
        }

        else if (strcmp(command, "abs_comp") == 0)
        {
            target = extract_single_arg(&p, vars);
            if (target != NULL)
            {
                abs_comp(*target);
            }
        }

        else
            printf("Undefined command name\n");
    }

    return 0;
}

complex *extract_double_arg(char **p, complex *vars[], double *n1_out)
{
    complex *target;
    char *endptr, varName;
    double n1;

    /* Fast-forward through any spaces immediately following the command */
    skip_spaces(p);

    /* The print_comp command takes a single variable; commas are strictly forbidden */
    if (**p == ',')
    {
        printf("Illegal comma\n");
        return NULL;
    }

    /* Ensure the user didn't just press Enter without providing a variable */
    if (**p == '\0' || **p == '\n')
    {
        printf("Missing parameter\n");
        return NULL;
    }

    /* Extract the variable letter safely */
    varName = **p;
    /* Safely advance the underlying char* pointer */
    (*p)++;

    /* * Extract the variable character, advance the pointer to the next character,
     * and map it to the actual complex number memory address.
     */
    target = get_var(varName, vars);

    /* Abort operation if the variable was out of bounds (handled by get_var) */
    if (target == NULL)
        return NULL;

    /* Fast-forward through any spaces immediately following the command */
    skip_spaces(p);

    if (**p == '\0' || **p == '\n')
    {
        printf("Missing parameter\n");
        return NULL;
    }
    if (**p != ',')
    {
        printf("Missing comma\n");
        return NULL;
    }
    (*p)++;

    /* Fast-forward through any spaces immediately following the command */
    skip_spaces(p);

    if (**p == ',')
    {
        printf("Multiple consecutive commas\n");
        return NULL;
    }

    if (**p == '\0' || **p == '\n')
    {
        printf("Missing parameter\n");
        return NULL;
    }

    n1 = strtod(*p, &endptr);

    if (*p == endptr)
    {
        printf("Invalid parameter - not a number\n");
        return NULL;
    }
    *p = endptr;

    /* Skip any trailing spaces after the valid variable */
    skip_spaces(p);

    /* * Validate that nothing else was typed after the variable.
     * This strictly catches garbage text or illegal trailing commas (e.g., "print_comp A ,").
     */
    if (**p != '\n' && **p != '\0')
    {
        printf("Extraneous text after end of command\n");
        return NULL;
    }

    *n1_out = n1;
    return target;
}

/*
 * extract_single_arg:
 * Parses a command line that strictly requires exactly one complex variable parameter.
 * It utilizes validation helpers to enforce syntax rules (no commas, no empty inputs, no trailing garbage).
 * * Parameters:
 * p    - A double pointer to the current position in the command string.
 * vars - The array of pointers to the system's complex variables (A-F).
 * * Returns:
 * A pointer to the requested complex variable if parsing succeeds.
 * NULL if any syntax error occurs or if the variable is undefined.
 */
complex *extract_single_arg(char **p, complex *vars[])
{
    complex *target;
    char varName;

    /* Fast-forward to the first meaningful character of the parameter */
    skip_spaces(p);

    /* Enforce strict single-parameter syntax: reject unexpected commas and empty inputs */
    if (check_illegal_comma(**p))
        return NULL;
    if (check_missing_parameter(**p))
        return NULL;

    /* Extract the variable identifier and advance the main parsing pointer */
    varName = **p;
    (*p)++;

    /* Map the identifier (e.g., 'A') to its actual memory address */
    target = get_var(varName, vars);
    if (target == NULL)
        return NULL;

    /* Fast-forward past the valid variable to inspect the end of the line */
    skip_spaces(p);

    /* Guarantee no additional arguments or garbage text follow the variable */
    if (check_extraneous_text(**p))
        return NULL;

    /* All validations passed - return the safely extracted variable */
    return target;
}

/*
 * check_illegal_comma:
 * Validates that the current character is not an unexpected comma.
 * Used to enforce strict syntax in commands that do not accept multiple parameters.
 * Returns: 1 if an illegal comma is detected (and prints an error), 0 otherwise.
 */
int check_illegal_comma(char c)
{
    if (c == ',')
    {
        printf("Illegal comma\n");
        return 1;
    }
    return 0;
}

/*
 * check_missing_parameter:
 * Checks if the command string has ended prematurely before a required argument.
 * Detects null terminators ('\0') or newline characters ('\n').
 * Returns: 1 if a parameter is missing (and prints an error), 0 otherwise.
 */
int check_missing_parameter(char c)
{
    if (c == '\0' || c == '\n')
    {
        printf("Missing parameter\n");
        return 1;
    }
    return 0;
}

/*
 * check_extraneous_text:
 * Ensures the command line terminates cleanly after all arguments are parsed.
 * Any character other than a newline or null terminator is considered garbage.
 * Returns: 1 if extra text/garbage is found (and prints an error), 0 otherwise.
 */
int check_extraneous_text(char c)
{
    if (c != '\n' && c != '\0')
    {
        printf("Extraneous text after end of command\n");
        return 1;
    }
    return 0;
}

/*
 * skip_spaces:
 * Fast-forwards the parsing pointer past any spaces or tab characters.
 * Uses a double pointer (char **) to permanently advance the position
 * of the pointer within the calling function's context.
 */
void skip_spaces(char **p)
{
    while (**p == ' ' || **p == '\t')
    {
        (*p)++;
    }
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
