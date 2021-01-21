#include <stdio.h>
#include <stdlib.h>

struct PTCLRates {
    float freedom500L;
    float freedom1000L;
    float freedom3000L;
    float freedom5000L;
    float freedom8000L;
    float mb6B;
    float mb8B;
    float mb15B;
    float mb25B;
    float mb50B;
    float mb100B;
    float smartTVWOB;
    float smartTVWB;
    float smartTVApp;
    float dataUC;
    float data20C;
    float data30C;
    float data50C;
    float mobile;
    float other;
    float internationalZone1;
    float withholdingTaxMoreThan1000L;
    float withholdingTaxB;
    float serviceTaxB;
    float serviceTaxTV;
    float overallServiceTax;
};

char* ptclRates = "../DataFiles/PTCLRates.txt";

int PTCLRatesModification();

int main() {

}

int PTCLRatesModification() {
    int option1;
    float temp1, temp2;
    char selection1;
    struct PTCLRates data;
    FILE* pointer;

    pointer = fopen(ptclRates, "rb+");

    if (pointer == NULL) {
        return 404;
    }

    top:
    printf("Enter 1 to change the price of freedom 500 landline package\n");
    printf("Enter 2 to change the price of freedom 1000 landline package\n");
    printf("Enter 3 to change the price of freedom 3000 landline package\n");
    printf("Enter 4 to change the price of freedom 5000 landline package\n");
    printf("Enter 5 to change the price of freedom 8000 landline package\n");    
    printf("Enter 6 to change the price of 6 Mbps broadband package\n");
    printf("Enter 7 to change the price of 8 Mbps broadband package\n");
    printf("Enter 8 to change the price of 15 Mbps broadband package\n");
    printf("Enter 9 to change the price of 25 Mbps broadband package\n");
    printf("Enter 10 to change the price of 50 Mbps broadband package\n");
    printf("Enter 11 to change the price of 100 Mbps broadband package\n");
    printf("Enter 12 to change the price of Smart TV subscription without broadband\n");
    printf("Enter 13 to change the price of Smart TV subscription with broadband\n");
    printf("Enter 14 to change the price of Smart TV App subscription\n");
    printf("Enter 15 to change the price of Unlimited data Charji package\n");
    printf("Enter 16 to change the price of 20 GB data Charji package\n");
    printf("Enter 17 to change the price of 30 GB data Charji package\n");
    printf("Enter 18 to change the price of 50 GB data Charji package\n");
    printf("Enter 19 to change the price of per minute call to mobile number\n");
    printf("Enter 20 to change the price of per minute call to other number\n");
    printf("Enter 21 to change the price of per minute call to International Zone 1 number\n");
    printf("Enter 22 to change the percentage of withholding tax on telephone bill greater than 1000\n");
    printf("Enter 23 to change the percentage of withholding tax on broadband\n");
    printf("Enter 24 to change the percentage of service tax on broadband\n");
    printf("Enter 25 to change the percentage of service tax on TV\n");
    printf("Enter 26 to change the percentage of service tax\n");
    printf("Enter 27 to go back\n");
    printf("Enter you desired option: ");
    scan("%d", &option1);
    fflush(stdin);

    switch (option1) {

        case 1: {
            case1:
            printf("Enter price of freedom 500 landline package: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of freedom 500 landline package again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of freedom 500 landline package for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.freedom500L = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case1;
            }
            break;
        }

        case 2: {
            case2:
            printf("Enter price of freedom 1000 landline package: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of freedom 1000 landline package again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of freedom 1000 landline package for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.freedom1000L = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case2;
            }
            break;
        }

        case 3: {
            case3:
            printf("Enter price of freedom 3000 landline package: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of freedom 3000 landline package again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of freedom 3000 landline package for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.freedom3000L = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case3;
            }
            break;
        }

        case 4: {
            case4:
            printf("Enter price of freedom 5000 landline package: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of freedom 5000 landline package again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of freedom 5000 landline package for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.freedom5000L = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case4;
            }
            break;
        }

        case 5: {
            case5:
            printf("Enter price of freedom 8000 landline package: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of freedom 8000 landline package again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of freedom 8000 landline package for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.freedom8000L = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case5;
            }
            break;
        }

        case 6: {
            case6:
            printf("Enter price of 6 Mbps broadband package: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of 6 Mbps broadband package again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of 6 Mbps broadband package for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.mb6B = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case6;
            }
            break;
        }

        case 7: {
            case7:
            printf("Enter price of 8 Mbps broadband package: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of 8 Mbps broadband package again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of 8 Mbps broadband package for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.mb8B = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case7;
            }
            break;
        }

        case 8: {
            case8:
            printf("Enter price of 15 Mbps broadband package: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of 15 Mbps broadband package again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of 15 Mbps broadband package for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.mb15B = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case8;
            }
            break;
        }

        case 9: {
            case9:
            printf("Enter price of 25 Mbps broadband package: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of 25 Mbps broadband package again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of 25 Mbps broadband package for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.mb25B = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case9;
            }
            break;
        }

        case 10: {
            case10:
            printf("Enter price of 50 Mbps broadband package: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of 50 Mbps broadband package again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of 50 Mbps broadband package for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.mb50B = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case10;
            }
            break;
        }

        case 11: {
            case11:
            printf("Enter price of 100 Mbps broadband package: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of 100 Mbps broadband package again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of 100 Mbps broadband package for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.mb100B = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case11;
            }
            break;
        }

        case 12: {
            case12:
            printf("Enter price of Smart TV subscription without broadband: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of Smart TV subscription without broadband again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of Smart TV subscription without broadband for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.smartTVWOB = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case12;
            }
            break;
        }

        case 13: {
            case13:
            printf("Enter price of Smart TV subscription with broadband: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of Smart TV subscription with broadband again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of Smart TV subscription with broadband for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.smartTVWB = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case13;
            }
            break;
        }

        case 14: {
            case14:
            printf("Enter price of Smart TV App subscription: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of Smart TV App subscription again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of Smart TV App subscription for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.smartTVApp = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case14;
            }
            break;
        }

        case 15: {
            case15:
            printf("Enter price of Unlimited Charji package: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of Unlimited Charji package again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of Unlimited Charji package for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.dataUC = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case15;
            }
            break;
        }

        case 16: {
            case16:
            printf("Enter price of 20 GB Charji package: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of 20 GB Charji package again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of 20 GB Charji package for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.data20C = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case16;
            }
            break;
        }

        case 17: {
            case17:
            printf("Enter price of 30 GB Charji package: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of 30 GB Charji package again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of 30 GB Charji package for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.data30C = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case17;
            }
            break;
        }

        case 18: {
            case18:
            printf("Enter price of 50 GB Charji package: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of 50 GB Charji package again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of 50 GB Charji package for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.data50C = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case18;
            }
            break;
        }

        case 19: {
            case19:
            printf("Enter price of per minute call to mobile number: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of per minute call to mobile number again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of per minute call to mobile number for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.mobile = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case19;
            }
            break;
        }

        case 20: {
            case20:
            printf("Enter price of per minute call to other number: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of per minute call to other number again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of per minute call to other number for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.other = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case20;
            }
            break;
        }

        case 21: {
            case21:
            printf("Enter price of per minute call to International Zone 1 number: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of per minute call to International Zone 1 number again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of per minute call to International Zone 1 number for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.internationalZone1 = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case21;
            }
            break;
        }

        case 22: {
            case22:
            printf("Enter the percentage of withholding tax on telephone bill greater than 1000: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect percentage entered!\n");
                printf("Enter the percentage of withholding tax on telephone bill greater than 1000 again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter the percentage of withholding tax on telephone bill greater than 1000 for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.withholdingTaxMoreThan1000L = temp2 / 100;                        
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case22;
            }
            break;
        }

        case 23: {
            case23:
            printf("Enter the percentage of withholding tax on broadband: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect percentage entered!\n");
                printf("Enter the percentage of withholding tax on broadband again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter the percentage of withholding tax on broadband for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.withholdingTaxB = temp2 / 100;                        
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case23;
            }
            break;
        }

        case 24: {
            case24:
            printf("Enter the percentage of service tax on broadband: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect percentage entered!\n");
                printf("Enter the percentage of service tax on broadband again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter the percentage of service tax on broadband for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.serviceTaxB = temp2 / 100;                        
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case24;
            }
            break;
        }

        case 25: {
            case25:
            printf("Enter the percentage of service tax on TV: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect percentage entered!\n");
                printf("Enter the percentage of service tax on TV again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter the percentage of service tax on TV for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.serviceTaxTV = temp2 / 100;                        
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case25;
            }
            break;
        }

        case 26: {
            case26:
            printf("Enter the percentage of service tax: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect percentage entered!\n");
                printf("Enter the percentage of service tax again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter the percentage of service tax for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.overallServiceTax = temp2 / 100;                        
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case26;
            }
            break;
        }

        case 27: {
            return 2;
            break;
        }

        default: {
            printf("\nIncorrect option selected!\n\n");
            goto top;
            break;
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
            fwrite(&data, sizeof(struct PTCLRates), 1, pointer);
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