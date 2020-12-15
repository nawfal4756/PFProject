#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

void PTCLPriceCalculator(int packageLandline, int packageBroadband, char packageTV, char packageCharji, int onNetMinutes, int mobileMinutes, int otherMinutes, int internationalZone1Minutes, int internationalOtherZoneMinutes, int counter2, float payments[6][12]);

struct PTCLData {
    int packageLandline;
    int packageBroadband;
    char packageTV;
    char packageCharji;
    int onNetMinutes;
    int mobileMinutes;
    int otherMinutes;
    int internationalZone1Minutes;
    int internationalOtherZoneMinutes;
    // 0 = bill of PTCL, 1 = Service Tax, 2 = Withholding Tax, 3 = Late Payment Surcgarge, 4 = Total Bill, 5 = Recieved Payment
    float payments[6][12];
};

int main() {
    struct PTCLData userData;
    int counter = 0;

    printf("\nEnter 1 for Basic Package\n");
    printf("Enter 500 for Freedom 500\n");
    printf("Enter 1000 for Freedom 1000\n");
    printf("Enter 3000 for Freedom 3000\n");
    printf("Enter 5000 for Freedom 5000\n");
    printf("Enter 8000 for Freedom 8000\n");        
    printf("Enter landline package of person %d: ", 1);
    scanf("%d", &userData.packageLandline);
    fflush(stdin);
    while (userData.packageLandline != 500 && userData.packageLandline != 1000 && userData.packageLandline != 3000 && userData.packageLandline != 5000 && userData.packageLandline != 8000 && userData.packageLandline != 1) {
        printf("\nInvaid Option selected\n");
        printf("Enter package land line of person %d again: ", 1);
        scanf("%d", &userData.packageLandline);
        fflush(stdin);
    }

    printf("\nEnter 6 for 6Mbps broadband package\n");
    printf("Enter 8 for 8Mbps broadband package\n");
    printf("Enter 15 for 15Mbps broadband package\n");
    printf("Enter 25 for 25Mbps broadband package\n");
    printf("Enter 50 for 50Mbps broadband package\n");
    printf("Enter 100 for 100Mbps broadband package\n");
    printf("Enter 0 for no active broadband package\n");
    printf("Enter broadband package of person %d: ", 1);
    scanf("%d", &userData.packageBroadband);
    fflush(stdin);
    while (userData.packageBroadband != 6 && userData.packageBroadband != 8 && userData.packageBroadband != 15 && userData.packageBroadband != 25 && userData.packageBroadband != 50 && userData.packageBroadband != 100 && userData.packageBroadband != 0) {
        printf("\nInvaid Option selected\n");
        printf("Enter broadband package of person %d again: ", 1);
        scanf("%d", &userData.packageBroadband);
        fflush(stdin);
    }

    printf("\nEnter T for Smart TV only\n");
    printf("Enter A for Smart TV App only\n");
    printf("Enter B for both Smart TVs\n");
    printf("Enter N for no Smart TV packages active\n");
    printf("Enter Smart TV package for person %d: ", 1);
    scanf("%c", &userData.packageTV);
    fflush(stdin);
    while (userData.packageTV != 'T' && userData.packageTV != 'A' && userData.packageTV != 'B' && userData.packageTV != 'N') {
        printf("\nInvaid Option selected\n");
        printf("Enter Smart TV package for person %d again: ", 1);
        printf("%c", &userData.packageTV);
        fflush(stdin);
    }

    printf("\nEnter U for Unlimited Data package on Charji\n");
    printf("Enter S for 20 GB Data package on Charji\n");
    printf("Enter M for 30 GB Data package on Charji\n");
    printf("Enter L for 50 GB Data package on Charji\n");
    printf("Enter N for no Data package on Charji\n");
    printf("Enter Charji Package for person %d: ", 1);
    scanf("%c", &userData.packageCharji);
    fflush(stdin);
    while (userData.packageCharji != 'U' && userData.packageCharji != 'S' && userData.packageCharji != 'M' && userData.packageCharji != 'L' && userData.packageCharji != 'N') {
        printf("\nInvaid Option selected\n");
        printf("Enter Charji Package for person %d again: ", 1);
        scanf("%c", &userData.packageCharji);
        fflush(stdin);
    }

    srand(time(0));
    
    do {
        userData.onNetMinutes = rand() % 15001;
    } while (userData.onNetMinutes < 0 || userData.onNetMinutes > 15000);
    
    do {
        userData.mobileMinutes = rand() % 15001;
    } while (userData.mobileMinutes < 0 || userData.mobileMinutes > 15000);
    
    do {
        userData.otherMinutes = rand() % 251;
    } while (userData.otherMinutes < 0 || userData.otherMinutes > 250);

    do {
        userData.internationalZone1Minutes = rand() % 151;
    } while (userData.internationalZone1Minutes < 0 || userData.internationalZone1Minutes > 150);
    
    do {
        userData.internationalOtherZoneMinutes = rand() % 151;
    } while (userData.internationalOtherZoneMinutes < 0 || userData.internationalOtherZoneMinutes > 150);
    
    PTCLPriceCalculator(userData.packageLandline, userData.packageBroadband, userData.packageTV, userData.packageCharji, userData.onNetMinutes, userData.mobileMinutes, userData.otherMinutes, userData.internationalZone1Minutes, userData.internationalOtherZoneMinutes, counter, userData.payments);

    for (counter = 0; counter < 6; counter++) {
        printf("%.2f\n", userData.payments[counter][0]);
    }

    getch();
    
}

void PTCLPriceCalculator(int packageLandline, int packageBroadband, char packageTV, char packageCharji, int onNetMinutes, int mobileMinutes, int otherMinutes, int internationalZone1Minutes, int internationalOtherZoneMinutes, int counter2, float payments[6][12]) {
    int counter1;
    float price = 0, tempRate = 0, telephoneBill = 0, serviceTax = 0, withholdingTax = 0;

    srand(time(0));
    do {
        tempRate = rand() % 41;
    } while (tempRate >= 35 && tempRate <= 40);
    // tempRate = 37.5;

    price += otherMinutes * 2;
    price += internationalOtherZoneMinutes * tempRate;

    if (packageLandline != 1 && packageBroadband == 0) {
        switch (packageLandline) {
            case 1: {
                price += onNetMinutes * 0;
                price += mobileMinutes * 2.5;
                price += internationalZone1Minutes * 3.6;            
                break;
            }

            case 500: {
                mobileMinutes -= 200;
                
                if (mobileMinutes > 0) {
                    price += mobileMinutes * 2.5;
                }            
                price += internationalZone1Minutes * 3.6;            
                break;
            }

            case 1000: {
                mobileMinutes -= 700;
                internationalZone1Minutes -= 200;

                if (mobileMinutes > 0) {
                    price += mobileMinutes * 2.5;
                }            
                if (internationalZone1Minutes > 0) {
                    price += internationalZone1Minutes * 3.6;
                }            
                break;
            }

            case 3000: {
                mobileMinutes -= 2000;
                internationalZone1Minutes -= 200;

                if (mobileMinutes > 0) {
                    price += mobileMinutes * 2.5;
                }
                if (internationalZone1Minutes > 0) {
                    price += internationalZone1Minutes * 3.6;
                }            
                break;
            }

            case 5000: {
                mobileMinutes -= 4000;
                internationalZone1Minutes -= 400;

                if (mobileMinutes > 0) {
                    price += mobileMinutes * 2.5;
                }            
                if (internationalZone1Minutes > 0) {
                    price += internationalZone1Minutes * 3.6;
                }            
                break;
            }

            case 8000: {
                mobileMinutes -= 8000;
                internationalZone1Minutes -= 800;

                if (mobileMinutes > 0) {
                    price += mobileMinutes * 2.5;
                }            
                if (internationalZone1Minutes > 0) {
                    price += internationalZone1Minutes * 3.6;
                }            
                break;
            }
            
            default:
                break;
        }

        telephoneBill = price;
    }
    
    

    switch (packageBroadband) {
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

    switch (packageTV) {
        case 'N': {
            break;
        }
        
        case 'T': {
            if (packageBroadband == 0) {
                price += 799;
            }

            if (packageBroadband == 6) {
                price += 525;
            }
            break;
        }

        case 'A': {
            if (packageBroadband == 0 || packageBroadband == 6) {
                price += 99;   
            }            
            break;
        }

        case 'B': {
            if (packageBroadband == 0) {
                price += 799;
                price += 99;
            }

            if (packageBroadband == 6) {
                price += 525;
                price += 99;
            }

        }
        
        default:
            break;
    }

    switch (packageCharji) {
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

    if (packageBroadband != 0 || packageCharji != 'N') {
        serviceTax += price * 0.195;
        withholdingTax += price * 0.125;
    }

    if (packageTV != 'N') {
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
