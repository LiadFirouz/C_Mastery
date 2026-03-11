/*Write  a  function  reverse(s)  that  reverses  the  character  string  s.  Use  it  to
write a program that reverses its input a line at a time.*/

#include <stdio.h>

#define SIZE 100

int get_line(char s[], int lim);
void reverse(char line[]);

int main(void)
{
    char line[SIZE];
    int lineLength = 0;

    while ((lineLength = get_line(line, SIZE)) > 0)
    {
        reverse(line);
        printf("%s", line);
    }
}

void reverse(char line[])
{
    int lineLength = 0;
    while (line[lineLength] != '\0')
        lineLength++;

    if (lineLength == 0)
        return;

    int i = lineLength - 1, j = 0;

    if (line[i] == '\n')
        i--;
    while (j < i)
    {
        char temp = line[j];
        line[j++] = line[i];
        line[i--] = temp;
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