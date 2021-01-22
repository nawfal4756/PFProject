#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct SSGCData {
    // New Structure
    unsigned long long int consumerId;
    char name[30];
    char address[70];
    unsigned long long int contactNumber;
    char usageType;
    // 0 = units, 1 = amount os natural gas used, 2 = Sales Tax, 3 = Income Tax, 4 = amount due, 5 = amount paid
    float unitsAndPayment[6][12];
    int billYear[12];
    float total;
};

struct SSGCData SSGCGenerateCurrentBill(struct SSGCData userData);

int main() {

}

struct SSGCData SSGCGenerateCurrentBill(struct SSGCData userData) {
    time_t currentTime;
    struct tm* time1;
    int month;

    time(&currentTime);
    time1 = localtime(&currentTime);

    month = time1->tm_mon;

    printf("Enter the number of units used: ");
    scan("%f", &userData.unitsAndPayment[0][month]);
    fflush(stdin);
    while(userData.unitsAndPayment[0][month] < 0) {
        printf("\nIncorrect value entered!\n");
        printf("Enter the number of units used again: ");
        scan("%f", &userData.unitsAndPayment[0][month]);
        fflush(stdin);
    }

    // SSGCPriceCalculator(&userData, month);

    userData.billYear[month] = time1->tm_year + 1900;

    return userData;
}