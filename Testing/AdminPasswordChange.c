#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct AdminControl {
    char username[40];
    char password[40];
};

int AdminPasswordChange();
int ArraySize(FILE* pointer, int structSize);

char* adminFile = "../DataFiles/AdminFile.txt";

int main() {
    int response;

    response = AdminPasswordChange();

    printf("\n\n");

    if (response == 404) {
        printf("Error!");
    }
    else if (response == 1) {
        printf("Successful!");
    }
}

int AdminPasswordChange() {
    struct AdminControl userData, userFromFile;
    FILE* pointer;
    int sizeFromFile, counter1, length, found = 0;
    char tempPassword1[40], tempPassword2[40];

    pointer = fopen(adminFile, "rb+");

    if (pointer == NULL) {
        return 404;
    }

    printf("Enter username: ");
    gets(userData.username);
    fflush(stdin);

    length = strlen(userData.username);

    for (counter1 = 0; counter1 < length; counter1++) {
        if (userData.username[counter1] >= 'A' && userData.username[counter1] <= 'Z') {
            userData.username[counter1] += 32;
        }
    } 

    printf("Enter old password: ");
    gets(userData.password);
    fflush(stdin);

    sizeFromFile = ArraySize(pointer, sizeof(struct AdminControl));

    for (counter1 = 0; counter1 < sizeFromFile; counter1++) {
        fread(&userFromFile, sizeof(struct AdminControl), 1, pointer);
        if (strcmp(userData.username, userFromFile.username) == 0) {
            if (strcmp(userData.password, userFromFile.password) == 0) {
                found = 1;
                break;
            }
        }
    }    
    
    if (found == 0) {
        return 0;
    }
    
    newpassword:
    printf("Enter new password: ");
    gets(tempPassword1);
    fflush(stdin);
    while(strlen(tempPassword1) <= 0) {
        printf("\nPassword field cannot be empty!\n");
        printf("Enter new password again: ");
        gets(tempPassword1);
        fflush(stdin);
    }

    printf("Enter new password again for confirmation: ");
    gets(tempPassword2);
    fflush(stdin);

    if (strcmp(tempPassword1, tempPassword2) != 0) {
        printf("\nPassword does not match!\n");
        goto newpassword;
    }

    strcpy(userData.password, tempPassword2);

    fseek(pointer, -(sizeof(struct AdminControl)), SEEK_CUR);
    fseek(pointer, 0L, SEEK_CUR);

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