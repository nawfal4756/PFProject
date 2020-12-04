#include <stdio.h>

float SSGCPriceCalculator(float units);

int main() {
    float temp, price;
    
    srand(time(NULL));
    do {
        temp = rand() % 501;
        printf("%f\n", temp);
    } while (temp < 25 || temp > 500);

    price = SSGCPriceCalculator(temp);
    printf("%.2f", price);
}

float SSGCPriceCalculator(float units) {
    float price = 0;
    
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

    return price;
}