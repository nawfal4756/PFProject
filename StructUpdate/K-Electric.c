#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

struct KElectricDataNew {
    //New Structure
    unsigned long long int accountNumber;
    char name[30];
    char address[70];
    unsigned long long int contactNumber;
    char usageType;
    float allotedLoad;
    int numberOfTV;
    // 0 = off peak units, 1 = on peak units, 2 = amount of electricity, 3 = electricity duty, 4 = Sales Tax, 5 = Income tax, 6 = tv license fee, 7 = amount due, 8 = amount paid
    float unitsAndPayment[9][12];
    int billYear[12];
    bool timePayment[12];
    float total;
};

int ArraySize(FILE* pointer, int structSize);

int main() {
    struct KElectricData dataOld;
    struct KElectricDataNew dataNew;
    FILE* pointerOld, * pointerNew;
    int sizeOld, counter1, counter2, counter3;
    float diff;

    pointerOld = fopen("../DataFiles/KElectricDataOld.txt", "rb");

    if (pointerOld == NULL) {
        printf("Pointer Old Error\n");
        exit(1);
    }

    pointerNew = fopen("../DataFiles/KElectricData.txt", "wb");

    if (pointerNew == NULL) {
        printf("Pointer New Error\n");
        exit(1);
    }

    sizeOld = ArraySize(pointerOld, sizeof(struct KElectricData));

    for (counter1 = 0; counter1 < sizeOld; counter1++) {
        fread(&dataOld, sizeof(struct KElectricData), 1, pointerOld);

        dataNew.total = 0;

        dataNew.accountNumber = dataOld.accountNumber;

        for (counter2 = 0; counter2 < 30; counter2++) {
            dataNew.name[counter2] = dataOld.name[counter2];    
        }
        for (counter2 = 0; counter2 < 70; counter2++) {
            dataNew.address[counter2] = dataOld.address[counter2];    
        }
                
        dataNew.contactNumber = dataOld.contactNumber;
        dataNew.usageType = dataOld.usageType;
        dataNew.allotedLoad = dataOld.allotedLoad;
        dataNew.numberOfTV = dataOld.numberOfTV;        

        for (counter2 = 0; counter2 < 9; counter2++) {
            for (counter3 = 0; counter3 < 12; counter3++) {
                dataNew.unitsAndPayment[counter2][counter3] = dataOld.unitsAndPayment[counter2][counter3];
            }
        }
        
        for (counter2 = 0; counter2 < 12; counter2++) {
            dataNew.billYear[counter2] = 2020;
            
            dataNew.timePayment[counter2] = dataOld.timePayment[counter2];

            diff = dataOld.unitsAndPayment[7][counter2] - dataOld.unitsAndPayment[8][counter2];
            dataNew.total += diff;
        }

        dataNew.billYear[0] = 2021;

        fwrite(&dataNew, sizeof(struct KElectricDataNew), 1, pointerNew);
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