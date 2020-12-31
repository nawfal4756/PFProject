#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>

struct PTCLData {
    // New Structure
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
    int billYear[12];
    float total;
};

int PTCLRecordUpdate(struct PTCLData dataNew);

int ArraySize(FILE* pointer, int structSize);

int main() {
    struct PTCLData data;
    int response;

    printf("Account ID: ");
    scanf("%llu", &data.accountID);
    fflush(stdin);

    printf("Name: ");
    gets(data.name);

    response = PTCLRecordUpdate(data);

    if (response == 404) {
        printf("Error");
    }
    else if (response = 1) {
        printf("Successful");
    }

    getch();
}

int PTCLRecordUpdate(struct PTCLData dataNew) {
    struct PTCLData dataFromFile;
    FILE* pointer;
    int counter1, sizeFromFile, size, found = 0;

    pointer = fopen("../DataFiles/PTCLData.txt", "rb+");

    if (pointer == NULL) {
        return 404;
    }

    sizeFromFile = ArraySize(pointer, sizeof(struct PTCLData));    

    for (counter1 = 0; counter1 < sizeFromFile; counter1) {
        fread(&dataFromFile, sizeof(struct PTCLData), 1, pointer);
        if (dataFromFile.accountID == dataNew.accountID) {
            found = 1;
            break;
        }
    }

    if (found == 0) {
        return 404;
    }

    fseek(pointer, -(sizeof(struct PTCLData)), SEEK_CUR);
    fseek(pointer, 0L, SEEK_CUR);

    fwrite(&dataNew, sizeof(struct PTCLData), 1, pointer);

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