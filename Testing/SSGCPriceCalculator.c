#include <stdio.h>

struct SSGCData {
    // New Structure
    unsigned long long int consumerId;
    char name[30];
    char address[70];
    unsigned long long int contactNumber;
    char usageType;
    // 0 = units, 1 = amount os natural gas used, 2 = Sales Tax, 3 = Income Tax, 4 = amount due, 5 = amount paid
    float unitsAndPayment[6][12];
    int billYear[12];
    float total;
};

struct SSGCRates {
    float upTo50;
    float upTo150;
    float upTo250;
    float upTo350;
    float upTo450;
    float moreThan450;
    float minR;
    float salesTaxR;
    float incomeTaxR;
    float unitPriceC;
    float minC;
    float salesTaxC;
    float incomeTaxC;
};

char* ssgcRates = "../DataFiles/SSGCRates.txt";

void SSGCPriceCalculator(struct SSGCData* data, int month);

int main() {
    // float temp1, temp2, price1, price2;
    
    // srand(time(0));
    // do {
    //     temp1 = rand() % 501;
    //     printf("Residential Units = %f\n", temp1);
    // } while (temp1 < 25 || temp1 > 500);

    // do {
    //     temp2 = rand() % 7001;
    //     printf("Industrial units = %f\n", temp2);
    // } while (temp2 < 25 || temp1 > 7000);

    // price1 = SSGCPriceCalculator(temp1, 'R');
    // price2 = SSGCPriceCalculator(temp2, 'I');

    // printf("Residential price = %.2f\n", price1);
    // printf("Industrial price = %.2f", price2);
}

void SSGCPriceCalculator(struct SSGCData* data, int month) {
    float price = 0, units = data->unitsAndPayment[0][month];
    FILE* pointer;
    struct SSGCRates prices;
    int counter1;

    pointer = fopen(ssgcRates, "rb");
    if (pointer == NULL) {
        printf("\nUnable to open file\n\n");
        return;
    }
    fread(&prices, sizeof(struct SSGCData), 1, pointer);
    fclose(pointer);
    
    switch (data->usageType) {
        case 'R': {
            if (units > 50) {
                price = 50 * prices.upTo50;
                units -= 50;
                if (units > 100) {
                    price += 100 * prices.upTo150;
                    units -= 100;
                    if (units > 100) {
                        price += 100 * prices.upTo250;
                        units -= 100;
                        if (units > 100) {
                            price += 100 * prices.upTo350;
                            units -= 100;
                            if (units > 100) {
                                price += 100 * prices.upTo450;
                                units -= 100;
                                if (units > 0) {
                                    price += units * prices.moreThan450;
                                }
                            }
                            else {
                                price += units * prices.upTo450;
                            }
                        }
                        else {
                            price += units * prices.upTo350;
                        }
                    }
                    else {
                        price += units * prices.upTo250;
                    }
                }
                else {
                    price += units * prices.upTo150;
                }
            }
            else {
                price = units * prices.upTo50;
            }

            if (price <= prices.minR) {
                price = prices.minR;
            }

            data->unitsAndPayment[1][month] = price;
            data->unitsAndPayment[2][month] = price * prices.salesTaxR;
            data->unitsAndPayment[3][month] = price * prices.incomeTaxR;
            data->unitsAndPayment[4][month] = 0;

            for (counter1 = 1; counter1 < 4; counter1++) {
                data->unitsAndPayment[4][month] += data->unitsAndPayment[counter1][month];
            }            

            break;
        }

        case 'I': {
            price = units * 1225.25;
            if (price <= 29967.34) {
                price = 29967.34;
            }
            break;
        }

        default: {
            price = 0;
            break;
        }
    }    

    return price;
}