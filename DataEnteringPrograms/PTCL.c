#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <time.h>

struct PTCLData {
    unsigned long long int accountID;
    char name[30];
    char address[70];
    unsigned long long int contactNumber;
    int packageLandline;
    int packageBroadband;
    char packageTV;
    char packageCharji;
    int onNetMinutes[12];
    int mobileMinutes[12];
    int otherMinutes[12];
    int internationalZone1Minutes[12];
    int internationalOtherZoneMinutes[12];
    // 0 = bill of PTCL, 1 = Service Tax, 2 = Withholding Tax, 3 = Late Payment Surcgarge, 4 = Total Bill, 5 = Recieved Payment
    float payments[6][12];
};

int ArraySize(FILE* pointer, int structSize);
bool PTCLAccountIDVerification(unsigned long long int accountID);
bool ContactNumberVerification(unsigned long long int number);
void PTCLPriceCalculator(struct PTCLData userInfo, int counter2, float payments[6][12]);

int main() {
    struct PTCLData userData[125];
    FILE* pointer;
    int userLength, counter, counter2, sizeFromFile = 0;
    int tempOnNetMinutes, tempMobileMinutes, tempOtherMinutes, tempInt1Minutes, tempIntOtherMinutes;

    pointer = fopen("PTCLData.txt", "rb");

    if (pointer == NULL) {
        fclose(pointer);
        pointer = fopen("PTCLData.txt", "ab");
        fclose(pointer);
        pointer = fopen("PTCLData.txt", "rb");
        if (pointer == NULL) {
            printf("Error Opening file! Closing program.\nPress enter to continue...");
            getch();
            exit(1);
        }
    }

    sizeFromFile = ArraySize(pointer, sizeof(struct PTCLData));
    fread(userData, sizeof(struct PTCLData), sizeFromFile, pointer);

    fclose(pointer);

    if (sizeFromFile > 120) {
        printf("Entries exceed 120 so no need of more data! Exiting program...\nPress enter to continue...");
        getch();
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

    pointer = fopen("PTCLData.txt", "wb");

    if (pointer == NULL) {
        printf("\n\nUnable to open file! Closing program\nPress enter to continue...");
        getch();
        exit(1);
    }

    for (counter = sizeFromFile; counter < userLength + sizeFromFile; counter++) {
        accountID:
        printf("Enter account ID of person %d: ", counter + 1);
        scanf("%llu", &userData[counter].accountID);
        fflush(stdin);
        while (!PTCLAccountIDVerification(userData[counter].accountID)) {
            printf("Incorrect value!\n");
            printf("Enter account ID of person %d again: ", counter + 1);
            scanf("%llu", &userData[counter].accountID);
            fflush(stdin);
        }
        for (counter2 = 0; counter2 < counter; counter2++) {
            if(userData[counter].accountID == userData[counter2].accountID) {
                printf("\nUser already exist with this account ID. Enter another ID\n");
                goto accountID;
            }
        }

        printf("Enter name of person %d: ", counter + 1);
        gets(userData[counter].name);
        fflush(stdin);

        printf("Enter address of person %d: ", counter + 1);
        gets(userData[counter].address);
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

        printf("\nEnter 1 for Basic Package\n");
        printf("Enter 500 for Freedom 500\n");
        printf("Enter 1000 for Freedom 1000\n");
        printf("Enter 3000 for Freedom 3000\n");
        printf("Enter 5000 for Freedom 5000\n");
        printf("Enter 8000 for Freedom 8000\n");        
        printf("Enter landline package of person %d: ", counter + 1);
        scanf("%d", &userData[counter].packageLandline);
        fflush(stdin);
        while (userData[counter].packageLandline != 500 && userData[counter].packageLandline != 1000 && userData[counter].packageLandline != 3000 && userData[counter].packageLandline != 5000 && userData[counter].packageLandline != 8000 && userData[counter].packageLandline != 1) {
            printf("\nInvaid Option selected\n");
            printf("Enter package land line of person %d again: ", counter + 1);
            scanf("%d", &userData[counter].packageLandline);
            fflush(stdin);
        }

        printf("\nEnter 6 for 6Mbps broadband package\n");
        printf("Enter 8 for 8Mbps broadband package\n");
        printf("Enter 15 for 15Mbps broadband package\n");
        printf("Enter 25 for 25Mbps broadband package\n");
        printf("Enter 50 for 50Mbps broadband package\n");
        printf("Enter 100 for 100Mbps broadband package\n");
        printf("Enter 0 for no active broadband package\n");
        printf("Enter broadband package of person %d: ", counter + 1);
        scanf("%d", &userData[counter].packageBroadband);
        fflush(stdin);
        while (userData[counter].packageBroadband != 6 && userData[counter].packageBroadband != 8 && userData[counter].packageBroadband != 15 && userData[counter].packageBroadband != 25 && userData[counter].packageBroadband != 50 && userData[counter].packageBroadband != 100 && userData[counter].packageBroadband != 0) {
            printf("\nInvaid Option selected\n");
            printf("Enter broadband package of person %d again: ", counter + 1);
            scanf("%d", &userData[counter].packageBroadband);
            fflush(stdin);
        }

        printf("\nEnter T for Smart TV only\n");
        printf("Enter A for Smart TV App only\n");
        printf("Enter B for both Smart TVs\n");
        printf("Enter N for no Smart TV packages active\n");
        printf("Enter Smart TV package for person %d: ", counter + 1);
        scanf("%c", &userData[counter].packageTV);
        fflush(stdin);
        while (userData[counter].packageTV != 'T' && userData[counter].packageTV != 'A' && userData[counter].packageTV != 'B' && userData[counter].packageTV != 'N') {
            printf("\nInvaid Option selected\n");
            printf("Enter Smart TV package for person %d again: ", counter + 1);
            printf("%c", &userData[counter].packageTV);
            fflush(stdin);
        }

        printf("\nEnter U for Unlimited Data package on Charji\n");
        printf("Enter S for 20 GB Data package on Charji\n");
        printf("Enter M for 30 GB Data package on Charji\n");
        printf("Enter L for 50 GB Data package on Charji\n");
        printf("Enter N for no Data package on Charji\n");
        printf("Enter Charji Package for person %d: ", 1);
        scanf("%c", &userData[counter].packageCharji);
        fflush(stdin);
        while (userData[counter].packageCharji != 'U' && userData[counter].packageCharji != 'S' && userData[counter].packageCharji != 'M' && userData[counter].packageCharji != 'L' && userData[counter].packageCharji != 'N') {
            printf("\nInvaid Option selected\n");
            printf("Enter Charji Package for person %d again: ", 1);
            scanf("%c", &userData[counter].packageCharji);
            fflush(stdin);
        }

        srand(time(0));
        
        for (counter2 = 0; counter2 < 12; counter2++) {
            tempOnNetMinutes = 0;
            tempMobileMinutes = 0;
            tempOtherMinutes = 0;
            tempInt1Minutes = 0;
            tempIntOtherMinutes = 0;

            do {
                tempOnNetMinutes = rand() % 15001;
            } while (tempOnNetMinutes < 0 || tempOnNetMinutes > 15000);

            do {
                tempMobileMinutes = rand() % 15001;
            } while (tempMobileMinutes < 0 || tempMobileMinutes > 15000);

            do {
                tempOtherMinutes = rand() % 251;
            } while (tempOtherMinutes < 0 || tempOtherMinutes > 250);

            do {
                tempInt1Minutes = rand() % 151;
            } while (tempInt1Minutes < 0 || tempInt1Minutes > 150);

            do {
                tempIntOtherMinutes = rand() % 151;
            } while (tempIntOtherMinutes < 0 || tempIntOtherMinutes > 150);

            userData[counter].onNetMinutes[counter2] = tempOnNetMinutes;
            userData[counter].mobileMinutes[counter2] = tempMobileMinutes;
            userData[counter].otherMinutes[counter2] = tempOtherMinutes;
            userData[counter].internationalZone1Minutes[counter2] = tempInt1Minutes;
            userData[counter].internationalOtherZoneMinutes[counter2] = tempIntOtherMinutes;

            PTCLPriceCalculator(userData[counter], counter2, userData[counter].payments);
        }

        printf("\n\n");
    }

    fwrite(userData, sizeof(struct PTCLData), userLength + sizeFromFile, pointer);
    fclose(pointer);
    
    printf("Data Written successfully!\nPress enter to continue...");
    getch();
    
}

int ArraySize(FILE* pointer, int structSize) {
    int size;

    fseek(pointer, 0L, SEEK_END);
    size = ftell(pointer);
    size = size / structSize;
    fseek(pointer, 0L, SEEK_SET);

    return size;
}

bool PTCLAccountIDVerification(unsigned long long int accountID) {
    if (accountID >= 1000000000 && accountID <= 9999999999) {
        return true;
    }
    else {
        return false;
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

void PTCLPriceCalculator(struct PTCLData userInfo, int counter2, float payments[6][12]) {
    int counter1;
    float price = 0, tempRate = 0, telephoneBill = 0, serviceTax = 0, withholdingTax = 0;

    srand(time(0));
    do {
        tempRate = rand() % 41;
    } while (tempRate >= 35 && tempRate <= 40);
    // tempRate = 37.5;

    price += userInfo.otherMinutes[counter2] * 2;
    price += userInfo.internationalOtherZoneMinutes[counter2] * tempRate;

    if (userInfo.packageLandline != 1 && userInfo.packageBroadband == 0) {
        switch (userInfo.packageLandline) {
            case 1: {                
                price += userInfo.mobileMinutes[counter2] * 2.5;
                price += userInfo.internationalZone1Minutes[counter2] * 3.6;            
                break;
            }

            case 500: {
                userInfo.mobileMinutes[counter2] -= 200;
                
                if (userInfo.mobileMinutes[counter2] > 0) {
                    price += userInfo.mobileMinutes[counter2] * 2.5;
                }            
                price += userInfo.internationalZone1Minutes[counter2] * 3.6;            
                break;
            }

            case 1000: {
                userInfo.mobileMinutes[counter2] -= 700;
                userInfo.internationalZone1Minutes[counter2] -= 200;

                if (userInfo.mobileMinutes[counter2] > 0) {
                    price += userInfo.mobileMinutes[counter2] * 2.5;
                }            
                if (userInfo.internationalZone1Minutes[counter2] > 0) {
                    price += userInfo.internationalZone1Minutes[counter2] * 3.6;
                }            
                break;
            }

            case 3000: {
                userInfo.mobileMinutes[counter2] -= 2000;
                userInfo.internationalZone1Minutes[counter2] -= 200;

                if (userInfo.mobileMinutes[counter2] > 0) {
                    price += userInfo.mobileMinutes[counter2] * 2.5;
                }
                if (userInfo.internationalZone1Minutes[counter2] > 0) {
                    price += userInfo.internationalZone1Minutes[counter2] * 3.6;
                }            
                break;
            }

            case 5000: {
                userInfo.mobileMinutes[counter2] -= 4000;
                userInfo.internationalZone1Minutes[counter2] -= 400;

                if (userInfo.mobileMinutes[counter2] > 0) {
                    price += userInfo.mobileMinutes[counter2] * 2.5;
                }            
                if (userInfo.internationalZone1Minutes[counter2] > 0) {
                    price += userInfo.internationalZone1Minutes[counter2] * 3.6;
                }            
                break;
            }

            case 8000: {
                userInfo.mobileMinutes[counter2] -= 8000;
                userInfo.internationalZone1Minutes[counter2] -= 800;

                if (userInfo.mobileMinutes[counter2] > 0) {
                    price += userInfo.mobileMinutes[counter2] * 2.5;
                }            
                if (userInfo.internationalZone1Minutes[counter2] > 0) {
                    price += userInfo.internationalZone1Minutes[counter2] * 3.6;
                }            
                break;
            }
            
            default:
                break;
        }

        telephoneBill = price;
    }
    
    

    switch (userInfo.packageBroadband) {
        case 0: {
            break;
        }

        case 6: {
            price += 1799;
            break;
        }

        case 8: {
            price += 2249;
            break;
        }

        case 15: {
            price += 2749;
            break;
        }

        case 25: {
            price += 3299;
            break;
        }

        case 50: {
            price += 5099;
            break;
        }

        case 100: {
            price += 7599;
            break;
        }
        
        default: {
            break;
        }
    }

    switch (userInfo.packageTV) {
        case 'N': {
            break;
        }
        
        case 'T': {
            if (userInfo.packageBroadband == 0) {
                price += 799;
            }

            if (userInfo.packageBroadband == 6) {
                price += 525;
            }
            break;
        }

        case 'A': {
            if (userInfo.packageBroadband == 0 || userInfo.packageBroadband == 6) {
                price += 99;   
            }            
            break;
        }

        case 'B': {
            if (userInfo.packageBroadband == 0) {
                price += 799;
                price += 99;
            }

            if (userInfo.packageBroadband == 6) {
                price += 525;
                price += 99;
            }

        }
        
        default:
            break;
    }

    switch (userInfo.packageCharji) {
        case 'U': {
            price += 1999;
            break;
        }

        case 'S': {
            price += 1000;
            break;
        }

        case 'M': {
            price += 1250;
            break;
        }

        case 'L': {
            price += 1500;
            break;
        }

        case 'N': {
            break;
        }
    }

    serviceTax += price * 0.195;

    if (telephoneBill > 1000) {
        withholdingTax += price * 0.1;
    }

    if (userInfo.packageBroadband != 0 || userInfo.packageCharji != 'N') {
        serviceTax += price * 0.195;
        withholdingTax += price * 0.125;
    }

    if (userInfo.packageTV != 'N') {
        serviceTax += price * 0.1;
    }

    *(*(payments + 0) + counter2) = price;
    *(*(payments + 1) + counter2) = serviceTax;
    *(*(payments + 2) + counter2) = withholdingTax;
    *(*(payments + 3) + counter2) = 0;
    *(*(payments + 4) + counter2) = 0;
    
    for ( counter1 = 0; counter1 < 4; counter1++) {
        *(*(payments + 4) + counter2) += *(*(payments + counter1) + counter2);
    }
}