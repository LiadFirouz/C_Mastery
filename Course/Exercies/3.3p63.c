/*Exercise 3-3. Write a function expand(s1,s2) that expands shorthand notations like a-z in
the  string  s1  into  the  equivalent  complete  list  abc...xyz  in  s2.  Allow  for  letters  of  either
case  and  digits,  and  be  prepared  to  handle  cases  like  a-b-c  and  a-z0-9  and  -a-z.  Arrange
that a leading or trailing - is taken literally.*/

#include <stdio.h>

#define MAX 1000

void expand(char s1[], char s2[]);
int get_line(char s[], int lim);

int main(void)
{
    char s1[MAX], s2[MAX];

    printf("Enter shorthand notation: ");
    get_line(s1, MAX);

    expand(s1, s2);

    printf("Expanded: %s\n", s2);
    return 0;
}

void expand(char s1[], char s2[])
{
    int i = 0, j = 0;

    while (s1[i] != '\0')
    {
        /* GATE 1: Is it a hyphen securely sandwiched between two characters? */
        if (s1[i] == '-' && i > 0 && s1[i + 1] != '\0')
        {
            char first = s1[i - 1];
            char last = s1[i + 1];

            /* GATE 2: Is it a valid, logical sequence? */
            if (((first >= 'a' && last <= 'z') ||
                 (first >= 'A' && last <= 'Z') ||
                 (first >= '0' && last <= '9')) &&
                (first < last))
            {
                /* SUCCESS: Expand the gap */
                first++;
                while (first < last)
                {
                    s2[j++] = first++;
                }
            }
            else
            {
                /* FAILURE AT GATE 2: It's a middle hyphen, but an invalid range (e.g., a-R). */
                s2[j++] = s1[i];
            }
        }
        else
        {
            /* FAILURE AT GATE 1: Not a middle hyphen. Just a normal character or edge hyphen. */
            s2[j++] = s1[i];
        }

        /* The loop advances NO MATTER WHICH PATH was taken above. */
        i++;
    }

    /* Safely cap the string ONLY AFTER the entire while loop is completely finished. */
    s2[j] = '\0';
}

/* getline: read a line into s, return length */
int get_line(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    s[i] = '\0';
    return i;
}
