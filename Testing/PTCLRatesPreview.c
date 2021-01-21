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

void PTCLRatesPreview();

int main() {
    PTCLRatesPreview();
}

void PTCLRatesPreview() {
    FILE* pointer;
    struct PTCLRates data;

    pointer = fopen(ptclRates, "rb");

    if (pointer == NULL) {
        exit (1);
    }

    fread(&data, sizeof(struct PTCLRates), 1, pointer);

    printf("Price for Freedom 500 landline package: %.2f\n", data.freedom500L);
    printf("Price for Freedom 1000 landline package: %.2f\n", data.freedom1000L);
    printf("Price for Freedom 3000 landline package: %.2f\n", data.freedom3000L);
    printf("Price for Freedom 5000 landline package: %.2f\n", data.freedom5000L);
    printf("Price for Freedom 8000 landline package: %.2f\n", data.freedom8000L);
    printf("Charges for 6 Mbps broadband package: %.2f\n", data.mb6B);
    printf("Charges for 8 Mbps broadband package: %.2f\n", data.mb8B);
    printf("Charges for 15 Mbps broadband package: %.2f\n", data.mb15B);
    printf("Charges for 25 Mbps broadband package: %.2f\n", data.mb25B);
    printf("Charges for 50 Mbps broadband package: %.2f\n", data.mb50B);
    printf("Charges for 100 Mbps broadband package: %.2f\n", data.mb100B);
    printf("Charges for smart TV without broadband: %.2f\n", data.smartTVWOB);
    printf("Charges for smart TV without broadband: %.2f\n", data.smartTVWB);
    printf("Charges for smart TV App: %.2f\n", data.smartTVApp);
    printf("Charges for unlimited package of Charji: %.2f\n", data.dataUC);    
    printf("Charges for 20GB package of Charji: %.2f\n", data.data20C);
    printf("Charges for 30GB package of Charji: %.2f\n", data.data30C);
    printf("Charges for 50GB package of Charji: %.2f\n", data.data50C);
    printf("Charges of per minute for call on mobile numbers: %.2f\n", data.mobile);
    printf("Charges of per minute for call on other numbers: %.2f\n", data.other);
    printf("Charges of per minute for call on international zone 1 numbers: %.2f\n", data.internationalZone1);
    printf("Withholding tax percentage when telephone bill is greater than 1000: %.2f\n", data.withholdingTaxMoreThan1000L * 100);
    printf("Withholding tax percentage on broadband: %.2f\n", data.withholdingTaxB * 100);
    printf("Service tax percentage on broadband: %.2f\n", data.serviceTaxB * 100);
    printf("Service tax percentage on TV: %.2f\n", data.serviceTaxTV * 100);
    printf("Service tax percentage: %.2f\n", data.overallServiceTax * 100);
    
    fclose(pointer);
}