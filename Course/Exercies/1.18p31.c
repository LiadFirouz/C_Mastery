/* Write  a  program  to  remove  trailing  blanks  and  tabs  from  each  line  of  input,
and to delete entirely blank lines. */

#include <stdio.h>

#define SIZE 100

int getline(char line[], int maxline);
void copy(char to[], char from[]);

int main(void)
{
    char line[SIZE];
    int lineLength = 0, i = 0, j = 0;

    while ((lineLength = getline(line, SIZE)) != 0)
    {

        i = lineLength - 2;
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

/* getline:  read a line into s, return length  */
int getline(char s[], int lim)
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

/* copy:  copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
    int i;
    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}