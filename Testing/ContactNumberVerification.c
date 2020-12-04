#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool ContactNumberVerification(unsigned long long int number);

int main() {
    unsigned long long int phoneNumber;
    int answer;

    printf("Enter a number: ");
    scanf("%llu", &phoneNumber);

    // answer = ContactNumberVerification(phoneNumber);
    // printf("%d", answer);

    if (ContactNumberVerification(phoneNumber)) {
        printf("1");
    }
    else {
        printf("0");
    }
}

bool ContactNumberVerification(unsigned long long int number) {
    int temp;
    temp = number / 1000000000;
    
    if (temp == 3) {        
        if (number >= 3000000000 && number <= 39999999999) {
            return true;
        }
    }

    return false;
}