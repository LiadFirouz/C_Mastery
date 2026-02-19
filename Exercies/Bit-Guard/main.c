#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Bitmask Definitions
#define READ    0x01  // 00000001 (1) 
#define WRITE   0x02  // 00000010 (2)
#define EXECUTE 0x04  // 00000100 (4)
#define DELETE  0x08  // 00001000 (8)
#define ADMIN   0x80  // 10000000 (128)

// User Structer
typedef struct User
{
    int id; //user id
    char name [50]; // user name
    unsigned char permissions; // user permissions
    struct User* next; // pointer to the next use
}User;

// Functions
void addUser(User** head);
void togglePermission (User* head, int id, unsigned char mask);
void printUsers(User* head);
void deleteUser(User** head, int id);
void freeList(User* head);

int main(){

    return 0;
}

void addUser(User** head){
    // allocate new memory
    User* newUser = (User*)malloc(sizeof(User));

    // check if the pointer is point on the new memory
    if(newUser == NULL){
        printf("Error: Memory allocation failed!\n");
        return;
    }

    // get user id
    printf("Enter User ID: ");
    scanf("%d", &newUser->id);

    // clear the Enter from the last input
    while (getchar() != '\n');
    
    // get the new new 
    printf("Enter User Name:");
    fgets(newUser->name, 50, stdin);

    // remove "\n" from the name
    newUser->name[strcspn(newUser->name, "\n")] = 0;

    // point to the last person on the list
    newUser->next = *head;

    // point the start of the list to the new one
    *head = newUser;
}

void togglePermission (User* head, int id, unsigned char mask){
    
    User *pointer = head;

    while(pointer != NULL){
        if(pointer->id == id){
           pointer->permissions ^= mask;
        }
    }

    printf("User with ID %d not found.\n", id);
}

void printUsers(User* head){
    
}





