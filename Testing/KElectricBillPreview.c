#include<stdbool.h>
#include <stdlib.h>
#include <string.h>
#include<stdio.h>

char* kefile = "..\\DataFiles\\KElectricData.txt";

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
int ArraySize(FILE* pointer, int structSize);
void KElectricBillPreview(struct KElectricData KE);
struct KElectricData KElectricIDSearch(unsigned long long int id);
int main()
{
    unsigned long long int accountNumber;
    struct KElectricData data;

    printf("Enter the account number: ");
    scanf("%llu", &accountNumber);

    data = KElectricIDSearch(accountNumber);
    KElectricBillPreview(data);
}
void KElectricBillPreview(struct KElectricData KE)
{
    int counter2,counter3,counter,maximum,index=0;
    for(counter=0;counter<12;counter++) {
        if (counter == 0) {
            maximum=KE.billYear[0];
        }        
        if(KE.billYear[counter]>=maximum) {
            maximum=KE.billYear[counter];
            index=counter+1;
        }
    }

    printf("-----------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\t\tKELECTRIC\t\t\n");
    printf("\t\t\t\t\t\tEnergy That Moves Life\t\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------------\n");
    
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
    printf("Account number: %llu\n", KE.accountNumber);
    printf("Name: ");
    puts(KE.name);
    printf("Address: %s\n", KE.address);
    printf("Contact number: %llu\n",KE.contactNumber);
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
struct KElectricData KElectricIDSearch(unsigned long long int id) {
    // 0 = Not Found, 404 = Error
    
    FILE* pointer;
    struct KElectricData data;
    int sizeFromFile, counter1 = 0, found = 0;

    pointer = fopen(kefile, "rb");

    if (pointer == NULL) {
        printf("Data Null");
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
int ArraySize(FILE* pointer, int structSize) {
    int size;

    fseek(pointer, 0L, SEEK_END);
    size = ftell(pointer);
    size = size / structSize;
    fseek(pointer, 0L, SEEK_SET);

    return size;
}