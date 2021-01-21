#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <conio.h>

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
    float unitPriceC;
    float minC;
};

char* keFile = "./DataFiles/KElectricData.txt";
char* ssgcFile = "./DataFiles/SSGCData.txt";
char* ptclFile = "./DataFiles/PTCLData.txt";
char* creditCardFile = "./DataFiles/CreditCardData.txt";
char* adminFile = "./DataFiles/AdminFile.txt";
char* kelectricRates = "./DataFiles/KElectricRates.txt";
char* ssgcRates = "./DataFiles/SSGCRates.txt";

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

