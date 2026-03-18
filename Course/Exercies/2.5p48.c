/*Exercise  2-5.  Write  the  function  any(s1,s2),  which  returns  the  first  location  in  a  string  s1
where  any  character  from  the  string  s2  occurs,  or  -1  if  s1  contains  no  characters  from  s2.
(The  standard  library  function  strpbrk  does  the  same  job  but  returns  a  pointer  to  the
location.)*/

#include <stdio.h>

#define MAX 100

int any(char s1[], char s2[]);
int get_line(char s[], int lim);

int main(void)
{
    char s1[MAX], s2[MAX];

    get_line(s1, MAX);
    get_line(s2, MAX);

    printf("location: %d\n", any(s1, s2));
}

int any(char s1[], char s2[])
{
    int i = 0, j = 0;

    if (s1[0] == '\0' || s2[0] == '\0')
        return -1;

    while (s1[i] != '\0')
    {
        while (s2[j] != '\0')
        {
            if (s1[i] == s2[j])
                return i;
            j++;
        }
        j = 0;
        i++;
    }
    return -1;
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
