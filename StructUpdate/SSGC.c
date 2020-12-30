#include <stdio.h>
#include <stdlib.h>

struct SSGCData {
    unsigned long long int consumerId;
    char name[30];
    char address[70];
    unsigned long long int contactNumber;
    char usageType;
    // 0 = units, 1 = amount os natural gas used, 2 = Sales Tax, 3 = Income Tax, 4 = amount due, 5 = amount paid
    float unitsAndPayment[6][12];
};

struct SSGCDataNew {
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

int main() {
    struct SSGCData dataOld;
    struct SSGCDataNew dataNew;
    FILE* pointerOld, * pointerNew;
    int sizeOld, counter1, counter2, counter3;
    float diff;

    pointerOld = fopen("../DataFiles/SSGCDataOld.txt", "rb");

    if (pointerOld == NULL) {
        printf("Pointer Old Error\n");
        exit(1);
    }    

    pointerNew = fopen("../DataFiles/SSGCData.txt", "wb");

    if (pointerNew == NULL) {
        printf("Pointer New Error\n");
        exit(1);
    }

    sizeOld = ArraySize(pointerOld, sizeof(struct SSGCData));

    for (counter1 = 0; counter1 < sizeOld; counter1++) {
        fread(&dataOld, sizeof(struct SSGCData), 1, pointerOld);

        dataNew.total = 0;

        dataNew.consumerId = dataOld.consumerId;

        for (counter2 = 0; counter2 < 30; counter2++) {
            dataNew.name[counter2] = dataOld.name[counter2];    
        }
        for (counter2 = 0; counter2 < 70; counter2++) {
            dataNew.address[counter2] = dataOld.address[counter2];    
        }
                
        dataNew.contactNumber = dataOld.contactNumber;
        dataNew.usageType = dataOld.usageType;

        for (counter2 = 0; counter2 < 6; counter2++) {
            for (counter3 = 0; counter3 < 12; counter3++) {
                dataNew.unitsAndPayment[counter2][counter3] = dataOld.unitsAndPayment[counter2][counter3];
            }
        }

        for (counter2 = 0; counter2 < 12; counter2++) {
            dataNew.billYear[counter2] = 2019;                        

            diff = dataOld.unitsAndPayment[4][counter2] - dataOld.unitsAndPayment[5][counter2];
            dataNew.total += diff;
        }

        fwrite(&dataNew, sizeof(struct SSGCDataNew), 1, pointerNew);
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