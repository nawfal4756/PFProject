#include<stdbool.h>
#include <stdlib.h>
#include <string.h>
#include<stdio.h>

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
void PTCLBillPreview(struct PTCLData PTCL);
struct PTCLData PTCLIDSearch(unsigned long long int id);

int main()
{
    unsigned long long int accountID;
    struct PTCLData data;

    printf("Enter the account ID: ");
    scanf("%llu", &accountID);

    data = PTCLIDSearch(accountID);
    PTCLBillPreview(data);
}

void PTCLBillPreview(struct PTCLData PTCL)
{
    int counter2,counter3,counter,maximum,index=0;
    for(counter=0;counter<12;counter++) {
        maximum=PTCL.billYear[0];
        if(PTCL.billYear[counter]>=maximum) {
            maximum=PTCL.billYear[counter];
            index=counter+1;
        }
    }

    printf("-----------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\t\t\tPTCL\t\t\n");
    printf("\t\t\t\t\t\tHello to the Future\t\n");
    printf("-----------------------------------------------------------------------------------------------------------------\n");

    switch(index) {
        case 1:
        printf("Current Month and Year: January,%d\n",maximum);
        break;

        case 2:
        printf("Current Month and Year: February,%d\n",maximum);
        break;

        case 3:
        printf("Current Month and Year: March,%d\n",maximum);
        break;

        case 4:
        printf("Current Month and Year: April,%d\n",maximum);
        break;

        case 5:
        printf("Current Month and Year: May,%d\n",maximum);
        break;

        case 6:
        printf("Current Month and Year: June,%d\n",maximum);
        break;

        case 7:
        printf("Current Month and Year: July,%d\n",maximum);
        break;

        case 8:
        printf("Current Month and Year: August,%d\n",maximum);
        break;

        case 9:
        printf("Current Month and Year: September,%d\n",maximum);
        break;

        case 10:
        printf("Current Month and Year: October,%d\n",maximum);
        break;

        case 11:
        printf("Current Month and Year: November,%d\n",maximum);
        break;

        case 12:
        printf("Current Month and Year: December,%d\n",maximum);
        break;

    }
    
    printf("Consumer ID: %llu\n", PTCL.accountID);
    printf("Name: ");
    puts(PTCL.name);
    printf("Address: %s\n", PTCL.address);
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

int ArraySize(FILE* pointer, int structSize) {
    int size;

    fseek(pointer, 0L, SEEK_END);
    size = ftell(pointer);
    size = size / structSize;
    fseek(pointer, 0L, SEEK_SET);

    return size;
}
