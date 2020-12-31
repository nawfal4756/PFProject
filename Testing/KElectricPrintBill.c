#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>

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

int KElectricPrintBill(struct KElectricData data);

int main() {
    struct KElectricData data;
    data.accountNumber = 2534567898;
    KElectricPrintBill(data);
}

int KElectricPrintBill(struct KElectricData data) {
    FILE* pointer;
    char accountNumber[15], fileName[50] = "KElectricBill-";    

    snprintf(accountNumber, sizeof(accountNumber), "%llu", data.accountNumber);
    strcat(fileName, accountNumber);
    strcat(fileName, ".txt");

    pointer = fopen(fileName, "w");

    if (pointer == NULL) {
        return 404;
    }

    fprintf(pointer, "Account Number: %llu\n", data.accountNumber);
    fprintf(pointer, "Name: %s\n", data.name);
    fprintf(pointer, "Address: %s\n", data.address);
    fprintf(pointer, "Contact Number: %llu\n", data.contactNumber);

    // if (StarConsumerFunction) {
    //     printf("\nYou are a star consumer!\n\n");
    // }

    fprintf(pointer, "Usage Type: %s\n", data.usageType == 'R' ? "Residential" : "Commercial");
    fprintf(pointer, "Alloted Load %.2f\n", data.allotedLoad);
    fprintf(pointer, "Number of Tvs: %d\n", data.numberOfTV);

    



}