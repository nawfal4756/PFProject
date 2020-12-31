#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include "Functions.c"

// struct KElectricData {
//     //New Structure
//     unsigned long long int accountNumber;
//     char name[30];
//     char address[70];
//     unsigned long long int contactNumber;
//     char usageType;
//     float allotedLoad;
//     int numberOfTV;
//     // 0 = off peak units, 1 = on peak units, 2 = amount of electricity, 3 = electricity duty, 4 = Sales Tax, 5 = Income tax, 6 = tv license fee, 7 = amount due, 8 = amount paid
//     float unitsAndPayment[9][12];
//     int billYear[12];
//     bool timePayment[12];
//     float total;
// };

// struct SSGCData {
//     // New Structure
//     unsigned long long int consumerId;
//     char name[30];
//     char address[70];
//     unsigned long long int contactNumber;
//     char usageType;
//     // 0 = units, 1 = amount os natural gas used, 2 = Sales Tax, 3 = Income Tax, 4 = amount due, 5 = amount paid
//     float unitsAndPayment[6][12];
//     int billYear[12];
//     float total;
// };

// struct PTCLData {
//     // New Structure
//     unsigned long long int accountID;
//     char name[30];
//     char address[70];
//     unsigned long long int contactNumber;
//     int packageLandline;
//     int packageBroadband;
//     char packageTV;
//     char packageCharji;
//     int onNetMinutes[12];
//     int mobileMinutes[12];
//     int otherMinutes[12];
//     int internationalZone1Minutes[12];
//     int internationalOtherZoneMinutes[12];
//     // 0 = bill of PTCL, 1 = Service Tax, 2 = Withholding Tax, 3 = Late Payment Surcgarge, 4 = Total Bill, 5 = Recieved Payment
//     float payments[6][12];
//     int billYear[12];
//     float total;
// };

void Header(char id);
int Admin();
int Client();

// From Functions.c
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

int main() {
    char userInputClient, exitSelection;
    int selection;

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
    int userInput1;

    adminTop:
    Header('m');
    Header('a');
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
            printf("\n\nK-Electric: \n");
            printf("Enter 1 to add a new customer\n");
        }

        case 2: {
            
        }

        case 3: {
            
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
                    printf("\n\nNo record found of the account number entered\n");
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