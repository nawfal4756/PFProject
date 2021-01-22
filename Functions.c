#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <conio.h>

// Structures

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

struct SSGCData {
    // New Structure
    unsigned long long int consumerId;
    char name[30];
    char address[70];
    unsigned long long int contactNumber;
    char usageType;
    // 0 = units, 1 = amount os natural gas used, 2 = Sales Tax, 3 = Income Tax, 4 = amount due, 5 = amount paid
    float unitsAndPayment[6][12];
    int billYear[12];
    float total;
};

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

struct CardDate {
    int month;
    int year;
};

struct CreditCard {
    unsigned long long int cardNumber;
    char name[30];
    struct CardDate expiryDate;
    int cvc;
};

struct AdminControl {
    char username[40];
    char password[40];
};

struct KElectricRates {
    float offPeakUnitsMoreThan5KW;
    float onPeakUnitsMoreThan5KW;
    float unitsUpto50;
    float unitsUpto100;
    float unitsUpto200;
    float unitsUpto300;
    float unitsUpto700;
    float unitsAbove700;
    float minR;
    float electricityDutyR;
    float salesTaxR;
    float incomeTaxR;
    float tvLicenseFeeR;
    float unitsLessThan5KWC;
    float offPeakUnitsMoreThan5KWC;
    float onPeakUnitsMoreThan5KWC;
    float minC;
    float electricityDutyC;
    float salesTaxC;
    float incomeTaxC;
    float tvLicenseFeeC;
};

struct SSGCRates {
    float upTo50;
    float upTo150;
    float upTo250;
    float upTo350;
    float upTo450;
    float moreThan450;
    float minR;
    float salesTaxR;
    float incomeTaxR;
    float unitPriceC;
    float minC;
    float salesTaxC;
    float incomeTaxC;
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

// File Paths

char* keFile = "./DataFiles/KElectricData.txt";
char* ssgcFile = "./DataFiles/SSGCData.txt";
char* ptclFile = "./DataFiles/PTCLData.txt";
char* creditCardFile = "./DataFiles/CreditCardData.txt";
char* adminFile = "./DataFiles/AdminFile.txt";
char* kelectricRates = "./DataFiles/KElectricRates.txt";
char* ssgcRates = "./DataFiles/SSGCRates.txt";
char* ptclRates = "./DataFiles/PTCLRates.txt";

// Client Function Prototypes

int ArraySize(FILE* pointer, int structSize);
bool KElectricAccountNumberVerification(unsigned long long int accountNumber);
bool SSGCConsumerIDVerification(unsigned long long int consumerID);
bool PTCLAccountIDVerification(unsigned long long int accountID);
struct KElectricData KElectricIDSearch(unsigned long long int id);
struct SSGCData SSGCIDSearch(unsigned long long int id);
struct PTCLData PTCLIDSearch(unsigned long long int id);
void KElectricBillPreview(struct KElectricData KE);
void SSGCBillPreview(struct SSGCData SSGC);
void PTCLBillPreview(struct PTCLData PTCL);
int CreditCardVerification(struct CreditCard data);
int Payment(float amount);
int KElectricRecordUpdate(struct KElectricData dataNew);
int SSGCRecordUpdate(struct SSGCData dataNew);
int PTCLRecordUpdate(struct PTCLData dataNew);
int KElectricPrintBill(struct KElectricData KE);
int SSGCPrintBill(struct SSGCData SSGC);
int PTCLPrintBill(struct PTCLData PTCL);
bool StarConsumer(bool timePayment[12]);

// Admin Function Prototypes

int KElectricAddCustomer();
int SSGCAddCustomer();
int PTCLAddCustomer();
void KElectricPriceCalculator(struct KElectricData* data, int month);
void SSGCPriceCalculator(struct SSGCData* data, int month);
void PTCLPriceCalculator(struct PTCLData* data, int month);
struct KElectricData KElectricDataModification(struct KElectricData KE);
struct SSGCData SSGCDataModification(struct SSGCData SSGC);
struct PTCLData PTCLDataModification(struct PTCLData PTCL);
struct KElectricData KElectricGenerateCurrentBill(struct KElectricData userData);
struct SSGCData SSGCGenerateCurrentBill(struct SSGCData userData);
struct PTCLData PTCLGenerateCurrentBill(struct PTCLData userData);
int KElectricRatesModification(char category);
int SSGCRatesModification(char category);
int PTCLRatesModification();
int AdminPasswordChange();
int AdminAdd();
int AdminVerification(struct AdminControl userData);

// Client Functions

int ArraySize(FILE* pointer, int structSize) {
    int size;

    fseek(pointer, 0L, SEEK_END);
    size = ftell(pointer);
    size = size / structSize;
    fseek(pointer, 0L, SEEK_SET);

    return size;
}

bool KElectricAccountNumberVerification(unsigned long long int accountNumber) {
    if (accountNumber >= 10000000000 && accountNumber <= 99999999999) {
        return true;
    }
    else {
        return false;
    }
}

bool SSGCConsumerIDVerification(unsigned long long int consumerID) {
    if (consumerID >= 1000000000 && consumerID <= 9999999999) {
        return true;
    }
    else {
        return false;
    }
}

bool PTCLAccountIDVerification(unsigned long long int accountID) {
    if (accountID >= 1000000000 && accountID <= 9999999999) {
        return true;
    }
    else {
        return false;
    }
}

struct KElectricData KElectricIDSearch(unsigned long long int id) {
    // 0 = Not Found, 404 = Error
    
    FILE* pointer;
    struct KElectricData data;
    int sizeFromFile, counter1 = 0, found = 0;

    pointer = fopen(keFile, "rb");

    if (pointer == NULL) {        
        data.accountNumber = 404;
        return data;
    }

    sizeFromFile = ArraySize(pointer, sizeof(struct KElectricData));

    while (counter1 < sizeFromFile) {
        fread(&data, sizeof (struct KElectricData), 1, pointer);
        if (data.accountNumber == id) {
            found = 1;
            break;
        }
        counter1++;
    }

    if (found == 0) {
        data.accountNumber = 0;
    }

    return data;
}

struct SSGCData SSGCIDSearch(unsigned long long int id) {
    // 0 = Not Found, 404 = Error
    
    FILE* pointer;
    struct SSGCData data;
    int sizeFromFile, counter1 = 0, found = 0;

    pointer = fopen(ssgcFile, "rb");

    if (pointer == NULL) {        
        data.consumerId = 404;
        return data;
    }

    sizeFromFile = ArraySize(pointer, sizeof(struct SSGCData));

    while (counter1 < sizeFromFile) {
        fread(&data, sizeof (struct SSGCData), 1, pointer);
        if (data.consumerId == id) {
            found = 1;
            break;
        }
        counter1++;
    }

    if (found == 0) {
        data.consumerId = 0;
    }

    return data;
}

struct PTCLData PTCLIDSearch(unsigned long long int id) {
    // 0 = Not Found, 404 = Error
    
    FILE* pointer;
    struct PTCLData data;
    int sizeFromFile, counter1 = 0, found = 0;

    pointer = fopen(ptclFile, "rb");

    if (pointer == NULL) {        
        data.accountID = 404;
        return data;
    }

    sizeFromFile = ArraySize(pointer, sizeof(struct PTCLData));

    while (counter1 < sizeFromFile) {
        fread(&data, sizeof (struct PTCLData), 1, pointer);
        if (data.accountID == id) {
            found = 1;
            break;
        }
        counter1++;
    }

    if (found == 0) {
        data.accountID = 0;
    }

    return data;


}

void KElectricBillPreview(struct KElectricData KE) {
    int counter2,counter3,counter;
    printf("-----------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\t\tKELECTRIC\t\t\n");
    printf("\t\t\t\t\t\tEnergy That Moves Life\t\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------------\n");
    printf("Name: ");
    puts(KE.name);
    printf("Address: %s\n", KE.address);
    printf("Account number: %llu\n", KE.accountNumber);
    printf("Contact number: %llu\n",KE.contactNumber);
    if (StarConsumer(KE.timePayment)) {
        printf("\nYou are a star consumer!\n\n");
    }
    printf("Usage type: %s\n", KE.usageType == 'R' ? "Residential" : "Commercial");
    printf("Alloted load: %f\n",KE.allotedLoad);
    printf("Number of TV: %d\n",KE.numberOfTV);
    printf("Pending Payment: %.2f",KE.total);
    printf("\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%13s%14s%11s%13s%17s%11s%13s%14s%9s","Month/","Off Peak","On Peak","Amount of","Electricity","Sales","Income","TV License","Amount","Amount");
    printf("%12s\n","Amount");
    printf("%11s%14s%12s%15s%12s%14s%13s%12s%11s%12s\n","Year","Units","Units","Electricity","Duty","Tax","Tax","Fee","Due","Paid");
    printf("-----------------------------------------------------------------------------------------------------------------------------------\n");
    for (counter2 = 0; counter2 < 12; counter2++) {
        switch(counter2)
        {
            case 0:
            printf("%11s %d","January",KE.billYear[counter2]);
            break;

            case 1:
            printf("%11s %d","February",KE.billYear[counter2]);
            break;

            case 2:
            printf("%11s %d","March",KE.billYear[counter2]);
            break;

            case 3:
            printf("%11s %d","April",KE.billYear[counter2]);
            break;

            case 4:
            printf("%11s %d","May",KE.billYear[counter2]);
            break;

            case 5:
            printf("%11s %d","June",KE.billYear[counter2]);
            break;

            case 6:
            printf("%11s %d","July",KE.billYear[counter2]);
            break;

            case 7:
            printf("%11s %d","August",KE.billYear[counter2]);
            break;

            case 8:
            printf("%11s %d","September",KE.billYear[counter2]);
            break;

            case 9:
            printf("%11s %d","October",KE.billYear[counter2]);
            break;

            case 10:
            printf("%11s %d","November",KE.billYear[counter2]);
            break;

            case 11:
            printf("%11s %d","December",KE.billYear[counter2]);
            break;
        }
        for (counter3 = 0; counter3 < 9; counter3++) {
            switch(counter3){
                case 0:
                printf("%11.2f", KE.unitsAndPayment[counter3][counter2]);
                break;

                case 1:
                printf("%11.2f   ", KE.unitsAndPayment[counter3][counter2]);
                break;

                case 2:
                printf("%11.2f   ", KE.unitsAndPayment[counter3][counter2]);
                break;

                case 3:
                printf("%11.2f   ", KE.unitsAndPayment[counter3][counter2]);
                break;

                case 4:
                printf("%11.2f   ", KE.unitsAndPayment[counter3][counter2]);
                break;

                case 5:
                printf("%11.2f   ", KE.unitsAndPayment[counter3][counter2]);
                break;

                case 6:
                printf("%7.2f   ", KE.unitsAndPayment[counter3][counter2]);
                break;

                case 7:
                printf("%9.2f   ", KE.unitsAndPayment[counter3][counter2]);
                break;

                case 8:
                printf("%9.2f   ", KE.unitsAndPayment[counter3][counter2]);
                break;


            }
            
        }
        printf("\n");
    }
    printf("-----------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\nPress enter to continue...");
    getch();
}

void SSGCBillPreview(struct SSGCData SSGC) {
    int counter2,counter3,counter;
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\tSui Southern Gas Company Limited\t\t\n");
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    printf("Name: ");
    puts(SSGC.name);
    printf("Address: %s\n", SSGC.address);
    printf("Consumer ID: %llu\n", SSGC.consumerId);
    printf("Contact number: %llu\n",SSGC.contactNumber);
    printf("Usage type: %s\n", SSGC.usageType == 'R' ? "Residential" : "Commercial");
    printf("Pending Payment: %.2f",SSGC.total);
    printf("\n");
    printf("------------------------------------------------------------------------------------------------------------------\n");
    printf("%13s%14s%14s%10s%14s%13s","Month/","Units","Bill Without","Sales","Income","Amount");
    printf("%15s\n","Amount");
    printf("%11s%15s%10s%14s%13s%13s%16s\n","Year","Used","Tax","Tax","Tax","Due","Paid");
    printf("------------------------------------------------------------------------------------------------------------------\n");
    for (counter2 = 0; counter2 < 12; counter2++) {
        switch(counter2)
        {
            case 0:
            printf("%11s %d","January",SSGC.billYear[counter2]);
            break;

            case 1:
            printf("%11s %d","February",SSGC.billYear[counter2]);
            break;

            case 2:
            printf("%11s %d","March",SSGC.billYear[counter2]);
            break;

            case 3:
            printf("%11s %d","April",SSGC.billYear[counter2]);
            break;

            case 4:
            printf("%11s %d","May",SSGC.billYear[counter2]);
            break;

            case 5:
            printf("%11s %d","June",SSGC.billYear[counter2]);
            break;

            case 6:
            printf("%11s %d","July",SSGC.billYear[counter2]);
            break;

            case 7:
            printf("%11s %d","August",SSGC.billYear[counter2]);
            break;

            case 8:
            printf("%11s %d","September",SSGC.billYear[counter2]);
            break;

            case 9:
            printf("%11s %d","October",SSGC.billYear[counter2]);
            break;

            case 10:
            printf("%11s %d","November",SSGC.billYear[counter2]);
            break;

            case 11:
            printf("%11s %d","December",SSGC.billYear[counter2]);
            break;
        }
        for (counter3 = 0; counter3 < 6; counter3++) {
            switch(counter3){
                case 0:
                printf("%11.2f", SSGC.unitsAndPayment[counter3][counter2]);
                break;

                case 1:
                printf("%11.2f   ", SSGC.unitsAndPayment[counter3][counter2]);
                break;

                case 2:
                printf("%11.2f   ", SSGC.unitsAndPayment[counter3][counter2]);
                break;

                case 3:
                printf("%11.2f   ", SSGC.unitsAndPayment[counter3][counter2]);
                break;

                case 4:
                printf("%11.2f   ", SSGC.unitsAndPayment[counter3][counter2]);
                break;

                case 5:
                printf("%11.2f   ", SSGC.unitsAndPayment[counter3][counter2]);
                break;
            }
            
        }
        printf("\n");
    }
    printf("------------------------------------------------------------------------------------------------------------------\n");
    printf("\nPress enter to continue...");
    getch();
}

void PTCLBillPreview(struct PTCLData PTCL) {
    int counter2,counter3,counter;
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\t\t\tPTCL\t\t\n");
    printf("\t\t\t\t\t\tHello to the Future\t\n");
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    printf("Name: ");
    puts(PTCL.name);
    printf("Address: %s\n", PTCL.address);
    printf("Consumer ID: %llu\n", PTCL.accountID);
    printf("Contact number: %llu\n",PTCL.contactNumber);
    switch(PTCL.packageLandline)
    {
        case 500:
        printf("Landline Package: Freedom 500\n");
        break;

        case 1000:
        printf("Landline Package: Freedom 1000\n");
        break;

        case 3000:
        printf("Landline Package: Freedom 3000\n");
        break;

        case 5000:
        printf("Landline Package: Freedom 5000\n");
        break;

        case 8000:
        printf("Landline Package: Freedom 8000\n");
        break;

        case 1:
        printf("Landline Package: Basic Package\n");
        break;
    }
    switch(PTCL.packageBroadband)
    {
        case 6:
        printf("Broadband Package: 6Mbps Broadband Package\n");
        break;

        case 8:
        printf("Broadband Package: 8Mbps Broadband Package\n");
        break;

        case 15:
        printf("Broadband Package: 15Mbps Broadband Package\n");
        break;

        case 25:
        printf("Broadband Package: 25Mbps Broadband Package\n");
        break;

        case 50:
        printf("Broadband Package: 50Mbps Broadband Package\n");
        break;

        case 100:
        printf("Broadband Package: 100Mbps Broadband Package\n");
        break;

        case 0:
        printf("No active Broadband Package\n");
        break;
    }
    switch(PTCL.packageTV)
    {
        case 'A':
        printf("Smart TV Package: Smart TV App only\n");
        break;

        case 'T':
        printf("Smart TV Package: Smart TV only\n");
        break;

        case 'B':
        printf("Smart TV Package: Smart TV and Smart TV App\n");
        break;

        case 'N':
        printf("Smart TV Package: No Smart TV Package activated\n");
        break;
    }
    switch(PTCL.packageCharji)
    {
        case 'U':
        printf("Charji Package: Unlimited Data Package on Charji\n");
        break;

        case 'S':
        printf("Charji Package: 20 GB Data Package on Charji\n");
        break;

        case 'M':
        printf("Charji Package: 30 GB Data Package on Charji\n");
        break;

        case 'L':
        printf("Charji Package: 50 GB Data Package on Charji\n");
        break;

        case 'N':
        printf("Charji Package: No Data Package on Charji is activated\n");
        break;
    }
    printf("Pending Payment: %.2f",PTCL.total);
    printf("\n");
    printf("------------------------------------------------------------------------------------------------------------------\n");
    printf("%13s%14s%12s%15s%16s%9s","Month/","Bill of","Service","Withholding","Late Payment","Total");
    printf("%16s\n","Received");
    printf("%11s%15s%10s%14s%18s%11s%16s\n","Year","PTCL","Tax","Tax","Surcgarge","Bill","Payment");
    printf("------------------------------------------------------------------------------------------------------------------\n");
    for (counter2 = 0; counter2 < 12; counter2++) {
        switch(counter2)
        {
            case 0:
            printf("%11s %d","January",PTCL.billYear[counter2]);
            break;

            case 1:
            printf("%11s %d","February",PTCL.billYear[counter2]);
            break;

            case 2:
            printf("%11s %d","March",PTCL.billYear[counter2]);
            break;

            case 3:
            printf("%11s %d","April",PTCL.billYear[counter2]);
            break;

            case 4:
            printf("%11s %d","May",PTCL.billYear[counter2]);
            break;

            case 5:
            printf("%11s %d","June",PTCL.billYear[counter2]);
            break;

            case 6:
            printf("%11s %d","July",PTCL.billYear[counter2]);
            break;

            case 7:
            printf("%11s %d","August",PTCL.billYear[counter2]);
            break;

            case 8:
            printf("%11s %d","September",PTCL.billYear[counter2]);
            break;

            case 9:
            printf("%11s %d","October",PTCL.billYear[counter2]);
            break;

            case 10:
            printf("%11s %d","November",PTCL.billYear[counter2]);
            break;

            case 11:
            printf("%11s %d","December",PTCL.billYear[counter2]);
            break;
        }
        for (counter3 = 0; counter3 < 6; counter3++) {
            switch(counter3){
                case 0:
                printf("%11.2f", PTCL.payments[counter3][counter2]);
                break;

                case 1:
                printf("%11.2f   ", PTCL.payments[counter3][counter2]);
                break;

                case 2:
                printf("%11.2f   ", PTCL.payments[counter3][counter2]);
                break;

                case 3:
                printf("%11.2f   ", PTCL.payments[counter3][counter2]);
                break;

                case 4:
                printf("%11.2f   ", PTCL.payments[counter3][counter2]);
                break;

                case 5:
                printf("%11.2f   ", PTCL.payments[counter3][counter2]);
                break;
            } 
        }
        printf("\n");
    }
    printf("------------------------------------------------------------------------------------------------------------------\n");
    printf("\nPress enter to continue...");
    getch();
}

int CreditCardVerification(struct CreditCard data) {
    time_t currentTime;
    struct tm* time1;
    struct CreditCard originalData;
    FILE* pointer;
    int sizeFromFile, counter1 = 0, found = 0;

    // 1 = Verified, 0 = Not Verified, 404 = Error
    
    pointer = fopen(creditCardFile, "rb");

    if (pointer == NULL) {
        return 404;
    }
    
    sizeFromFile = ArraySize(pointer, sizeof(struct CreditCard));

    while (counter1 < sizeFromFile) {
        fread(&originalData, sizeof(struct CreditCard), 1, pointer);
        if (originalData.cardNumber == data.cardNumber) {
            found = 1;
            break;
        }
        counter1++;
    }    

    if (found == 0) {
        return 0;
    }

    time(&currentTime);
    time1 = localtime(&currentTime);

    if (time1->tm_year + 1900 > data.expiryDate.year) {
        return 0;
    }
    
    if (time1->tm_year + 1900 == data.expiryDate.year) {
        if (time1->tm_mon + 1 >= data.expiryDate.month) {
            return 0;
        }
    }    

    if (originalData.expiryDate.month == data.expiryDate.month && originalData.expiryDate.year == data.expiryDate.year) {
        if (strcmp(originalData.name, data.name) == 0) {        
            if (originalData.cvc == data.cvc) {
                return 1;
            }
        }
    }
    
    return 0;
}

int Payment(float amount) {
    struct CreditCard data;
    int length, counter1, response;

    printf("\t\t\t\t\t\t\tPayment\n");
    printf("--------------------------------------------------------------------------------------------------------------------\n\n");

    printf("Enter Card Number: ");
    scanf("%llu", data.cardNumber);
    fflush(stdin);
    while (data.cardNumber < 1000000000000000 || data.cardNumber > 9999999999999999) {
        printf("Incorrect Card Number\n");
        printf("Enter Card Number Again: ");
        scanf("%llu", data.cardNumber);
        fflush(stdin);
    }

    printf("Enter Card Holder Name: ");
    gets(data.name);
    fflush(stdin);

    printf("Enter Card Expiry Month (mm): ");
    scanf("%d", data.expiryDate.month);
    fflush(stdin);
    while (data.expiryDate.month < 1 || data.expiryDate.month > 12) {
        printf("Incorrect Month Entered!\n");
        printf("Enter Card Expiry Month Again (mm): ");
        scanf("%d", data.expiryDate.month);
        fflush(stdin);
    }

    printf("Enter Card Expiry Year (yyyy): ");
    scanf("%d", data.expiryDate.year);
    fflush(stdin);
    while (data.expiryDate.year < 1000 || data.expiryDate.year > 9999) {
        printf("Incorrect Year Entered!\n");
        printf("Enter Card Expiry Year Again (yyyy): ");
        scanf("%d", data.expiryDate.year);
        fflush(stdin);
    }

    printf("Enter Card CVC: ");
    scanf("%d", data.cvc);
    fflush(stdin);
    while (data.cvc < 100 || data.cvc > 999) {
        printf("Incorrect CVC Entered!\n");
        printf("Enter Card CVC: ");
        scanf("%d", data.cvc);
        fflush(stdin);
    } 

    length = strlen(data.name);
    for(counter1 = 0; counter1 < length; counter1++) {
        if (data.name[counter1] >= 'A' && data.name[counter1] <= 'Z') {
            data.name[counter1] += 32;
        }
    }

    response = CreditCardVerification(data);

    if (response == 1) {
        printf("Payment Successful!\nPress enter to continue...");
        getch();
        return 1;
    }
    else if (response == 0) {
        printf("Payment Unsuccessful!\nPress enter to continue...");
        getch();
        return 0;
    }
    else {
        printf("ERROR!\nPress enter to continue...");
        getch();
        return 404;
    }
    
}

int KElectricRecordUpdate(struct KElectricData dataNew) {
    struct KElectricData dataFromFile;
    FILE* pointer;
    int counter1, sizeFromFile, size, found = 0;

    pointer = fopen(keFile, "rb+");

    if (pointer == NULL) {
        return 404;
    }

    sizeFromFile = ArraySize(pointer, sizeof(struct KElectricData));    

    for (counter1 = 0; counter1 < sizeFromFile; counter1) {
        fread(&dataFromFile, sizeof(struct KElectricData), 1, pointer);
        if (dataFromFile.accountNumber == dataNew.accountNumber) {
            found = 1;
            break;
        }
    }

    if (found == 0) {
        return 404;
    }

    fseek(pointer, -(sizeof(struct KElectricData)), SEEK_CUR);
    fseek(pointer, 0L, SEEK_CUR);

    fwrite(&dataNew, sizeof(struct KElectricData), 1, pointer);

    fclose(pointer);

    return 1;
}

int SSGCRecordUpdate(struct SSGCData dataNew) {
    struct SSGCData dataFromFile;
    FILE* pointer;
    int counter1, sizeFromFile, size, found = 0;

    pointer = fopen(ssgcFile, "rb+");

    if (pointer == NULL) {
        return 404;
    }

    sizeFromFile = ArraySize(pointer, sizeof(struct SSGCData));    

    for (counter1 = 0; counter1 < sizeFromFile; counter1) {
        fread(&dataFromFile, sizeof(struct SSGCData), 1, pointer);
        if (dataFromFile.consumerId == dataNew.consumerId) {
            found = 1;
            break;
        }
    }

    if (found == 0) {
        return 404;
    }

    fseek(pointer, -(sizeof(struct SSGCData)), SEEK_CUR);
    fseek(pointer, 0L, SEEK_CUR);

    fwrite(&dataNew, sizeof(struct SSGCData), 1, pointer);

    fclose(pointer);

    return 1;
}

int PTCLRecordUpdate(struct PTCLData dataNew) {
    struct PTCLData dataFromFile;
    FILE* pointer;
    int counter1, sizeFromFile, size, found = 0;

    pointer = fopen(ptclFile, "rb+");

    if (pointer == NULL) {
        return 404;
    }

    sizeFromFile = ArraySize(pointer, sizeof(struct PTCLData));    

    for (counter1 = 0; counter1 < sizeFromFile; counter1) {
        fread(&dataFromFile, sizeof(struct PTCLData), 1, pointer);
        if (dataFromFile.accountID == dataNew.accountID) {
            found = 1;
            break;
        }
    }

    if (found == 0) {
        return 404;
    }

    fseek(pointer, -(sizeof(struct PTCLData)), SEEK_CUR);
    fseek(pointer, 0L, SEEK_CUR);

    fwrite(&dataNew, sizeof(struct PTCLData), 1, pointer);

    fclose(pointer);

    return 1;
}

int KElectricPrintBill(struct KElectricData KE) {
    FILE* pointer;
    char accountNumber[15], fileName[50] = "KElectricBill-";
    int counter2, counter3;

    snprintf(accountNumber, sizeof(accountNumber), "%llu", KE.accountNumber);
    strcat(fileName, accountNumber);
    strcat(fileName, ".txt");

    pointer = fopen(fileName, "w");

    if (pointer == NULL) {
        return 404;
    }

    fprintf(pointer, "-----------------------------------------------------------------------------------------------------------------------------------\n");
    fprintf(pointer, "\t\t\t\t\t\t\tKELECTRIC\t\t\n");
    fprintf(pointer, "\t\t\t\t\t\tEnergy That Moves Life\t\n");
    fprintf(pointer, "-----------------------------------------------------------------------------------------------------------------------------------\n");
    fprintf(pointer, "Name: %s\n", KE.name);    
    fprintf(pointer, "Address: %s\n", KE.address);
    fprintf(pointer, "Account number: %llu\n", KE.accountNumber);
    fprintf(pointer, "Contact number: %llu\n",KE.contactNumber);
    fprintf(pointer, "Usage type: %s\n", KE.usageType == 'R' ? "Residential" : "Commercial");
    fprintf(pointer, "Alloted load: %f\n",KE.allotedLoad);
    fprintf(pointer, "Number of TV: %d\n",KE.numberOfTV);
    fprintf(pointer, "Pending Amount: %d\n",KE.total);    
    fprintf(pointer, "-----------------------------------------------------------------------------------------------------------------------------------\n");
    fprintf(pointer, "%13s%14s%11s%13s%17s%11s%13s%14s%9s","Month/","Off Peak","On Peak","Amount of","Electricity","Sales","Income","TV License","Amount","Amount");
    fprintf(pointer, "%12s\n","Amount");
    fprintf(pointer, "%11s%14s%12s%15s%12s%14s%13s%12s%11s%12s\n","Year","Units","Units","Electricity","Duty","Tax","Tax","Fee","Due","Paid");
    fprintf(pointer, "-----------------------------------------------------------------------------------------------------------------------------------\n");
    for (counter2 = 0; counter2 < 12; counter2++) {
        switch(counter2)
        {
            case 0:
            fprintf(pointer, "%11s %d","January",KE.billYear[counter2]);
            break;

            case 1:
            fprintf(pointer, "%11s %d","February",KE.billYear[counter2]);
            break;

            case 2:
            fprintf(pointer, "%11s %d","March",KE.billYear[counter2]);
            break;

            case 3:
            fprintf(pointer, "%11s %d","April",KE.billYear[counter2]);
            break;

            case 4:
            fprintf(pointer, "%11s %d","May",KE.billYear[counter2]);
            break;

            case 5:
            fprintf(pointer, "%11s %d","June",KE.billYear[counter2]);
            break;

            case 6:
            fprintf(pointer, "%11s %d","July",KE.billYear[counter2]);
            break;

            case 7:
            fprintf(pointer, "%11s %d","August",KE.billYear[counter2]);
            break;

            case 8:
            fprintf(pointer, "%11s %d","September",KE.billYear[counter2]);
            break;

            case 9:
            fprintf(pointer, "%11s %d","October",KE.billYear[counter2]);
            break;

            case 10:
            fprintf(pointer, "%11s %d","November",KE.billYear[counter2]);
            break;

            case 11:
            fprintf(pointer, "%11s %d","December",KE.billYear[counter2]);
            break;
        }
        for (counter3 = 0; counter3 < 9; counter3++) {
            switch(counter3){
                case 0:
                fprintf(pointer, "%11.2f", KE.unitsAndPayment[counter3][counter2]);
                break;

                case 1:
                fprintf(pointer, "%11.2f   ", KE.unitsAndPayment[counter3][counter2]);
                break;

                case 2:
                fprintf(pointer, "%11.2f   ", KE.unitsAndPayment[counter3][counter2]);
                break;

                case 3:
                fprintf(pointer, "%11.2f   ", KE.unitsAndPayment[counter3][counter2]);
                break;

                case 4:
                fprintf(pointer, "%11.2f   ", KE.unitsAndPayment[counter3][counter2]);
                break;

                case 5:
                fprintf(pointer, "%11.2f   ", KE.unitsAndPayment[counter3][counter2]);
                break;

                case 6:
                fprintf(pointer, "%7.2f   ", KE.unitsAndPayment[counter3][counter2]);
                break;

                case 7:
                fprintf(pointer, "%9.2f   ", KE.unitsAndPayment[counter3][counter2]);
                break;

                case 8:
                fprintf(pointer, "%9.2f   ", KE.unitsAndPayment[counter3][counter2]);
                break;


            }
            
        }
        fprintf(pointer, "\n");
    }

    fclose(pointer);
    return 1;
}

int SSGCPrintBill(struct SSGCData SSGC) {
    int counter2, counter3;
    FILE* pointer;
    char consumerId[15], fileName[50] = "SSGCBill-";

    snprintf(consumerId, sizeof(consumerId), "%llu", SSGC.consumerId);
    strcat(fileName, consumerId);
    strcat(fileName, ".txt");

    pointer = fopen(fileName, "w");

    if (pointer == NULL) {
        return 404;
    }

    fprintf(pointer, "-----------------------------------------------------------------------------------------------------------------\n");
    fprintf(pointer, "\t\t\t\t\tSui Southern Gas Company Limited\t\t\n");
    fprintf(pointer, "-----------------------------------------------------------------------------------------------------------------\n");
    fprintf(pointer, "Consumer ID: %llu\n", SSGC.consumerId);
    fprintf(pointer, "Name: %s\n", SSGC.name);    
    fprintf(pointer, "Address: %s\n", SSGC.address);
    fprintf(pointer, "Contact number: %llu\n",SSGC.contactNumber);
    fprintf(pointer, "Usage type: %s\n", SSGC.usageType == 'R' ? "Residential" : "Commercial");
    fprintf(pointer, "Total Bill: %.2f\n",SSGC.total);    
    fprintf(pointer, "------------------------------------------------------------------------------------------------------------------\n");
    fprintf(pointer, "%13s%14s%14s%10s%14s%13s","Month/","Units","Bill Without","Sales","Income","Amount");
    fprintf(pointer, "%15s\n","Amount");
    fprintf(pointer, "%11s%15s%10s%14s%13s%13s%16s\n","Year","Used","Tax","Tax","Tax","Due","Paid");
    fprintf(pointer, "------------------------------------------------------------------------------------------------------------------\n");
    for (counter2 = 0; counter2 < 12; counter2++) {
        switch(counter2)
        {
            case 0:
            fprintf(pointer, "%11s %d","January",SSGC.billYear[counter2]);
            break;

            case 1:
            fprintf(pointer, "%11s %d","February",SSGC.billYear[counter2]);
            break;

            case 2:
            fprintf(pointer, "%11s %d","March",SSGC.billYear[counter2]);
            break;

            case 3:
            fprintf(pointer, "%11s %d","April",SSGC.billYear[counter2]);
            break;

            case 4:
            fprintf(pointer, "%11s %d","May",SSGC.billYear[counter2]);
            break;

            case 5:
            fprintf(pointer, "%11s %d","June",SSGC.billYear[counter2]);
            break;

            case 6:
            fprintf(pointer, "%11s %d","July",SSGC.billYear[counter2]);
            break;

            case 7:
            fprintf(pointer, "%11s %d","August",SSGC.billYear[counter2]);
            break;

            case 8:
            fprintf(pointer, "%11s %d","September",SSGC.billYear[counter2]);
            break;

            case 9:
            fprintf(pointer, "%11s %d","October",SSGC.billYear[counter2]);
            break;

            case 10:
            fprintf(pointer, "%11s %d","November",SSGC.billYear[counter2]);
            break;

            case 11:
            fprintf(pointer, "%11s %d","December",SSGC.billYear[counter2]);
            break;
        }
        for (counter3 = 0; counter3 < 6; counter3++) {
            switch(counter3){
                case 0:
                fprintf(pointer, "%11.2f", SSGC.unitsAndPayment[counter3][counter2]);
                break;

                case 1:
                fprintf(pointer, "%11.2f   ", SSGC.unitsAndPayment[counter3][counter2]);
                break;

                case 2:
                fprintf(pointer, "%11.2f   ", SSGC.unitsAndPayment[counter3][counter2]);
                break;

                case 3:
                fprintf(pointer, "%11.2f   ", SSGC.unitsAndPayment[counter3][counter2]);
                break;

                case 4:
                fprintf(pointer, "%11.2f   ", SSGC.unitsAndPayment[counter3][counter2]);
                break;

                case 5:
                fprintf(pointer, "%11.2f   ", SSGC.unitsAndPayment[counter3][counter2]);
                break;
            }
            
        }
        fprintf(pointer, "\n");
    }

    fclose(pointer);
    return 1;
}

int PTCLPrintBill(struct PTCLData PTCL) {
    FILE* pointer;
    int counter2, counter3;
    char accountId[15], fileName[50] = "PTCLBill-";

    snprintf(accountId, sizeof(accountId), "%llu", PTCL.accountID);
    strcat(fileName, accountId);
    strcat(fileName, ".txt");

    pointer = fopen(fileName, "w");

    if (pointer == NULL) {
        return 404;
    }

    fprintf(pointer, "-----------------------------------------------------------------------------------------------------------------\n");
    fprintf(pointer, "\t\t\t\t\t\t\t\tPTCL\t\t\n");
    fprintf(pointer, "\t\t\t\t\t\tHello to the Future\t\n");
    fprintf(pointer, "-----------------------------------------------------------------------------------------------------------------\n");
    fprintf(pointer, "Account ID: %llu\n", PTCL.accountID);
    fprintf(pointer, "Name: %s\n", PTCL.name);    
    fprintf(pointer, "Address: %s\n", PTCL.address);    
    fprintf(pointer, "Contact number: %llu\n",PTCL.contactNumber);
    switch(PTCL.packageLandline)
    {
        case 500:
        fprintf(pointer, "Landline Package: Freedom 500\n");
        break;

        case 1000:
        fprintf(pointer, "Landline Package: Freedom 1000\n");
        break;

        case 3000:
        fprintf(pointer, "Landline Package: Freedom 3000\n");
        break;

        case 5000:
        fprintf(pointer, "Landline Package: Freedom 5000\n");
        break;

        case 8000:
        fprintf(pointer, "Landline Package: Freedom 8000\n");
        break;

        case 1:
        fprintf(pointer, "Landline Package: Basic Package\n");
        break;
    }
    switch(PTCL.packageBroadband)
    {
        case 6:
        fprintf(pointer, "Broadband Package: 6Mbps Broadband Package\n");
        break;

        case 8:
        fprintf(pointer, "Broadband Package: 8Mbps Broadband Package\n");
        break;

        case 15:
        fprintf(pointer, "Broadband Package: 15Mbps Broadband Package\n");
        break;

        case 25:
        fprintf(pointer, "Broadband Package: 25Mbps Broadband Package\n");
        break;

        case 50:
        fprintf(pointer, "Broadband Package: 50Mbps Broadband Package\n");
        break;

        case 100:
        fprintf(pointer, "Broadband Package: 100Mbps Broadband Package\n");
        break;

        case 0:
        fprintf(pointer, "No active Broadband Package\n");
        break;
    }
    switch(PTCL.packageTV)
    {
        case 'A':
        fprintf(pointer, "Smart TV Package: Smart TV App only\n");
        break;

        case 'T':
        fprintf(pointer, "Smart TV Package: Smart TV only\n");
        break;

        case 'B':
        fprintf(pointer, "Smart TV Package: Smart TV and Smart TV App\n");
        break;

        case 'N':
        fprintf(pointer, "Smart TV Package: No Smart TV Package activated\n");
        break;
    }
    switch(PTCL.packageCharji)
    {
        case 'U':
        fprintf(pointer, "Charji Package: Unlimited Data Package on Charji\n");
        break;

        case 'S':
        fprintf(pointer, "Charji Package: 20 GB Data Package on Charji\n");
        break;

        case 'M':
        fprintf(pointer, "Charji Package: 30 GB Data Package on Charji\n");
        break;

        case 'L':
        fprintf(pointer, "Charji Package: 50 GB Data Package on Charji\n");
        break;

        case 'N':
        fprintf(pointer, "Charji Package: No Data Package on Charji is activated\n");
        break;
    }
    fprintf(pointer, "Pending Payment: %.2f\n",PTCL.total);    
    fprintf(pointer, "------------------------------------------------------------------------------------------------------------------\n");
    fprintf(pointer, "%13s%14s%12s%15s%16s%9s","Month/","Bill of","Service","Withholding","Late Payment","Total");
    fprintf(pointer, "%16s\n","Received");
    fprintf(pointer, "%11s%15s%10s%14s%18s%11s%16s\n","Year","PTCL","Tax","Tax","Surcgarge","Bill","Payment");
    fprintf(pointer, "------------------------------------------------------------------------------------------------------------------\n");
    for (counter2 = 0; counter2 < 12; counter2++) {
        switch(counter2)
        {
            case 0:
            fprintf(pointer, "%11s %d","January",PTCL.billYear[counter2]);
            break;

            case 1:
            fprintf(pointer, "%11s %d","February",PTCL.billYear[counter2]);
            break;

            case 2:
            fprintf(pointer, "%11s %d","March",PTCL.billYear[counter2]);
            break;

            case 3:
            fprintf(pointer, "%11s %d","April",PTCL.billYear[counter2]);
            break;

            case 4:
            fprintf(pointer, "%11s %d","May",PTCL.billYear[counter2]);
            break;

            case 5:
            fprintf(pointer, "%11s %d","June",PTCL.billYear[counter2]);
            break;

            case 6:
            fprintf(pointer, "%11s %d","July",PTCL.billYear[counter2]);
            break;

            case 7:
            fprintf(pointer, "%11s %d","August",PTCL.billYear[counter2]);
            break;

            case 8:
            fprintf(pointer, "%11s %d","September",PTCL.billYear[counter2]);
            break;

            case 9:
            fprintf(pointer, "%11s %d","October",PTCL.billYear[counter2]);
            break;

            case 10:
            fprintf(pointer, "%11s %d","November",PTCL.billYear[counter2]);
            break;

            case 11:
            fprintf(pointer, "%11s %d","December",PTCL.billYear[counter2]);
            break;
        }
        for (counter3 = 0; counter3 < 6; counter3++) {
            switch(counter3){
                case 0:
                fprintf(pointer, "%11.2f", PTCL.payments[counter3][counter2]);
                break;

                case 1:
                fprintf(pointer, "%11.2f   ", PTCL.payments[counter3][counter2]);
                break;

                case 2:
                fprintf(pointer, "%11.2f   ", PTCL.payments[counter3][counter2]);
                break;

                case 3:
                fprintf(pointer, "%11.2f   ", PTCL.payments[counter3][counter2]);
                break;

                case 4:
                fprintf(pointer, "%11.2f   ", PTCL.payments[counter3][counter2]);
                break;

                case 5:
                fprintf(pointer, "%11.2f   ", PTCL.payments[counter3][counter2]);
                break;
            } 
        }
        fprintf(pointer, "\n");
    }

    fclose(pointer);
    return 1;
}

bool StarConsumer(bool timePayment[12]) {
    int counter1, falseData = 0;
    
    for (counter1 = 0; counter1 < 12; counter1++) {
        if (timePayment[counter1] == false) {
            falseData = 1;
            break;
        }
    }

    if (falseData == 1) {
        return false;
    }

    return true;
}

// Admin Functions

int KElectricAddCustomer() {
    struct KElectricData userData, userDataFile;
    FILE* pointer;
    int sizeFromFile, month, counter1, counter2;
    time_t currentTime;
    struct tm* time1;

    time(&currentTime);
    time1 = localtime(&currentTime);

    month = time1->tm_mon;

    pointer = fopen(keFile, "ab+");

    if (pointer == NULL) {
        return 404;
    }

    for (counter1 = 0; counter1 < 9; counter1++) {
        for (counter2 = 0; counter2 < 12; counter2++) {
            userData.unitsAndPayment[counter1][counter2] = 0;
        }
    }

    for (counter1 = 0; counter1 < 12; counter1++) {
        userData.billYear[counter1] = 0;
        userData.timePayment[counter1] = false;
    }

    sizeFromFile = ArraySize(pointer, sizeof(struct KElectricData));

    accountNumber:
    printf("Enter account number of customer: ");
    scanf("%llu", &userData.accountNumber);
    fflush(stdin);
    while (!KElectricAccountNumberVerification(userData.accountNumber)) {
        printf("\nIncorrect value!\n");
        printf("Enter account number of customer again: ");
        scanf("%llu", &userData.accountNumber);
        fflush(stdin);
    }
    
    for (counter1 = 0; counter1 < sizeFromFile; counter1++) {
        fread(&userDataFile, sizeof(struct KElectricData), 1, pointer);
        if(userData.accountNumber == userDataFile.accountNumber) {
            printf("\nUser already exist with this aacount number. Enter another ID\n");
            goto accountNumber;
        }
    }
    
    fseek(pointer, 0L, SEEK_END);

    printf("Enter name of customer: ");
    gets(userData.name);
    fflush(stdin);
    while(strlen(userData.name) <= 0) {
        printf("\nName is required!\n");
        printf("Enter name of customer again: ");
        gets(userData.name);
        fflush(stdin);
    }

    printf("Enter address of customer: ");
    gets(userData.address);
    fflush(stdin);
    while(strlen(userData.address) <= 0) {
        printf("\nAddress is required!\n");
        printf("Enter address of customer again: ");
        gets(userData.address);
        fflush(stdin);
    }

    printf("Enter contact number of customer: ");
    scanf("%llu", &userData.contactNumber);
    fflush(stdin);
    while (!ContactNumberVerification(userData.contactNumber)) {
        printf("\nIncorrect value!\n");
        printf("Enter contact number of customer again: ");
        scanf("%llu", &userData.contactNumber);
        fflush(stdin);
    }

    printf("Enter usage type of customer (R - Residential, C - Commercial): ");
    scanf("%c", &userData.usageType);
    fflush(stdin);
    while (userData.usageType != 'R' && userData.usageType != 'C' && userData.usageType != 'r' && userData.usageType != 'c') {
        printf("\nIncorrect value!\n");
        printf("Enter usage type of customer again (R - Residential, C - Commercial): ");
        scanf("%c", &userData.usageType);
        fflush(stdin);
    }

    if (userData.usageType == 'r') {
        userData.usageType = 'R';
    }
    else if (userData.usageType == 'c') {
        userData.usageType = 'C';
    }

    printf("Enter alloted load of customer: ");
    scanf("%f", &userData.allotedLoad);
    fflush(stdin);
    while (userData.allotedLoad <= 0) {
        printf("\nIncorrect amount!\n");
        printf("Enter alloted load of customer again: ");
        scanf("%f", &userData.allotedLoad);
        fflush(stdin);
    }

    printf("Enter number of TV's for customer: ");
    scanf("%d", &userData.numberOfTV);
    fflush(stdin);
    while (userData.numberOfTV <= 0) {
        printf("\nIncorrect amount of TVs!\n");
        printf("Enter number of TV's for customer again: ");
        scanf("%d", &userData.numberOfTV);
        fflush(stdin);
    }

    printf("Enter number of units used in off peak timing: ");
    scanf("%f", &userData.unitsAndPayment[0][month]);
    fflush(stdin);
    while (userData.unitsAndPayment[0][month] < 0) {
        printf("\nIncorrect value!\n");
        printf("Enter number of units used in off peak timing again: ");
        scanf("%f", &userData.unitsAndPayment[0][month]);
        fflush(stdin);
    }

    printf("Enter number of units used in on peak timing: ");
    scanf("%f", &userData.unitsAndPayment[1][month]);
    fflush(stdin);
    while (userData.unitsAndPayment[1][month] < 0) {
        printf("\nIncorrect value!\n");
        printf("Enter number of units used in on peak timing again: ");
        scanf("%f", &userData.unitsAndPayment[1][month]);
        fflush(stdin);
    }

    KElectricPriceCalculator(&userData, month);

    userData.billYear[month] = time1->tm_year + 1900;
    userData.total = userData.unitsAndPayment[7][month];

    fwrite(&userData, sizeof(struct KElectricData), 1, pointer);

    fclose(pointer);
    return 1;
}

int SSGCAddCustomer() {
    struct SSGCData userData, userDataFile;
    FILE* pointer;
    int sizeFromFile, month, counter1, counter2;
    time_t currentTime;
    struct tm* time1;

    time(&currentTime);
    time1 = localtime(&currentTime);

    month = time1->tm_mon;

    pointer = fopen(ssgcFile, "ab+");

    if (pointer == NULL) {
        return 404;
    }

    for (counter1 = 0; counter1 < 6; counter1++) {
        for (counter2 = 0; counter2 < 12; counter2++) {
            userData.unitsAndPayment[counter1][counter2] = 0;
        }
    }

    for (counter1 = 0; counter1 < 12; counter1++) {
        userData.billYear[counter1] = 0;        
    }

    sizeFromFile = ArraySize(pointer, sizeof(struct SSGCData));

    consumerID:
    printf("Enter consumer ID of customer: ");
    scanf("%llu", &userData.consumerId);
    fflush(stdin);
    while (!SSGCConsumerIDVerification(userData.consumerId)) {
        printf("\nIncorrect value!\n");
        printf("Enter consumer ID of customer again: ");
        scanf("%llu", &userData.consumerId);
        fflush(stdin);
    }
    
    for (counter1 = 0; counter1 < sizeFromFile; counter1++) {
        fread(&userDataFile, sizeof(struct SSGCData), 1, pointer);
        if(userData.consumerId == userDataFile.consumerId) {
            printf("\nUser already exist with this consumer ID. Enter another ID\n");
            goto consumerID;
        }
    }
    
    fseek(pointer, 0L, SEEK_END);

    printf("Enter name of customer: ");
    gets(userData.name);
    fflush(stdin);
    while(strlen(userData.name) <= 0) {
        printf("\nName is required!\n");
        printf("Enter name of customer again: ");
        gets(userData.name);
        fflush(stdin);
    }

    printf("Enter address of customer: ");
    gets(userData.address);
    fflush(stdin);
    while(strlen(userData.address) <= 0) {
        printf("\nAddress is required!\n");
        printf("Enter address of customer again: ");
        gets(userData.address);
        fflush(stdin);
    }

    printf("Enter contact number of customer: ");
    scanf("%llu", &userData.contactNumber);
    fflush(stdin);
    while (!ContactNumberVerification(userData.contactNumber)) {
        printf("\nIncorrect value!\n");
        printf("Enter contact number of customer again: ");
        scanf("%llu", &userData.contactNumber);
        fflush(stdin);
    }

    printf("Enter usage type (R - Residential, I - Industrial): ");
    scanf("%c", &userData.usageType);
    fflush(stdin);
    while (userData.usageType != 'R' && userData.usageType != 'I' && userData.usageType != 'r' && userData.usageType != 'i') {
        printf("\nIncorrect option entered! Enter either R or I only\n");
        printf("Enter usage type (R - Residential, I - Industrial) again: ");
        scanf("%c", &userData.usageType);
        fflush(stdin);
    }

    if (userData.usageType == 'r') {
        userData.usageType = 'R';
    }

    if (userData.usageType == 'i') {
        userData.usageType = 'I';
    }

    printf("Enter number of units used: ");
    scanf("%f", &userData.unitsAndPayment[0][month]);
    fflush(stdin);
    while(userData.unitsAndPayment[0][month] < 0) {
        printf("\nIncorrect amount entered!\n");
        printf("Enter number of units used again: ");
        scanf("%f", &userData.unitsAndPayment[0][month]);
        fflush(stdin);
    }

    SSGCPriceCalculator(&userData, month);

    userData.billYear[month] = time1->tm_year + 1900;
    userData.total = userData.unitsAndPayment[4][month];

    fwrite(&userData, sizeof(struct SSGCData), 1, pointer);
    fclose(pointer);

    return 1;
}

int PTCLAddCustomer() {
    struct PTCLData userData, userDataFile;
    FILE* pointer;
    int sizeFromFile, month, counter1, counter2;
    time_t currentTime;
    struct tm* time1;

    time(&currentTime);
    time1 = localtime(&currentTime);

    month = time1->tm_mon;

    pointer = fopen(ptclFile, "ab+");

    if (pointer == NULL) {
        return 404;
    }

    for (counter1 = 0; counter1 < 6; counter1++) {
        for (counter2 = 0; counter2 < 12; counter2++) {
            userData.payments[counter1][counter2] = 0;
        }
    }

    for (counter1 = 0; counter1 < 12; counter1++) {
        userData.onNetMinutes[counter1] = 0;
        userData.mobileMinutes[counter1] = 0;
        userData.otherMinutes[counter1] = 0;
        userData.internationalZone1Minutes[counter1] = 0;
        userData.internationalOtherZoneMinutes[counter1] = 0;
        userData.billYear[counter1] = 0;        
    }

    sizeFromFile = ArraySize(pointer, sizeof(struct PTCLData));

    accountID:
    printf("Enter account ID of customer: ");
    scanf("%llu", &userData.accountID);
    fflush(stdin);
    while (!PTCLAccountIDVerification(userData.accountID)) {
        printf("Incorrect value!\n");
        printf("Enter account ID of customer again: ");
        scanf("%llu", &userData.accountID);
        fflush(stdin);
    }
    
    for (counter1 = 0; counter1 < sizeFromFile; counter1++) {
        fread(&userDataFile, sizeof(struct PTCLData), 1, pointer);
        if(userData.accountID == userDataFile.accountID) {
            printf("\nUser already exist with this consumer ID. Enter another ID\n");
            goto accountID;
        }
    }
    
    fseek(pointer, 0L, SEEK_END);

    printf("Enter name of customer: ");
    gets(userData.name);
    fflush(stdin);
    while(strlen(userData.name) <= 0) {
        printf("\nName is required!\n");
        printf("Enter name of customer again: ");
        gets(userData.name);
        fflush(stdin);
    }

    printf("Enter address of customer: ");
    gets(userData.address);
    fflush(stdin);
    while(strlen(userData.address) <= 0) {
        printf("\nAddress is required!\n");
        printf("Enter address of customer again: ");
        gets(userData.address);
        fflush(stdin);
    }

    printf("Enter contact number of customer: ");
    scanf("%llu", &userData.contactNumber);
    fflush(stdin);
    while (!ContactNumberVerification(userData.contactNumber)) {
        printf("\nIncorrect value!\n");
        printf("Enter contact number of customer again: ");
        scanf("%llu", &userData.contactNumber);
        fflush(stdin);
    }

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

    PTCLPriceCalculator(&userData, month);

    userData.billYear[month] = time1->tm_year + 1900;
    userData.total = userData.payments[4][month];

    fwrite(&userData, sizeof(struct PTCLData), 1, pointer);
    fclose(pointer);

    return 1;
}

void KElectricPriceCalculator(struct KElectricData* data, int month) {
    int counter;
    float price = 0, units = 0;
    FILE* pointer;
    struct KElectricRates rates;

    pointer = fopen(kelectricRates, "rb");
    if (pointer == NULL) {
        printf("\nUnable to open file\n\n");
        return;
    }
    fread(&rates, sizeof(struct KElectricRates), 1, pointer);
    fclose(pointer);

    units = data->unitsAndPayment[0][month] + data->unitsAndPayment[1][month];

    switch (data->usageType) {
        case 'R': {
            if (data->allotedLoad < 5) {
                if (units <= 50) {
                    price = units * rates.unitsUpto50;
                }
                if (units > 100) {
                    units -= 100;
                    price += 100 * rates.unitsUpto100;
                    if (units > 100) {
                        units -= 100;
                        price += 100 * rates.unitsUpto200;
                        if (units > 100) {
                            units -= 100;
                            price += 100 * rates.unitsUpto300;
                            if (units > 400) {
                                units -= 400;
                                price += 400 * rates.unitsUpto700;
                                if (units > 0) {
                                    price += units * rates.unitsAbove700;
                                }
                            }
                            else {
                                price += units * rates.unitsUpto700;
                            }
                        }
                        else {
                            price += units * rates.unitsUpto300;    
                        }
                    }
                    else {
                        price += units * rates.unitsUpto200;
                    }
                }
                else {
                    price += units * rates.unitsUpto100;
                }
            }
            else {
                price += data->unitsAndPayment[1][month] * rates.onPeakUnitsMoreThan5KW;
                price += data->unitsAndPayment[0][month] * rates.offPeakUnitsMoreThan5KW;
            }

            if (price < rates.minR) {
                price = rates.minR;
            }

            break;
        }

        case 'C': {
            if (data->allotedLoad < 5) {
                price = units * rates.unitsLessThan5KWC;
            }
            else {
                price += data->unitsAndPayment[0][month] * rates.offPeakUnitsMoreThan5KWC;
                price += data->unitsAndPayment[1][month] * rates.onPeakUnitsMoreThan5KWC;
            }
            
            if (price < rates.minC) {
                price = rates.minC;
            }
        }
    }

    data->unitsAndPayment[2][month] = price;

    switch (data->usageType) {
        case 'R': {            
            data->unitsAndPayment[3][month] = price * rates.electricityDutyR;
            data->unitsAndPayment[4][month] = price * rates.salesTaxR;
            data->unitsAndPayment[5][month] = price * rates.incomeTaxR;
            data->unitsAndPayment[6][month] = data->numberOfTV * rates.tvLicenseFeeR;
            break;
        }

        case 'C': {
            data->unitsAndPayment[3][month] = price * rates.electricityDutyC;
            data->unitsAndPayment[4][month] = price * rates.salesTaxC;
            data->unitsAndPayment[5][month] = price * rates.incomeTaxC;
            data->unitsAndPayment[6][month] = data->numberOfTV * rates.tvLicenseFeeC;
            break;
        }
    }

    data->unitsAndPayment[7][month] = 0;

    for (counter = 2; counter < 7; counter++) {
        data->unitsAndPayment[7][month] += data->unitsAndPayment[counter][month];
    }
               
}

void SSGCPriceCalculator(struct SSGCData* data, int month) {
    float price = 0, units = data->unitsAndPayment[0][month];
    FILE* pointer;
    struct SSGCRates prices;
    int counter1;

    pointer = fopen(ssgcRates, "rb");
    if (pointer == NULL) {
        printf("\nUnable to open file\n\n");
        return;
    }
    fread(&prices, sizeof(struct SSGCData), 1, pointer);
    fclose(pointer);
    
    switch (data->usageType) {
        case 'R': {
            if (units > 50) {
                price = 50 * prices.upTo50;
                units -= 50;
                if (units > 100) {
                    price += 100 * prices.upTo150;
                    units -= 100;
                    if (units > 100) {
                        price += 100 * prices.upTo250;
                        units -= 100;
                        if (units > 100) {
                            price += 100 * prices.upTo350;
                            units -= 100;
                            if (units > 100) {
                                price += 100 * prices.upTo450;
                                units -= 100;
                                if (units > 0) {
                                    price += units * prices.moreThan450;
                                }
                            }
                            else {
                                price += units * prices.upTo450;
                            }
                        }
                        else {
                            price += units * prices.upTo350;
                        }
                    }
                    else {
                        price += units * prices.upTo250;
                    }
                }
                else {
                    price += units * prices.upTo150;
                }
            }
            else {
                price = units * prices.upTo50;
            }

            if (price <= prices.minR) {
                price = prices.minR;
            }

            data->unitsAndPayment[1][month] = price;
            data->unitsAndPayment[2][month] = price * prices.salesTaxR;
            data->unitsAndPayment[3][month] = price * prices.incomeTaxR;
            data->unitsAndPayment[4][month] = 0;

            for (counter1 = 1; counter1 < 4; counter1++) {
                data->unitsAndPayment[4][month] += data->unitsAndPayment[counter1][month];
            }            

            break;
        }

        case 'I': {
            price = units * prices.unitPriceC;
            if (price <= prices.minC) {
                price = prices.minC;
            }

            data->unitsAndPayment[1][month] = price;
            data->unitsAndPayment[2][month] = price * prices.salesTaxC;
            data->unitsAndPayment[3][month] = price * prices.incomeTaxC;
            data->unitsAndPayment[4][month] = 0;

            for (counter1 = 1; counter1 < 4; counter1++) {
                data->unitsAndPayment[4][month] += data->unitsAndPayment[counter1][month];
            }

            break;
        }
    }        
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

struct KElectricData KElectricDataModification(struct KElectricData KE) {
    int choice, ch, year, month;
    char selection1;
    
    jump:
    printf("Which one you want to modify?\n");
    printf("Press 1 to modify the Name\n");
    printf("Press 2 to modify the Contact Number\n");
    printf("Press 3 to modify the Alloted Load\n");
    printf("Press 4 to modify the Number of TVs\n");
    printf("Press 5 to modify the Number of Units\n");
    printf("Your choice:\n");
    scanf("%d",&choice);
    fflush(stdin);

    switch (choice) {
        case 1: {
            printf("Enter the new Name:");
            gets(KE.name);
            fflush(stdin);
            while (strlen(KE.name) <= 0) {
                printf("\nName field cannot be empty!\n");
                printf("Enter the new Name again:");
                gets(KE.name);
                fflush(stdin);
            }
            break;
        }

        case 2: {
            printf("Enter the new Contact Number:");
            scanf("%llu", &KE.contactNumber);
            fflush(stdin);
            while (!ContactNumberVerification(KE.contactNumber)) {
                printf("Incorrect value!\n");
                printf("Enter the new Contact Number again: ");
                scanf("%llu", &KE.contactNumber);
                fflush(stdin);
            }
            break;
        }

        case 3: {
            printf("Enter the new Alloted Load: ");
            scanf("%f", &KE.allotedLoad);
            fflush(stdin);
            while (KE.allotedLoad <= 0) {
                printf("Incorrect number!\n");
                printf("Enter the new Alloted Load again: ");
                scanf("%f", &KE.allotedLoad);
                fflush(stdin);
            }
            break;
        }

        case 4: {
            printf("Enter the new Number of TVs: ");
            scanf("%d", &KE.numberOfTV);
            fflush(stdin);
            while (KE.numberOfTV < 0) {
                printf("\nNumber of Tvs is required!\n");
                printf("Enter the new Number of TVs again: ");
                scanf("%d", &KE.numberOfTV);
                fflush(stdin);
            }
            break;
        }

        case 5: {
            printf("Enter the month of the bill:\n");
            printf("Enter 1 for january, 2 for february and so on...\n");
            scanf("%d",&month);
            fflush(stdin);
            while(month < 1 || month > 12) {
                printf("Incorrect month!\n");
                printf("Enter the month of the bill again:");
                scanf("%d",&month);
                fflush(stdin);
            }

            printf("Enter the year of bill:");
            scanf("%d",&year);
            fflush(stdin);
            if(year != KE.billYear[month-1]) {
                printf("The record for %d year does not exist!\n", year);
                goto jump;
            }
            
            printf("Which units you want to change?\n");
            printf("press 0 to modify off peak units\n");
            printf("Press 1 to modify on peak units\n");
            printf("Your choice:");
            scanf("%d",&ch);
            fflush(stdin);

            while(ch != 0 && ch != 1) {
                printf("\nIncorrect choice!\n");
                printf("Enter your choice again:");
                scanf("%d",&ch);
                fflush(stdin);
            }

            if(ch == 0) {
                printf("Enter the new off peak units:");
                scanf("%f",&KE.unitsAndPayment[0][month-1]);
                fflush(stdin);
            }
            else if(ch==1) {
                printf("Enter the new on peak units:");
                scanf("%f",&KE.unitsAndPayment[1][month-1]);
                fflush(stdin);
            }
        }

        default: {
            printf("\nIncorrect option selected!\n");
            goto jump;
            break;
        }
    }

    exit:
    printf("\n\nDo you want to modify anything else? (Yes or No)\n");
    scanf("%c", &selection1);
    fflush(stdin);

    switch (selection1) {
        case 'Y':
        case 'y': {
            printf("\n\n");
            goto jump;
            break;
        }

        case 'N':
        case 'n': {
            return KE;
            break;
        }

        default: {
            printf("\nIncorrect option entered!\n");
            goto exit;
            break;
        }
    }    
}

struct SSGCData SSGCDataModification(struct SSGCData SSGC) {
    int choice, ch, year, month;
    char selection1;
    
    jump:
    printf("Which one you want to modify?\n");
    printf("Press 1 to modify the Name\n");
    printf("Press 2 to modify the Contact Number\n");
    printf("Press 3 to modify the units\n");
    printf("Your choice:\n");
    scanf("%d",&choice);
    fflush(stdin);

    switch(choice) {
        case 1: {
            printf("Enter the new Name:");
            gets(SSGC.name);
            fflush(stdin);
            while (strlen(SSGC.name) <= 0) {
                printf("\nName field cannot be empty!\n");
                printf("Enter the new Name again:");
                gets(SSGC.name);
                fflush(stdin);
            }
            break;
        }

        case 2: {
            printf("Enter the new contact number: ");
            scanf("%llu", &SSGC.contactNumber);
            fflush(stdin);
            while (!ContactNumberVerification(SSGC.contactNumber)) {
                printf("Incorrect value!\n");
                printf("Enter the new contact number again: ");
                scanf("%llu", &SSGC.contactNumber);
                fflush(stdin);
            }
            break;
        }

        case 3: {
            printf("Enter the month of the bill:\n");
            printf("Enter 1 for january, 2 for february and so on...\n");
            scanf("%d",&month);
            fflush(stdin);
            while(month < 1 || month > 12) {
                printf("Incorrect month!\n");
                printf("Enter the month of the bill again:");
                scanf("%d",&month);
                fflush(stdin);
            }

            printf("Enter the year of bill:");
            scanf("%d",&year);
            fflush(stdin);
            if(year != SSGC.billYear[month-1]) {
                printf("The record for %d year does not exist!\n", year);
                goto jump;
            }
            
            printf("Enter the new units:");
            scanf("%f",&SSGC.unitsAndPayment[0][month-1]);
            fflush(stdin);
        }
        break;
    }
    return SSGC;
}

struct PTCLData PTCLDataModification(struct PTCLData PTCL) {
    int choice, ch, year, month;
    
    jump1:
    printf("Which one you want to modify?\n");
    printf("Press 1 to modify the Name\n");
    printf("Press 2 to modify the Contact Number\n");
    printf("Press 3 to modify the Package Landline\n");
    printf("Press 4 to modify the Broadband Package\n");
    printf("Press 5 to modify the Smart TV Package\n");
    printf("Press 6 to modify the Charji Package\n");
    printf("Press 7 to modify the minutes\n");
    printf("Your choice:\n");
    scanf("%d",&choice);
    fflush(stdin);
    
    switch (choice) {
        case 1: {
            printf("Enter the new Name:");
            gets(PTCL.name);
            fflush(stdin);
            while (strlen(PTCL.name) <= 0) {
                printf("\nName field cannot be empty!\n");
                printf("Enter the new Name again:");
                gets(PTCL.name);
                fflush(stdin);
            }
            break;
        }

        case 2: {
            printf("Enter the new contact number: ");
            scanf("%llu", &PTCL.contactNumber);
            fflush(stdin);
            while (!ContactNumberVerification(PTCL.contactNumber)) {
                printf("Incorrect value!\n");
                printf("Enter the new contact number again: ");
                scanf("%llu", &PTCL.contactNumber);
                fflush(stdin);
            }
            break;
        }
        
        case 3: {
            printf("\nEnter 1 for Basic Package\n");
            printf("Enter 500 for Freedom 500\n");
            printf("Enter 1000 for Freedom 1000\n");
            printf("Enter 3000 for Freedom 3000\n");
            printf("Enter 5000 for Freedom 5000\n");
            printf("Enter 8000 for Freedom 8000\n");        
            printf("Enter the new landline package: ");
            scanf("%d", &PTCL.packageLandline);
            fflush(stdin);
            while (PTCL.packageLandline != 500 && PTCL.packageLandline != 1000 && PTCL.packageLandline != 3000 && PTCL.packageLandline != 5000 && PTCL.packageLandline != 8000 && PTCL.packageLandline != 1) {
               printf("\nInvaid Option selected\n");
               printf("Enter the new package land line again: ");
               scanf("%d", &PTCL.packageLandline);
               fflush(stdin);
            }
            break;
        }

        case 4: {
            printf("\nEnter 6 for 6Mbps broadband package\n");
            printf("Enter 8 for 8Mbps broadband package\n");
            printf("Enter 15 for 15Mbps broadband package\n");
            printf("Enter 25 for 25Mbps broadband package\n");
            printf("Enter 50 for 50Mbps broadband package\n");
            printf("Enter 100 for 100Mbps broadband package\n");
            printf("Enter 0 for no active broadband package\n");
            printf("Enter the new broadband package: ");
            scanf("%d", &PTCL.packageBroadband);
            fflush(stdin);
            while (PTCL.packageBroadband != 6 && PTCL.packageBroadband != 8 && PTCL.packageBroadband != 15 && PTCL.packageBroadband != 25 && PTCL.packageBroadband != 50 && PTCL.packageBroadband != 100 && PTCL.packageBroadband != 0) {
               printf("\nInvaid Option selected\n");
               printf("Enter the new broadband package again: ");
               scanf("%d", &PTCL.packageBroadband);
               fflush(stdin);
            }
            break;
        }

        case 5: {
            printf("\nEnter T for Smart TV only\n");
            printf("Enter A for Smart TV App only\n");
            printf("Enter B for both Smart TVs\n");
            printf("Enter N for no Smart TV packages active\n");
            printf("Enter Smart the new TV package: ");
            scanf("%c", &PTCL.packageTV);
            fflush(stdin);
            while (PTCL.packageTV != 'T' && PTCL.packageTV != 'A' && PTCL.packageTV != 'B' && PTCL.packageTV != 'N') {
               printf("\nInvaid Option selected\n");
               printf("Enter the new Smart TV package again: ");
               printf("%c", &PTCL.packageTV);
               fflush(stdin);
            }
            break;
        }

        case 6: {
            printf("\nEnter U for Unlimited Data package on Charji\n");
            printf("Enter S for 20 GB Data package on Charji\n");
            printf("Enter M for 30 GB Data package on Charji\n");
            printf("Enter L for 50 GB Data package on Charji\n");
            printf("Enter N for no Data package on Charji\n");
            printf("Enter Charji Package for person %d: ", 1);
            scanf("%c", &PTCL.packageCharji);
            fflush(stdin);
            while (PTCL.packageCharji != 'U' && PTCL.packageCharji != 'S' && PTCL.packageCharji != 'M' && PTCL.packageCharji != 'L' && PTCL.packageCharji != 'N') {
               printf("\nInvaid Option selected\n");
               printf("Enter Charji Package for person %d again: ", 1);
               scanf("%c", &PTCL.packageCharji);
               fflush(stdin);
            }
            break;
        }
    
        case 7:{
            printf("Enter the month of the bill:\n");
            printf("Enter 1 for january, 2 for february and so on...\n");
            scanf("%d",&month);
            fflush(stdin);
            while(month < 1 || month > 12) {
                printf("Incorrect month!\n");
                printf("Enter the month of the bill again:");
                scanf("%d",&month);
                fflush(stdin);
            }

            printf("Enter the year of bill:");
            scanf("%d",&year);
            fflush(stdin);
            if(year != PTCL.billYear[month-1]) {
                printf("The record for %d year does not exist!\n", year);
                goto jump1;
            }
            
            jump2:
            printf("Which minutes you want to change?\n");
            printf("Press 1 to change the On Net Minutes\n");
            printf("Press 2 to change the Mobile Minutes\n");
            printf("Press 3 to change the Other Minutes\n");
            printf("Press 4 to change the International Zone 1 Minutes\n");
            printf("Press 5 to change the International Other Zone Minutes\n");
            printf("Your choice:");
            scanf("%d",&ch);
            fflush(stdin);
            
            switch(ch)
            {
                case 1: {
                    printf("Enter the new On Net Minutes:");
                    scanf("%d",&PTCL.onNetMinutes[month-1]);
                    fflush(stdin);
                    break;
                }
                case 2: {
                    printf("Enter the new Mobile Minutes:");
                    scanf("%d",&PTCL.mobileMinutes[month-1]);
                    fflush(stdin);
                    break;
                }

                case 3: {
                    printf("Enter the new Other Minutes:");
                    scanf("%d",&PTCL.otherMinutes[month-1]);
                    fflush(stdin);
                    break;
                }

                case 4: {
                    printf("Enter the new International Zone 1 Minutes:");
                    scanf("%d",&PTCL.internationalZone1Minutes[month-1]);
                    fflush(stdin);
                    break;
                }

                case 5:{
                    printf("Enter the new International Other Zone Minutes:");
                    scanf("%d",&PTCL.internationalOtherZoneMinutes[month-1]);
                    fflush(stdin);
                    break;
                }

                default: {
                    printf("\nIncorrect choice!\n");
                    goto jump2;
                    break;
                }
                
            }
            break;
        }

        default: {
            printf("\nIncorrect option selected!\n");
            goto jump2;
            break;
        }

    }
    return PTCL;     
}

struct KElectricData KElectricGenerateCurrentBill(struct KElectricData userData) {
    time_t currentTime;
    struct tm* time1;
    int month;

    time(&currentTime);
    time1 = localtime(&currentTime);

    month = time1->tm_mon;

    printf("Enter the number of off peak units used: ");
    scan("%f", &userData.unitsAndPayment[0][month]);
    fflush(stdin);
    while(userData.unitsAndPayment[0][month] < 0) {
        printf("\nIncorrect value entered!\n");
        printf("Enter the number of off peak units used again: ");
        scan("%f", &userData.unitsAndPayment[0][month]);
        fflush(stdin);
    }

    printf("Enter the number of on peak units used: ");
    scan("%f", &userData.unitsAndPayment[1][month]);
    fflush(stdin);
    while(userData.unitsAndPayment[1][month] < 0) {
        printf("\nIncorrect value entered!\n");
        printf("Enter the number of on peak units used again: ");
        scan("%f", &userData.unitsAndPayment[1][month]);
        fflush(stdin);
    }

    KElectricPriceCalculator(&userData, month);

    userData.billYear[month] = time1->tm_year + 1900;

    return userData;
}

struct SSGCData SSGCGenerateCurrentBill(struct SSGCData userData) {
    time_t currentTime;
    struct tm* time1;
    int month;

    time(&currentTime);
    time1 = localtime(&currentTime);

    month = time1->tm_mon;

    printf("Enter the number of units used: ");
    scan("%f", &userData.unitsAndPayment[0][month]);
    fflush(stdin);
    while(userData.unitsAndPayment[0][month] < 0) {
        printf("\nIncorrect value entered!\n");
        printf("Enter the number of units used again: ");
        scan("%f", &userData.unitsAndPayment[0][month]);
        fflush(stdin);
    }

    SSGCPriceCalculator(&userData, month);

    userData.billYear[month] = time1->tm_year + 1900;

    return userData;
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

    PTCLPriceCalculator(&userData, month);

    userData.billYear[month] = time1->tm_year + 1900;

    return userData;
 }

int KElectricRatesModification(char category) {
    int option1;
    float temp1, temp2;
    FILE* pointer;
    struct KElectricRates data;
    char selection1;

    pointer = fopen(kelectricRates, "rb+");

    if (pointer == NULL) {
        return 404;
    }

    fread(&data, sizeof(struct KElectricRates), 1, pointer);
    top:
    switch (category) {
        case 'R': {
            options1:
            printf("\n\nResidential:\n");
            printf("Enter 1 to change the rate of off peak for more than 5 KW\n");
            printf("Enter 2 to change the rate of on peak for more than 5 KW\n");
            printf("For less than 5KW:\n");
            printf("Enter 3 to change the rate for up to 50 units\n");
            printf("Enter 4 to change the rate for up to 100 units\n");
            printf("Enter 5 to change the rate for up to 200 units\n");
            printf("Enter 6 to change the rate for up to 300 units\n");
            printf("Enter 7 to change the rate for up to 700 units\n");
            printf("Enter 8 to change the rate for more than 700 units\n");
            printf("Enter 9 to change the minimum rate\n");
            printf("Enter 10 to change the percentage of electricity duty\n");
            printf("Enter 11 to change the percentage of sales tax\n");
            printf("Enter 12 to change the percentage of income tax\n");
            printf("Enter 13 to change the TV license fee\n");
            printf("Enter 14 to go back\n");
            printf("Enter you desired option: ");
            scan("%d", &option1);
            fflush(stdin);

            switch (option1) {
                case 1: {
                    case1:
                    printf("Enter off peak units rate for less than 5 KW: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter off peak units rate for less than 5 KW again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }
                    printf("Enter off peak units rate for less than 5 KW for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.offPeakUnitsMoreThan5KW = temp2;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case1;
                    }
                    break;
                }

                case 2: {
                    case2:
                    printf("Enter on peak units rate for less than 5 KW: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter on peak units rate for less than 5 KW again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }
                    printf("Enter on peak units rate for less than 5 KW for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.onPeakUnitsMoreThan5KW = temp2;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case2;
                    }
                    break;
                }

                case 3: {
                    case3:
                    printf("Enter the rate for up to 50 units for more than 5 KW: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter the rate again for up to 50 units for more than 5 KW: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the rate for up to 50 units for more than 5 KW for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.unitsUpto50 = temp2;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case3;
                    }
                    break;
                }

                case 4: {
                    case4:
                    printf("Enter the rate for up to 100 units for more than 5 KW: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter the rate again for up to 100 units for more than 5 KW: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the rate for up to 100 units for more than 5 KW for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.unitsUpto100 = temp2;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case4;
                    }
                    break;
                }

                case 5: {
                    case5:
                    printf("Enter the rate for up to 200 units for more than 5 KW: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter the rate again for up to 200 units for more than 5 KW: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the rate for up to 200 units for more than 5 KW for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.unitsUpto200 = temp2;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case5;
                    }
                    break;
                }

                case 6: {
                    case6:
                    printf("Enter the rate for up to 300 units for more than 5 KW: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter the rate again for up to 300 units for more than 5 KW: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the rate for up to 300 units for more than 5 KW for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.unitsUpto300 = temp2;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case6;
                    }
                    break;
                }

                case 7: {
                    case7:
                    printf("Enter the rate for up to 700 units for more than 5 KW: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter the rate again for up to 700 units for more than 5 KW: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the rate for up to 700 units for more than 5 KW for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.unitsUpto700 = temp2;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case7;
                    }
                    break;
                }

                case 8: {
                    case8:
                    printf("Enter the rate for more than 700 units for more than 5 KW: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter the rate again for more than 700 units for more than 5 KW: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the rate for more than 700 units for more than 5 KW for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.unitsAbove700 = temp2;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case8;
                    }
                    break;
                }

                case 9: {
                    case9:
                    printf("Enter the minimum rate: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter the minimum rate again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the minimum rate for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.minR = temp2;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case9;
                    }
                    break;
                }

                case 10: {
                    case10:
                    printf("Enter the electricity duty in percentage: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect percentage entered!\n");
                        printf("Enter the electricity duty in percentage again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the electricity duty in percentage for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.electricityDutyR = temp2 / 100;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case10;
                    }
                    break;
                }

                case 11: {
                    case11:
                    printf("Enter the sales tax in percentage: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect percentage entered!\n");
                        printf("Enter the sales tax in percentage again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the sales tax in percentage for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.salesTaxR = temp2 / 100;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case11;
                    }
                    break;
                }

                case 12: {
                    case12:
                    printf("Enter the income tax in percentage: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect percentage entered!\n");
                        printf("Enter the income tax in percentage again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the income tax in percentage for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.incomeTaxR = temp2 / 100;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case12;
                    }
                    break;
                }

                case 13: {
                    case13:
                    printf("Enter the TV license fee: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect percentage entered!\n");
                        printf("Enter the TV license fee again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the TV license fee for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.tvLicenseFeeR = temp2;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case13;
                    }
                    break;
                }

                case 14: {
                    return 2;
                    break;
                }

                default: {
                    printf("\nIncorrect option selected!\n");
                    goto options1;
                    break;
                }
            }            
        }

        case 'C': {
            options2:
            printf("\n\nCommercial:\n");
            printf("Enter 1 to change the rate for less than 5 KW\n");
            printf("For more than 5KW:\n");
            printf("Enter 2 to change the rate of off peak\n");
            printf("Enter 3 to change the rate of on peak\n");
            printf("Enter 4 to change the minimum rate\n");
            printf("Enter 5 to change the percentage of electricity duty\n");
            printf("Enter 6 to change the percentage of sales tax\n");
            printf("Enter 7 to change the percentage of income tax\n");
            printf("Enter 8 to change the TV license fee\n");
            printf("Enter 9 to go back\n");
            printf("Enter you desired option: ");
            scan("%d", &option1);
            fflush(stdin);

            switch (option1) {
                case 1: {
                    case1C:
                    printf("Enter units rate for less than 5 KW: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter units rate for less than 5 KW again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }
                    printf("Enter units rate for less than 5 KW for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.unitsLessThan5KWC = temp2;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case1C;
                    }
                    break;
                }

                case 2: {
                    case2C:
                    printf("Enter off peak units rate for more than 5 KW: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter off peak units rate for more than 5 KW again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }
                    printf("Enter off peak units rate for more than 5 KW for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.offPeakUnitsMoreThan5KWC = temp2;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case2C;
                    }
                    break;
                }

                case 3: {
                    case3C:
                    printf("Enter on peak units rate for more than 5 KW: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter on peak units rate for more than 5 KW again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }
                    printf("Enter on peak units rate for more than 5 KW for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.onPeakUnitsMoreThan5KWC = temp2;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case3C;
                    }
                    break;
                }

                case 4: {
                    case4C:
                    printf("Enter the minimum rate: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter the minimum rate again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the minimum rate for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.minC = temp2;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case4C;
                    }
                    break;
                }

                case 5: {
                    case5C:
                    printf("Enter the electricity duty in percentage: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect percentage entered!\n");
                        printf("Enter the electricity duty in percentage again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the electricity duty in percentage for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.electricityDutyC = temp2 / 100;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case5C;
                    }
                    break;
                }

                case 6: {
                    case6C:
                    printf("Enter the sales tax in percentage: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect percentage entered!\n");
                        printf("Enter the sales tax in percentage again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the sales tax in percentage for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.salesTaxC = temp2 / 100;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case6C;
                    }
                    break;
                }

                case 7: {
                    case7C:
                    printf("Enter the income tax in percentage: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect percentage entered!\n");
                        printf("Enter the income tax in percentage again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the income tax in percentage for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.incomeTaxC = temp2 / 100;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case7C;
                    }
                    break;
                }

                case 8: {
                    case8C:
                    printf("Enter the TV license fee: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect percentage entered!\n");
                        printf("Enter the TV license fee again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the TV license fee for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.tvLicenseFeeC = temp2;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case8C;
                    }
                    break;
                }

                case 9: {
                   return 2;
                   break; 
                }

                default: {
                    printf("\nIncorrect option selected!\n");
                    goto options2;
                    break;
                }
            }
        }        
    }

    exit:
    printf("\n\nDo you want to modify any other rates? (Yes or No)\n");
    scanf("%c", &selection1);
    fflush(stdin);

    switch (selection1) {
        case 'Y':
        case 'y': {
            printf("\n\n");
            goto top;
            break;
        }

        case 'N':
        case 'n': {
            fseek(pointer, 0L, SEEK_SET);
            fwrite(&data, sizeof(struct KElectricRates), 1, pointer);
            fclose(pointer);
            return 1;
            break;
        }

        default: {
            printf("\nIncorrect option entered!\n");
            goto exit;
            break;
        }
    }
}

int SSGCRatesModification(char category) {
    int option1;
    float temp1, temp2;
    char selection1;
    FILE* pointer;
    struct SSGCRates data;

    pointer = fopen(ssgcRates, "rb+");

    if (pointer == NULL) {
        return 404;
    }

    top:
    switch (category) {
        case 'R': {
            options1:
            printf("\n\nResidential:\n");
            printf("Enter 1 to change the unit price for up to 50 units\n");
            printf("Enter 2 to change the unit price for up to 150 units\n");
            printf("Enter 3 to change the unit price for up to 250 units\n");
            printf("Enter 4 to change the unit price for up to 350 units\n");
            printf("Enter 5 to change the unit price for up to 450 units\n");
            printf("Enter 6 to change the unit price for more than 450 units\n");
            printf("Enter 7 to chnage the minimum price\n");
            printf("Enter 8 to change the sales tax percentage\n");
            printf("Enter 9 to change the income tax percentage\n");
            printf("Enter 10 to go back\n");
            printf("Enter you desired option: ");
            scan("%d", &option1);
            fflush(stdin);

            switch (option1) {
                case 1: {
                    case1:
                    printf("Enter unit price for up to 50 units: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter unit price for up to 50 units again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter unit price for up to 50 units for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.upTo50 = temp2;
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case1;
                    }
                    break;
                }

                case 2: {
                    case2:
                    printf("Enter unit price for up to 150 units: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter unit price for up to 150 units again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter unit price for up to 150 units for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.upTo150 = temp2;
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case2;
                    }
                    break;
                }

                case 3: {
                    case3:
                    printf("Enter unit price for up to 250 units: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter unit price for up to 250 units again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter unit price for up to 250 units for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.upTo250 = temp2;
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case3;
                    }
                    break;
                }

                case 4: {
                    case4:
                    printf("Enter unit price for up to 350 units: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter unit price for up to 350 units again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter unit price for up to 350 units for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.upTo350 = temp2;
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case4;
                    }
                    break;
                }

                case 5: {
                    case5:
                    printf("Enter unit price for up to 450 units: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter unit price for up to 450 units again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter unit price for up to 450 units for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.upTo450 = temp2;
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case5;
                    }
                    break;
                }

                case 6: {
                    case6:
                    printf("Enter unit price for more than 450 units: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter unit price for more than 450 units again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter unit price for more than 450 units for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.moreThan450 = temp2;
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case6;
                    }
                    break;
                }

                case 7: {
                    case7:
                    printf("Enter the minimum price: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter the minimum price again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the minimum price for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.minR = temp2;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case7;
                    }
                    break;
                }

                case 8: {
                    case8:
                    printf("Enter the sales tax in percentage: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect percentage entered!\n");
                        printf("Enter the sales tax in percentage again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the sales tax in percentage for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.salesTaxR = temp2 / 100;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case8;
                    }
                    break;
                }

                case 9: {
                    case9:
                    printf("Enter the income tax in percentage: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect percentage entered!\n");
                        printf("Enter the income tax in percentage again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the income tax in percentage for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.incomeTaxR = temp2 / 100;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case9;
                    }
                    break;
                }

                case 10: {
                    return 2;
                    break;
                }

                default: {
                    printf("\nIncorrect option selected!\n");
                    goto options1;
                    break;
                }
            }
        }

        case 'C': {
            options2:
            printf("\n\nCommercial:\n");
            printf("Enter 1 to change the unit price\n");
            printf("enter 2 to chnage the minimum price\n");
            printf("Enter 3 to change the sales tax percentage\n");
            printf("Enter 4 to change the income tax percentage\n");
            printf("Enter 5 to go back\n");
            printf("Enter you desired option: ");
            scan("%d", &option1);
            fflush(stdin);

            switch (option1) {
                case 1: {
                    case1C:
                    printf("Enter unit price: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter unit price again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter unit price for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.unitPriceC = temp2;
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case1C;
                    }
                    break;
                }

                case 2: {
                    case2C:
                    printf("Enter the minimum price: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect amount entered!\n");
                        printf("Enter the minimum price again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the minimum price for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.minC = temp2;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case2C;
                    }
                    break;
                }

                case 3: {
                    case3C:
                    printf("Enter the sales tax in percentage: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect percentage entered!\n");
                        printf("Enter the sales tax in percentage again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the sales tax in percentage for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.salesTaxC = temp2 / 100;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case3C;
                    }
                    break;
                }

                case 4: {
                    case4C:
                    printf("Enter the income tax in percentage: ");
                    scanf("%f", &temp1);
                    fflush(stdin);
                    while (temp1 < 0) {
                        printf("\nIncorrect percentage entered!\n");
                        printf("Enter the income tax in percentage again: ");
                        scanf("%f", &temp1);
                        fflush(stdin);
                    }

                    printf("Enter the income tax in percentage for confirmation: ");
                    scanf("%f", &temp2);
                    fflush(stdin);

                    if (temp1 == temp2) {
                        data.incomeTaxC = temp2 / 100;                        
                    }
                    else {
                        printf("\nRates entered does not match!\n");
                        goto case4C;
                    }
                    break;
                }

                case 5: {
                    return 2;
                    break;
                }

                default: {
                    printf("\nIncorrect option selected!\n");
                    goto options2;
                    break;
                }
            }
        }
    }

    exit:
    printf("\n\nDo you want to modify any other rates? (Yes or No)\n");
    scanf("%c", &selection1);
    fflush(stdin);

    switch (selection1) {
        case 'Y':
        case 'y': {
            printf("\n\n");
            goto top;
            break;
        }

        case 'N':
        case 'n': {
            fseek(pointer, 0L, SEEK_SET);
            fwrite(&data, sizeof(struct SSGCRates), 1, pointer);
            fclose(pointer);
            return 1;
            break;
        }

        default: {
            printf("\nIncorrect option entered!\n");
            goto exit;
            break;
        }
    }
}

int PTCLRatesModification() {
    int option1;
    float temp1, temp2;
    char selection1;
    struct PTCLRates data;
    FILE* pointer;

    pointer = fopen(ptclRates, "rb+");

    if (pointer == NULL) {
        return 404;
    }

    top:
    printf("Enter 1 to change the price of freedom 500 landline package\n");
    printf("Enter 2 to change the price of freedom 1000 landline package\n");
    printf("Enter 3 to change the price of freedom 3000 landline package\n");
    printf("Enter 4 to change the price of freedom 5000 landline package\n");
    printf("Enter 5 to change the price of freedom 8000 landline package\n");    
    printf("Enter 6 to change the price of 6 Mbps broadband package\n");
    printf("Enter 7 to change the price of 8 Mbps broadband package\n");
    printf("Enter 8 to change the price of 15 Mbps broadband package\n");
    printf("Enter 9 to change the price of 25 Mbps broadband package\n");
    printf("Enter 10 to change the price of 50 Mbps broadband package\n");
    printf("Enter 11 to change the price of 100 Mbps broadband package\n");
    printf("Enter 12 to change the price of Smart TV subscription without broadband\n");
    printf("Enter 13 to change the price of Smart TV subscription with broadband\n");
    printf("Enter 14 to change the price of Smart TV App subscription\n");
    printf("Enter 15 to change the price of Unlimited data Charji package\n");
    printf("Enter 16 to change the price of 20 GB data Charji package\n");
    printf("Enter 17 to change the price of 30 GB data Charji package\n");
    printf("Enter 18 to change the price of 50 GB data Charji package\n");
    printf("Enter 19 to change the price of per minute call to mobile number\n");
    printf("Enter 20 to change the price of per minute call to other number\n");
    printf("Enter 21 to change the price of per minute call to International Zone 1 number\n");
    printf("Enter 22 to change the percentage of withholding tax on telephone bill greater than 1000\n");
    printf("Enter 23 to change the percentage of withholding tax on broadband\n");
    printf("Enter 24 to change the percentage of service tax on broadband\n");
    printf("Enter 25 to change the percentage of service tax on TV\n");
    printf("Enter 26 to change the percentage of service tax\n");
    printf("Enter 27 to go back\n");
    printf("Enter you desired option: ");
    scan("%d", &option1);
    fflush(stdin);

    switch (option1) {

        case 1: {
            case1:
            printf("Enter price of freedom 500 landline package: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of freedom 500 landline package again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of freedom 500 landline package for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.freedom500L = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case1;
            }
            break;
        }

        case 2: {
            case2:
            printf("Enter price of freedom 1000 landline package: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of freedom 1000 landline package again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of freedom 1000 landline package for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.freedom1000L = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case2;
            }
            break;
        }

        case 3: {
            case3:
            printf("Enter price of freedom 3000 landline package: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of freedom 3000 landline package again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of freedom 3000 landline package for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.freedom3000L = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case3;
            }
            break;
        }

        case 4: {
            case4:
            printf("Enter price of freedom 5000 landline package: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of freedom 5000 landline package again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of freedom 5000 landline package for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.freedom5000L = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case4;
            }
            break;
        }

        case 5: {
            case5:
            printf("Enter price of freedom 8000 landline package: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of freedom 8000 landline package again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of freedom 8000 landline package for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.freedom8000L = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case5;
            }
            break;
        }

        case 6: {
            case6:
            printf("Enter price of 6 Mbps broadband package: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of 6 Mbps broadband package again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of 6 Mbps broadband package for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.mb6B = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case6;
            }
            break;
        }

        case 7: {
            case7:
            printf("Enter price of 8 Mbps broadband package: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of 8 Mbps broadband package again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of 8 Mbps broadband package for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.mb8B = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case7;
            }
            break;
        }

        case 8: {
            case8:
            printf("Enter price of 15 Mbps broadband package: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of 15 Mbps broadband package again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of 15 Mbps broadband package for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.mb15B = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case8;
            }
            break;
        }

        case 9: {
            case9:
            printf("Enter price of 25 Mbps broadband package: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of 25 Mbps broadband package again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of 25 Mbps broadband package for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.mb25B = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case9;
            }
            break;
        }

        case 10: {
            case10:
            printf("Enter price of 50 Mbps broadband package: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of 50 Mbps broadband package again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of 50 Mbps broadband package for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.mb50B = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case10;
            }
            break;
        }

        case 11: {
            case11:
            printf("Enter price of 100 Mbps broadband package: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of 100 Mbps broadband package again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of 100 Mbps broadband package for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.mb100B = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case11;
            }
            break;
        }

        case 12: {
            case12:
            printf("Enter price of Smart TV subscription without broadband: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of Smart TV subscription without broadband again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of Smart TV subscription without broadband for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.smartTVWOB = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case12;
            }
            break;
        }

        case 13: {
            case13:
            printf("Enter price of Smart TV subscription with broadband: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of Smart TV subscription with broadband again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of Smart TV subscription with broadband for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.smartTVWB = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case13;
            }
            break;
        }

        case 14: {
            case14:
            printf("Enter price of Smart TV App subscription: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of Smart TV App subscription again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of Smart TV App subscription for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.smartTVApp = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case14;
            }
            break;
        }

        case 15: {
            case15:
            printf("Enter price of Unlimited Charji package: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of Unlimited Charji package again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of Unlimited Charji package for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.dataUC = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case15;
            }
            break;
        }

        case 16: {
            case16:
            printf("Enter price of 20 GB Charji package: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of 20 GB Charji package again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of 20 GB Charji package for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.data20C = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case16;
            }
            break;
        }

        case 17: {
            case17:
            printf("Enter price of 30 GB Charji package: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of 30 GB Charji package again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of 30 GB Charji package for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.data30C = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case17;
            }
            break;
        }

        case 18: {
            case18:
            printf("Enter price of 50 GB Charji package: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of 50 GB Charji package again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of 50 GB Charji package for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.data50C = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case18;
            }
            break;
        }

        case 19: {
            case19:
            printf("Enter price of per minute call to mobile number: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of per minute call to mobile number again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of per minute call to mobile number for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.mobile = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case19;
            }
            break;
        }

        case 20: {
            case20:
            printf("Enter price of per minute call to other number: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of per minute call to other number again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of per minute call to other number for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.other = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case20;
            }
            break;
        }

        case 21: {
            case21:
            printf("Enter price of per minute call to International Zone 1 number: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect amount entered!\n");
                printf("Enter price of per minute call to International Zone 1 number again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter price of per minute call to International Zone 1 number for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.internationalZone1 = temp2;
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case21;
            }
            break;
        }

        case 22: {
            case22:
            printf("Enter the percentage of withholding tax on telephone bill greater than 1000: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect percentage entered!\n");
                printf("Enter the percentage of withholding tax on telephone bill greater than 1000 again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter the percentage of withholding tax on telephone bill greater than 1000 for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.withholdingTaxMoreThan1000L = temp2 / 100;                        
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case22;
            }
            break;
        }

        case 23: {
            case23:
            printf("Enter the percentage of withholding tax on broadband: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect percentage entered!\n");
                printf("Enter the percentage of withholding tax on broadband again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter the percentage of withholding tax on broadband for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.withholdingTaxB = temp2 / 100;                        
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case23;
            }
            break;
        }

        case 24: {
            case24:
            printf("Enter the percentage of service tax on broadband: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect percentage entered!\n");
                printf("Enter the percentage of service tax on broadband again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter the percentage of service tax on broadband for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.serviceTaxB = temp2 / 100;                        
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case24;
            }
            break;
        }

        case 25: {
            case25:
            printf("Enter the percentage of service tax on TV: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect percentage entered!\n");
                printf("Enter the percentage of service tax on TV again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter the percentage of service tax on TV for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.serviceTaxTV = temp2 / 100;                        
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case25;
            }
            break;
        }

        case 26: {
            case26:
            printf("Enter the percentage of service tax: ");
            scanf("%f", &temp1);
            fflush(stdin);
            while (temp1 < 0) {
                printf("\nIncorrect percentage entered!\n");
                printf("Enter the percentage of service tax again: ");
                scanf("%f", &temp1);
                fflush(stdin);
            }

            printf("Enter the percentage of service tax for confirmation: ");
            scanf("%f", &temp2);
            fflush(stdin);

            if (temp1 == temp2) {
                data.overallServiceTax = temp2 / 100;                        
            }
            else {
                printf("\nRates entered does not match!\n");
                goto case26;
            }
            break;
        }

        case 27: {
            return 2;
            break;
        }

        default: {
            printf("\nIncorrect option selected!\n\n");
            goto top;
            break;
        }
    }

    exit:
    printf("\n\nDo you want to modify any other rates? (Yes or No)\n");
    scanf("%c", &selection1);
    fflush(stdin);

    switch (selection1) {
        case 'Y':
        case 'y': {
            printf("\n\n");
            goto top;
            break;
        }

        case 'N':
        case 'n': {
            fseek(pointer, 0L, SEEK_SET);
            fwrite(&data, sizeof(struct PTCLRates), 1, pointer);
            fclose(pointer);
            return 1;
            break;
        }

        default: {
            printf("\nIncorrect option entered!\n");
            goto exit;
            break;
        }
    }
}

int AdminPasswordChange() {
    struct AdminControl userData, userFromFile;
    FILE* pointer;
    int sizeFromFile, counter1, length, found = 0;
    char tempPassword1[40], tempPassword2[40];

    pointer = fopen(adminFile, "rb+");

    if (pointer == NULL) {
        return 404;
    }

    printf("Enter username: ");
    gets(userData.username);
    fflush(stdin);

    length = strlen(userData.username);

    for (counter1 = 0; counter1 < length; counter1++) {
        if (userData.username[counter1] >= 'A' && userData.username[counter1] <= 'Z') {
            userData.username[counter1] += 32;
        }
    } 

    printf("Enter old password: ");
    gets(userData.password);
    fflush(stdin);

    sizeFromFile = ArraySize(pointer, sizeof(struct AdminControl));

    for (counter1 = 0; counter1 < sizeFromFile; counter1++) {
        fread(&userFromFile, sizeof(struct AdminControl), 1, pointer);
        if (strcmp(userData.username, userFromFile.username) == 0) {
            if (strcmp(userData.password, userFromFile.password) == 0) {
                found = 1;
                break;
            }
        }
    }    
    
    if (found == 0) {
        return 0;
    }
    
    newpassword:
    printf("Enter new password: ");
    gets(tempPassword1);
    fflush(stdin);
    while(strlen(tempPassword1) <= 0) {
        printf("\nPassword field cannot be empty!\n");
        printf("Enter new password again: ");
        gets(tempPassword1);
        fflush(stdin);
    }

    printf("Enter new password again for confirmation: ");
    gets(tempPassword2);
    fflush(stdin);

    if (strcmp(tempPassword1, tempPassword2) != 0) {
        printf("\nPassword does not match!\n");
        goto newpassword;
    }

    strcpy(userData.password, tempPassword2);

    fseek(pointer, -(sizeof(struct AdminControl)), SEEK_CUR);
    fseek(pointer, 0L, SEEK_CUR);

    fwrite(&userData, sizeof(struct AdminControl), 1, pointer);
    fclose(pointer);

    return 1;
}

int AdminAdd() {
    struct AdminControl userData, userFromFile;
    FILE* pointer;
    int counter1, length, sizeFromFile;

    pointer = fopen(adminFile, "ab+");

    if (pointer == NULL) {
        return 404;
    }

    sizeFromFile = ArraySize(pointer, sizeof(struct AdminControl));

    username:
    printf("Enter username: ");
    gets(userData.username);
    fflush(stdin);
    while(strlen(userData.username) <= 0) {
        printf("\nUsername is required!\n");
        printf("Enter username again: ");
        gets(userData.username);
        fflush(stdin);
    }

    length = strlen(userData.username);

    for (counter1 = 0; counter1 < length; counter1++) {
        if (userData.username[counter1] >= 'A' && userData.username[counter1] <= 'Z') {
            userData.username[counter1] += 32;
        }
    } 

    for (counter1 = 0; counter1 < sizeFromFile; counter1++) {
        fread(&userFromFile, sizeof(struct AdminControl), 1, pointer);
        if (strcmp(userData.username, userFromFile.username) == 0) {
            printf("\nUser with this username already exists! User another username\n");
            goto username;
        }
    }

    printf("Enter password: ");
    gets(userData.password);
    fflush(stdin);
    while(strlen(userData.password) <= 0) {
        printf("\nPassword is required!\n");
        printf("Enter password again: ");
        gets(userData.password);
        fflush(stdin);
    }

    fseek(pointer, 0L, SEEK_END);
    fwrite(&userData, sizeof(struct AdminControl), 1, pointer);
    fclose(pointer);

    return 1;
}

int AdminVerification(struct AdminControl userData) {
    struct AdminControl userFromFile;
    FILE* pointer;
    int sizeFromFile, counter1, found = 0;

    pointer = fopen(adminFile, "rb");

    if (pointer == NULL) {
        return 404;
    }

    sizeFromFile = ArraySize(pointer, sizeof(struct AdminControl));

    for (counter1 = 0; counter1 < sizeFromFile; counter1++) {
        fread(&userFromFile, sizeof(struct AdminControl), 1, pointer);
        if (strcmp(userData.username, userFromFile.username) == 0) {
            found = 1;
            break;
        }
    }

    if (found == 0) {
        return 0;
    }

    fclose(pointer);

    if (strcmp(userData.password, userFromFile.password) == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

