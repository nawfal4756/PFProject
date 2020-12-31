#include<stdbool.h>
#include <stdlib.h>
#include <string.h>
#include<stdio.h>

char* SSGCfile = "..\\DataFiles\\SSGCData.txt";

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

int ArraySize(FILE* pointer, int structSize);
void SSGCBillPreview(struct SSGCData SSGC);
struct SSGCData SSGCIDSearch(unsigned long long int id);

int main()
{
    unsigned long long int consumerId;
    struct SSGCData data;

    printf("Enter the account number: ");
    scanf("%llu", &consumerId);

    data = SSGCIDSearch(consumerId);
    SSGCBillPreview(data);
}

void SSGCBillPreview(struct SSGCData SSGC)
{
    int counter2,counter3,counter;
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\tSui Southern Gas Company Limited\t\t\n");
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    printf("Name: ");
    puts(SSGC.name);
    printf("Address: %s\n", SSGC.address);
    printf("Consumer ID: %llu\n", SSGC.consumerId);
    printf("Contact number: %llu\n",SSGC.contactNumber);
    printf("Usage type: %s\n", SSGC.usageType == 'R' ? "Residential" : "Commercial");
    printf("Total Bill: %.2f",SSGC.total);
    printf("\n");
    printf("------------------------------------------------------------------------------------------------------------------\n");
    printf("%13s%14s%14s%10s%14s%13s","Month/","Units","Bill Without","Sales","Income","Amount");
    printf("%15s\n","Amount");
    printf("%11s%15s%10s%14s%13s%13s%16s\n","Year","Used","Tax","Tax","Tax","Due","Paid");
    printf("------------------------------------------------------------------------------------------------------------------\n");
    for (counter2 = 0; counter2 < 12; counter2++) {
        switch(counter2)
        {
            case 0:
            printf("%11s %d","January",SSGC.billYear[counter2]);
            break;

            case 1:
            printf("%11s %d","February",SSGC.billYear[counter2]);
            break;

            case 2:
            printf("%11s %d","March",SSGC.billYear[counter2]);
            break;

            case 3:
            printf("%11s %d","April",SSGC.billYear[counter2]);
            break;

            case 4:
            printf("%11s %d","May",SSGC.billYear[counter2]);
            break;

            case 5:
            printf("%11s %d","June",SSGC.billYear[counter2]);
            break;

            case 6:
            printf("%11s %d","July",SSGC.billYear[counter2]);
            break;

            case 7:
            printf("%11s %d","August",SSGC.billYear[counter2]);
            break;

            case 8:
            printf("%11s %d","September",SSGC.billYear[counter2]);
            break;

            case 9:
            printf("%11s %d","October",SSGC.billYear[counter2]);
            break;

            case 10:
            printf("%11s %d","November",SSGC.billYear[counter2]);
            break;

            case 11:
            printf("%11s %d","December",SSGC.billYear[counter2]);
            break;
        }
        for (counter3 = 0; counter3 < 6; counter3++) {
            switch(counter3){
                case 0:
                printf("%11.2f", SSGC.unitsAndPayment[counter3][counter2]);
                break;

                case 1:
                printf("%11.2f   ", SSGC.unitsAndPayment[counter3][counter2]);
                break;

                case 2:
                printf("%11.2f   ", SSGC.unitsAndPayment[counter3][counter2]);
                break;

                case 3:
                printf("%11.2f   ", SSGC.unitsAndPayment[counter3][counter2]);
                break;

                case 4:
                printf("%11.2f   ", SSGC.unitsAndPayment[counter3][counter2]);
                break;

                case 5:
                printf("%11.2f   ", SSGC.unitsAndPayment[counter3][counter2]);
                break;
            }
            
        }
        printf("\n");
    }
    printf("------------------------------------------------------------------------------------------------------------------\n");
    printf("\nPress enter to continue...");
    getch();
}

struct SSGCData SSGCIDSearch(unsigned long long int id) {
    // 0 = Not Found, 404 = Error
    
    FILE* pointer;
    struct SSGCData data;
    int sizeFromFile, counter1 = 0, found = 0;

    pointer = fopen(SSGCfile, "rb");

    if (pointer == NULL) {
        printf("Data Null");
        data.consumerId = 404;
        return data;
    }

    sizeFromFile = ArraySize(pointer, sizeof(struct SSGCData));

    while (counter1 < sizeFromFile) {
        fread(&data, sizeof (struct SSGCData), 1, pointer);
        if (data.consumerId == id) {
            found = 1;
            break;
        }
        counter1++;
    }

    if (found == 0) {
        data.consumerId = 0;
    }

    return data;
}

int ArraySize(FILE* pointer, int structSize) {
    int size;

    fseek(pointer, 0L, SEEK_END);
    size = ftell(pointer);
    size = size / structSize;
    fseek(pointer, 0L, SEEK_SET);

    return size;
}