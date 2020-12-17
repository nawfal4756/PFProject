#include <stdio.h>
#include <stdbool.h>

struct SSGCData {
    unsigned long long int consumerId;
    char name[30];
    char address[70];
    unsigned long long int contactNumber;
    float unitsAndPayment[3][12];
};

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
    FILE* pointer;
    int size;

    pointer = fopen("KElectricData.txt", "rb");

    if (pointer != NULL) {
        printf("File opened successfully!\n");
        size = ArraySize(pointer, sizeof(struct KElectricData));
        printf("%d", size);
    }
    else {
        printf("Unable to open file!");
    }

}

int ArraySize(FILE* pointer, int structSize) {
    int size;

    fseek(pointer, 0L, SEEK_END);
    size = ftell(pointer);
    size = size / structSize;
    fseek(pointer, 0L, SEEK_SET);

    return size;
}
