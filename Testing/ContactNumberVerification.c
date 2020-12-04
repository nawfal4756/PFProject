#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int ContactNumberVerification(unsigned long long int number);

int main() {
    unsigned long long int phoneNumber;
    int answer;

    printf("Enter a number: ");
    scanf("%llu", &phoneNumber);

    answer = ContactNumberVerification(phoneNumber);
    printf("%d", answer);

    // if (ContactNumberVerification(phoneNumber)) {
    //     printf("1");
    // }
    // else {
    //     printf("0");
    // }
}

int ContactNumberVerification(unsigned long long int number) {
    int temp;
    temp = number / 10000000000;
    printf("%d", temp);
    if (temp == 3) {
        return 1;
        if (number >= 3000000000 && number <= 39999999999) {
            return 1;
        }
    }

    return 0;
}