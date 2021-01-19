#include <stdio.h>
#include <string.h>
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

int KElectricAddCustomer();
int ArraySize(FILE* pointer, int structSize);

char* keFile = "../DataFiles/KElectricData.c";

int main() {
    
}

int KElectricAddCustomer() {
    struct KElectricData userData, userDataFile;
    FILE* pointer;
    int sizeFromFile, month, counter1, counter2;
    time_t currentTime;
    struct tm* time1;

    time(&currentTime);
    time1 = localtime(&currentTime);

    month = time1->tm_mon;

    pointer = fopen(keFile, "ab+");

    if (pointer == NULL) {
        return 404;
    }

    for (counter1 = 0; counter1 < 9; counter1++) {
        for (counter2 = 0; counter2 < 12; counter2++) {
            userData.unitsAndPayment[counter1][counter2] = 0;
        }
    }

    for (counter1 = 0; counter1 < 12; counter1++) {
        userData.billYear[counter1] = 0;
        userData.timePayment[counter1] = false;
    }

    sizeFromFile = ArraySize(pointer, sizeof(struct KElectricData));

    accountNumber:
    printf("Enter account number of customer: ");
    scanf("%llu", &userData.accountNumber);
    fflush(stdin);
    while (!KElectricAccountNumberVerification(userData.accountNumber)) {
        printf("\nIncorrect value!\n");
        printf("Enter account number of customer again: ");
        scanf("%llu", &userData.accountNumber);
        fflush(stdin);
    }
    
    for (counter1 = 0; counter1 < sizeFromFile; counter1++) {
        fread(&userDataFile, sizeof(struct KElectricData), 1, pointer);
        if(userData.accountNumber == userDataFile.accountNumber) {
            printf("\nUser already exist with this aacount number. Enter another ID\n");
            goto accountNumber;
        }
    }
    
    fseek(pointer, 0L, SEEK_END);

    printf("Enter name of customer: ");
    gets(userData.name);
    fflush(stdin);

    printf("Enter address of customer: ");
    gets(userData.address);
    fflush(stdin);

    printf("Enter contact number of customer: ");
    scanf("%llu", &userData.contactNumber);
    fflush(stdin);
    while (!ContactNumberVerification(userData.contactNumber)) {
        printf("\nIncorrect value!\n");
        printf("Enter contact number of customer again: ");
        scanf("%llu", &userData.contactNumber);
        fflush(stdin);
    }

    printf("Enter usage type of customer (R - Residential, C - Commercial): ");
    scanf("%c", &userData.usageType);
    fflush(stdin);
    while (userData.usageType != 'R' && userData.usageType != 'C' && userData.usageType != 'r' && userData.usageType != 'c') {
        printf("\nIncorrect value!\n");
        printf("Enter usage type of customer again (R - Residential, C - Commercial): ");
        scanf("%c", &userData.usageType);
        fflush(stdin);
    }

    if (userData.usageType == 'r') {
        userData.usageType = 'R';
    }
    else if (userData.usageType == 'c') {
        userData.usageType = 'C';
    }

    printf("Enter alloted load of customer: ");
    scanf("%f", &userData.allotedLoad);
    fflush(stdin);
    while (userData.allotedLoad <= 0) {
        printf("\nIncorrect amount!\n");
        printf("Enter alloted load of customer again: ");
        scanf("%f", &userData.allotedLoad);
        fflush(stdin);
    }

    printf("Enter number of TV's for customer: ");
    scanf("%d", &userData.numberOfTV);
    fflush(stdin);
    while (userData.numberOfTV <= 0) {
        printf("\nIncorrect amount of TVs!\n");
        printf("Enter number of TV's for customer again: ");
        scanf("%d", &userData.numberOfTV);
        fflush(stdin);
    }

    printf("Enter number of units used in off peak timing: ");
    scanf("%f", &userData.unitsAndPayment[0][month]);
    fflush(stdin);
    while (userData.unitsAndPayment[0][month] < 0) {
        printf("\nIncorrect value!\n");
        printf("Enter number of units used in off peak timing again: ");
        scanf("%f", &userData.unitsAndPayment[0][month]);
        fflush(stdin);
    }

    printf("Enter number of units used in on peak timing: ");
    scanf("%f", &userData.unitsAndPayment[1][month]);
    fflush(stdin);
    while (userData.unitsAndPayment[1][month] < 0) {
        printf("\nIncorrect value!\n");
        printf("Enter number of units used in on peak timing again: ");
        scanf("%f", &userData.unitsAndPayment[1][month]);
        fflush(stdin);
    }

    KElectricPriceCalculator();

    userData.billYear[month] = time1->tm_year + 1900;
    userData.total = userData.unitsAndPayment[7][month];

    fwrite(&userData, sizeof(struct KElectricData), 1, pointer);

    fclose(pointer);
    return 1;
}

int ArraySize(FILE* pointer, int structSize) {
    int size;

    fseek(pointer, 0L, SEEK_END);
    size = ftell(pointer);
    size = size / structSize;
    fseek(pointer, 0L, SEEK_SET);

    return size;
}