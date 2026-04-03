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
complex *extract_two_vars(char **p, complex *vars[], complex **target2_out);
complex *extract_read_args(char **p, complex *vars[], double *n1_out, double *n2_out);
complex *extract_double_arg(char **p, complex *vars[], double *n1_out);
complex *extract_single_arg(char **p, complex *vars[]);
int check_missing_comma(char c);
int check_multiple_comma(char c);
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
    complex *vars[6], *target, *target2;

    char line[MAX], command[MAX], extra[MAX];
    double n1, n2;
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
            target = extract_read_args(&p, vars, &n1, &n2);
            if (target != NULL)
            {
                read_comp(target, n1, n2);
            }
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
            target = extract_two_vars(&p, vars, &target2);
            if (target != NULL)
            {
                add_comp(*target, *target2);
            }
        }

        else if (strcmp(command, "sub_comp") == 0)
        {
            target = extract_two_vars(&p, vars, &target2);
            if (target != NULL)
            {
                sub_comp(*target, *target2);
            }
        }

        else if (strcmp(command, "mult_comp_real") == 0)
        {
            target = extract_double_arg(&p, vars, &n1);
            if (target != NULL)
            {
                mult_comp_real(*target, n1);
            }
        }

        else if (strcmp(command, "mult_comp_img") == 0)
        {
            target = extract_double_arg(&p, vars, &n1);
            if (target != NULL)
            {
                mult_comp_img(*target, n1);
            }
        }

        else if (strcmp(command, "mult_comp_comp") == 0)
        {
            target = extract_two_vars(&p, vars, &target2);
            if (target != NULL)
            {
                mult_comp_comp(*target, *target2);
            }
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

complex *extract_two_vars(char **p, complex *vars[], complex **target2_out)
{
    complex *target, *target2;
    char varName;

    /* --- Stage 1: Variable Extraction --- */

    /* Fast-forward to the first meaningful character */
    skip_spaces(p);

    /* Ensure the string doesn't start with a stray comma or end prematurely */
    if (check_illegal_comma(**p))
        return NULL;
    if (check_missing_parameter(**p))
        return NULL;

    /* Extract the variable identifier (e.g., 'A') and advance the pointer */
    varName = **p;
    (*p)++;

    /* Map the identifier to its actual memory address */
    target = get_var(varName, vars);
    if (target == NULL)
        return NULL;

    /* --- Stage 2: First Comma Validation --- */

    /* Fast-forward to locate the mandatory separating comma */
    skip_spaces(p);
    if (check_missing_parameter(**p))
        return NULL;
    if (check_missing_comma(**p))
        return NULL;

    /* Hop over the valid comma */
    (*p)++;

    /* --- Stage 3: First Number (Real Part) Extraction --- */

    /* Fast-forward past the comma to locate the real number */
    skip_spaces(p);
    if (check_multiple_comma(**p))
        return NULL;
    if (check_missing_parameter(**p))
        return NULL;

    /* Extract second variable identifier and advance */
    varName = **p;
    (*p)++;

    target2 = get_var(varName, vars);
    if (target2 == NULL)
        return NULL;

    /* --- Stage 4: Final Validation --- */

    skip_spaces(p);
    if (check_extraneous_text(**p))
        return NULL;

    /* All validations passed - export both numbers and return the variable pointer */
    *target2_out = target2;
    return target;
}

/*
 * extract_read_args:
 * Parses a command line that requires exactly three arguments: a complex variable and two real numbers.
 * Expected strict syntax: [Variable] , [Real Number] , [Imaginary Number] (e.g., "A, -3.5, 4.2").
 * It utilizes validation helpers to enforce comma placement, prevent missing parameters,
 * and block trailing garbage.
 * * Parameters:
 * p      - A double pointer to the current position in the command string.
 * vars   - The array of pointers to the system's complex variables (A-F).
 * n1_out - Pointer to a double where the parsed real part will be safely stored upon success.
 * n2_out - Pointer to a double where the parsed imaginary part will be safely stored upon success.
 * * Returns:
 * A pointer to the requested complex variable if parsing succeeds.
 * NULL if any syntax error occurs, if the variable is undefined, or if the numbers are invalid.
 */
complex *extract_read_args(char **p, complex *vars[], double *n1_out, double *n2_out)
{
    complex *target;
    char *endptr, varName;
    double n1, n2;

    /* --- Stage 1: Variable Extraction --- */

    /* Fast-forward to the first meaningful character */
    skip_spaces(p);

    /* Ensure the string doesn't start with a stray comma or end prematurely */
    if (check_illegal_comma(**p))
        return NULL;
    if (check_missing_parameter(**p))
        return NULL;

    /* Extract the variable identifier (e.g., 'A') and advance the pointer */
    varName = **p;
    (*p)++;

    /* Map the identifier to its actual memory address */
    target = get_var(varName, vars);
    if (target == NULL)
        return NULL;

    /* --- Stage 2: First Comma Validation --- */

    /* Fast-forward to locate the mandatory separating comma */
    skip_spaces(p);

    /* Ensure the command didn't end before the comma, and verify the comma exists */
    if (check_missing_parameter(**p))
        return NULL;
    if (check_missing_comma(**p))
        return NULL;

    /* Hop over the valid comma */
    (*p)++;

    /* --- Stage 3: First Number (Real Part) Extraction --- */

    /* Fast-forward past the comma to locate the real number */
    skip_spaces(p);

    /* Reject multiple consecutive commas (e.g., "A,,5") and check for unexpected EOF */
    if (check_multiple_comma(**p))
        return NULL;
    if (check_missing_parameter(**p))
        return NULL;

    /* Attempt to extract a double-precision floating-point number */
    n1 = strtod(*p, &endptr);

    /* If the pointer didn't move, no valid number was found */
    if (*p == endptr)
    {
        printf("Invalid parameter - not a number\n");
        return NULL;
    }

    /* Advance the main parsing pointer past the extracted number */
    *p = endptr;

    /* --- Stage 4: Second Comma Validation --- */

    /* Fast-forward to locate the mandatory separating comma */
    skip_spaces(p);

    /* Ensure the command didn't end before the comma, and verify the comma exists */
    if (check_missing_parameter(**p))
        return NULL;
    if (check_missing_comma(**p))
        return NULL;

    /* Hop over the valid comma */
    (*p)++;

    /* --- Stage 5: Second Number (Imaginary Part) Extraction --- */

    /* Fast-forward past the comma to locate the real number */
    skip_spaces(p);

    /* Reject multiple consecutive commas and check for unexpected EOF */
    if (check_multiple_comma(**p))
        return NULL;
    if (check_missing_parameter(**p))
        return NULL;

    /* Attempt to extract the second double-precision floating-point number */
    n2 = strtod(*p, &endptr);

    /* If the pointer didn't move, no valid number was found */
    if (*p == endptr)
    {
        printf("Invalid parameter - not a number\n");
        return NULL;
    }

    /* Advance the main parsing pointer past the extracted number */
    *p = endptr;

    /* --- Stage 6: Final Validation --- */

    /* Fast-forward past the number to inspect the end of the line */
    skip_spaces(p);

    /* Guarantee no additional arguments or garbage text follow the number */
    if (check_extraneous_text(**p))
        return NULL;

    /* All validations passed - export both numbers and return the variable pointer */
    *n1_out = n1;
    *n2_out = n2;

    return target;
}

/*
 * extract_double_arg:
 * Parses a command line that requires exactly two arguments: a complex variable and a real number.
 * Expected strict syntax: [Variable] , [Real Number] (e.g., "A, 5.5").
 * It utilizes validation helpers to enforce comma placement, prevent missing parameters,
 * and block trailing garbage.
 * * Parameters:
 * p      - A double pointer to the current position in the command string.
 * vars   - The array of pointers to the system's complex variables (A-F).
 * n1_out - Pointer to a double where the parsed real number will be safely stored upon success.
 * * Returns:
 * A pointer to the requested complex variable if parsing succeeds.
 * NULL if any syntax error occurs, if the variable is undefined, or if the number is invalid.
 */
complex *extract_double_arg(char **p, complex *vars[], double *n1_out)
{
    complex *target;
    char *endptr, varName;
    double n1;

    /* --- Stage 1: Variable Extraction --- */

    /* Fast-forward to the first meaningful character */
    skip_spaces(p);

    /* Ensure the string doesn't start with a stray comma or end prematurely */
    if (check_illegal_comma(**p))
        return NULL;
    if (check_missing_parameter(**p))
        return NULL;

    /* Extract the variable identifier (e.g., 'A') and advance the pointer */
    varName = **p;
    (*p)++;

    /* Map the identifier to its actual memory address */
    target = get_var(varName, vars);
    if (target == NULL)
        return NULL;

    /* --- Stage 2: Comma Validation --- */

    /* Fast-forward to locate the mandatory separating comma */
    skip_spaces(p);

    /* Ensure the command didn't end before the comma, and verify the comma exists */
    if (check_missing_parameter(**p))
        return NULL;
    if (check_missing_comma(**p))
        return NULL;

    /* Hop over the valid comma */
    (*p)++;

    /* --- Stage 3: Number Extraction --- */

    /* Fast-forward past the comma to locate the real number */
    skip_spaces(p);

    /* Reject multiple consecutive commas (e.g., "A,,5") and check for unexpected EOF */
    if (check_multiple_comma(**p))
        return NULL;
    if (check_missing_parameter(**p))
        return NULL;

    /* Attempt to extract a double-precision floating-point number */
    n1 = strtod(*p, &endptr);

    /* If the pointer didn't move, no valid number was found */
    if (*p == endptr)
    {
        printf("Invalid parameter - not a number\n");
        return NULL;
    }

    /* Advance the main parsing pointer past the extracted number */
    *p = endptr;

    /* --- Stage 4: Final Validation --- */

    /* Fast-forward past the number to inspect the end of the line */
    skip_spaces(p);

    /* Guarantee no additional arguments or garbage text follow the number */
    if (check_extraneous_text(**p))
        return NULL;

    /* All validations passed - export the number and return the variable pointer */
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
 * check_missing_comma:
 * Validates that the current character is have comma.
 * Used to enforce strict syntax in commands that do not accept multiple parameters.
 * Returns: 1 if an illegal comma is detected (and prints an error), 0 otherwise.
 */
int check_missing_comma(char c)
{
    if (c != ',')
    {
        printf("Missing comma\n");
        return 1;
    }
    return 0;
}

/*
 * check_multiple_comma:
 * Validates that the current character is not have multiple comma.
 * Used to enforce strict syntax in commands that do not accept multiple parameters.
 * Returns: 1 if an illegal comma is detected (and prints an error), 0 otherwise.
 */
int check_multiple_comma(char c)
{
    if (c == ',')
    {
        printf("Multiple consecutive commas\n");
        return 1;
    }
    return 0;
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
