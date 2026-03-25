#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "complex.h"

#define MAX 100

complex *get_var(char name, complex *vars[]);

int main(void)
{
    complex A = {0, 0}, B = {0, 0}, C = {0, 0}, D = {0, 0}, E = {0, 0}, F = {0, 0};
    complex *vars[6], *target, *target2;

    char line[MAX], command[MAX];
    char varName, varName2;
    double n1, n2;
    int args;

    vars[0] = &A;
    vars[1] = &B;
    vars[2] = &C;
    vars[3] = &D;
    vars[4] = &E;
    vars[5] = &F;

    while (1)
    {
        printf("Enter command: ");
        fgets(line, MAX, stdin);
        printf("You entered: %s", line);
        sscanf(line, "%s", command);

        if (strcmp(command, "stop") == 0)
            break;

        else if (strcmp(command, "read_comp") == 0)
        {
            args = sscanf(line, "%s %c , %lf , %lf", command, &varName, &n1, &n2);

            if (args != 4)
                printf("Missing parameter\n");
            else
            {
                target = get_var(varName, vars);
                if (target != NULL)
                    read_comp(target, n1, n2);
                else
                    printf("Error read_comp command\n");
            }
        }

        else if (strcmp(command, "print_comp") == 0)
        {
            sscanf(line, "%s %c", command, &varName);

            target = get_var(varName, vars);
            if (target != NULL)
                print_comp(*target);
        }

        else if (strcmp(command, "add_comp") == 0)
        {
            args = sscanf(line, "%s %c , %c", command, &varName, &varName2);

            if (args != 3)
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
            args = sscanf(line, "%s %c , %c", command, &varName, &varName2);

            if (args != 3)
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
            printf("Recognized mult_comp_real command\n");

        else if (strcmp(command, "mult_comp_img") == 0)
            printf("Recognized mult_comp_img command\n");

        else if (strcmp(command, "mult_comp_comp") == 0)
        {
            args = sscanf(line, "%s %c , %c", command, &varName, &varName2);

            if (args != 3)
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
            printf("Recognized abs_comp command\n");

        else
            printf("Undefined command name\n");
    }
}

complex *get_var(char name, complex *vars[])
{
    if (name >= 'A' && name <= 'F')
    {
        return vars[name - 'A'];
    }
    printf("Undefined complex variable\n");
    return NULL;
}
