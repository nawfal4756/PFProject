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

int SSGCAddCustomer();
int ArraySize(FILE* pointer, int structSize);

char* ssgcFile = "../DataFiles/SSGCData.txt";

int main() {

}

int SSGCAddCustomer() {
    struct SSGCData userData, userDataFile;
    FILE* pointer;
    int sizeFromFile, month, counter1, counter2;
    time_t currentTime;
    struct tm* time1;

    time(&currentTime);
    time1 = localtime(&currentTime);

    month = time1->tm_mon;

    pointer = fopen(ssgcFile, "ab+");

    if (pointer == NULL) {
        return 404;
    }

    for (counter1 = 0; counter1 < 6; counter1++) {
        for (counter2 = 0; counter2 < 12; counter2++) {
            userData.unitsAndPayment[counter1][counter2] = 0;
        }
    }

    for (counter1 = 0; counter1 < 12; counter1++) {
        userData.billYear[counter1] = 0;        
    }

    sizeFromFile = ArraySize(pointer, sizeof(struct SSGCData));

    consumerID:
    printf("Enter consumer ID of customer: ");
    scanf("%llu", &userData.consumerId);
    fflush(stdin);
    while (!SSGCConsumerIDVerification(userData.consumerId)) {
        printf("Incorrect value!\n");
        printf("Enter account number of customer again: ");
        scanf("%llu", &userData.consumerId);
        fflush(stdin);
    }
    
    for (counter1 = 0; counter1 < sizeFromFile; counter1++) {
        fread(&userDataFile, sizeof(struct SSGCData), 1, pointer);
        if(userData.consumerId == userDataFile.consumerId) {
            printf("\nUser already exist with this consumer ID. Enter another ID\n");
            goto consumerID;
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
        printf("Incorrect value!\n");
        printf("Enter contact number of customer again: ");
        scanf("%llu", &userData.contactNumber);
        fflush(stdin);
    }

    printf("Enter usage type (R - Residential, I - Industrial): ");
    scanf("%c", &userData.usageType);
    fflush(stdin);
    while (userData.usageType != 'R' && userData.usageType != 'I' && userData.usageType != 'r' && userData.usageType != 'i') {
        printf("Incorrect option entered! Enter either R or I only\n");
        printf("Enter usage type (R - Residential, I - Industrial) again: ");
        scanf("%c", &userData.usageType);
        fflush(stdin);
    }

    if (userData.usageType == 'r') {
        userData.usageType = 'R';
    }

    if (userData.usageType == 'i') {
        userData.usageType = 'I';
    }

    printf("Enter number of units used: ");
    scanf("%f", &userData.unitsAndPayment[0][month]);
    fflush(stdin);
    while(userData.unitsAndPayment[0][month] < 0) {
        printf("Incorrect amount entered!\n");
        printf("Enter number of units used again: ");
        scanf("%f", &userData.unitsAndPayment[0][month]);
        fflush(stdin);
    }

    // Price Function Call

    userData.billYear[month] = time1->tm_year + 1900;
    userData.total = userData.unitsAndPayment[4][month];

    fwrite(&userData, sizeof(struct SSGCData), 1, pointer);
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