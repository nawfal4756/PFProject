#include <stdio.h>
#include <stdbool.h>

struct KElectricData {
    //New Structure
    unsigned long long int accountNumber;
    char name[30];
    char address[70];
    unsigned long long int contactNumber;
    char usageType;
    float allotedLoad;
    int numberOfTV;
    // 0 = off peak units, 1 = on peak units, 2 = amount of electricity, 3 = electricity duty, 4 = Sales Tax, 5 = Income tax, 6 = tv license fee, 7 = amount due, 8 = amount paid
    float unitsAndPayment[9][12];
    int billYear[12];
    bool timePayment[12];
    float total;
};

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

void KElectricPriceCalculator(struct KElectricData* data, int month);

int main() {
    float temp, temp1, temp2, price1, price2, price3, price4;
    
    srand(time(0));
    do {
        temp1 = rand() % 1251;
        temp2 = rand() % 1251;
        temp = temp1 + temp2;
        printf("%f\n", temp1);
        printf("%f\n", temp2);
    } while (temp < 0 || temp > 2501);

}

void KElectricPriceCalculator(struct KElectricData* data, int month) {
    int counter;
    float price = 0, units = 0;
    FILE* pointer;
    struct KElectricRates rates;

    pointer = fopen(kelectricRates, "rb");
    if (pointer == NULL) {
        printf("\nUnable to open file\n\n");
    }
    fread(&rates, sizeof(struct KElectricRates), 1, pointer);
    fclose(pointer);

    units = data->unitsAndPayment[0][month] + data->unitsAndPayment[1][month];

    switch (data->usageType) {
        case 'R': {
            if (data->allotedLoad < 5) {
                if (units <= 50) {
                    price = units * rates.unitsUpto50;
                }
                if (units > 100) {
                    units -= 100;
                    price += 100 * rates.unitsUpto100;
                    if (units > 100) {
                        units -= 100;
                        price += 100 * rates.unitsUpto200;
                        if (units > 100) {
                            units -= 100;
                            price += 100 * rates.unitsUpto300;
                            if (units > 400) {
                                units -= 400;
                                price += 400 * rates.unitsUpto700;
                                if (units > 0) {
                                    price += units * rates.unitsAbove700;
                                }
                            }
                            else {
                                price += units * rates.unitsUpto700;
                            }
                        }
                        else {
                            price += units * rates.unitsUpto300;    
                        }
                    }
                    else {
                        price += units * rates.unitsUpto200;
                    }
                }
                else {
                    price += units * rates.unitsUpto100;
                }
            }
            else {
                price += data->unitsAndPayment[1][month] * rates.onPeakUnitsMoreThan5KW;
                price += data->unitsAndPayment[0][month] * rates.offPeakUnitsMoreThan5KW;
            }

            if (price < rates.minR) {
                price = rates.minR;
            }

            break;
        }

        case 'C': {
            if (data->allotedLoad < 5) {
                price = units * rates.unitsLessThan5KWC;
            }
            else {
                price += data->unitsAndPayment[0][month] * rates.offPeakUnitsMoreThan5KWC;
                price += data->unitsAndPayment[1][month] * rates.onPeakUnitsMoreThan5KWC;
            }
            
            if (price < rates.minC) {
                price = rates.minC;
            }
        }
    }

    data->unitsAndPayment[2][month] = price;

    switch (data->usageType) {
        case 'R': {            
            data->unitsAndPayment[3][month] = price * rates.electricityDutyR;
            data->unitsAndPayment[4][month] = price * rates.salesTaxR;
            data->unitsAndPayment[5][month] = price * rates.incomeTaxR;
            data->unitsAndPayment[6][month] = data->numberOfTV * rates.tvLicenseFeeR;
            break;
        }

        case 'C': {
            data->unitsAndPayment[3][month] = price * rates.electricityDutyC;
            data->unitsAndPayment[4][month] = price * rates.salesTaxC;
            data->unitsAndPayment[5][month] = price * rates.incomeTaxC;
            data->unitsAndPayment[6][month] = data->numberOfTV * rates.tvLicenseFeeC;
            break;
        }
    }

    data->unitsAndPayment[7][month] = 0;

    for (counter = 2; counter < 7; counter++) {
        data->unitsAndPayment[7][month] += data->unitsAndPayment[counter][month];
    }

    
    data->unitsAndPayment[8][month] = 0;                
}