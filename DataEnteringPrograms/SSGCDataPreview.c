#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// struct SSGCData {
//     unsigned long long int consumerId;
//     char name[30];
//     char address[70];
//     unsigned long long int contactNumber;
//     char usageType;
//     // 0 = units, 1 = amount os natural gas used, 2 = Sales Tax, 3 = Income Tax, 4 = amount due, 5 = amount paid
//     float unitsAndPayment[6][12];
// };

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

int ArraySize(FILE* pointer, int structSize);

int main() {
    int counter, counter2, counter3, size;
    FILE* pointer;
    struct SSGCData userData[125];

    pointer = fopen("../DataFiles/SSGCData.txt", "rb");

    if (pointer != NULL) {
        size = ArraySize(pointer, sizeof(struct SSGCData));
        fread(userData, sizeof(struct SSGCData), size, pointer);
        for (counter = 0; counter < size; counter++) {
            printf("%llu\n", userData[counter].consumerId);
            printf("%s\n", userData[counter].name);
            printf("%s\n", userData[counter].address);
            printf("0%llu\n", userData[counter].contactNumber);
            printf("%c\n", userData[counter].usageType);

            for (counter2 = 0; counter2 < 12; counter2++) {
                for (counter3 = 0; counter3 < 6; counter3++) {
                    printf("%.2f\t", userData[counter].unitsAndPayment[counter3][counter2]);
                }
                printf("%d\n", userData[counter].billYear[counter2]);
            }

            printf("%.2f\n", userData[counter].total);
            
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