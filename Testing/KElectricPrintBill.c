#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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

int KElectricPrintBill(struct KElectricData data);

int main() {
    struct KElectricData data;
    int response;
    data.accountNumber = 2534567898;
    response = KElectricPrintBill(data);
    if (response == 404) {
        printf("404");
    }
    else if (response == 1) {
        printf("1");
    }
    else {
        printf("Unknown");
    }
}

int KElectricPrintBill(struct KElectricData KE) {
    FILE* pointer;
    char accountNumber[15], fileName[50] = "KElectricBill-";
    int counter2, counter3, counter, maximum, index = 0;

    snprintf(accountNumber, sizeof(accountNumber), "%llu", KE.accountNumber);
    strcat(fileName, accountNumber);
    strcat(fileName, ".txt");
    
    pointer = fopen(fileName, "w");

    if (pointer == NULL) {
        return 404;
    }

    for(counter=0;counter<12;counter++) {
        if (counter == 0) {
            maximum=KE.billYear[0];
        }        
        if(KE.billYear[counter]>=maximum) {
            maximum=KE.billYear[counter];
            index=counter+1;
        }
    }
    
    fprintf(pointer, "-----------------------------------------------------------------------------------------------------------------------------------\n");
    fprintf(pointer, "\t\t\t\t\t\t\tKELECTRIC\t\t\n");
    fprintf(pointer, "\t\t\t\t\t\tEnergy That Moves Life\t\n");
    fprintf(pointer, "-----------------------------------------------------------------------------------------------------------------------------------\n");

    switch(index) {
        case 1: {
            fprintf(pointer, "Current Month and Year: January,%d\n", maximum);
            break;
        }

        case 2: {
            fprintf(pointer, "Current Month and Year: February,%d\n", maximum);
            break;
        }
        case 3: {
            fprintf(pointer, "Current Month and Year: March,%d\n", maximum);
            break;
        }        

        case 4: {
            fprintf(pointer, "Current Month and Year: April,%d\n", maximum);
            break;
        }

        case 5: {
            fprintf(pointer, "Current Month and Year: May,%d\n", maximum);
            break;
        }

        case 6: {
            fprintf(pointer, "Current Month and Year: June,%d\n", maximum);
            break;
        }

        case 7: {
            fprintf(pointer, "Current Month and Year: July,%d\n", maximum);
            break;
        }

        case 8: {
            fprintf(pointer, "Current Month and Year: August,%d\n", maximum);
            break;
        }

        case 9: {
            fprintf(pointer, "Current Month and Year: September,%d\n", maximum);
            break;
        }

        case 10: {
            fprintf(pointer, "Current Month and Year: October,%d\n", maximum);
            break;
        }

        case 11: {
            fprintf(pointer, "Current Month and Year: November,%d\n", maximum);
            break;
        }

        case 12: {
            fprintf(pointer, "Current Month and Year: December,%d\n", maximum);
            break;
        }
        
    }

    fprintf(pointer, "Account number: %llu\n", KE.accountNumber);
    fprintf(pointer, "Name: %s\n", KE.name);    
    fprintf(pointer, "Address: %s\n", KE.address);
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