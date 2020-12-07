#include <stdio.h>

float KElectricPriceCalculator(float unitsOffPeak, float unitsOnPeak, float allotedKW);

int main() {
    float temp, temp1, temp2, price1, price2;
    
    srand(time(0));
    do {
        temp1 = rand() % 1251;
        temp2 = rand() % 1251;
        temp = temp1 + temp2;
        printf("%f\n", temp1);
        printf("%f\n", temp2);
    } while (temp < 0 || temp > 2501);

    price1 = KElectricPriceCalculator(temp1, temp2, 5);
    price1 = KElectricPriceCalculator(temp1, temp2, 8);
    printf("Less than 5kw = %.2f\n", price1);
    printf("More than 5kw = %.2f\n", price2);
}

float KElectricPriceCalculator(float unitsOffPeak, float unitsOnPeak, float allotedKW) {
    float price = 0, units = 0;
    
    if (allotedKW <= 5) {
        units = unitsOffPeak + unitsOnPeak;
        if (units <= 50) {
            price = units * 2;
        }
        if (units > 100) {
            units -= 100;
            price += 100 * 5.79;
            if (units > 100) {
                units -= 100;
                price += 100 * 8.11;
                if (units > 100) {
                    units -= 100;
                    price += 100 * 10.2;
                    if (units > 400) {
                        units -= 400;
                        price += 400 * 19.25;
                        if (units > 0) {
                            price += units * 22.35;
                        }
                    }
                    else {
                        price += units * 19.25;
                    }
                }
                else {
                    price += units * 10.2;    
                }
            }
            else {
                price += units * 8.11;
            }
        }
        else {
            price += units * 5.79;
        }
    }
    else {

    }

    return price;
}