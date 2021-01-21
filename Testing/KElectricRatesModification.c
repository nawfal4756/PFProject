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

int KElectricRatesModification(char category);

int main() {

}

int KElectricRatesModification(char category) {
    int option1,temp1, temp2;
    FILE* pointer;
    struct KElectricRates data;
    char selection1;

    pointer = fopen(kelectricRates, "rb+");

    if (pointer == NULL) {
        return 404;
    }

    fread(&data, sizeof(struct KElectricRates), 1, pointer);
    top:
    switch (category) {
        case 'R': {
            options1:
            printf("\n\nResidential:\n");
            printf("Enter 1 to change the rate of off peak for more than 5 KW\n");
            printf("Enter 2 to change the rate of on peak for more than 5 KW\n");
            printf("For less than 5KW:\n");
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
                        data.offPeakUnitsMoreThan5KW = temp2;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case1;
                    }
                    break;
                }

                case 2: {
                    case2:
                    printf("Enter on peak units rate for less than 5 KW: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter on peak units rate for less than 5 KW again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }
                    printf("Enter on peak units rate for less than 5 KW for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.onPeakUnitsMoreThan5KW = temp2;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case2;
                    }
                    break;
                }

                case 3: {
                    case3:
                    printf("Enter the rate for up to 50 units for more than 5 KW: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter the rate again for up to 50 units for more than 5 KW: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the rate for up to 50 units for more than 5 KW for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.unitsUpto50 = temp2;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case3;
                    }
                    break;
                }

                case 4: {
                    case4:
                    printf("Enter the rate for up to 100 units for more than 5 KW: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter the rate again for up to 100 units for more than 5 KW: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the rate for up to 100 units for more than 5 KW for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.unitsUpto100 = temp2;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case4;
                    }
                    break;
                }

                case 5: {
                    case5:
                    printf("Enter the rate for up to 200 units for more than 5 KW: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter the rate again for up to 200 units for more than 5 KW: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the rate for up to 200 units for more than 5 KW for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.unitsUpto200 = temp2;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case5;
                    }
                    break;
                }

                case 6: {
                    case6:
                    printf("Enter the rate for up to 300 units for more than 5 KW: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter the rate again for up to 300 units for more than 5 KW: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the rate for up to 300 units for more than 5 KW for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.unitsUpto300 = temp2;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case6;
                    }
                    break;
                }

                case 7: {
                    case7:
                    printf("Enter the rate for up to 700 units for more than 5 KW: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter the rate again for up to 700 units for more than 5 KW: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the rate for up to 700 units for more than 5 KW for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.unitsUpto700 = temp2;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case7;
                    }
                    break;
                }

                case 8: {
                    case8:
                    printf("Enter the rate for more than 700 units for more than 5 KW: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter the rate again for more than 700 units for more than 5 KW: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the rate for more than 700 units for more than 5 KW for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.unitsAbove700 = temp2;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case8;
                    }
                    break;
                }

                case 9: {
                    case9:
                    printf("Enter the minimum rate: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter the minimum rate again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the minimum rate for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.minR = temp2;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case9;
                    }
                    break;
                }

                case 10: {
                    case10:
                    printf("Enter the electricity duty in percentage: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect percentage entered!\n");
                        printf("Enter the electricity duty in percentage again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the electricity duty in percentage for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.electricityDutyR = temp2 / 100;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case10;
                    }
                    break;
                }

                case 11: {
                    case11:
                    printf("Enter the sales tax in percentage: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect percentage entered!\n");
                        printf("Enter the sales tax in percentage again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the sales tax in percentage for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.salesTaxR = temp2 / 100;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case11;
                    }
                    break;
                }

                case 12: {
                    case12:
                    printf("Enter the income tax in percentage: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect percentage entered!\n");
                        printf("Enter the income tax in percentage again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the income tax in percentage for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.incomeTaxR = temp2 / 100;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case12;
                    }
                    break;
                }

                case 13: {
                    case13:
                    printf("Enter the TV license fee: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect percentage entered!\n");
                        printf("Enter the TV license fee again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the TV license fee for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.tvLicenseFeeR = temp2;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case13;
                    }
                    break;
                }

                case 14: {
                    return 2;
                    break;
                }

                default: {
                    printf("\nIncorrect option selected!\n");
                    goto options1;
                    break;
                }
            }            
        }

        case 'C': {
            options2:
            printf("\n\nCommercial:\n");
            printf("Enter 1 to change the rate for less than 5 KW\n");
            printf("For more than 5KW:\n");
            printf("Enter 2 to change the rate of off peak\n");
            printf("Enter 3 to change the rate of on peak\n");
            printf("Enter 4 to change the minimum rate\n");
            printf("Enter 5 to change the percentage of electricity duty\n");
            printf("Enter 6 to change the percentage of sales tax\n");
            printf("Enter 7 to change the percentage of income tax\n");
            printf("Enter 8 to change the TV license fee\n");
            printf("Enter 9 to go back\n");
            printf("Enter you desired option: ");
            scan("%d", &option1);
            fflush(stdin);

            switch (option1) {
                case 1: {
                    case1C:
                    printf("Enter units rate for less than 5 KW: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter units rate for less than 5 KW again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }
                    printf("Enter units rate for less than 5 KW for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.unitsLessThan5KWC = temp2;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case1C;
                    }
                    break;
                }

                case 2: {
                    case2C:
                    printf("Enter off peak units rate for more than 5 KW: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter off peak units rate for more than 5 KW again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }
                    printf("Enter off peak units rate for more than 5 KW for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.offPeakUnitsMoreThan5KWC = temp2;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case2C;
                    }
                    break;
                }

                case 3: {
                    case3C:
                    printf("Enter on peak units rate for more than 5 KW: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter on peak units rate for more than 5 KW again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }
                    printf("Enter on peak units rate for more than 5 KW for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.onPeakUnitsMoreThan5KWC = temp2;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case3C;
                    }
                    break;
                }

                case 4: {
                    case4C:
                    printf("Enter the minimum rate: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter the minimum rate again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the minimum rate for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.minC = temp2;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case4C;
                    }
                    break;
                }

                case 5: {
                    case5C:
                    printf("Enter the electricity duty in percentage: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect percentage entered!\n");
                        printf("Enter the electricity duty in percentage again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the electricity duty in percentage for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.electricityDutyC = temp2 / 100;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case5C;
                    }
                    break;
                }

                case 6: {
                    case6C:
                    printf("Enter the sales tax in percentage: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect percentage entered!\n");
                        printf("Enter the sales tax in percentage again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the sales tax in percentage for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.salesTaxC = temp2 / 100;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case6C;
                    }
                    break;
                }

                case 7: {
                    case7C:
                    printf("Enter the income tax in percentage: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect percentage entered!\n");
                        printf("Enter the income tax in percentage again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the income tax in percentage for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.incomeTaxC = temp2 / 100;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case7C;
                    }
                    break;
                }

                case 8: {
                    case8C:
                    printf("Enter the TV license fee: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect percentage entered!\n");
                        printf("Enter the TV license fee again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the TV license fee for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.tvLicenseFeeC = temp2;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case8C;
                    }
                    break;
                }

                case 9: {
                   return 2;
                   break; 
                }

                default: {
                    printf("\nIncorrect option selected!\n");
                    goto options2;
                    break;
                }
            }
        }        
    }

    exit:
    printf("\n\nDo you want to modify any other rates? (Yes or No)\n");
    scanf("%c", &selection1);
    fflush(stdin);

    switch (selection1) {
        case 'Y':
        case 'y': {
            printf("\n\n");
            goto top;
            break;
        }

        case 'N':
        case 'n': {
            fseek(pointer, 0L, SEEK_SET);
            fwrite(&data, sizeof(struct KElectricRates), 1, pointer);
            fclose(pointer);
            return 1;
            break;
        }

        default: {
            printf("\nIncorrect option entered!\n");
            goto exit;
            break;
        }
    }
}