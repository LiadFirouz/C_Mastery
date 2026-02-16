#define OUT 0
#define IN 1

#include <stdio.h>

int main(){
    int c, nl, nw, nc;

    nl=0, nw=0, nc=0;
    while ((c=getchar()) != EOF){
        if(c == '\n')
            ++nl;
        if(c == ' ')
            nw++;
        nc++;

    }

    printf("End of the PROGRAM.\n number of rows:%d\n"
         "number of words:%d\n number of chars:%d\n ", nl,nw,nc);
    return 0;
}