#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

struct PTCLData {
    // New Structure
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
    int billYear[12];
    float total;
};

struct PTCLRates {
    float freedom500L;
    float freedom1000L;
    float freedom3000L;
    float freedom5000L;
    float freedom8000L;
    float mb6B;
    float mb8B;
    float mb15B;
    float mb25B;
    float mb50B;
    float mb100B;
    float smartTVWOB;
    float smartTVWB;
    float smartTVApp;
    float dataUC;
    float data20C;
    float data30C;
    float data50C;
    float mobile;
    float other;
    float internationalZone1;
    float withholdingTaxMoreThan1000L;
    float withholdingTaxB;
    float serviceTaxB;
    float serviceTaxTV;
    float overallServiceTax;
};

char* ptclRates = "../DataFiles/PTCLRates.txt";

void PTCLPriceCalculator(struct PTCLData* data, int month);


int main() {
    // struct PTCLData userData;
    // int counter = 0;

    // printf("\nEnter 1 for Basic Package\n");
    // printf("Enter 500 for Freedom 500\n");
    // printf("Enter 1000 for Freedom 1000\n");
    // printf("Enter 3000 for Freedom 3000\n");
    // printf("Enter 5000 for Freedom 5000\n");
    // printf("Enter 8000 for Freedom 8000\n");        
    // printf("Enter landline package of person %d: ", 1);
    // scanf("%d", &userData.packageLandline);
    // fflush(stdin);
    // while (userData.packageLandline != 500 && userData.packageLandline != 1000 && userData.packageLandline != 3000 && userData.packageLandline != 5000 && userData.packageLandline != 8000 && userData.packageLandline != 1) {
    //     printf("\nInvaid Option selected\n");
    //     printf("Enter package land line of person %d again: ", 1);
    //     scanf("%d", &userData.packageLandline);
    //     fflush(stdin);
    // }

    // printf("\nEnter 6 for 6Mbps broadband package\n");
    // printf("Enter 8 for 8Mbps broadband package\n");
    // printf("Enter 15 for 15Mbps broadband package\n");
    // printf("Enter 25 for 25Mbps broadband package\n");
    // printf("Enter 50 for 50Mbps broadband package\n");
    // printf("Enter 100 for 100Mbps broadband package\n");
    // printf("Enter 0 for no active broadband package\n");
    // printf("Enter broadband package of person %d: ", 1);
    // scanf("%d", &userData.packageBroadband);
    // fflush(stdin);
    // while (userData.packageBroadband != 6 && userData.packageBroadband != 8 && userData.packageBroadband != 15 && userData.packageBroadband != 25 && userData.packageBroadband != 50 && userData.packageBroadband != 100 && userData.packageBroadband != 0) {
    //     printf("\nInvaid Option selected\n");
    //     printf("Enter broadband package of person %d again: ", 1);
    //     scanf("%d", &userData.packageBroadband);
    //     fflush(stdin);
    // }

    // printf("\nEnter T for Smart TV only\n");
    // printf("Enter A for Smart TV App only\n");
    // printf("Enter B for both Smart TVs\n");
    // printf("Enter N for no Smart TV packages active\n");
    // printf("Enter Smart TV package for person %d: ", 1);
    // scanf("%c", &userData.packageTV);
    // fflush(stdin);
    // while (userData.packageTV != 'T' && userData.packageTV != 'A' && userData.packageTV != 'B' && userData.packageTV != 'N') {
    //     printf("\nInvaid Option selected\n");
    //     printf("Enter Smart TV package for person %d again: ", 1);
    //     printf("%c", &userData.packageTV);
    //     fflush(stdin);
    // }

    // printf("\nEnter U for Unlimited Data package on Charji\n");
    // printf("Enter S for 20 GB Data package on Charji\n");
    // printf("Enter M for 30 GB Data package on Charji\n");
    // printf("Enter L for 50 GB Data package on Charji\n");
    // printf("Enter N for no Data package on Charji\n");
    // printf("Enter Charji Package for person %d: ", 1);
    // scanf("%c", &userData.packageCharji);
    // fflush(stdin);
    // while (userData.packageCharji != 'U' && userData.packageCharji != 'S' && userData.packageCharji != 'M' && userData.packageCharji != 'L' && userData.packageCharji != 'N') {
    //     printf("\nInvaid Option selected\n");
    //     printf("Enter Charji Package for person %d again: ", 1);
    //     scanf("%c", &userData.packageCharji);
    //     fflush(stdin);
    // }

    // srand(time(0));
    
    // do {
    //     userData.onNetMinutes = rand() % 15001;
    // } while (userData.onNetMinutes < 0 || userData.onNetMinutes > 15000);
    
    // do {
    //     userData.mobileMinutes = rand() % 15001;
    // } while (userData.mobileMinutes < 0 || userData.mobileMinutes > 15000);
    
    // do {
    //     userData.otherMinutes = rand() % 251;
    // } while (userData.otherMinutes < 0 || userData.otherMinutes > 250);

    // do {
    //     userData.internationalZone1Minutes = rand() % 151;
    // } while (userData.internationalZone1Minutes < 0 || userData.internationalZone1Minutes > 150);
    
    // do {
    //     userData.internationalOtherZoneMinutes = rand() % 151;
    // } while (userData.internationalOtherZoneMinutes < 0 || userData.internationalOtherZoneMinutes > 150);

    // PTCLPriceCalculator(&userData, counter);

    // for (counter = 0; counter < 6; counter++) {
    //     printf("%.2f\n", userData.payments[counter][0]);
    // }

    // getch();
    
}

void PTCLPriceCalculator(struct PTCLData* data, int month) {
    int counter1;
    float price = 0, tempRate = 0, telephoneBill = 0, serviceTax = 0, withholdingTax = 0;
    struct PTCLData userInfo;
    struct PTCLRates rates;
    FILE* pointer;

    pointer = fopen(ptclRates, "rb");

    if (pointer == NULL) {
        printf("\nFile could not open\n\n");
        return;
    }
    fread(&rates, sizeof(struct PTCLRates), 1, pointer);
    fclose(pointer);

    userInfo = *data;

    srand(time(0));
    do {
        tempRate = rand() % 41;
    } while (tempRate >= 35 && tempRate <= 40);
    // tempRate = 37.5;

    price += userInfo.otherMinutes[month] * rates.other;
    price += userInfo.internationalOtherZoneMinutes[month] * tempRate;

    if (userInfo.packageLandline != 1 && userInfo.packageBroadband == 0) {
        switch (userInfo.packageLandline) {
            case 1: {
                price += userInfo.onNetMinutes[month] * 0;
                price += userInfo.mobileMinutes[month] * rates.mobile;
                price += userInfo.internationalZone1Minutes[month] * rates.internationalZone1;                            
                break;
            }

            case 500: {
                userInfo.mobileMinutes[month] -= 200;
                
                if (userInfo.mobileMinutes[month] > 0) {
                    price += userInfo.mobileMinutes[month] * rates.mobile;
                }            
                price += userInfo.internationalZone1Minutes[month] * rates.internationalZone1; 
                price += rates.freedom500L;          
                break;
            }

            case 1000: {
                userInfo.mobileMinutes[month] -= 700;
                userInfo.internationalZone1Minutes[month] -= 200;

                if (userInfo.mobileMinutes > 0) {
                    price += userInfo.mobileMinutes[month] * rates.mobile;
                }            
                if (userInfo.internationalZone1Minutes > 0) {
                    price += userInfo.internationalZone1Minutes[month] * rates.internationalZone1;
                }
                price += rates.freedom1000L;
                break;
            }

            case 3000: {
                userInfo.mobileMinutes[month] -= 2000;
                userInfo.internationalZone1Minutes[month] -= 200;

                if (userInfo.mobileMinutes > 0) {
                    price += userInfo.mobileMinutes[month] * rates.mobile;
                }
                if (userInfo.internationalZone1Minutes > 0) {
                    price += userInfo.internationalZone1Minutes[month] * rates.internationalZone1;
                }
                price += rates.freedom3000L;     
                break;
            }

            case 5000: {
                userInfo.mobileMinutes[month] -= 4000;
                userInfo.internationalZone1Minutes[month] -= 400;

                if (userInfo.mobileMinutes > 0) {
                    price += userInfo.mobileMinutes[month] * rates.mobile;
                }            
                if (userInfo.internationalZone1Minutes > 0) {
                    price += userInfo.internationalZone1Minutes[month] * rates.internationalZone1;
                }
                price += rates.freedom5000L;
                break;
            }

            case 8000: {
                userInfo.mobileMinutes[month] -= 8000;
                userInfo.internationalZone1Minutes[month] -= 800;

                if (userInfo.mobileMinutes > 0) {
                    price += userInfo.mobileMinutes[month] * rates.mobile;
                }            
                if (userInfo.internationalZone1Minutes > 0) {
                    price += userInfo.internationalZone1Minutes[month] * rates.internationalZone1;
                }
                price += rates.freedom8000L;    
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
            price += rates.mb6B;
            break;
        }

        case 8: {
            price += rates.mb8B;
            break;
        }

        case 15: {
            price += rates.mb15B;
            break;
        }

        case 25: {
            price += rates.mb25B;
            break;
        }

        case 50: {
            price += rates.mb50B;
            break;
        }

        case 100: {
            price += rates.mb100B;
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
                price += rates.smartTVWOB;
            }

            if (userInfo.packageBroadband == 6) {
                price += rates.smartTVWB;
            }
            break;
        }

        case 'A': {
            if (userInfo.packageBroadband == 0 || userInfo.packageBroadband == 6) {
                price += rates.smartTVApp;   
            }            
            break;
        }

        case 'B': {
            if (userInfo.packageBroadband == 0) {
                price += rates.smartTVWOB;
                price += rates.smartTVApp;
            }

            if (userInfo.packageBroadband == 6) {
                price += rates.smartTVWB;
                price += rates.smartTVApp;
            }

        }
        
        default:
            break;
    }

    switch (userInfo.packageCharji) {
        case 'U': {
            price += rates.dataUC;
            break;
        }

        case 'S': {
            price += rates.data20C;
            break;
        }

        case 'M': {
            price += rates.data30C;
            break;
        }

        case 'L': {
            price += rates.data50C;
            break;
        }

        case 'N': {
            break;
        }
    }

    serviceTax += price * rates.overallServiceTax;

    if (telephoneBill > 1000) {
        withholdingTax += price * rates.withholdingTaxMoreThan1000L;
    }

    if (userInfo.packageBroadband != 0 || userInfo.packageCharji != 'N') {
        serviceTax += price * rates.serviceTaxB;
        withholdingTax += price * rates.withholdingTaxB;
    }

    if (userInfo.packageTV != 'N') {
        serviceTax += price * rates.serviceTaxTV;
    }

    data->payments[0][month] = price;
    data->payments[1][month] = serviceTax;
    data->payments[2][month] = withholdingTax;
    data->payments[3][month] = 0;
    data->payments[4][month] = 0;
    
    for ( counter1 = 0; counter1 < 4; counter1++) {
        data->payments[4][month] += data->payments[counter1][month];
    }
}