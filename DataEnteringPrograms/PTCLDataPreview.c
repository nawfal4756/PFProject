#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// struct PTCLData {
//     unsigned long long int accountID;
//     char name[30];
//     char address[70];
//     unsigned long long int contactNumber;
//     int packageLandline;
//     int packageBroadband;
//     char packageTV;
//     char packageCharji;
//     int onNetMinutes[12];
//     int mobileMinutes[12];
//     int otherMinutes[12];
//     int internationalZone1Minutes[12];
//     int internationalOtherZoneMinutes[12];
//     // 0 = bill of PTCL, 1 = Service Tax, 2 = Withholding Tax, 3 = Late Payment Surcgarge, 4 = Total Bill, 5 = Recieved Payment
//     float payments[6][12];
// };

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

int ArraySize(FILE* pointer, int structSize);

int main() {
    FILE* pointer;
    struct PTCLData userData[125];
    int counter1, counter2, counter3, sizeFromFile;

    pointer = fopen("../DataFiles/PTCLData.txt", "rb");

    if (pointer == NULL) {
        printf("Unable to open file! Exiting program...\nPress enter to continue...");
        getch();
        exit(1);
    }

    sizeFromFile = ArraySize(pointer, sizeof(struct PTCLData));
    fread(userData, sizeof(struct PTCLData), sizeFromFile, pointer);

    for (counter1 = 0; counter1 < sizeFromFile; counter1++) {
        printf("%llu\n", userData[counter1].accountID);
        puts(userData[counter1].name);
        puts(userData[counter1].address);
        printf("%llu\n", userData[counter1].contactNumber);
        printf("%d\n", userData[counter1].packageLandline);
        printf("%d\n", userData[counter1].packageBroadband);
        printf("%c\n", userData[counter1].packageTV);
        printf("%c\n", userData[counter1].packageCharji);

        for ( counter2 = 0; counter2 < 12; counter2++) {
            printf("%5d\t", userData[counter1].onNetMinutes[counter2]);
        }
        printf("\n");

        for ( counter2 = 0; counter2 < 12; counter2++) {
            printf("%5d\t", userData[counter1].mobileMinutes[counter2]);
        }
        printf("\n");

        for ( counter2 = 0; counter2 < 12; counter2++) {
            printf("%5d\t", userData[counter1].otherMinutes[counter2]);
        }
        printf("\n");

        for ( counter2 = 0; counter2 < 12; counter2++) {
            printf("%5d\t", userData[counter1].internationalZone1Minutes[counter2]);
        }
        printf("\n");

        for ( counter2 = 0; counter2 < 12; counter2++) {
            printf("%5d\t", userData[counter1].internationalOtherZoneMinutes[counter2]);
        }
        printf("\n");

        for (counter2 = 0; counter2 < 6; counter2++) {
            for ( counter3 = 0; counter3 < 12; counter3++) {
                printf("%.2f\t", userData[counter1].payments[counter2][counter3]);
            }            
            printf("\n");
        }

        for (counter2 = 0; counter2 < 12; counter2++) {
            printf("%d\t", userData[counter1].billYear[counter2]);
        }
        printf("\n");

        printf("%.2f\n", userData[counter1].total);

        printf("\n\n");
    }

    fclose(pointer);
    printf("\nPress enter to continue...");
    getch();
}

int ArraySize(FILE* pointer, int structSize) {
    int size;

    fseek(pointer, 0L, SEEK_END);
    size = ftell(pointer);
    size = size / structSize;
    fseek(pointer, 0L, SEEK_SET);

    return size;
}