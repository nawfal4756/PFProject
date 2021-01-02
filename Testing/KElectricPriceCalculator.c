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
    units = data->unitsAndPayment[0][month] + data->unitsAndPayment[1][month];

    switch (data->usageType) {
        case 'R': {
            if (data->allotedLoad < 5) {
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
                price += data->unitsAndPayment[1][month] * 22.35;
                price += data->unitsAndPayment[0][month] * 16.03;
            }

            if (price < 150) {
                price = 150;
            }

            break;
        }

        case 'C': {
            if (data->allotedLoad < 5) {
                price = units * 19.09;
            }
            else {
                price += data->unitsAndPayment[0][month] * 18.52;
                price += data->unitsAndPayment[1][month] * 24.49;
            }
            
            if (price < 350) {
                price = 350;
            }
        }
    }

    data->unitsAndPayment[2][month] = price;

    switch (data->usageType) {
        case 'R': {            
            data->unitsAndPayment[3][month] = price * 0.015;
            data->unitsAndPayment[4][month] = price * 0.17;
            data->unitsAndPayment[5][month] = price * 0.04;
            data->unitsAndPayment[6][month] = data->numberOfTV * 35;
            break;
        }

        case 'C': {
            data->unitsAndPayment[3][month] = price * 0.02;
            data->unitsAndPayment[4][month] = price * 0.17;
            data->unitsAndPayment[5][month] = price * 0.08;
            data->unitsAndPayment[6][month] = data->numberOfTV * 60;
            break;
        }
    }

    data->unitsAndPayment[7][month] = 0;

    for (counter = 2; counter < 7; counter++) {
        data->unitsAndPayment[7][month] += data->unitsAndPayment[counter][month];
    }

    data->unitsAndPayment[8][month] = 0;                
}