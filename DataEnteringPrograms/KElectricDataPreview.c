#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
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

int ArraySize(FILE* pointer, int structSize);

int main() {
    int counter, counter2, counter3, size;
    FILE* pointer;
    struct KElectricData userData[125];

    pointer = fopen("../DataFiles/KElectricData.txt", "rb");

    if (pointer != NULL) {
        size = ArraySize(pointer, sizeof(struct KElectricData));
        fread(userData, sizeof(struct KElectricData), size, pointer);
        for (counter = 0; counter < size; counter++) {
            printf("%llu\n", userData[counter].accountNumber);
            puts(userData[counter].name);
            puts(userData[counter].address);
            printf("0%llu\n", userData[counter].contactNumber);
            printf("%c\n", userData[counter].usageType);
            printf("%.2f\n", userData[counter].allotedLoad);
            printf("%d\n", userData[counter].numberOfTV);
            for (counter2 = 0; counter2 < 12; counter2++) {
                for (counter3 = 0; counter3 < 9; counter3++) {
                    printf("%.2f\t", userData[counter].unitsAndPayment[counter3][counter2]);
                }
                printf("%s\n", userData[counter].timePayment[counter2] ? "True" : "False");
            }
            
            printf("\n\n");
        }
    }
    else {
        printf("Unable to open file!\n");
        exit(1);
    }

    fclose(pointer);
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