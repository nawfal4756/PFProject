#include <stdio.h>
#include <stdlib.h>

struct AdminControl {
    char username[40];
    char password[40];
};

char* adminFile = "../DataFiles/AdminFile.txt";

int main() {
    FILE* pointer;
    struct AdminControl userData;

    pointer = fopen(adminFile, "ab");

    printf("Enter the username: ");
    gets(userData.username);
    fflush(stdin);

    printf("Enter the password for %s: ", userData.username);
    gets(userData.password);
    fflush(stdin);

    fwrite(&userData, sizeof(struct AdminControl), 1, pointer);
    fclose(pointer);

    printf("\n\nUsername: %s\n", userData.username);
    printf("Password: %s", userData.password);
}