#include <stdio.h>
#include <string.h>

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

int Payment(float amount);

int main() {
    Payment(252.25);
}

int Payment(float amount) {
    struct CreditCard data;
    int length, counter1, response;

    printf("\t\t\t\t\t\t\tPayment\n");
    printf("--------------------------------------------------------------------------------------------------------------------\n\n");

    printf("Enter Card Number: ");
    scanf("%llu", data.cardNumber);
    fflush(stdin);
    while (data.cardNumber < 1000000000000000 || data.cardNumber > 9999999999999999) {
        printf("Incorrect Card Number\n");
        printf("Enter Card Number Again: ");
        scanf("%llu", data.cardNumber);
        fflush(stdin);
    }

    printf("Enter Card Holder Name: ");
    gets(data.name);
    fflush(stdin);

    printf("Enter Card Expiry Month (mm): ");
    scanf("%d", data.expiryDate.month);
    fflush(stdin);
    while (data.expiryDate.month < 1 || data.expiryDate.month > 12) {
        printf("Incorrect Month Entered!\n");
        printf("Enter Card Expiry Month Again (mm): ");
        scanf("%d", data.expiryDate.month);
        fflush(stdin);
    }

    printf("Enter Card Expiry Year (yyyy): ");
    scanf("%d", data.expiryDate.year);
    fflush(stdin);
    while (data.expiryDate.year < 1000 || data.expiryDate.year > 9999) {
        printf("Incorrect Year Entered!\n");
        printf("Enter Card Expiry Year Again (yyyy): ");
        scanf("%d", data.expiryDate.year);
        fflush(stdin);
    }

    printf("Enter Card CVC: ");
    scanf("%d", data.cvc);
    fflush(stdin);
    while (data.cvc < 100 || data.cvc > 999) {
        printf("Incorrect CVC Entered!\n");
        printf("Enter Card CVC: ");
        scanf("%d", data.cvc);
        fflush(stdin);
    } 

    length = strlen(data.name);
    for(counter1 = 0; counter1 < length; counter1++) {
        if (data.name[counter1] >= 'A' && data.name[counter1] <= 'Z') {
            data.name[counter1] += 32;
        }
    }

    // response = CreditCardVerificationFunction;

    if (response == 1) {
        return 1;
    }
    else if (response == 0) {
        return 0;
    }
    else {
        return 404;
    }
    
}