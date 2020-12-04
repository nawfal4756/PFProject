#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<time.h>

struct SSGCData {
    unsigned long long int consumerId;
    char name[30];
    char address[70];
    unsigned long long int contactNumber;
    float unitsAndPayment[3][12];
};

bool ContactNumberVerification(unsigned long long int number);
float SSGCPriceCalculator(float units);
int ArraySize(FILE* pointer, int structSize);

int main() {
    struct SSGCData userData[125];
    int userLength, counter, counter2, price, sizeFromFile;
    float tempUnits, tempPrice;
    FILE *pointer;

    pointer = fopen("SSGCData.txt", "rb");
    if (pointer != NULL) {
        sizeFromFile = ArraySize(pointer, sizeof(struct SSGCData));
        fread(userData, sizeof(struct SSGCData), sizeFromFile, pointer);        
    }
    else {
        printf("Unable to open file!");
        exit(1);
    }

    fclose(pointer);
    
    printf("Enter number of records you want to enter: ");
    scanf("%d", &userLength);
    fflush(stdin);
    while (userLength < 0 || userLength >= 20) {
        printf("Incorrect value!\n");
        printf("Enter value between 1 and 20 inclusive\n");
        printf("Enter number of records you want to enter again: ");
        scanf("%d", &userLength);
        fflush(stdin);
    }

    pointer = fopen("SSGCData.txt", "wb");

    if (pointer != NULL) {

        for (counter = sizeFromFile; counter < userLength + sizeFromFile; counter++) {
            consumerID:
            printf("Enter consumer id of person %d: ", counter + 1);
            scanf("%llu", &userData[counter].consumerId);
            fflush(stdin);
            while (userData[counter].consumerId < 999999999 || userData[counter].consumerId > 10000000000) {
                printf("Incorrect value!\n");
                printf("Enter consumer id of person %d again: ", counter + 1);
                scanf("%llu", &userData[counter].consumerId);
                fflush(stdin);
            }
            for (counter2 = 0; counter2 < counter; counter2++) {
                if(userData[counter].consumerId == userData[counter2].consumerId) {
                    printf("\nUser already exist with this consumer ID. Enter another ID\n");
                    goto consumerID;
                }
            }

            printf("Enter name of person %d: ", counter + 1);
            scanf("%s", &userData[counter].name);
            fflush(stdin);

            printf("Enter address of person %d: ", counter + 1);
            scanf("%s", &userData[counter].address);
            fflush(stdin);

            printf("Enter contact number of person %d: ", counter + 1);
            scanf("%llu", &userData[counter].contactNumber);
            fflush(stdin);
            while (!ContactNumberVerification(userData[counter].contactNumber)) {
                printf("Incorrect value!\n");
                printf("Enter contact number of person %d again: ", counter + 1);
                scanf("%llu", &userData[counter].contactNumber);
                fflush(stdin);
            }

            
            srand(time(0));
            for (counter2 = 0; counter2 < 12; counter2++) {
                tempUnits = 0;
                do {
                    tempUnits = rand() % 501;                
                } while (tempUnits < 25 || tempUnits > 500);

                userData[counter].unitsAndPayment[0][counter2] = tempUnits;
                userData[counter].unitsAndPayment[1][counter2] = SSGCPriceCalculator(userData[counter].unitsAndPayment[0][counter2]);
                price = userData[counter].unitsAndPayment[1][counter2];

                if (userData[counter].unitsAndPayment[1][counter2] < 200000) {
                    tempPrice = userData[counter].unitsAndPayment[1][counter2];
                }
                else {
                    do {
                        tempPrice = rand() % price;                
                    } while (tempPrice > price); 
                }
                
                userData[counter].unitsAndPayment[2][counter2] = tempPrice;
                
            }
            
        }

        fwrite(userData, sizeof(struct SSGCData), userLength + sizeFromFile, pointer);
        printf("\n\nData written on file successfully!");

        fclose(pointer);
    }
    else {
        printf("\n\nUnable to open file!");
        exit(1);
    }

}

bool ContactNumberVerification(unsigned long long int number) {
    int temp;
    temp = number / 1000000000;
    
    if (temp == 3) {        
        if (number >= 3000000000 && number <= 39999999999) {
            return true;
        }
    }

    return false;
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

int ArraySize(FILE* pointer, int structSize) {
    int size;

    fseek(pointer, 0L, SEEK_END);
    size = ftell(pointer);
    size = size / structSize;
    fseek(pointer, 0L, SEEK_SET);

    return size;
}