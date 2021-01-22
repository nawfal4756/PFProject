#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

 struct PTCLData PTCLGenerateCurrentBill(struct PTCLData userData);

 int main() {

 }

 struct PTCLData PTCLGenerateCurrentBill(struct PTCLData userData) {
    time_t currentTime;
    struct tm* time1;
    int month;

    time(&currentTime);
    time1 = localtime(&currentTime);

    month = time1->tm_mon;

    printf("\nEnter 1 for Basic Package\n");
    printf("Enter 500 for Freedom 500\n");
    printf("Enter 1000 for Freedom 1000\n");
    printf("Enter 3000 for Freedom 3000\n");
    printf("Enter 5000 for Freedom 5000\n");
    printf("Enter 8000 for Freedom 8000\n");        
    printf("Enter landline package: ");
    scanf("%d", &userData.packageLandline);
    fflush(stdin);
    while (userData.packageLandline != 500 && userData.packageLandline != 1000 && userData.packageLandline != 3000 && userData.packageLandline != 5000 && userData.packageLandline != 8000 && userData.packageLandline != 1) {
        printf("\nInvaid Option selected\n");
        printf("Enter package land line again: ");
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
    printf("Enter broadband package: ");
    scanf("%d", &userData.packageBroadband);
    fflush(stdin);
    while (userData.packageBroadband != 6 && userData.packageBroadband != 8 && userData.packageBroadband != 15 && userData.packageBroadband != 25 && userData.packageBroadband != 50 && userData.packageBroadband != 100 && userData.packageBroadband != 0) {
        printf("\nInvaid Option selected\n");
        printf("Enter broadband package again: ");
        scanf("%d", &userData.packageBroadband);
        fflush(stdin);
    }

    printf("\nEnter T for Smart TV only\n");
    printf("Enter A for Smart TV App only\n");
    printf("Enter B for both Smart TVs\n");
    printf("Enter N for no Smart TV packages active\n");
    printf("Enter Smart TV package: ");
    scanf("%c", &userData.packageTV);
    fflush(stdin);
    while (userData.packageTV != 'T' && userData.packageTV != 'A' && userData.packageTV != 'B' && userData.packageTV != 'N') {
        printf("\nInvaid Option selected\n");
        printf("Enter Smart TV package again: ");
        printf("%c", &userData.packageTV);
        fflush(stdin);
    }

    printf("\nEnter U for Unlimited Data package on Charji\n");
    printf("Enter S for 20 GB Data package on Charji\n");
    printf("Enter M for 30 GB Data package on Charji\n");
    printf("Enter L for 50 GB Data package on Charji\n");
    printf("Enter N for no Data package on Charji\n");
    printf("Enter Charji Package: ");
    scanf("%c", &userData.packageCharji);
    fflush(stdin);
    while (userData.packageCharji != 'U' && userData.packageCharji != 'S' && userData.packageCharji != 'M' && userData.packageCharji != 'L' && userData.packageCharji != 'N') {
        printf("\nInvaid Option selected\n");
        printf("Enter Charji Package again: ");
        scanf("%c", &userData.packageCharji);
        fflush(stdin);
    }

    printf("Enter on-net minutes: ");
    scanf("%d", &userData.onNetMinutes[month]);
    fflush(stdin);
    while(userData.onNetMinutes[month] < 0) {
        printf("\nInvalid minutes entered!\n");
        printf("Enter on-net minutes again: ");
        scanf("%d", &userData.onNetMinutes[month]);
        fflush(stdin);
    }

    printf("Enter number of minutes called on mobile: ");
    scanf("%d", &userData.mobileMinutes[month]);
    fflush(stdin);
    while(userData.mobileMinutes[month] < 0) {
        printf("\nInvalid minutes entered!\n");
        printf("Enter number of minutes called on mobile again: ");
        scanf("%d", &userData.mobileMinutes[month]);
        fflush(stdin);
    }

    printf("Enter other network minutes: ");
    scanf("%d", &userData.otherMinutes[month]);
    fflush(stdin);
    while(userData.otherMinutes[month] < 0) {
        printf("\nInvalid minutes entered!\n");
        printf("Enter other network minutes again: ");
        scanf("%d", &userData.otherMinutes[month]);
        fflush(stdin);
    }

    printf("Enter number of minutes called on International Zone 1: ");
    scanf("%d", &userData.internationalZone1Minutes[month]);
    fflush(stdin);
    while(userData.internationalZone1Minutes[month] < 0) {
        printf("\nInvalid minutes entered!\n");
        printf("Enter number of minutes called on International Zone 1 again: ");
        scanf("%d", &userData.internationalZone1Minutes[month]);
        fflush(stdin);
    }

    printf("Enter number of minutes called on other than International Zone 1: ");
    scanf("%d", &userData.internationalOtherZoneMinutes[month]);
    fflush(stdin);
    while(userData.internationalOtherZoneMinutes[month] < 0) {
        printf("\nInvalid minutes entered!\n");
        printf("Enter number of minutes called on other than International Zone 1 again: ");
        scanf("%d", &userData.internationalOtherZoneMinutes[month]);
        fflush(stdin);
    }

    // PTCLPriceCalculator(&userData, month);

    userData.billYear[month] = time1->tm_year + 1900;

    return userData;
 }