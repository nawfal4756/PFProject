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

int SSGCRatesModification(char category);

int main() {

}

int SSGCRatesModification(char category) {
    int option1;
    float temp1, temp2;
    char selection1;
    FILE* pointer;
    struct SSGCRates data;

    pointer = fopen(ssgcRates, "rb+");

    if (pointer == NULL) {
        return 404;
    }

    top:
    switch (category) {
        case 'R': {
            options1:
            printf("\n\nResidential:\n");
            printf("Enter 1 to change the unit price for up to 50 units: \n");
            printf("Enter 2 to change the unit price for up to 150 units: \n");
            printf("Enter 3 to change the unit price for up to 250 units: \n");
            printf("Enter 4 to change the unit price for up to 350 units: \n");
            printf("Enter 5 to change the unit price for up to 450 units: \n");
            printf("Enter 6 to change the unit price for more than 450 units: \n");
            printf("enter 7 to chnage the minimum price\n");
            printf("Enter 8 to go back\n");
            printf("Enter you desired option: ");
            scan("%d", &option1);
            fflush(stdin);

            switch (option1) {
                case 1: {
                    case1:
                    printf("Enter unit price for up to 50 units: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter unit price for up to 50 units: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter unit price for up to 50 units for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.upTo50 = temp2;
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case1;
                    }
                }

                case 2: {
                    case2:
                    printf("Enter unit price for up to 150 units: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter unit price for up to 150 units: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter unit price for up to 150 units for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.upTo150 = temp2;
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case2;
                    }
                }

                case 3: {
                    case3:
                    printf("Enter unit price for up to 250 units: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter unit price for up to 250 units: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter unit price for up to 250 units for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.upTo250 = temp2;
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case3;
                    }
                }

                case 4: {
                    case4:
                    printf("Enter unit price for up to 350 units: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter unit price for up to 350 units: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter unit price for up to 350 units for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.upTo350 = temp2;
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case4;
                    }
                }

                case 5: {
                    case5:
                    printf("Enter unit price for up to 450 units: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter unit price for up to 450 units: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter unit price for up to 450 units for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.upTo450 = temp2;
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case5;
                    }
                }

                case 6: {
                    case6:
                    printf("Enter unit price for more than 450 units: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter unit price for more than 450 units: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter unit price for more than 450 units for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.moreThan450 = temp2;
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case6;
                    }
                }

                case 7: {
                    case7:
                    printf("Enter the minimum price: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter the minimum price again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the minimum price for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.minR = temp2;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case7;
                    }
                    break;
                }

                case 8: {
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
            printf("Enter 1 to change the unit price: \n");
            printf("enter 2 to chnage the minimum price\n");
            printf("Enter 3 to go back\n");
            printf("Enter you desired option: ");
            scan("%d", &option1);
            fflush(stdin);

            switch (option1) {
                case 1: {
                    case1C:
                    printf("Enter unit price: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter unit price again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter unit price for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.unitPriceC = temp2;
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case1C;
                    }
                }

                case 2: {
                    case2C:
                    printf("Enter the minimum price: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter the minimum price again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the minimum price for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.minC = temp2;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case2C;
                    }
                    break;
                }

                case 3: {
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
            fwrite(&data, sizeof(struct SSGCRates), 1, pointer);
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