#include <stdio.h>
#include <string.h>

#define STRING_LEN 256

void remove_blanks(char *string);

int main(){
    char string [STRING_LEN];

    while(fgets(string, STRING_LEN, stdin) != NULL){
        string[strcspn(string, "\n")] = '\0';
        printf("The Input string:\n\"%s\"\n", string);
        remove_blanks(string);
        printf("The string at the end of the function:\n\"%s\"\n\n\n", string);
    }
    return 0;
}

void remove_blanks(char *string){
    int writeIndex = 0, readIndex = 0;

    printf("The string as received by the function:\n\"%s\"\n", string);

    for(readIndex = 0; string[readIndex] != '\0'; readIndex++){
        if(!(string[readIndex] == ' ' || string[readIndex] == '\t' || string[readIndex] == '\n')){
            string[writeIndex] = string[readIndex];
            writeIndex ++;
        }
    }

    string[writeIndex] = '\0';
}
