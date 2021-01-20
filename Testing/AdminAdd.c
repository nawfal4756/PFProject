#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct AdminControl {
    char username[40];
    char password[40];
};

int AdminAdd();
int ArraySize(FILE* pointer, int structSize);

char* adminFile = "../DataFiles/AdminFile.txt";

int main() {
    int response;

    response = AdminAdd();

    printf("\n\n");

    if (response == 404) {
        printf("Error!");
    }
    else if (response == 1) {
        printf("Successful");
    }
    else {
        printf("Unsuccessful");
    }
}  

int AdminAdd() {
    struct AdminControl userData, userFromFile;
    FILE* pointer;
    int counter1, length, sizeFromFile;

    pointer = fopen(adminFile, "ab+");

    if (pointer == NULL) {
        return 404;
    }

    sizeFromFile = ArraySize(pointer, sizeof(struct AdminControl));

    username:
    printf("Enter username: ");
    gets(userData.username);
    fflush(stdin);
    while(strlen(userData.username) <= 0) {
        printf("\nUsername is required!\n");
        printf("Enter username again: ");
        gets(userData.username);
        fflush(stdin);
    }

    length = strlen(userData.username);

    for (counter1 = 0; counter1 < length; counter1++) {
        if (userData.username[counter1] >= 'A' && userData.username[counter1] <= 'Z') {
            userData.username[counter1] += 32;
        }
    } 

    for (counter1 = 0; counter1 < sizeFromFile; counter1++) {
        fread(&userFromFile, sizeof(struct AdminControl), 1, pointer);
        if (strcmp(userData.username, userFromFile.username) == 0) {
            printf("\nUser with this username already exists! User another username\n");
            goto username;
        }
    }

    printf("Enter password: ");
    gets(userData.password);
    fflush(stdin);
    while(strlen(userData.password) <= 0) {
        printf("\nPassword is required!\n");
        printf("Enter password again: ");
        gets(userData.password);
        fflush(stdin);
    }

    fseek(pointer, 0L, SEEK_END);
    fwrite(&userData, sizeof(struct AdminControl), 1, pointer);
    fclose(pointer);

    return 1;
}

int ArraySize(FILE* pointer, int structSize) {
    int size;

    fseek(pointer, 0L, SEEK_END);
    size = ftell(pointer);
    size = size / structSize;
    fseek(pointer, 0L, SEEK_SET);

    return size;
}
