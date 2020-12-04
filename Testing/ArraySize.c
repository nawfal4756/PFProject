#include <stdio.h>

struct SSGCData {
    unsigned long long int consumerId;
    char name[30];
    char address[70];
    unsigned long long int contactNumber;
    float unitsAndPayment[3][12];
};

int ArraySize(FILE* pointer, int structSize);

int main() {
    FILE* pointer;
    int size;

    pointer = fopen("SSGCData.txt", "rb");

    if (pointer != NULL) {
        printf("File opened successfully!\n");
        size = ArraySize(pointer, sizeof(struct SSGCData));
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