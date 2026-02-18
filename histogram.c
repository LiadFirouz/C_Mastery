#define IN 1
#define OUT 0
#define MAX_LEN 20

#include <stdio.h>
int main(){
    int state = OUT;
    int arr[MAX_LEN];
    int c, counter = 0;

    for(int i = 0; i < MAX_LEN; i++){
        arr[i] = 0;
    }

    while ((c = getchar()) != EOF)
    {
        if(c == ' ' || c == '\n' || c == '\t'){
            if (state == IN)
                if(state == IN && counter < MAX_LEN)
                    arr[counter]++;
                counter=0;
            state = OUT;
        }
  
        else {
            state = IN;
            counter++;
        }
    }

    for(int i=1; i< MAX_LEN; i++){
        printf("%2d: ", i);
        for(int j=0; j<arr[i]; j++){
            printf("*");
        }
        printf("\n");
    }

    return 0;
}