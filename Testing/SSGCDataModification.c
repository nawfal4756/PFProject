#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char* SSGCfile = "..\\DataFiles\\SSGCData.txt";

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

int ArraySize(FILE* pointer, int structSize);
bool ContactNumberVerification(unsigned long long int number);
struct SSGCData SSGCIDSearch(unsigned long long int id);
int SSGCRecordUpdate(struct SSGCData dataNew);
struct SSGCData SSGCDataModification(struct SSGCData SSGC);

int main()
{ 
    int response;
    char answer;
    unsigned long long int accountNumber;
    struct SSGCData data;
    struct SSGCData ModifiedData;

    printf("Enter the account number of that person whose data you want to modify: ");
    scanf("%llu", &accountNumber);
    fflush(stdin);

    data = SSGCIDSearch(accountNumber);
    ModifiedData=SSGCDataModification(data);
    response=SSGCRecordUpdate(ModifiedData);

    if (response == 404) {
        printf("Error");
    }
    else if (response = 1) {
        printf("Successful\n");
        printf("Do you want to modify another one?\n");
        printf("Press Y for yes and press N for no\n");
        printf("Your answer:");
        scanf("%c",&answer);
        fflush(stdin);
        
        if(answer=='Y'||answer=='y')
        {
            printf("Enter the account number of that person whose data you want to modify: ");
            scanf("%llu", &accountNumber);
            fflush(stdin);

            data = SSGCIDSearch(accountNumber);
            ModifiedData=SSGCDataModification(data);
            response=SSGCRecordUpdate(ModifiedData);
        }
        
        else if (answer=='N'||answer=='n')
        {
            printf("Programme has been exited!");
            exit(0);
        }
        
        while(answer!='Y'&&answer!='y'&&answer!='N'&&answer!='n')
        {
            printf("Incorrect answer!\n");
            printf("Please enter your answer again!\n");
            printf("Press Y for yes and press N for no\n");
            printf("Your answer:");
            scanf("%c",&answer);
            fflush(stdin);
        }

    }

}

struct SSGCData SSGCIDSearch(unsigned long long int id) {
    // 0 = Not Found, 404 = Error
    
    FILE* pointer;
    struct SSGCData data;
    int sizeFromFile, counter1 = 0, found = 0;

    pointer = fopen(SSGCfile, "rb");

    if (pointer == NULL) {
        printf("Data Null");
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

struct SSGCData SSGCDataModification(struct SSGCData SSGC)
{
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

int SSGCRecordUpdate(struct SSGCData dataNew) {
    struct SSGCData dataFromFile;
    FILE* pointer;
    int counter1, sizeFromFile, size, found = 0;

    pointer = fopen("../DataFiles/SSGCData.txt", "rb+");

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

int ArraySize(FILE* pointer, int structSize) {
    int size;

    fseek(pointer, 0L, SEEK_END);
    size = ftell(pointer);
    size = size / structSize;
    fseek(pointer, 0L, SEEK_SET);

    return size;
}

