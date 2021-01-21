#include <stdio.h>
#include <stdlib.h>

struct KElectricRates {
    float offPeakUnitsMoreThan5KW;
    float onPeakUnitsMoreThan5KW;
    float unitsUpto50;
    float unitsUpto100;
    float unitsUpto200;
    float unitsUpto300;
    float unitsUpto700;
    float unitsAbove700;
    float minR;
    float electricityDutyR;
    float salesTaxR;
    float incomeTaxR;
    float tvLicenseFeeR;
    float unitsLessThan5KWC;
    float offPeakUnitsMoreThan5KWC;
    float onPeakUnitsMoreThan5KWC;
    float minC;
    float electricityDutyC;
    float salesTaxC;
    float incomeTaxC;
    float tvLicenseFeeC;
};

char* kelectricRates = "../DataFiles/KElectricRates.txt";

void KElectricRatesPreview();

int main() {
    KElectricRatesPreview();
}

void KElectricRatesPreview() {
    struct KElectricRates data;
    FILE* pointer;

    pointer = fopen(kelectricRates, "rb");

    if (pointer == NULL) {
        exit(1);
    }

    fread(&data, sizeof(struct KElectricRates), 1, pointer);

    printf("\nResidential:\n");
    printf("Residential off peak units rate for more than 5 KW: %.2f\n", data.offPeakUnitsMoreThan5KW);
    printf("Residential on peak units rate for more than 5 KW: %.2f\n", data.onPeakUnitsMoreThan5KW);
    printf("Residential rate for upto 50 units less than 5 KW: %.2f\n", data.unitsUpto50);
    printf("Residential rate for upto 100 units less than 5 KW: %.2f\n", data.unitsUpto100);    
    printf("Residential rate for upto 200 units less than 5 KW: %.2f\n", data.unitsUpto200);    
    printf("Residential rate for upto 300 units less than 5 KW: %.2f\n", data.unitsUpto300);
    printf("Residential rate for upto 700 units less than 5 KW: %.2f\n", data.unitsUpto700);
    printf("Residential rate for more than 700 units less than 5 KW: %.2f\n", data.unitsAbove700);    
    printf("Residential minimum rate: %.2f\n", data.minR);    
    printf("Electricity duty for Residential in percentage: %.2f %%\n", data.electricityDutyR * 100);    
    printf("Sales tax for Residential in percentage: %.2f %%\n", data.salesTaxR * 100);    
    printf("Income tax for Residential in percentage: %.2f %%\n", data.incomeTaxR * 100);
    printf("TV License fee for Residential: %.2f\n", data.tvLicenseFeeR);
    printf("\nCommericial:\n");
    printf("Commercial rate for units less than 5KW: %.2f\n", data.unitsLessThan5KWC);
    printf("Commercial off peak units rate for more than 5 KW: %.2f\n", data.offPeakUnitsMoreThan5KWC);
    printf("Commercial on peak units rate for more than 5 KW: %.2f\n", data.onPeakUnitsMoreThan5KWC);
    printf("Commercial minimum rate: %.2f\n", data.minC);
    printf("Electricity duty for Commercial in percentage: %.2f %%\n", data.electricityDutyC * 100);
    printf("Sales tax for Commercial in percentage: %.2f %%\n", data.salesTaxC * 100);
    printf("Income tax for Commercial in percentage: %.2f %%\n", data.incomeTaxC * 100);
    printf("TV License fee for Commercial: %.2f\n", data.tvLicenseFeeC);

    fclose(pointer);
}