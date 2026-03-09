// Write a program to count blanks, tabs, and newlines

#include <stdio.h>

int main(){
    int c = 0, spaces = 0, tabs = 0, newLine = 0;

    while(((c = getchar()) != EOF)){
        if(c == ' ')
            spaces++;
        if(c == '\t')
            tabs++;
        if(c == '\n')
            newLine++;
    }

    printf("Total spaces: spaces:%d, tabs:%d, new lines:%d", spaces, tabs, newLine);
}