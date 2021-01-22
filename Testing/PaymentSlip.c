#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void PaymentSlip(float amount, char company, unsigned long long int id);

int main() {
    PaymentSlip(252.25, 'K', 1234567113);
}

void PaymentSlip(float amount, char company, unsigned long long int id) {
    FILE* pointer;
    char consumerId[15], companyName[50], monthYear[50], fileName[70] = "PaymentSlip-";
    time_t currentTime;
    struct tm* time1;

    time(&currentTime);
    time1 = localtime(&currentTime);

    snprintf(monthYear, sizeof(monthYear), "%d/%d", time1->tm_mon + 1, time1->tm_year + 1900);
    snprintf(consumerId, sizeof(consumerId), "%llu", id);

    switch (company) {
        case 'K': {
            strcpy(companyName, "KElectric-");
            break;
        }

        case 'S': {
            strcpy(companyName, "SSGC-");
            break;
        }

        case 'P': {
            strcpy(companyName, "PTCL-");
            break;
        }
    }

    strcat(fileName, companyName);
    strcat(fileName, consumerId);
    strcat(fileName, "-");
    strcat(fileName, monthYear);
    strcat(fileName, ".txt");

    pointer = fopen(fileName, "w");
    
    fprintf(pointer, "\t\t\t\t\t\t\tPayment\n");
    fprintf(pointer, "--------------------------------------------------------------------------------------------------------------------\n\n");
    fprintf(pointer, "Payment against ID: %llu\n", id);
    fprintf(pointer, "Payment made on: %s\n", monthYear);
    fprintf(pointer, "Payment to %s\n", companyName);
    fprintf(pointer, "Payment amount: %.2f\n", amount);
    fprintf(pointer, "Payment made from Cedit Card");

    fclose(pointer);
    
}