#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>

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

int SSGCRecordUpdate(struct SSGCData dataNew);

int ArraySize(FILE* pointer, int structSize);

int main() {
    struct SSGCData data;
    int response;

    printf("Consumer ID: ");
    scanf("%llu", &data.consumerId);
    fflush(stdin);

    printf("Name: ");
    gets(data.name);

    response = SSGCRecordUpdate(data);

    if (response == 404) {
        printf("Error");
    }
    else if (response = 1) {
        printf("Successful");
    }

    getch();
}

int SSGCRecordUpdate(struct SSGCData dataNew) {
    struct SSGCData dataFromFile;
    FILE* pointer;
    int counter1, sizeFromFile, size, found = 0;

    pointer = fopen("../DataFiles/SSGCData.txt", "rb+");

    if (pointer == NULL) {
        return 404;
    }

    sizeFromFile = ArraySize(pointer, sizeof(struct SSGCData));    

    for (counter1 = 0; counter1 < sizeFromFile; counter1) {
        fread(&dataFromFile, sizeof(struct SSGCData), 1, pointer);
        if (dataFromFile.consumerId == dataNew.consumerId) {
            found = 1;
            break;
        }
    }

    if (found == 0) {
        return 404;
    }

    fseek(pointer, -(sizeof(struct SSGCData)), SEEK_CUR);
    fseek(pointer, 0L, SEEK_CUR);

    fwrite(&dataNew, sizeof(struct SSGCData), 1, pointer);

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