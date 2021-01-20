#include <stdio.h>
#include <stdlib.h>

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

struct PTCLDataNew {
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
    struct PTCLData dataOld;
    struct PTCLDataNew dataNew;
    FILE* pointerOld, * pointerNew;
    int sizeOld, counter1, counter2, counter3;
    float diff;

    pointerOld = fopen("../DataFiles/PTCLDataOld.txt", "rb");

    if (pointerOld == NULL) {
        printf("Pointer Old Error\n");
        exit(1);
    }

    pointerNew = fopen("../DataFiles/PTCLData.txt", "wb");

    if (pointerNew == NULL) {
        printf("Pointer New Error\n");
        exit(1);
    }

    sizeOld = ArraySize(pointerOld, sizeof(struct PTCLData));

    for (counter1 = 0; counter1 < sizeOld; counter1++) {
        fread(&dataOld, sizeof(struct PTCLData), 1, pointerOld);

        dataNew.total = 0;

        dataNew.accountID = dataOld.accountID;

        for (counter2 = 0; counter2 < 30; counter2++) {
            dataNew.name[counter2] = dataOld.name[counter2];    
        }
        for (counter2 = 0; counter2 < 70; counter2++) {
            dataNew.address[counter2] = dataOld.address[counter2];    
        }
                
        dataNew.contactNumber = dataOld.contactNumber;
        dataNew.packageLandline = dataOld.packageLandline;
        dataNew.packageBroadband = dataOld.packageBroadband;
        dataNew.packageTV = dataOld.packageTV;
        dataNew.packageCharji = dataOld.packageCharji;

        for (counter2 = 0; counter2 < 12; counter2++) {
            dataNew.onNetMinutes[counter2] = dataOld.onNetMinutes[counter2];
            dataNew.mobileMinutes[counter2] = dataOld.mobileMinutes[counter2];
            dataNew.otherMinutes[counter2] = dataOld.otherMinutes[counter2];
            dataNew.internationalZone1Minutes[counter2] = dataOld.internationalZone1Minutes[counter2];
            dataNew.internationalOtherZoneMinutes[counter2] = dataOld.internationalOtherZoneMinutes[counter2];
            
            dataNew.billYear[counter2] = 2020;

            diff = dataOld.payments[4][counter2] - dataOld.payments[5][counter2];
            dataNew.total += diff;
        }

        for (counter2 = 0; counter2 < 6; counter2++) {
            for (counter3 = 0; counter3 < 12; counter3++) {
                dataNew.payments[counter2][counter3] = dataOld.payments[counter2][counter3];
            }
        }
        
        dataNew.billYear[0] = 2021;

        fwrite(&dataNew, sizeof(struct PTCLDataNew), 1, pointerNew);
    }

    fclose(pointerOld);
    fclose(pointerNew);

    printf("Data Entered Successfully");
}

int ArraySize(FILE* pointer, int structSize) {
    int size;

    fseek(pointer, 0L, SEEK_END);
    size = ftell(pointer);
    size = size / structSize;
    fseek(pointer, 0L, SEEK_SET);

    return size;
}
