#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE* pointer;

    pointer = fopen("PaymentSlip-KElectric-1234567113-1/2021.txt", "w");

    if (pointer == NULL) {
        printf("Error");
    }

    fclose(pointer);
}