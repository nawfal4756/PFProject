#include <stdio.h>

int main() {
    char userInput;

    printf("R - Residential, I - Industrial: ");
    scanf("%c", &userInput);
    fflush(stdin);
    usageType:
    while (userInput != 'R' && userInput != 'I') {
        printf("Incorrect option entered! Enter either R or I only\n");
        printf("R - Residential, I - Industrial again: ");
        scanf("%c", &userInput);
        fflush(stdin);
        goto usageType;
    }

    if (userInput == 'R' || userInput == 'I') {
        printf("\nTrue");
    }
    else {
        printf("\nFalse");
    }
}