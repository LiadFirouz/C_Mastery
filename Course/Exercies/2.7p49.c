/*Write  a  function  invert(x,p,n)  that  returns  x  with  the  n  bits  that  begin  at
position p inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged. */

#include <stdio.h>

int invert(int x, int p, int n);

int main(void)
{
    int x = 0, p = 0, n = 0;
    printf("Enter a number: x=");
    scanf("%d", &x);
    printf("p=");
    scanf("%d", &p);
    printf("n=");
    scanf("%d", &n);

    printf("The invert num is: %d", invert(x, p, n));
}

int invert(int x, int p, int n)
{
    int mask = ~(~0 << n) << (p + 1 - n);
    return x ^ mask;
}
