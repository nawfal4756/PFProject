#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<time.h>

struct SSGCData {
    unsigned long long int consumerId;
    char name[30];
    char address[70];
    unsigned long long int contactNumber;
    float unitsAndPayment[2][12];
};

bool ContactNumberVerification(unsigned long long int number);
float BillCalculatorSSGC(float units);

int main() {
    struct SSGCData userData[100];
    int userLength, counter, counter2;
    float temp;

    printf("Enter number of records you want to enter: ");
    scanf("%d", &userLength);
    fflush(stdin);
    while (userLength < 0 || userLength >= 100) {
        printf("Incorrect value!\n");
        printf("Enter value between 1 and 99 inclusive\n");
        printf("Enter number of records you want to enter again: ");
        scanf("%d", &userLength);
        fflush(stdin);
    }

    for (counter = 0; counter < userLength; counter++) {
        printf("Enter consumer id of person %d: ", counter + 1);
        scanf("%llu", &userData[counter].consumerId);
        fflush(stdin);
        while (userData[counter].consumerId < 999999999 || userData[counter].consumerId > 10000000000) {
            printf("Incorrect value!\n");
            printf("Enter consumer id of person %d again: ", counter + 1);
            scanf("%llu", &userData[counter].consumerId);
            fflush(stdin);
        }

        printf("Enter name of person %d: ", counter + 1);
        scanf("%s", &userData[counter].name);
        fflush(stdin);

        printf("Enter address of person %d: ", counter + 1);
        scanf("%s", &userData[counter].address);
        fflush(stdin);

        printf("Enter contact number of person %d: ", counter + 1);
        scanf("%llu", &userData[counter].contactNumber);
        fflush(stdin);
        while (!ContactNumberVerification(userData[counter].contactNumber)) {
            printf("Incorrect value!\n");
            printf("Enter contact number of person %d again: ", counter + 1);
            scanf("%llu", &userData[counter].contactNumber);
            fflush(stdin);
        }

        
        for (counter2 = 0; counter2 < 12; counter2++) {
            srand(time(0));

            printf("Enter units for month %d: ", counter2 + 1);
            do {
                temp = rand();
            } while (temp < 25 || temp > 400);
            
            userData[counter].unitsAndPayment[0][counter2] = temp;
            printf("%f", userData[counter].unitsAndPayment[0][counter2]);

            printf("Enter amount paid for month %d: ", counter2 + 1);
            scanf("%d", &userData[counter].unitsAndPayment[1][counter2]);
            fflush(stdin);
        }
        
    }
}

bool ContactNumberVerification(unsigned long long int number) {
    if (number / 10000000000 == 3) {
        if (number >= 3000000000 && number <= 39999999999) {
            return true;
        }
    }

    return false;
}