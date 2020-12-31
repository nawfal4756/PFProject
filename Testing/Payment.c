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

    printf("Enter Card Holder Name: ");
    gets(data.name);

    printf("Enter Card Expiry Month (mm): ");
    scanf("%d", data.expiryDate.month);

    printf("Enter Card Expiry Year (yyyy): ");
    scanf("%d", data.expiryDate.year);

    printf("Enter Card CVC: ");
    scanf("%d", data.cvc);

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