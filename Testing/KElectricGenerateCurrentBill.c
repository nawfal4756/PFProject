#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

struct KElectricData {
    //New Structure
    unsigned long long int accountNumber;
    char name[30];
    char address[70];
    unsigned long long int contactNumber;
    char usageType;
    float allotedLoad;
    int numberOfTV;
    // 0 = off peak units, 1 = on peak units, 2 = amount of electricity, 3 = electricity duty, 4 = Sales Tax, 5 = Income tax, 6 = tv license fee, 7 = amount due, 8 = amount paid
    float unitsAndPayment[9][12];
    int billYear[12];
    bool timePayment[12];
    float total;
};

struct KElectricData KElectricGenerateCurrentBill(struct KElectricData userData);

int main() {

}

struct KElectricData KElectricGenerateCurrentBill(struct KElectricData userData) {
    time_t currentTime;
    struct tm* time1;
    int month;

    time(&currentTime);
    time1 = localtime(&currentTime);

    month = time1->tm_mon;

    printf("Enter the number of off peak units used: ");
    scan("%f", &userData.unitsAndPayment[0][month]);
    fflush(stdin);
    while(userData.unitsAndPayment[0][month] < 0) {
        printf("\nIncorrect value entered!\n");
        printf("Enter the number of off peak units used again: ");
        scan("%f", &userData.unitsAndPayment[0][month]);
        fflush(stdin);
    }

    printf("Enter the number of on peak units used: ");
    scan("%f", &userData.unitsAndPayment[1][month]);
    fflush(stdin);
    while(userData.unitsAndPayment[1][month] < 0) {
        printf("\nIncorrect value entered!\n");
        printf("Enter the number of on peak units used again: ");
        scan("%f", &userData.unitsAndPayment[1][month]);
        fflush(stdin);
    }

    // KElectricPriceCalculator(&userData, month);

    userData.billYear[month] = time1->tm_year + 1900;

    return userData;
}