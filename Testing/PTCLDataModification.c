#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* PTCLfile = "..\\DataFiles\\PTCLData.txt";

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
struct PTCLData PTCLDataModification(struct PTCLData PTCL);
struct PTCLData PTCLIDSearch(unsigned long long int id);
int PTCLRecordUpdate(struct PTCLData dataNew);
bool ContactNumberVerification(unsigned long long int number);

int main()
{ 
    int response;
    char answer;
    unsigned long long int accountNumber;
    struct PTCLData data;
    struct PTCLData ModifiedData;

    printf("Enter the account number of that person whose data you want to modify: ");
    scanf("%llu", &accountNumber);
    fflush(stdin);

    data = PTCLIDSearch(accountNumber);
    ModifiedData=PTCLDataModification(data);
    response=PTCLRecordUpdate(ModifiedData);

    response:
    if (response == 404) {
        printf("Error");
    }
    else if (response = 1) {
        printf("Successful\n");
        printf("Do you want to modify another one?\n");
        printf("Press Y for yes and press N for no\n");
        printf("Your answer:");
        scanf("%c ",&answer);
        fflush(stdin);
        
        if(answer=='Y'||answer=='y')
        {
            printf("Enter the account number of that person whose data you want to modify: ");
            scanf("%llu", &accountNumber);
            fflush(stdin);

            data = PTCLIDSearch(accountNumber);
            ModifiedData=PTCLDataModification(data);
            response=PTCLRecordUpdate(ModifiedData);
            goto response;
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

struct PTCLData PTCLIDSearch(unsigned long long int id) {
    // 0 = Not Found, 404 = Error
    
    FILE* pointer;
    struct PTCLData data;
    int sizeFromFile, counter1 = 0, found = 0;

    pointer = fopen(PTCLfile, "rb");

    if (pointer == NULL) {
        printf("Data Null");
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

struct PTCLData PTCLDataModification(struct PTCLData PTCL)
{
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

int PTCLRecordUpdate(struct PTCLData dataNew) {
    struct PTCLData dataFromFile;
    FILE* pointer;
    int counter1, sizeFromFile, size, found = 0;

    pointer = fopen("../DataFiles/PTCLData.txt", "rb+");

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
