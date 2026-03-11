/* Write a program to ``fold'' long input lines into two or more shorter lines after
the  last  non-blank  character  that  occurs  before  the  n-th  column  of  input.  Make  sure  your
program  does  something  intelligent  with  very  long  lines,  and  if  there  are  no  blanks  or  tabs
before the specified column. */

#include <stdio.h>

#define SIZE 100
#define MAX_SIZE 20
#define TAB_WIDTH 8

int get_line(char s[], int lim);
void wordWrap(char line[], int lineLength);

int main(void)
{
    char line[SIZE];
    int lineLength = 0;

    while ((lineLength = get_line(line, SIZE)) > 0)
    {
        wordWrap(line, lineLength);
        printf("%s", line);
    }
}

void wordWrap(char line[], int lineLength)
{
    int column = 0, lastSpace = -1, i = 0;

    while (i < lineLength)
    {
        if (line[i] == '\n')
        {
            column = 0;
            lastSpace = -1;
            i++;
            continue;
        }

        if (line[i] == '\t' || line[i] == ' ')
            lastSpace = i;

        if (line[i] == '\t')
        {
            column = column + (TAB_WIDTH - (column % TAB_WIDTH));
        }
        else
        {
            column++;
        }

        if (column == MAX_SIZE)
        {
            if (lastSpace != -1)
            {
                line[lastSpace] = '\n';
                column = i - lastSpace;
                lastSpace = -1;
            }

            else
            {
                column = 0;
                lastSpace = -1;
            }
        }
        i++;
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
