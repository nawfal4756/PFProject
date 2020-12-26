#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct CardDate {
    int month;
    int year;
};

struct CreditCard {
    unsigned long long int cardNumber;
    char name[30];
    struct CardDate expiryDate;
    int cvc;
};

int ArraySize(FILE* pointer, int structSize);

int main() {
    int counter1, sizeFromFile;
    struct CreditCard data;
    FILE* pointer;

    pointer = fopen("CreditCardData.txt", "rb");
    if (pointer == NULL) {
        printf("Cannot open file or file does not exist! Exiting Program...\nPress enter to continue...");
        getch();
        exit(1);
    }

    sizeFromFile = ArraySize(pointer, sizeof(struct CreditCard));

    for (counter1 = 0; counter1 < sizeFromFile; counter1++) {
        fread(&data, sizeof(struct CreditCard), 1, pointer);

        printf("Credit Card Number %d: %llu\n", counter1 + 1, data.cardNumber);
        printf("Name on card %d: ", counter1 + 1);
        puts(data.name);
        printf("Expiry date on card %d: %d/%d\n", counter1 + 1, data.expiryDate.month, data.expiryDate.year);
        printf("CVC of card %d: %d", counter1 + 1, data.cvc);

        printf("\n\n");
    }

    fclose(pointer);

    printf("Press enter to continue...");
    getch();
}

int ArraySize(FILE* pointer, int structSize) {
    int size;

    fseek(pointer, 0L, SEEK_END);
    size = ftell(pointer);
    size = size / structSize;
    fseek(pointer, 0L, SEEK_SET);

    return size;
}