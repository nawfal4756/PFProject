#include <stdio.h>
#include <stdbool.h>

bool PTCLAccountIDVerification(unsigned long long int accountID);

int main() {
    unsigned long long int accountID;

    printf("Enter the account ID: ");
    scanf("%llu", &accountID);

    printf("\n");
    if (PTCLAccountIDVerification(accountID)) {
        printf("True");
    }
    else {
        printf("False");
    }

}

bool PTCLAccountIDVerification(unsigned long long int accountID) {
    if (accountID >= 1000000000 && accountID <= 9999999999) {
        return true;
    }
    else {
        return false;
    }
}