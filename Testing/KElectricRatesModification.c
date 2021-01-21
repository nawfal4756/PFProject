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

int KElectricRatesModification(char category);

int main() {

}

int KElectricRatesModification(char category) {
    int option1,temp1, temp2;
    FILE* pointer;
    struct KElectricRates data;

    pointer = fopen(kelectricRates, "rb+");

    if (pointer == NULL) {
        return 404;
    }

    fread(&data, sizeof(struct KElectricRates), 1, pointer);

    switch (category) {
        case 'R': {
            options1:
            printf("Enter 1 to change the rate of off peak for less than 5 KW\n");
            printf("Enter 2 to change the rate of on peak for less than 5 KW\n");
            printf("For more than 5KW:\n");
            printf("Enter 3 to change the rate for up to 50 units\n");
            printf("Enter 4 to change the rate for up to 100 units\n");
            printf("Enter 5 to change the rate for up to 200 units\n");
            printf("Enter 6 to change the rate for up to 300 units\n");
            printf("Enter 7 to change the rate for up to 700 units\n");
            printf("Enter 8 to change the rate for more than 700 units\n");
            printf("Enter 9 to change the minimum rate\n");
            printf("Enter 10 to change the percentage of electricity duty\n");
            printf("Enter 11 to change the percentage of sales tax\n");
            printf("Enter 12 to change the percentage of income tax\n");
            printf("Enter 13 to change the TV license fee\n");
            printf("Enter 14 to go back\n");
            printf("Enter you desired option: ");
            scan("%d", &option1);
            fflush(stdin);

            switch (option1) {
                case 1: {
                    case1:
                    printf("Enter off peak units rate for less than 5 KW: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter off peak units rate for less than 5 KW again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }
                    printf("Enter off peak units rate for less than 5 KW for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.offPeakUnitsLessThan5KW = temp2;
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case1;
                    }                    
                    break;
                }

                case 2: {

                }

                case 3: {

                }

                case 4: {

                }

                case 5: {
                    
                }

                case 6: {
                    
                }

                case 7: {
                    
                }

                case 8: {
                    
                }

                case 9: {
                    
                }

                case 10: {
                    
                }

                case 11: {
                    
                }

                case 12: {
                    
                }

                case 13: {
                    
                }

                case 14: {
                    
                }

                default: {
                    printf("\nIncorrect option selected!\n");
                    goto options1;
                    break;
                }
            }
        }
    }
}