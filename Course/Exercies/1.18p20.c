// Write a program to copy its input to its output, replacing each string of one or
// more blanks by a single blank.

#include <stdio.h>

#define SIZE 100

int get_line(char s[], int lim);

int main()
{
    int lineLength = 0;
    char line[SIZE];

    while ((lineLength = get_line(line, SIZE)) > 0)
    {
        int i = lineLength - 2;

        while (i >= 0 && (line[i] == ' ' || line[i] == '\t'))
        {
            i--;
        }

        if (i >= 0)
        {
            line[++i] = '\n';
            line[++i] = '\0';
        }
        printf("%s", line);
    }
}

/* getline: read a line into s, return length */
int get_line(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}
