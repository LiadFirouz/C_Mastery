#define OUT 0
#define IN 1

#include <stdio.h>

int main(){
    int c, nl, nw, nc, state;

    nl=0, nw=0, nc=0, state = OUT;
    while ((c=getchar()) != EOF){
        if(c == '\n' || c == '\t' || c == ' ')
            ++nl;
        if(c == ' ')
            state = OUT;
        if(state == OUT && c != ' '){
            ++nw;
            state = IN;
        }
        nc++;

    }

    printf("End of the PROGRAM.\n number of rows:%d\n"
         "number of words:%d\n number of chars:%d\n ", nl,nw,nc);
    return 0;
}