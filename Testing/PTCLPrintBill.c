#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int PTCLPrintBill(struct PTCLData PTCL);

int main() {
    struct PTCLData data;
    data.accountID = 26561561;
    PTCLPrintBill(data);
}

int PTCLPrintBill(struct PTCLData PTCL) {
    FILE* pointer;
    int counter2,counter3,counter,maximum,index=0;
    char accountId[15], fileName[50] = "PTCLBill-";

    snprintf(accountId, sizeof(accountId), "%llu", PTCL.accountID);
    strcat(fileName, accountId);
    strcat(fileName, ".txt");

    pointer = fopen(fileName, "w");

    if (pointer == NULL) {
        return 404;
    }

    for(counter=0;counter<12;counter++) {
        if (counter == 0) {
            maximum=PTCL.billYear[0];
        }        
        if(PTCL.billYear[counter]>=maximum) {
            maximum=PTCL.billYear[counter];
            index=counter+1;
        }
    }

    fprintf(pointer, "-----------------------------------------------------------------------------------------------------------------\n");
    fprintf(pointer, "\t\t\t\t\t\t\t\tPTCL\t\t\n");
    fprintf(pointer, "\t\t\t\t\t\tHello to the Future\t\n");
    fprintf(pointer, "-----------------------------------------------------------------------------------------------------------------\n");

    switch(index) {
        case 1:
        fprintf(pointer, "Current Month and Year: January,%d\n", maximum);
        break;

        case 2:
        fprintf(pointer, "Current Month and Year: February,%d\n", maximum);
        break;

        case 3:
        fprintf(pointer, "Current Month and Year: March,%d\n", maximum);
        break;

        case 4:
        fprintf(pointer, "Current Month and Year: April,%d\n", maximum);
        break;

        case 5:
        fprintf(pointer, "Current Month and Year: May,%d\n", maximum);
        break;

        case 6:
        fprintf(pointer, "Current Month and Year: June,%d\n", maximum);
        break;

        case 7:
        fprintf(pointer, "Current Month and Year: July,%d\n", maximum);
        break;

        case 8:
        fprintf(pointer, "Current Month and Year: August,%d\n", maximum);
        break;

        case 9:
        fprintf(pointer, "Current Month and Year: September,%d\n", maximum);
        break;

        case 10:
        fprintf(pointer, "Current Month and Year: October,%d\n", maximum);
        break;

        case 11:
        fprintf(pointer, "Current Month and Year: November,%d\n", maximum);
        break;

        case 12:
        fprintf(pointer, "Current Month and Year: December,%d\n", maximum);
        break;

    }

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