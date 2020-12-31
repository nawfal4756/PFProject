#include <stdio.h>
#include <stdlib.h>

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

int SSGCPrintBill(struct SSGCData SSGC);

int main() {

}

int SSGCPrintBill(struct SSGCData SSGC) {
    int counter2,counter3,counter;
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