#include <stdio.h>

float SSGCPriceCalculator(float units, char usageType);

int main() {
    float temp1, temp2, price1, price2;
    
    srand(time(0));
    do {
        temp1 = rand() % 501;
        printf("Residential Units = %f\n", temp1);
    } while (temp1 < 25 || temp1 > 500);

    do {
        temp2 = rand() % 7001;
        printf("Industrial units = %f\n", temp2);
    } while (temp2 < 25 || temp1 > 7000);

    price1 = SSGCPriceCalculator(temp1, 'R');
    price2 = SSGCPriceCalculator(temp2, 'I');

    printf("Residential price = %.2f\n", price1);
    printf("Industrial price = %.2f", price2);
}

float SSGCPriceCalculator(float units, char usageType) {
    float price = 0;
    
    switch (usageType) {
        case 'R': {
            if (units > 50) {
                price = 50 * 121;
                units -= 50;
                if (units > 100) {
                    price += 100 * 300;
                    units -= 100;
                    if (units > 100) {
                        price += 100 * 553;
                        units -= 100;
                        if (units > 100) {
                            price += 100 * 738;
                            units -= 100;
                            if (units > 100) {
                                price += 100 * 1107;
                                units -= 100;
                                if (units > 0) {
                                    price += units * 1460;
                                }
                            }
                            else {
                                price += units * 1107;
                            }
                        }
                        else {
                            price += units * 738;
                        }
                    }
                    else {
                        price += units * 553;
                    }
                }
                else {
                    price += units * 300;
                }
            }
            else {
                price = units * 121;
            }

            if (price <= 172.58) {
                price = 172.58;
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