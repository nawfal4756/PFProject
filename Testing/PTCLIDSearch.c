#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>

char* PTCLfile = "..\\DataFiles\\PTCLData.txt";

struct PTCLData {
    unsigned long long int accountID;
    char name[30];
    char address[70];
    unsigned long long int contactNumber;
    int packageLandline;
    int packageBroadband;
    char packageTV;
    char packageCharji;
    int onNetMinutes[12];
    int mobileMinutes[12];
    int otherMinutes[12];
    int internationalZone1Minutes[12];
    int internationalOtherZoneMinutes[12];
    // 0 = bill of PTCL, 1 = Service Tax, 2 = Withholding Tax, 3 = Late Payment Surcgarge, 4 = Total Bill, 5 = Recieved Payment
    float payments[6][12];
};

int ArraySize(FILE* pointer, int structSize);
struct PTCLData PTCLIDSearch(unsigned long long int id);

int main() {
    unsigned long long int accountID;
    struct PTCLData data;

    printf("Enter the account ID: ");
    scanf("%llu", &accountID);

    data = PTCLIDSearch(accountID);
    printf("\n\n");

    printf("Name: ");
    puts(data.name);
    printf("Address: %s\n", data.address);
    printf("Account ID: %llu\n", data.accountID);
    printf("\nPress enter to continue...");
    getch();
}

struct PTCLData PTCLIDSearch(unsigned long long int id) {
    // 0 = Not Found, 404 = Error
    
    FILE* pointer;
    struct PTCLData data;
    int sizeFromFile, counter1 = 0, found = 0;

    pointer = fopen(PTCLfile, "rb");

    if (pointer == NULL) {
        printf("Data Null");
        data.accountID = 404;
        return data;
    }

    sizeFromFile = ArraySize(pointer, sizeof(struct PTCLData));

    while (counter1 < sizeFromFile) {
        fread(&data, sizeof (struct PTCLData), 1, pointer);
        if (data.accountID == id) {
            found = 1;
            break;
        }
        counter1++;
    }

    if (found == 0) {
        data.accountID = 0;
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