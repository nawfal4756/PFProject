#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int ArraySize(FILE* pointer, int structSize);
bool KElectricAccountNumberVerification(unsigned long long int accountNumber);
bool SSGCConsumerIDVerification(unsigned long long int consumerID);
bool PTCLAccountIDVerification(unsigned long long int accountID);
struct KElectricData KElectricIDSearch(unsigned long long int id);
struct SSGCData SSGCIDSearch(unsigned long long int id);
struct PTCLData PTCLIDSearch(unsigned long long int id);

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

    pointer = fopen("./DataFiles/KElectricData.txt", "rb");

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

    pointer = fopen("./DataFiles/SSGCData.txt", "rb");

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

    pointer = fopen("./DataFiles/PTCLData.txt", "rb");

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