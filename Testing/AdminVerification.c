#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct AdminControl {
    char username[40];
    char password[40];
};

int AdminVerification(struct AdminControl userData);
int ArraySize(FILE* pointer, int structSize);

char* adminFile = "../DataFiles/AdminFile.txt";

int main() {
    struct AdminControl userData;
    int length, counter1, response;

    printf("Username: ");
    gets(userData.username);
    fflush(stdin);

    length = strlen(userData.username);

    for (counter1 = 0; counter1 < length; counter1++) {
        if (userData.username[counter1] >= 'A' && userData.username[counter1] <= 'Z') {
            userData.username[counter1] += 32;
        }
    }

    printf("Password: ");
    gets(userData.password);
    fflush(stdin);

    response = AdminVerification(userData);

    if (response == 404) {
        printf("Error!");
    }
    else if (response == 1) {
        printf("Successful");
    }
    else if (response == 0) {
        printf("Unsuccessful");
    }
}

int AdminVerification(struct AdminControl userData) {
    struct AdminControl userFromFile;
    FILE* pointer;
    int sizeFromFile, counter1, found = 0;

    pointer = fopen(adminFile, "rb");

    if (pointer == NULL) {
        return 404;
    }

    sizeFromFile = ArraySize(pointer, sizeof(struct AdminControl));

    for (counter1 = 0; counter1 < sizeFromFile; counter1++) {
        fread(&userFromFile, sizeof(struct AdminControl), 1, pointer);
        if (strcmp(userData.username, userFromFile.username) == 0) {
            found = 1;
            break;
        }
    }

    if (found == 0) {
        return 0;
    }

    fclose(pointer);

    if (strcmp(userData.password, userFromFile.password) == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

int ArraySize(FILE* pointer, int structSize) {
    int size;

    fseek(pointer, 0L, SEEK_END);
    size = ftell(pointer);
    size = size / structSize;
    fseek(pointer, 0L, SEEK_SET);

    return size;
}