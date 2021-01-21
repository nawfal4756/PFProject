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

int main() {
    FILE* pointer;
    struct PTCLRates data;

    pointer = fopen(ptclRates, "wb");

    if (pointer == NULL) {
        exit (1);
    }

    printf("Enter price for Freedom 500 landline package: ");
    scanf("%f", &data.freedom500L);
    fflush(stdin);

    printf("Enter price for Freedom 1000 landline package: ");
    scanf("%f", &data.freedom1000L);
    fflush(stdin);

    printf("Enter price for Freedom 3000 landline package: ");
    scanf("%f", &data.freedom3000L);
    fflush(stdin);

    printf("Enter price for Freedom 5000 landline package: ");
    scanf("%f", &data.freedom5000L);
    fflush(stdin);

    printf("Enter price for Freedom 8000 landline package: ");
    scanf("%f", &data.freedom8000L);
    fflush(stdin);

    printf("Enter the charges for 6 Mbps broadband package: ");
    scanf("%f", &data.mb6B);
    fflush(stdin);

    printf("Enter the charges for 8 Mbps broadband package: ");
    scanf("%f", &data.mb8B);
    fflush(stdin);

    printf("Enter the charges for 15 Mbps broadband package: ");
    scanf("%f", &data.mb15B);
    fflush(stdin);

    printf("Enter the charges for 25 Mbps broadband package: ");
    scanf("%f", &data.mb25B);
    fflush(stdin);

    printf("Enter the charges for 50 Mbps broadband package: ");
    scanf("%f", &data.mb50B);
    fflush(stdin);

    printf("Enter the charges for 100 Mbps broadband package: ");
    scanf("%f", &data.mb100B);
    fflush(stdin);

    printf("Enter the charges for smart TV without broadband: ");
    scanf("%f", &data.smartTVWOB);
    fflush(stdin);

    printf("Enter the charges for smart TV without broadband: ");
    scanf("%f", &data.smartTVWB);
    fflush(stdin);

    printf("Enter the charges for smart TV App: ");
    scanf("%f", &data.smartTVApp);
    fflush(stdin);

    printf("Enter the charges for unlimited package of Charji: ");
    scanf("%f", &data.dataUC);
    fflush(stdin);

    printf("Enter the charges for 20GB package of Charji: ");
    scanf("%f", &data.data20C);
    fflush(stdin);

    printf("Enter the charges for 30GB package of Charji: ");
    scanf("%f", &data.data30C);
    fflush(stdin);

    printf("Enter the charges for 50GB package of Charji: ");
    scanf("%f", &data.data50C);
    fflush(stdin);

    printf("Enter the charges of per minute for call on mobile numbers: ");
    scanf("%f", &data.mobile);
    fflush(stdin);

    printf("Enter the charges of per minute for call on other numbers: ");
    scanf("%f", &data.other);
    fflush(stdin);
    
    printf("Enter the charges of per minute for call on international zone 1 numbers: ");
    scanf("%f", &data.internationalZone1);
    fflush(stdin);

    printf("Enter the withholding tax percentage when telephone bill is greater than 1000: ");
    scanf("%f", &data.withholdingTaxMoreThan1000L);
    fflush(stdin);

    data.withholdingTaxMoreThan1000L = data.withholdingTaxMoreThan1000L / 100;

    printf("Enter the withholding tax percentage on broadband: ");
    scanf("%f", &data.withholdingTaxB);
    fflush(stdin);

    data.withholdingTaxB = data.withholdingTaxB / 100;

    printf("Enter the service tax percentage on broadband: ");
    scanf("%f", &data.serviceTaxB);
    fflush(stdin);

    data.serviceTaxB = data.serviceTaxB / 100;

    printf("Enter the service tax percentage on TV: ");
    scanf("%f", &data.serviceTaxTV);
    fflush(stdin);

    data.serviceTaxTV = data.serviceTaxTV / 100;

    printf("Enter the service tax percentage: ");
    scanf("%f", &data.overallServiceTax);
    fflush(stdin);

    data.overallServiceTax = data.overallServiceTax / 100;

    fwrite(&data, sizeof(struct PTCLRates), 1, pointer);
    fclose(pointer);
}