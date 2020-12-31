#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
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
int CreditCardVerification(struct CreditCard data);

int main() {
    int counter1, resposne, length;
    struct CreditCard data;    

    printf("Enter credit card number: ");
    scanf("%llu", &data.cardNumber);
    fflush(stdin);

    printf("Enter name of card holder: ");
    gets(data.name);
    fflush(stdin);

    length = strlen(data.name);
    for (counter1 = 0; counter1 < length; counter1++) {
        if (data.name[counter1] >= 'A' && data.name[counter1] <= 'Z') {
            data.name[counter1] += 32;
        }
    }

    printf("Enter expiry date month: ");
    scanf("%d", &data.expiryDate.month);
    fflush(stdin);

    printf("Enter expiry date year: ");
    scanf("%d", &data.expiryDate.year);
    fflush(stdin);

    printf("Enter cvc: ");
    scanf("%d", &data.cvc);
    fflush(stdin);

    printf("\n\n");

    resposne = CreditCardVerification(data);
    if (resposne == 1) {
        printf("Verified");
    }
    else if (resposne == 0) {
        printf("Not verified");
    }
    else if (resposne == -1) {
        printf("Error");
    }

    printf("\n\n");
    printf("Press enter to conitnue...");
    getch();
}

int CreditCardVerification(struct CreditCard data) {
    time_t currentTime;
    struct tm* time1;
    struct CreditCard originalData;
    FILE* pointer;
    int sizeFromFile, counter1 = 0, found = 0;

    // 1 = Verified, 0 = Not Verified, 404 = Error
    
    pointer = fopen("CreditCardData.txt", "rb");

    if (pointer == NULL) {
        return 404;
    }
    
    sizeFromFile = ArraySize(pointer, sizeof(struct CreditCard));

    while (counter1 < sizeFromFile) {
        fread(&originalData, sizeof(struct CreditCard), 1, pointer);
        if (originalData.cardNumber == data.cardNumber) {
            found = 1;
            break;
        }
        counter1++;
    }    

    if (found == 0) {
        return 0;
    }

    time(&currentTime);
    time1 = localtime(&currentTime);

    if (time1->tm_year + 1900 > data.expiryDate.year) {
        return 0;
    }
    
    if (time1->tm_year + 1900 == data.expiryDate.year) {
        if (time1->tm_mon + 1 >= data.expiryDate.month) {
            return 0;
        }
    }    

    if (originalData.expiryDate.month == data.expiryDate.month && originalData.expiryDate.year == data.expiryDate.year) {
        if (strcmp(originalData.name, data.name) == 0) {        
            if (originalData.cvc == data.cvc) {
                return 1;
            }
        }
    }
    
    return 0;
}

int ArraySize(FILE* pointer, int structSize) {
    int size;

    fseek(pointer, 0L, SEEK_END);
    size = ftell(pointer);
    size = size / structSize;
    fseek(pointer, 0L, SEEK_SET);

    return size;
}