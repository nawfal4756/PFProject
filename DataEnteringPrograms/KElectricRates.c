#include <stdio.h>
#include <stdlib.h>

struct KElectricRates {
    float offPeakUnitsLessThan5KW;
    float onPeakUnitsLessThan5KW;
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

int main() {
    struct KElectricRates data;
    FILE* pointer;

    pointer = fopen(kelectricRates, "wb");

    if (pointer == NULL) {
        exit(1);
    }

    printf("Enter off peak units rate for less than 5 KW Resedential: ");
    scanf("%f", &data.offPeakUnitsLessThan5KW);
    fflush(stdin);

    printf("Enter on peak units rate for less than 5 KW Resedential: ");
    scanf("%f", &data.onPeakUnitsLessThan5KW);
    fflush(stdin);

    printf("Enter rate for upto 50 units: ");
    scanf("%f", &data.unitsUpto50);
    fflush(stdin);

    printf("Enter rate for upto 100 units: ");
    scanf("%f", &data.unitsUpto100);
    fflush(stdin);

    printf("Enter rate for upto 200 units: ");
    scanf("%f", &data.unitsUpto200);
    fflush(stdin);

    printf("Enter rate for upto 300 units: ");
    scanf("%f", &data.unitsUpto300);
    fflush(stdin);

    printf("Enter rate for upto 700 units: ");
    scanf("%f", &data.unitsUpto700);
    fflush(stdin);

    printf("Enter rate for more than 700 units: ");
    scanf("%f", &data.unitsAbove700);
    fflush(stdin);

    printf("Enter minimum rate for Resedential: ");
    scanf("%f", &data.minR);

    printf("Enter electricity duty for Resedential in percentage: ");
    scanf("%f", &data.electricityDutyR);
    fflush(stdin);

    data.electricityDutyR = data.electricityDutyR / 100;

    printf("Enter sales tax for Resedential in percentage: ");
    scanf("%f", &data.salesTaxR);
    fflush(stdin);

    data.salesTaxR = data.salesTaxR / 100;

    printf("Enter income tax for Resedential in percentage: ");
    scanf("%f", &data.incomeTaxR);
    fflush(stdin);

    data.incomeTaxR = data.incomeTaxR / 100;

    printf("Enter TV License fee for Resedential: ");
    scanf("%f", &data.tvLicenseFeeR);
    fflush(stdin);

    printf("Enter rate for units less than 5KW for Commercial: ");
    scanf("%f", &data.unitsLessThan5KWC);
    fflush(stdin);

    printf("Enter off peak units rate for more than 5 KW Commercial: ");
    scanf("%f", &data.offPeakUnitsMoreThan5KWC);
    fflush(stdin);

    printf("Enter on peak units rate for more than 5 KW Commercial: ");
    scanf("%f", &data.onPeakUnitsMoreThan5KWC);
    fflush(stdin);

    printf("Enter minimum rate for Commercial: ");
    scanf("%f", &data.minC);

    printf("Enter electricity duty for Commercial in percentage: ");
    scanf("%f", &data.electricityDutyC);
    fflush(stdin);

    data.electricityDutyC = data.electricityDutyC / 100;

    printf("Enter sales tax for Commercial in percentage: ");
    scanf("%f", &data.salesTaxC);
    fflush(stdin);

    data.salesTaxC = data.salesTaxC / 100;

    printf("Enter income tax for Commercial in percentage: ");
    scanf("%f", &data.incomeTaxC);
    fflush(stdin);

    data.incomeTaxC = data.incomeTaxC / 100;

    printf("Enter TV License fee for Commercial: ");
    scanf("%f", &data.tvLicenseFeeC);
    fflush(stdin);

    fwrite(&data, sizeof(struct KElectricRates), 1, pointer);
    fclose(pointer);
}