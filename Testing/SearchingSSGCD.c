#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>

char* SSGCfile = "..\\DataFiles\\SSGCData.txt";

struct SSGCData {
    unsigned long long int consumerId;
    char name[30];
    char address[70];
    unsigned long long int contactNumber;
    char usageType;
    // 0 = units, 1 = amount os natural gas used, 2 = Sales Tax, 3 = Income Tax, 4 = amount due, 5 = amount paid
    float unitsAndPayment[6][12];
};

int ArraySize(FILE* pointer, int structSize);
struct SSGCData SearchSSGCID(unsigned long long int id);

int main() {
    unsigned long long int consumerId;
    struct SSGCData data;

    printf("Enter the consumer ID: ");
    scanf("%llu", &consumerId);

    data = SearchSSGCID(consumerId);
    printf("\n\n");

    printf("Name: ");
    puts(data.name);
    printf("Address: %s\n", data.address);
    printf("Consumer ID: %llu\n", data.consumerId);
    printf("\nPress enter to continue...");
    getch();
}

struct SSGCData SearchSSGCID(unsigned long long int id) {
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