#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

bool KElectricAccountNumberVerification(unsigned long long int accountNumber);
bool ContactNumberVerification(unsigned long long int number);

struct KElectricData {
    unsigned long long int accountNumber;
    char name[30];
    char address[70];
    unsigned long long int contactNumber;
    // 0 = off peak units, 1 = on peak units, 2 = amount due, 3 = amount paid
    float unitsAndPayment[4][12];
    bool timePayment[12];
};

int main() {
    struct KElectricData userData[125];
    int userLength, counter, counter2, price, sizeFromFile;
    float tempUnitsOffPeak, tempUnitsOnPeak, tempPrice;
    char tempBool;
    FILE *pointer;

    pointer = fopen("KElectricData.txt", "rb");
    if (pointer != NULL) {
        sizeFromFile = ArraySize(pointer, sizeof(struct KElectricData));
        fread(userData, sizeof(struct KElectricData), sizeFromFile, pointer);        
    }
    else {
        printf("Unable to open file!");
        exit(1);
    }

    fclose(pointer);

    if (sizeFromFile > 120) {
        printf("Entries exceed 120 so no need of more data");
        exit(1);
    }
    
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

    pointer = fopen("KElectricData.txt", "wb");

    if (pointer != NULL) {

        for (counter = sizeFromFile; counter < userLength + sizeFromFile; counter++) {
            consumerID:
            printf("Enter account number of person %d: ", counter + 1);
            scanf("%llu", &userData[counter].accountNumber);
            fflush(stdin);
            while (!KElectricAccountNumberVerification(userData[counter].accountNumber)) {
                printf("Incorrect value!\n");
                printf("Enter consumer id of person %d again: ", counter + 1);
                scanf("%llu", &userData[counter].accountNumber);
                fflush(stdin);
            }
            for (counter2 = 0; counter2 < counter; counter2++) {
                if(userData[counter].accountNumber == userData[counter2].accountNumber) {
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
                tempUnitsOffPeak = 0;
                tempUnitsOnPeak = 0;

                do {
                    tempUnitsOffPeak = rand() % 1251;
                } while (tempUnitsOffPeak < 0 || tempUnitsOffPeak > 1250);

                do {
                    tempUnitsOnPeak = rand() % 1251;
                } while (tempUnitsOnPeak < 0 || tempUnitsOnPeak > 1250);

                userData[counter].unitsAndPayment[0][counter2] = tempUnitsOffPeak;
                userData[counter].unitsAndPayment[1][counter2] = tempUnitsOnPeak;
            }

            for (counter2 = 0; counter2 < 12; counter2++) {
                printf("Enter if paid on time or not for person %d and for month %d(T or F): ", counter + 1, counter2 + 1);
                timelyPayment:
                scanf("%c", &tempBool);
                fflush(stdin);
                switch (tempBool) {
                    case 'T': {
                        userData[counter].timePayment[counter2] = true;
                        break;
                    }
                    case 'F': {
                        userData[counter].timePayment[counter2] = false;
                        break;
                    }
                    default: {
                        printf("Incorrect option selected! Enter T or F\n");
                        printf("Enter if paid on time or not for person %d and for month %d(T or F) again: ", counter + 1, counter2 + 1);
                        goto timelyPayment;
                        break;
                    }
                }
            }
            
            printf("\n\n");
        }

        fwrite(userData, sizeof(struct KElectricData), userLength + sizeFromFile, pointer);
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

bool KElectricAccountNumberVerification(unsigned long long int accountNumber) {
    if (accountNumber >= 10000000000 && accountNumber <= 99999999999) {
        return true;
    }
    else {
        return false;
    }
}