#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>

char* kefile = "..\\DataFiles\\KElectricData.txt";

struct KElectricData {
    unsigned long long int accountNumber;
    char name[30];
    char address[70];
    unsigned long long int contactNumber;
    char usageType;
    float allotedLoad;
    int numberOfTV;
    // 0 = off peak units, 1 = on peak units, 2 = amount of electricity, 3 = electricity duty, 4 = Sales Tax, 5 = Income tax, 6 = tv license fee, 7 = amount due, 8 = amount paid
    float unitsAndPayment[9][12];
    bool timePayment[12];
};

int ArraySize(FILE* pointer, int structSize);
struct KElectricData KElectricIDSearch(unsigned long long int id);

int main() {
    unsigned long long int accountNumber;
    struct KElectricData data;

    printf("Enter the account number: ");
    scanf("%llu", &accountNumber);

    data = KElectricIDSearch(accountNumber);
    printf("\n\n");

    printf("Name: ");
    puts(data.name);
    printf("Address: %s\n", data.address);
    printf("Account number: %llu\n", data.accountNumber);
    printf("\nPress enter to continue...");
    getch();
}

struct KElectricData KElectricIDSearch(unsigned long long int id) {
    // 0 = Not Found, 404 = Error
    
    FILE* pointer;
    struct KElectricData data;
    int sizeFromFile, counter1 = 0, found = 0;

    pointer = fopen(kefile, "rb");

    if (pointer == NULL) {
        printf("Data Null");
        data.accountNumber = 404;
        return data;
    }

    sizeFromFile = ArraySize(pointer, sizeof(struct KElectricData));

    while (counter1 < sizeFromFile) {
        fread(&data, sizeof (struct KElectricData), 1, pointer);
        if (data.accountNumber == id) {
            found = 1;
            break;
        }
        counter1++;
    }

    if (found == 0) {
        data.accountNumber = 0;
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