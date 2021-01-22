#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include "Functions.c"

void Header(char id);
int Admin();
int Client();

// From Functions.c
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

// Main Program

int main() {
    char userInputClient, exitSelection;
    int selection, response;    

    clientSelection:
    Header('m');
    printf("Press A for admin panel\n");
    printf("Press C for client panel\n");
    printf("Enter your selected option: ");
    scanf("%c", &userInputClient);
    fflush(stdin);

    printf("\n");
    // If a function returns 1 go to client selection and if a function returns 0 ask to exit the program
    switch(userInputClient) {
        case 'a':
        case 'A': {
            system("cls");
            selection = Admin();
            if (selection == 1) {
                system("cls");
                goto clientSelection;
            }
            break;
        }

        case 'c':
        case 'C': {
            system("cls");
            selection = Client();
            if (selection == 1) {
                system("cls");
                goto clientSelection;
            }
            break;
        }

        default: {
            printf("Incorrect option selected!\nPress enter to continue...");
            getch();
            system("cls");
            goto clientSelection;
            break;
        }
    }

    exit:
    printf("Are you sure you want to exit the program? (Yes or No)\n");
    scanf("%c", &exitSelection);

    switch (exitSelection) {
        case 'y':
        case 'Y': {
            printf("The programs is exiting...\nPress enter to continue...");
            getch();
            exit(1);
            break;
        }

        case 'n':
        case 'N': {
            system("cls");
            goto clientSelection;
            break;
        }

        default: {
            printf("Incorrect option entered!\n\n");
            goto exit;
            break;
        }
    }

    
}

void Header(char id) {
    switch (id) {
        case 'm': {
            printf("\t\t\t\t\tWelcome to Utility Bill Management System\n");
            break;
        }

        case 'a': {
            printf("\t\t\t\t\t\t\tAdmin Panel\n");
            break;
        }

        case 'c': {
            printf("\t\t\t\t\t\t\tClient Panel\n");
            break;
        }
    }

    printf("--------------------------------------------------------------------------------------------------------------------");
    printf("\n\n");
}

int Admin() {
    int userInput1, userInput2, response;
    char selection1;
    unsigned long long int accountNumber;
    struct KElectricData dataKe;
    struct SSGCData dataSsgc;
    struct PTCLData dataPtcl;
    struct AdminControl adminDetails;
    
    Header('m');
    Header('a');    
    printf("Enter your username: ");
    gets(adminDetails.username);

    printf("Enter your password: ");
    gets(adminDetails.password);

    system("cls");
    Header('m');
    Header('a');

    response = AdminVerification(adminDetails);
    if (response == 404) {
        printf("Error while opening file!\nPress enter to continue...");
        getch();
        return 1;
    }
    else if (response == 0) {
        printf("Incoorect username or password\nPress enter to continue...");
        getch();
        return 1;
    }
    else if (response == 1) {
        system("cls");
        goto adminTop;
    }
    else {
        printf("\n\nOH NOO!! We crashed!\n");
        printf("Press Enter to continue...");
        getch();
        return 1;
    }
    
    adminTop:
    Header('m');
    Header('a');
    printf("Select any one company to proceed\n");
    printf("Enter 1 for K-Electric\n");
    printf("Enter 2 for SSGC\n");
    printf("Enter 3 for PTCL\n");
    printf("Enter 4 to change current admin password\n");
    printf("Enter 5 to add a new admin account\n");
    printf("Enter 6 to go to switch panel\n");
    printf("enter 7 to exit the program\n");
    printf("Enter desired option: ");
    scanf("%d", &userInput1);
    fflush(stdin);

    switch (userInput1) {
        case 1: {
            kelectric:
            printf("\n\nK-Electric: \n");
            printf("Enter 1 to add a new customer\n");
            printf("Enter 2 to modify customer details\n");
            printf("Enter 3 to preview data of a customer\n");
            printf("Enter 4 to print a bill for the customer\n");
            printf("Enter 5 to generate a new bill for the current month\n");
            printf("Enter 6 to modify the rates\n");
            printf("Enter 7 to go to company selection\n");
            printf("Enter 8 to go to panel selection\n");
            printf("Enter 9 to exit the program\n");
            printf("Enter desired option: ");
            scanf("%d", &userInput2);
            fflush(stdin);

            printf("\n\n");

            switch (userInput2) {
                case 1: {
                    response = KElectricAddCustomer();
                    if (response == 404) {
                        printf("\nA file error occured!\nPress enter to continue...\n\n");
                        getch();
                        goto kelectric;
                    }
                    else if (response == 1) {
                        printf("\n\nCustomer added successfully!\nPress enter to continue...");
                        getch();
                        system("cls");
                        goto adminTop;
                    }
                    else {
                        printf("\n\nOH NOO!! We crashed!\n");
                        printf("Press Enter to continue...");
                        getch();
                        goto kelectric;
                    }
                    break;
                }

                case 2:
                case 3: 
                case 4:
                case 5: {
                    keAccountNum:
                    printf("Enter account number to get the data\n");
                    printf("Enter 1 to go to company selection\n");
                    printf("Enter 2 to go to switch panel page\n");
                    printf("Enter 3 to exit the program\n");
                    scanf("%llu", &accountNumber);
                    fflush(stdin);

                    if (accountNumber == 1) {
                        system("cls");
                        goto adminTop;
                    }
                    else if (accountNumber == 2) {
                        return 1;
                    }
                    else if (accountNumber == 3) {
                        return 0;
                    }

                    if (!KElectricAccountNumberVerification(accountNumber)) {
                        printf("Incorrect account number entered!\n");
                        printf("\n\n");
                        goto keAccountNum;
                    }

                    printf("\n\n");

                    dataKe = KElectricIDSearch(accountNumber);

                    if (dataKe.accountNumber != accountNumber) {
                        if (dataKe.accountNumber == 0) {
                            printf("No record found of the account number entered\n");
                            printf("Press Enter to continue...");
                            getch();
                            system("cls");
                            goto adminTop;
                        }
                        else if (dataKe.accountNumber == 404) {
                            printf("\n\nProgram Error with file\n");
                            printf("Press Enter to continue...");
                            getch();
                            system("cls");
                            goto adminTop;
                        }
                        else {
                            printf("\n\nOH NOO!! We crashed!\n");
                            printf("Press Enter to continue...");
                            getch();
                            system("cls");
                            goto adminTop;
                        }
                    }

                    if (userInput2 == 2) {
                        printf("Account Number: %llu\n", dataKe.accountNumber);
                        printf("Name: %s\n", dataKe.name);
                        printf("Address: %s\n", dataKe.address);
                        printf("Contact Number: %llu\n", dataKe.contactNumber);
                        if (StarConsumer(dataKe.timePayment)) {
                            printf("\nYou are a star consumer!\n\n");
                        }
                        printf("Current Payable amount: %.2f\n\n", dataKe.total);

                        modifyke:
                        printf("Do you want to modify the data for this account? (Yes or No)\n");
                        scanf("%c", &selection1);
                        fflush(stdin);
                        printf("\n");

                        switch (selection1) {
                            case 'Y':
                            case 'y': {
                                dataKe = KElectricDataModification(dataKe);
                                response = KElectricRecordUpdate(dataKe);

                                if (response == 404) {
                                    printf("\nA file error occured! Record not updated\nPress enter to continue...\n\n");
                                    getch();
                                    goto kelectric;
                                }
                                else if (response == 1) {
                                    printf("\n\nCustomer record updated successfully!\nPress enter to continue...");
                                    getch();
                                    system("cls");
                                    goto adminTop;
                                }
                                else {
                                    printf("\n\nOH NOO!! We crashed!\n");
                                    printf("Press Enter to continue...");
                                    getch();
                                    system("cls");
                                    goto adminTop;
                                }
                            }

                            case 'N':
                            case 'n': {
                                printf("\n\n");
                                goto kelectric;
                                break;
                            }

                            default: {                            
                                printf("\nIncorrect option entered!\n");
                                goto modifyke;
                                break;
                            }
                        
                        }
                    
                    }

                    if (userInput2 == 3) {
                        KElectricBillPreview(dataKe);
                        system("cls");
                        goto adminTop;                        
                    }

                    if (userInput2 == 4) {
                        response = KElectricPrintBill(dataKe);
                        if (response == 404) {
                            printf("ERROR!\n");
                            goto kelectric;
                        }
                        else if (response == 1) {
                            printf("\n\nPrinted Successfully\nPress enter to continue...");
                            getch();
                            system("cls");
                            goto adminTop;
                        }
                        else {
                            printf("\n\nOH NOO!! We crashed!\n");
                            printf("Press Enter to continue...");
                            getch();
                            system("cls");
                            goto adminTop;
                        }
                        system("cls");
                        goto adminTop;                    
                        break;
                    }

                    if (userInput2 == 5) {
                        dataKe = KElectricGenerateCurrentBill(dataKe);
                        response = KElectricRecordUpdate(dataKe);

                        if (response == 404) {
                            printf("\nA file error occured! Record not updated\nPress enter to continue...\n\n");
                            getch();
                            goto kelectric;
                        }
                        else if (response == 1) {
                            printf("\n\nCustomer record updated successfully!\nPress enter to continue...");
                            getch();
                            system("cls");
                            goto adminTop;
                        }
                        else {
                            printf("\n\nOH NOO!! We crashed!\n");
                            printf("Press Enter to continue...");
                            getch();
                            system("cls");
                            goto adminTop;
                        }
                    }

                    break;
                }                                  

                case 6: {
                    printf("Enter the category for which the rates are to be changed (R - Residential, C - Commercial): ");
                    scanf("%c", selection1);
                    fflush(stdin);
                    while(selection1 != 'R' && selection1 != 'C' && selection1 != 'r' && selection1 != 'c') {
                        printf("\nIncorrect option entered!\n");
                        printf("Enter the category again for which the rates are to be changed (R - Residential, C - Commercial): ");
                        scanf("%c", selection1);
                        fflush(stdin);
                    }

                    if (selection1 == 'r') {
                        selection1 = 'R';
                    }
                    if (selection1 == 'c') {
                        selection1 = 'C';
                    }

                    response = KElectricRatesModification(selection1);
                    if (response == 404) {
                        printf("\n\nFile could not open!\nPress enter to continue...\n");
                        getch();
                        printf("\n\n");
                        goto kelectric;
                    }
                    else if (response == 1) {
                        printf("\n\nRates updated successfully!\nPress enter to continue...");
                        getch();
                        system("cls");
                        goto adminTop;
                    }
                    else if (response == 2) {
                        printf("\n\n");
                        goto ssgc;
                        break;
                    }
                    break;
                }

                case 7: {
                    system("cls");
                    goto adminTop;
                    break;
                }

                case 8: {
                    return 1;
                    break;
                }

                case 9: {
                    return 0;
                    break;
                }

                default: {
                    printf("\nIncorrect option entered!\n");
                    goto kelectric;
                    break;
                }
            }

            break;
        }

        case 2: {
            ssgc:
            printf("\n\nSSGC: \n");
            printf("Enter 1 to add a new customer\n");
            printf("Enter 2 to modify customer details\n");
            printf("Enter 3 to preview data of a customer\n");
            printf("Enter 4 to print a bill for the customer\n");
            printf("Enter 5 to generate a new bill for the current month\n");
            printf("Enter 6 to modify the rates\n");
            printf("Enter 7 to go to company selection\n");
            printf("Enter 8 to go to panel selection\n");
            printf("Enter 9 to exit the program\n");
            printf("Enter desired option: ");
            scanf("%d", &userInput2);
            fflush(stdin);

            printf("\n\n");

            switch (userInput2) {
                case 1: {
                    response = SSGCAddCustomer();
                    if (response == 404) {
                        printf("\nA file error occured!\nPress enter to continue...\n\n");
                        getch();
                        goto ssgc;
                    }
                    else if (response == 1) {
                        printf("\n\nCustomer added successfully!\nPress enter to continue...");
                        getch();
                        system("cls");
                        goto adminTop;
                    }
                    else {
                        printf("\n\nOH NOO!! We crashed!\n");
                        printf("Press Enter to continue...");
                        getch();
                        goto ssgc;
                    }
                    break;
                }

                case 2:
                case 3: 
                case 4:
                case 5: {
                    ssgcConsumerId:
                    printf("\n\nSSGC: \n");
                    printf("Enter consumer ID to get the data\n");
                    printf("Enter 1 to go to company selection\n");
                    printf("Enter 2 to go to switch panel page\n");
                    printf("Enter 3 to exit the program\n");
                    scanf("%llu", &accountNumber);
                    fflush(stdin);

                    if (accountNumber == 1) {
                        system("cls");
                        goto adminTop;
                    }
                    else if (accountNumber == 2) {
                        return 1;
                    }
                    else if (accountNumber == 3) {
                        return 0;
                    }

                    if (!SSGCConsumerIDVerification(accountNumber)) {
                        printf("\nIncorrect account number entered!\n");
                        printf("\n\n");
                        goto ssgcConsumerId;
                    }

                    printf("\n\n");

                    dataSsgc = SSGCIDSearch(accountNumber);

                    if (dataSsgc.consumerId != accountNumber) {
                        if (dataSsgc.consumerId == 0) {
                            printf("\n\nNo record found of the account number entered\n");
                            printf("Press Enter to continue...");
                            getch();
                            system("cls");
                            goto adminTop;
                        }
                        else if (dataSsgc.consumerId == 404) {
                            printf("\n\nProgram Error with file\n");
                            printf("Press Enter to continue...");
                            getch();
                            system("cls");
                            goto adminTop;
                        }
                        else {
                            printf("\n\nOH NOO!! We crashed!\n");
                            printf("Press Enter to continue...");
                            getch();
                            system("cls");
                            goto adminTop;
                        }
                    }

                    if (userInput2 == 2) {
                        printf("Consumer ID: %llu\n", dataSsgc.consumerId);
                        printf("Name: %s\n", dataSsgc.name);
                        printf("Address: %s\n", dataSsgc.address);
                        printf("Contact Number: %llu\n", dataSsgc.contactNumber);
                        printf("Current Payable amount: %.2f\n", dataSsgc.total);

                        modifyssgc:
                        printf("Do you want to modify the data for this account? (Yes or No)\n");
                        scanf("%c", &selection1);
                        fflush(stdin);
                        printf("\n");

                        switch (selection1) {
                            case 'Y':
                            case 'y': {
                                dataSsgc = SSGCDataModification(dataSsgc);
                                response = SSGCRecordUpdate(dataSsgc);

                                if (response == 404) {
                                    printf("\nA file error occured! Record not updated\nPress enter to continue...\n\n");
                                    getch();
                                    goto ssgc;
                                }
                                else if (response == 1) {
                                    printf("\n\nCustomer record updated successfully!\nPress enter to continue...");
                                    getch();
                                    system("cls");
                                    goto adminTop;
                                }
                                else if (response == 0) {
                                    printf("\n\nNo record found with this ID! Record could not be updated\nPress enter to continue...");
                                    getch();
                                    system("cls");
                                    goto adminTop;
                                }
                            }

                            case 'N':
                            case 'n': {
                                printf("\n\n");
                                goto ssgc;
                                break;
                            }

                            default: {                            
                                printf("\nIncorrect option entered!\n");
                                goto modifyssgc;
                                break;
                            }
                        
                        }
                    
                    }

                    if (userInput2 == 3) {
                        SSGCBillPreview(dataSsgc);
                        system("cls");
                        goto adminTop;                        
                    }

                    if (userInput2 == 4) {
                        response = SSGCPrintBill(dataSsgc);
                        if (response == 404) {
                            printf("ERROR!\n");
                            goto ssgc;
                        }
                        else if (response == 1) {
                            printf("\n\nPrinted Successfully\nPress enter to continue...");
                            getch();
                            system("cls");
                            goto adminTop; 
                        }
                        else {
                            printf("\n\nOH NOO!! We crashed!\n");
                            printf("Press Enter to continue...");
                            getch();
                            system("cls");
                            goto adminTop;
                        }
                        system("cls");
                        goto adminTop;                    
                        break;
                    }

                    if (userInput2 == 5) {
                        dataSsgc = SSGCGenerateCurrentBill(dataSsgc);
                        response = SSGCRecordUpdate(dataSsgc);

                        if (response == 404) {
                            printf("\nA file error occured! Record not updated\nPress enter to continue...\n\n");
                            getch();
                            goto ssgc;
                        }
                        else if (response == 1) {
                            printf("\n\nCustomer record updated successfully!\nPress enter to continue...");
                            getch();
                            system("cls");
                            goto adminTop;
                        }
                        else {
                            printf("\n\nOH NOO!! We crashed!\n");
                            printf("Press Enter to continue...");
                            getch();
                            system("cls");
                            goto adminTop;
                        }
                    }

                    break;
                }

                case 6: {
                    printf("Enter the category for which the rates are to be changed (R - Residential, I - Industrial): ");
                    scanf("%c", selection1);
                    fflush(stdin);
                    while(selection1 != 'R' && selection1 != 'I' && selection1 != 'r' && selection1 != 'i') {
                        printf("\nIncorrect option entered!\n");
                        printf("Enter the category again for which the rates are to be changed (R - Residential, I - Industrial): ");
                        scanf("%c", selection1);
                        fflush(stdin);
                    }

                    if (selection1 == 'r') {
                        selection1 = 'R';
                    }
                    if (selection1 == 'i') {
                        selection1 = 'I';
                    }

                    response = SSGCRatesModification(selection1);
                    if (response == 404) {
                        printf("\n\nFile could not open!\nPress enter to continue...\n");
                        getch();
                        printf("\n\n");
                        goto ssgc;
                    }
                    else if (response == 1) {
                        printf("\n\nRates updated successfully!\nPress enter to continue...");
                        getch();
                        system("cls");
                        goto adminTop;
                    }
                    else if (response == 2) {
                        printf("\n\n");
                        goto ssgc;
                        break;
                    }
                    break;
                }

                case 7: {
                    system("cls");
                    goto adminTop;
                    break;
                }

                case 8: {
                    return 1;
                    break;
                }

                case 9: {
                    return 0;
                    break;
                }

                default: {
                    printf("\nIncorrect option entered!\n");
                    goto ssgc;
                    break;
                }
            }

            break;
        }

        case 3: {
            ptcl:
            printf("\n\nPTCL: \n");
            printf("Enter 1 to add a new customer\n");
            printf("Enter 2 to modify customer details\n");
            printf("Enter 3 to preview data of a customer\n");
            printf("Enter 4 to print a bill for the customer\n");
            printf("Enter 5 to generate a new bill for the current month\n");
            printf("Enter 6 to modify the rates\n");
            printf("Enter 7 to go to company selection\n");
            printf("Enter 8 to go to panel selection\n");
            printf("Enter 9 to exit the program\n");
            printf("Enter desired option: ");
            scanf("%d", &userInput2);
            fflush(stdin);

            printf("\n\n");

            switch (userInput2) {
                case 1: {
                    response = PTCLAddCustomer();
                    if (response == 404) {
                        printf("\nA file error occured!\nPress enter to continue...\n\n");
                        getch();
                        goto ptcl;
                    }
                    else if (response == 1) {
                        printf("\n\nCustomer added successfully!\nPress enter to continue...");
                        getch();
                        system("cls");
                        goto adminTop;
                    }
                    else {
                        printf("\n\nOH NOO!! We crashed!\n");
                        printf("Press Enter to continue...");
                        getch();
                        goto ptcl;
                    }
                    break;
                }

                case 2:
                case 3:
                case 4:
                case 5: {
                    ptclAccountId:
                    printf("\n\nPTCL: \n");
                    printf("Enter account ID to get the data\n");
                    printf("Enter 1 to go to company selection\n");
                    printf("Enter 2 to go to switch panel page\n");
                    printf("Enter 3 to exit the program\n");
                    scanf("%llu", &accountNumber);
                    fflush(stdin);

                    if (accountNumber == 1) {
                        system("cls");
                        goto adminTop;
                    }
                    else if (accountNumber == 2) {
                        return 1;
                    }
                    else if (accountNumber == 3) {
                        return 0;
                    }

                    if (!PTCLAccountIDVerification(accountNumber)) {
                        printf("\nIncorrect account number entered!\n");
                        printf("\n\n");
                        goto ptclAccountId;
                    }

                    printf("\n\n");

                    dataPtcl = PTCLIDSearch(accountNumber);

                    if (dataPtcl.accountID != accountNumber) {
                        if (dataPtcl.accountID == 0) {
                            printf("\n\nNo record found of the account number entered\n");
                            printf("Press Enter to continue...");
                            getch();
                            system("cls");
                            goto adminTop;
                        }
                        else if (dataPtcl.accountID == 404) {
                            printf("\n\nProgram Error with file\n");
                            printf("Press Enter to continue...");
                            getch();
                            system("cls");
                            goto adminTop;
                        }
                        else {
                            printf("\n\nOH NOO!! We crashed!\n");
                            printf("Press Enter to continue...");
                            getch();
                            system("cls");
                            goto adminTop;
                        }
                    }

                    if (userInput2 == 2) {
                        printf("Account ID: %llu\n", dataPtcl.accountID);
                        printf("Name: %s\n", dataPtcl.name);
                        printf("Address: %s\n", dataPtcl.address);
                        printf("Contact Number: %llu\n", dataPtcl.contactNumber);
                        printf("Current Payable amount: %.2f\n", dataPtcl.total);

                        modifyptcl:
                        printf("Do you want to modify the data for this account? (Yes or No)\n");
                        scanf("%c", &selection1);
                        fflush(stdin);
                        printf("\n");

                        switch (selection1) {
                            case 'Y':
                            case 'y': {
                                dataPtcl = PTCLDataModification(dataPtcl);
                                response = PTCLRecordUpdate(dataPtcl);

                                if (response == 404) {
                                    printf("\nA file error occured! Record not updated\nPress enter to continue...\n\n");
                                    getch();
                                    goto ptcl;
                                }
                                else if (response == 1) {
                                    printf("\n\nCustomer record updated successfully!\nPress enter to continue...");
                                    getch();
                                    system("cls");
                                    goto adminTop;
                                }
                                else if (response == 0) {
                                    printf("\n\nNo record found with this ID! Record could not be updated\nPress enter to continue...");
                                    getch();
                                    system("cls");
                                    goto adminTop;
                                }
                            }

                            case 'N':
                            case 'n': {
                                printf("\n\n");
                                goto ptcl;
                                break;
                            }

                            default: {                            
                                printf("\nIncorrect option entered!\n");
                                goto modifyptcl;
                                break;
                            }
                        
                        }
                    
                    }

                    if (userInput2 == 3) {
                        PTCLBillPreview(dataPtcl);
                        system("cls");
                        goto adminTop;                        
                    }

                    if (userInput2 == 4) {
                        response = PTCLPrintBill(dataPtcl);
                        if (response == 404) {
                            printf("ERROR!\n");
                            goto ptcl;
                        }
                        else if (response == 1) {
                            printf("\n\nPrinted Successfully\nPress enter to continue...");
                            getch();
                            system("cls");
                            goto adminTop;  
                        }
                        else {
                            printf("\n\nOH NOO!! We crashed!\n");
                            printf("Press Enter to continue...");
                            getch();
                            system("cls");
                            goto adminTop;
                        }
                        system("cls");
                        goto adminTop;                    
                        break;
                    }

                    if (userInput2 == 5) {
                        dataPtcl = PTCLGenerateCurrentBill(dataPtcl);
                        response = PTCLRecordUpdate(dataPtcl);

                        if (response == 404) {
                            printf("\nA file error occured! Record not updated\nPress enter to continue...\n\n");
                            getch();
                            goto ssgc;
                        }
                        else if (response == 1) {
                            printf("\n\nCustomer record updated successfully!\nPress enter to continue...");
                            getch();
                            system("cls");
                            goto adminTop;
                        }
                        else {
                            printf("\n\nOH NOO!! We crashed!\n");
                            printf("Press Enter to continue...");
                            getch();
                            system("cls");
                            goto adminTop;
                        }
                    }

                    break;
                }

                case 6: {
                    
                    if (response == 404) {
                        printf("\n\nFile could not open!\nPress enter to continue...\n");
                        getch();
                        printf("\n\n");
                        goto ssgc;
                    }
                    else if (response == 1) {
                        printf("\n\nRates updated successfully!\nPress enter to continue...");
                        getch();
                        system("cls");
                        goto adminTop;
                    }
                    else if (response == 2) {
                        printf("\n\n");
                        goto ssgc;
                        break;
                    }
                    break;
                }

                case 7: {
                    system("cls");
                    goto adminTop;
                    break;
                }

                case 8: {
                    return 1;
                    break;
                }

                case 9: {
                    return 0;
                    break;
                }

                default: {
                    printf("\nIncorrect option entered!\n");
                    goto ssgc;
                    break;
                }
            }

            break;
        }

        case 4: {
            response = AdminPasswordChange();
            if (response == 404) {
                printf("\nA file error occured!\nPress enter to continue...\n\n");
                getch();
                system("cls");
                goto adminTop;
            }
            else if (response == 1) {
                printf("\n\nPassword changed successfully!\nPress enter to continue...");
                getch();
                system("cls");
                goto adminTop;
            }
            else if (response == 0) {
                printf("\n\nNo user exists with this username!\nPress enter to continue...");
                getch();
                system("cls");
                goto adminTop;
            }
            else {
                printf("\n\nOH NOO!! We crashed!\n");
                printf("Press Enter to continue...");
                getch();
                goto adminTop;
            }
        }

        case 5: {
            response = AdminAdd();
            if (response == 404) {
                printf("\nA file error occured!\nPress enter to continue...\n\n");
                getch();
                system("cls");
                goto adminTop;
            }
            else if (response == 1) {
                printf("\n\nNew admin added successfully!\nPress enter to continue...");
                getch();
                system("cls");
                goto adminTop;
            }
            else {
                printf("\n\nOH NOO!! We crashed!\n");
                printf("Press Enter to continue...");
                getch();
                goto adminTop;
            }
        }

        case 6: {
            return 1;
            break;
        }

        case 7: {
            return 0;
            break;
        }

        default: {
            printf("Incorrect option selected!\n");
            system("cls");
            goto adminTop;
            break;
        }
    }
}

int Client() {
    int userInput1, userInput2, selection, selection2;
    float amount;
    unsigned long long int accountNumber;
    struct KElectricData dataKe;
    struct SSGCData dataSsgc;
    struct PTCLData dataPtcl;

    clientTop:
    Header('m');
    Header('c');
    printf("Select any one company to proceed\n");
    printf("Enter 1 for K-Electric\n");
    printf("Enter 2 for SSGC\n");
    printf("Enter 3 for PTCL\n");
    printf("Enter 4 to go to switch panel\n");
    printf("enter 5 to exit the program\n");
    printf("Enter desired option: ");
    scanf("%d", &userInput1);
    fflush(stdin);

    switch (userInput1) {
        case 1: {
            keAccountNum:
            printf("\n\nK-Electric: \n");
            printf("Enter account number to get the data\n");
            printf("Enter 1 to go to company selection\n");
            printf("Enter 2 to go to switch panel page\n");
            printf("Enter 3 to exit the program\n");
            scanf("%llu", &accountNumber);
            fflush(stdin);

            if (accountNumber == 1) {
                system("cls");
                goto clientTop;
            }
            else if (accountNumber == 2) {
                return 1;
            }
            else if (accountNumber == 3) {
                return 0;
            }

            if (!KElectricAccountNumberVerification(accountNumber)) {
                printf("Incorrect account number entered!\n");
                printf("\n\n");
                goto keAccountNum;
            }

            printf("\n\n");

            dataKe = KElectricIDSearch(accountNumber);

            if (dataKe.accountNumber != accountNumber) {
                if (dataKe.accountNumber == 0) {
                    printf("No record found of the account number entered\n");
                    printf("Press Enter to continue...");
                    getch();
                    system("cls");
                    goto clientTop;
                }
                else if (dataKe.accountNumber == 404) {
                    printf("\n\nProgram Error with file\n");
                    printf("Press Enter to continue...");
                    getch();
                    system("cls");
                    goto clientTop;
                }
                else {
                    printf("\n\nOH NOO!! We crashed!\n");
                    printf("Press Enter to continue...");
                    getch();
                    system("cls");
                    goto clientTop;
                }
            }

            printf("Account Number: %llu\n", dataKe.accountNumber);
            printf("Name: %s\n", dataKe.name);
            printf("Address: %s\n", dataKe.address);
            printf("Contact Number: %llu\n", dataKe.contactNumber);
            if (StarConsumer(dataKe.timePayment)) {
                printf("\nYou are a star consumer!\n\n");
            }
            printf("Current Payable amount: %.2f\n", dataKe.total);

            billOptionsKe:
            printf("\n\nEnter 1 to preview complete bill\n");
            printf("Enter 2 to print the bill\n");            
            printf("Enter 3 to pay the bill\n");
            printf("Enter 4 to enter different account number\n");
            printf("Enter 5 to go to company selection\n");
            printf("Enter 6 to go to switch panel change\n");
            printf("Enter 7 to exit the program\n");
            printf("Enter the selected option: ");
            scanf("%d", &userInput2);
            fflush(stdin);

            printf("\n\n");

            switch (userInput2) {
                case 1: {
                    KElectricBillPreview(dataKe);                    
                    system("cls");
                    goto clientTop;
                    break;
                }

                case 2: {
                    selection = KElectricPrintBill(dataKe);
                    if (selection == 404) {
                        printf("ERROR!\n");
                        goto billOptionsKe;
                    }
                    system("cls");
                    goto clientTop;
                    break;
                }

                case 3: {
                    printf("Enter amount to pay: ");
                    scanf("%f", &amount);
                    selection = Payment(amount);
                    if (selection = 1) {
                        dataKe.total -= amount;
                        selection2 = KElectricRecordUpdate(dataKe);
                        if (selection2 == 404 || selection2 == 0) {
                            printf("ERROR!\n\n");
                            goto billOptionsKe;
                        }
                        else if (selection2 == 1) {
                            system("cls");
                            goto clientTop;
                        }
                    }
                    else if (selection == 0) {
                        printf("\n\n");
                        goto billOptionsKe;
                    }
                    break;
                }

                case 4: {
                    goto keAccountNum;
                    break;
                }

                case 5: {
                    system("cls");
                    goto clientTop;
                    break;
                }

                case 6: {
                    return 1;
                    break;
                }

                case 7: {
                    return 0;
                    break;
                }

                default: {
                    printf("Incorrect option selected!\n");
                    goto billOptionsKe;
                    break;
                }
            }
            break;
        }

        case 2: {
            ssgcConsumerId:
            printf("\n\nSSGC: \n");
            printf("Enter consumer ID to get the data\n");
            printf("Enter 1 to go to company selection\n");
            printf("Enter 2 to go to switch panel page\n");
            printf("Enter 3 to exit the program\n");
            scanf("%llu", &accountNumber);
            fflush(stdin);

            if (accountNumber == 1) {
                system("cls");
                goto clientTop;
            }
            else if (accountNumber == 2) {
                return 1;
            }
            else if (accountNumber == 3) {
                return 0;
            }

            if (!SSGCConsumerIDVerification(accountNumber)) {
                printf("\nIncorrect account number entered!\n");
                printf("\n\n");
                goto ssgcConsumerId;
            }

            printf("\n\n");

            dataSsgc = SSGCIDSearch(accountNumber);

            if (dataSsgc.consumerId != accountNumber) {
                if (dataSsgc.consumerId == 0) {
                    printf("\n\nNo record found of the account number entered\n");
                    printf("Press Enter to continue...");
                    getch();
                    system("cls");
                    goto clientTop;
                }
                else if (dataSsgc.consumerId == 404) {
                    printf("\n\nProgram Error with file\n");
                    printf("Press Enter to continue...");
                    getch();
                    system("cls");
                    goto clientTop;
                }
                else {
                    printf("\n\nOH NOO!! We crashed!\n");
                    printf("Press Enter to continue...");
                    getch();
                    system("cls");
                    goto clientTop;
                }
            }

            printf("Consumer ID: %llu\n", dataSsgc.consumerId);
            printf("Name: %s\n", dataSsgc.name);
            printf("Address: %s\n", dataSsgc.address);
            printf("Contact Number: %llu\n", dataSsgc.contactNumber);
            printf("Current Payable amount: %.2f\n", dataSsgc.total);

            billOptionsSsgc:
            printf("\n\nEnter 1 to preview complete bill\n");
            printf("Enter 2 to print the bill\n");
            printf("Enter 3 to pay the bill\n");
            printf("Enter 4 to enter different account number\n");
            printf("Enter 5 to go to company selection\n");
            printf("Enter 6 to go to switch panel change\n");
            printf("Enter 7 to exit the program\n");
            printf("Enter the selected option: ");
            scanf("%d", &userInput2);
            fflush(stdin);

            switch (userInput2) {
                case 1: {
                    SSGCBillPreview(dataSsgc);
                    system("cls");
                    goto clientTop;
                    break;
                }

                case 2: {
                    selection = SSGCPrintBill(dataSsgc);
                    if (selection == 404) {
                        printf("ERROR!\n");
                        goto billOptionsSsgc;
                    }
                    system("cls");
                    goto clientTop;
                    break;
                }

                case 3: {
                    printf("Enter amount to pay: ");
                    scanf("%f", &amount);
                    selection = Payment(amount);
                    if (selection = 1) {
                        dataSsgc.total -= amount;
                        selection2 = SSGCRecordUpdate(dataSsgc);
                        if (selection2 == 404 || selection2 == 0) {
                            printf("ERROR!\n\n");
                            goto billOptionsSsgc;
                        }
                        else if (selection2 == 1) {
                            system("cls");
                            goto clientTop;
                        }
                    }
                    else if (selection == 0) {
                        printf("\n\n");
                        goto billOptionsSsgc;
                    }
                    break;
                }

                case 4: {
                    goto ssgcConsumerId;
                    break;
                }

                case 5: {
                    system("cls");
                    goto clientTop;
                    break;
                }

                case 6: {
                    return 1;
                    break;
                }

                case 7: {
                    return 0;
                    break;
                }

                default: {
                    printf("Incorrect option selected!\n");
                    goto billOptionsSsgc;
                    break;
                }
            }
            break;
        }

        case 3: {
            ptclAccountId:
            printf("\n\nPTCL: \n");
            printf("Enter account ID to get the data\n");
            printf("Enter 1 to go to company selection\n");
            printf("Enter 2 to go to switch panel page\n");
            printf("Enter 3 to exit the program\n");
            scanf("%llu", &accountNumber);
            fflush(stdin);

            if (accountNumber == 1) {
                system("cls");
                goto clientTop;
            }
            else if (accountNumber == 2) {
                return 1;
            }
            else if (accountNumber == 3) {
                return 0;
            }

            if (!PTCLAccountIDVerification(accountNumber)) {
                printf("\nIncorrect account number entered!\n");
                printf("\n\n");
                goto ptclAccountId;
            }

            printf("\n\n");

            dataPtcl = PTCLIDSearch(accountNumber);

            if (dataPtcl.accountID != accountNumber) {
                if (dataPtcl.accountID == 0) {
                    printf("\n\nNo record found of the account number entered\n");
                    printf("Press Enter to continue...");
                    getch();
                    system("cls");
                    goto clientTop;
                }
                else if (dataPtcl.accountID == 404) {
                    printf("\n\nProgram Error with file\n");
                    printf("Press Enter to continue...");
                    getch();
                    system("cls");
                    goto clientTop;
                }
                else {
                    printf("\n\nOH NOO!! We crashed!\n");
                    printf("Press Enter to continue...");
                    getch();
                    system("cls");
                    goto clientTop;
                }
            }

            printf("Account ID: %llu\n", dataPtcl.accountID);
            printf("Name: %s\n", dataPtcl.name);
            printf("Address: %s\n", dataPtcl.address);
            printf("Contact Number: %llu\n", dataPtcl.contactNumber);
            printf("Current Payable amount: %.2f\n", dataPtcl.total);

            billOptionsPtcl:
            printf("\n\nEnter 1 to preview complete bill\n");
            printf("Enter 2 to print the bill\n");
            printf("Enter 3 to pay the bill\n");
            printf("Enter 4 to enter different account number\n");
            printf("Enter 5 to go to company selection\n");
            printf("Enter 6 to go to switch panel change\n");
            printf("Enter 7 to exit the program\n");
            printf("Enter the selected option: ");
            scanf("%d", &userInput2);
            fflush(stdin);

            switch (userInput2) {
                case 1: {
                    PTCLBillPreview(dataPtcl);
                    break;
                }

                case 2: {
                    selection = PTCLPrintBill(dataPtcl);
                    if (selection == 404) {
                        printf("ERROR!\n");
                        goto billOptionsPtcl;
                    }
                    system("cls");
                    goto clientTop;
                    break;
                }

                case 3: {
                     printf("Enter amount to pay: ");
                    scanf("%f", &amount);
                    selection = Payment(amount);
                    if (selection = 1) {
                        dataPtcl.total -= amount;
                        selection2 = PTCLRecordUpdate(dataPtcl);
                        if (selection2 == 404 || selection2 == 0) {
                            printf("ERROR!\n\n");
                            goto billOptionsPtcl;
                        }
                        else if (selection2 == 1) {
                            system("cls");
                            goto clientTop;
                        }
                    }
                    else if (selection == 0) {
                        printf("\n\n");
                        goto billOptionsPtcl;
                    }
                    break;
                }

                case 4: {
                    goto ptclAccountId;
                    break;
                }

                case 5: {
                    system("cls");
                    goto clientTop;
                    break;
                }

                case 6: {
                    return 1;
                    break;
                }

                case 7: {
                    return 0;
                    break;
                }

                default: {
                    printf("Incorrect option selected!\n");
                    goto billOptionsPtcl;
                    break;
                }
            }
            break;
        }

        case 4: {
            return 1;
            break;
        }

        case 5: {
            return 0;
            break;
        }

        default: {
            printf("Incorrect option selected!\n");
            system("cls");
            goto clientTop;
            break;
        }
    }
}