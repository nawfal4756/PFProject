#include <stdio.h>
#include <stdbool.h>

bool KElectricAccountNumberVerification(unsigned long long int accountNumber);

int main() {
    unsigned long long int accountNumber;

    printf("Enter consumer id: ");
    scanf("%llu", &accountNumber);

    if(KElectricAccountNumberVerification(accountNumber)) {
        printf("True");
    }
    else {
        printf("False");
    }

}

bool KElectricAccountNumberVerification(unsigned long long int accountNumber) {
    if (accountNumber >= 10000000000 && accountNumber <= 99999999999) {
        return true;
    }
    else {
        return false;
    }
}