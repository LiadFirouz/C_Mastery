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

int main() {
    printf("---------WELCOME TO BIT-GUARD---------\n");
    
    // 1. THIS is the actual start of your list. A single pointer.
    User *head = NULL; 
    
    int user_choice;

    do {
        printf("\nEnter your choice:\n1. Add user\n2. Delete user\n3. Toggle permission\n4. Print users\n0. Exit Program\nChoice: ");
        scanf("%d", &user_choice);        
        
        // Clear the buffer safely
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        // 2. Use a switch statement for clean menu routing
        switch (user_choice) {
            case 1:
                // We pass the ADDRESS of the single pointer, which effectively makes it a User**
                addUser(&head); 
                break;
            case 2:{
                // TODO: How will you ask the user for the ID they want to delete?
                // TODO: Call deleteUser()

                // get user id
                int userId = 0;
                printf("Enter The User ID That you want to delete: ");
                scanf("%d", &userId);

                // clear the Enter from the last input
                while (getchar() != '\n');

                deleteUser(&head, userId);

                break;
            }
            case 3:{
                // TODO: Ask for the ID. Ask for the mask. 
                // TODO: Call togglePermission()

                // get user id
                int userId = 0;
                printf("Enter The User ID That you want to toggle: ");
                scanf("%d", &userId);
                // clear the Enter from the last input
                while (getchar() != '\n');

                int temp = 0;
                printf("Enter mask: ");
                scanf("%d", &temp);
                // clear the Enter from the last input
                while (getchar() != '\n');  
                unsigned char mask = (unsigned char) temp;

                togglePermission(&head, userId, mask);

                break;
            }
            case 4:
                // Notice printUsers only needs to READ the list, so it takes User*, not User**
                printUsers(head);
                break;
            case 0:
                printf("Exiting program...\n");
                // DANGER: What must you do here before the program closes to prevent a memory leak?
                freeList(head);
                break;
            default:
                printf("Invalid choice. Please enter a number between 0 and 4.\n");
        }
        
    } while(user_choice != 0);

    return 0;
}

void addUser(User** head){
    // allocate new memory
    User* newUser = (User*)malloc(sizeof(User));
    
    // check if the pointer is point on the new memory
    if(newUser == NULL){
        printf("Error: Memory allocation failed!\n");
        exit(1);
    }
    newUser->permissions = 0;

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
        if(pointer->id == id)
        pointer->permissions ^= mask;
        
        pointer = pointer->next;
    }

    printf("User with ID %d not found.\n", id);
}

void printUsers(User* head){
    User *pointer = head;
    int total_bits = sizeof(pointer->permissions) * 8;

    while(pointer != NULL){
        printf("User id = %d\n\tpermission =", pointer->id);
        for(int i=total_bits-1; i>=0 ; i--){
            int current_bit = (pointer->permissions >> i) & 1;
            printf("%d", current_bit);
        }
        pointer = pointer->next;
    }
    printf("END OF LIST");
}

void deleteUser(User** head, int id){
    
    // Senerio I: list is empty
    if (*head == NULL) {
        printf("List is empty. Cannot delete user %d.\n", id);
        return;
    }
    
    User * current = *head;
    User * previous = NULL;

    // Senerio II: The node to delete is the HEAD node
    if(current != NULL && current->id == id){
        *head = current->next;
        free(current);
        printf("User ID %d deleted successfully.\n", id);
        return;
    }

    // Senerio III: Traverse the list to find the node
    while(current != NULL && current->id != id){
        previous = current;
        current = current ->next;
    }

    if (current == NULL) {
        printf("User with ID %d not found.\n", id);
        return;
    }
    
    // Unlink the node from the linked list
    previous->next = current->next;
    
    // Free the isolated node from memory
    free(current);
    printf("User ID %d deleted successfully.\n", id);

}

void freeList(User* head){
    User * pointer = head;
    User * next;

    while(pointer != NULL){
        next = pointer->next;
        free(pointer);
        pointer = next;

    }
}



