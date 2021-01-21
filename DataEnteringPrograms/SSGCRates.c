#include <stdio.h>
#include <stdlib.h>

struct SSGCRates {
    float upTo50;
    float upTo150;
    float upTo250;
    float upTo350;
    float upTo450;
    float moreThan450;
    float minR;
    float unitPriceC;
    float minC;
};

char* ssgcRates = "../DataFiles/SSGCRates.txt";

int main() {
    FILE* pointer;
    struct SSGCRates data;

    pointer = fopen(ssgcRates, "wb");

    if (pointer == NULL) {
        exit(1);
    }

    printf("Enter units price for up to 50 units: ");
    scanf("%f", &data.upTo50);
    fflush(stdin);

    printf("Enter units price for up to 150 units: ");
    scanf("%f", &data.upTo150);
    fflush(stdin);

    printf("Enter units price for up to 250 units: ");
    scanf("%f", &data.upTo250);
    fflush(stdin);

    printf("Enter units price for up to 350 units: ");
    scanf("%f", &data.upTo350);
    fflush(stdin);

    printf("Enter units price for up to 450 units: ");
    scanf("%f", &data.upTo450);
    fflush(stdin);

    printf("Enter units price for more than 450 units: ");
    scanf("%f", &data.moreThan450);
    fflush(stdin);

    printf("Enter minimum price for Residential: ");
    scanf("%f", &data.minR);
    fflush(stdin);

    printf("Enter units price for commercial: ");
    scanf("%f", &data.unitPriceC);
    fflush(stdin);

    printf("Enter minimum price for commercial: ");
    scanf("%f", &data.minC);
    fflush(stdin);

    fwrite(&data, sizeof(struct SSGCRates), 1, pointer);
    fclose(pointer);
}