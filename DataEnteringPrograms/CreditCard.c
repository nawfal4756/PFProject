#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    struct CreditCard data;
    int counter1, counter2, length, sizeFromFile, userInput;
    FILE* pointer;

    pointer = fopen("CreditCardData.txt", "rb");
    if (pointer == NULL) {
        fclose(pointer);
        pointer = fopen("CreditCardData.txt", "ab");
        fclose(pointer);
        pointer = fopen("CreditCardData.txt", "rb");
        if (pointer == NULL) {
            printf("Error Opening file! Closing program.\nPress enter to continue...");
            getch();
            exit(1);
        }
    }

    sizeFromFile = ArraySize(pointer, sizeof(struct CreditCard));
    fclose(pointer);

    pointer = fopen("CreditCardData.txt", "ab");
    if (pointer == NULL) {
        printf("Error Opening file! Closing program.\nPress enter to continue...");
        getch();
        exit(1);
    }

    
    printf("How many data entries do you want to add?\n");
    scanf("%d", &userInput);
    fflush(stdin);
    while (userInput <= 0 || userInput > 5) {
        printf("Incorrect amount entered! Enter between 1 and 5\n");
        printf("How many data entries do you want to add again?\n");
        scanf("%d", &userInput);
        fflush(stdin);
    }

    for (counter1 = sizeFromFile; counter1 < userInput + sizeFromFile; counter1++) {
        printf("Enter Credit Card Number %d: ", counter1 + 1);
        scanf("%llu", &data.cardNumber);
        fflush(stdin);
        while (data.cardNumber < 100000000000 || data.cardNumber > 999999999999) {
            printf("Incorrect numbern\n");
            printf("Enter Credit Card Number %d again: ", counter1 + 1);
            scanf("%llu", &data.cardNumber);
            fflush(stdin);
        }
        
        printf("Enter card holder name %d: ", counter1 + 1);
        gets(data.name);
        fflush(stdin);

        length = strlen(data.name);
        for (counter2 = 0; counter2 < length; counter2++) {
            if (data.name[counter2] >= 'A' && data.name[counter2] <= 'Z') {
                data.name[counter2] += 32;
            }
        }

        printf("Enter expiry date month (mm) of card %d: ", counter1 + 1);
        scanf("%d", &data.expiryDate.month);
        fflush(stdin);
        while (data.expiryDate.month < 1 || data.expiryDate.month > 12) {
            printf("Incorrect month entered!\n");
            printf("Enter expiry date month (mm) of card %d again: ", counter1 + 1);
            scanf("%d", &data.expiryDate.month);
            fflush(stdin);
        }

        printf("Enter expiry date year (yyyy) of card %d: ", counter1 + 1);
        scanf("%d", &data.expiryDate.year);
        fflush(stdin);
        while (data.expiryDate.year < 2019 || data.expiryDate.year > 2030) {
            printf("Incorrect year entered!\n");
            printf("Enter expiry date year (yyyy) of card %d again: ", counter1 + 1);
            scanf("%d", &data.expiryDate.year);
            fflush(stdin);
        }

        printf("Enter cvc of card %d: ", counter1 + 1);
        scanf("%d", &data.cvc);
        fflush(stdin);
        while (data.cvc < 100 || data.cvc > 999) {
            printf("Incorrect cvc code entered!\n");
            printf("Enter cvc of card %d: ", counter1 + 1);
            scanf("%d", &data.cvc);
            fflush(stdin);
        } 

        printf("\n\n");

        fwrite(&data, sizeof(struct CreditCard), 1, pointer);
    }

    fclose(pointer);
    printf("\n\nData entered successfully\nPress enter to continue...");
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