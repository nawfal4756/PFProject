#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct AdminControl {
    char username[40];
    char password[40];
};

char* adminFile = "../DataFiles/AdminFile.txt";

int ArraySize(FILE* pointer, int structSize);

int main() {
    int sizeFromFile, counter1;
    FILE* pointer;
    struct AdminControl userData;

    pointer = fopen(adminFile, "rb");

    if (pointer == NULL) {
        exit(1);
    }

    sizeFromFile = ArraySize(pointer, sizeof(struct AdminControl));

    for (counter1 = 0; counter1 < sizeFromFile; counter1++) {
        fread(&userData, sizeof(struct AdminControl), 1, pointer);
        printf("Username: %s\n", userData.username);
        printf("Password: %s\n\n", userData.password);
    }

    fclose(pointer);
}

int ArraySize(FILE* pointer, int structSize) {
    int size;

    fseek(pointer, 0L, SEEK_END);
    size = ftell(pointer);
    size = size / structSize;
    fseek(pointer, 0L, SEEK_SET);

    return size;
}