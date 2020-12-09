#include <stdio.h>

float KElectricPriceCalculator(float unitsOffPeak, float unitsOnPeak, float allotedKW, char usageType);

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

    price1 = KElectricPriceCalculator(temp1, temp2, 4, 'R');
    price2 = KElectricPriceCalculator(temp1, temp2, 8, 'R');
    price3 = KElectricPriceCalculator(temp1, temp2, 4, 'C');
    price4 = KElectricPriceCalculator(temp1, temp2, 8, 'C');
    printf("Less than 5kw R = %.2f\n", price1);
    printf("More than 5kw R = %.2f\n", price2);
    printf("Less than 5kw R = %.2f\n", price3);
    printf("More than 5kw R = %.2f\n", price4);
}

float KElectricPriceCalculator(float unitsOffPeak, float unitsOnPeak, float allotedKW, char usageType) {
    float price = 0, units = 0;
    units = unitsOffPeak + unitsOnPeak;

    switch (usageType) {
        case 'R': {
            if (allotedKW < 5) {
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
                price += unitsOnPeak * 22.35;
                price += unitsOffPeak * 16.03;
            }

            if (price < 150) {
                price = 150;
            }

            break;
        }

        case 'C': {
            if (allotedKW < 5) {
                price = units * 19.09;
            }
            else {
                price += unitsOffPeak * 18.52;
                price += unitsOnPeak * 24.49;
            }
            
            if (price < 350) {
                price = 350;
            }
        }
    }

    return price;
}