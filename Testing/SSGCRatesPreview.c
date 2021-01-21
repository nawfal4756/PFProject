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

void SSGCRatesPreview();

int main() {
    SSGCRatesPreview();
}

void SSGCRatesPreview() {
    FILE* pointer;
    struct SSGCRates data;

    pointer = fopen(ssgcRates, "rb");

    if (pointer == NULL) {
        exit(1);
    }

    fread(&data, sizeof(struct SSGCRates), 1, pointer);

    printf("\nResidential:\n");
    printf("Unit price for up to 50 units: %.2f\n", data.upTo50);    
    printf("Unit price for up to 150 units: %.2f\n", data.upTo150);    
    printf("Unit price for up to 250 units: %.2f\n", data.upTo250);
    printf("Unit price for up to 350 units: %.2f\n", data.upTo350);    
    printf("Unit price for up to 450 units: %.2f\n", data.upTo450);    
    printf("Unit price for more than 450 units: %.2f\n", data.moreThan450);    
    printf("Minimum price: %.2f\n", data.minR);
    printf("\nCommercial:\n");  
    printf("Unit price: %.2f\n", data.unitPriceC);    
    printf("Minimum price: %.2f\n", data.minC);
    
    fclose(pointer);
}