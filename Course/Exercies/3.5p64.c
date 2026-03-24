/*Exercise  3-5.  Write  the  function  itob(n,s,b)  that  converts  the  integer  n  into  a  base  b
character representation in the string s. In particular, itob(n,s,16) formats s as a
hexadecimal integer in s. */

#include <stdio.h>

#define MAX 1000

void itob(int n, char s[], int b);
int get_line(char s[], int lim);
void reverse(char s[]);

int main(void)
{
    int n = 0, b = 0;
    char s[MAX];

    printf("Enter your number: ");
    scanf("%d", n);

    printf("Enter your number: ");
    scanf("%d\n", b);

    get_line(s, MAX);
}

void reverse(char s[])
{
    int i = 0, j = 0;

    int sLength = 0;
    while (s[i++] != '\0')
    {
        sLength++;
    }
    char newS[sLength--];

    while (sLength != 0)
    {
        newS[j++] = s[sLength--];
    }
    newS[j] = '\0';
    s = &newS;
}

void itob(int n, char s[], int b)
{
    int i = 0, sign = n;

    if (n < 0)
        s[i++] = '-';

    if (n == 0)
    {
        s[0] = '0';
        s[1] = '\0';
        return;
    }

    while (n != 0)
    {
        int rem = n % b;
        n = n / b;

        if (rem >= 10)
        {
            s[i++] = (rem - 10) + 'a';
        }

        else if (rem < 10)
            s[i++] = rem + '0';
    }
    s[i] = '\0';
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
