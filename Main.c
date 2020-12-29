#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>

struct KElectricData {
    unsigned long long int accountNumber;
    char name[30];
    char address[70];
    unsigned long long int contactNumber;
    char usageType;
    float allotedLoad;
    int numberOfTV;
    // 0 = off peak units, 1 = on peak units, 2 = amount of electricity, 3 = electricity duty, 4 = Sales Tax, 5 = Income tax, 6 = tv license fee, 7 = amount due, 8 = amount paid
    float unitsAndPayment[9][12];
    bool timePayment[12];
};

struct SSGCData {
    unsigned long long int consumerId;
    char name[30];
    char address[70];
    unsigned long long int contactNumber;
    char usageType;
    // 0 = units, 1 = amount os natural gas used, 2 = Sales Tax, 3 = Income Tax, 4 = amount due, 5 = amount paid
    float unitsAndPayment[6][12];
};

struct PTCLData {
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
};

void Header(char id);
int Admin();
int Client();

int main() {
    char userInputClient;
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

    getch();
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
            printf("\t\t\t\t\t\tClient Panel\n");
            break;
        }
    }

    printf("--------------------------------------------------------------------------------------------------------------------");
    printf("\n\n");
}

int Admin() {
    Header('m');
    Header('a');
}

int Client() {
    int userInput1, userInput2, selection;
    unsigned long long int accountNumber;
    struct KElectricData dataKe;
    struct SSGCData dataSsgc;
    struct PTCLData dataPtcl;

    clientTop:
    Header('m');
    Header('c');
    printf("Select any one company to proceed\n");
    printf("Press 1 for K-Electric\n");
    printf("Press 2 for SSGC\n");
    printf("Press 3 for PTCL\n");
    printf("Enter desired option: ");
    scanf("%d", &userInput1);
    fflush(stdin);

    switch (userInput1) {
        case 1: {
            keAccountNum:
            printf("K-Electric: \n");
            printf("Enter account number to get the data\n");
            printf("Enter 1 to go to company selection\n");
            printf("Enter 2 to go to switch panel page\n");
            scanf("%llu", &accountNumber);
            fflush(stdin);

            if (accountNumber == 1) {
                system("cls");
                goto clientTop;
            }
            else if (accountNumber == 2) {
                return 1;
            }

            // if (verification function) {
            //     printf("Incorrect account number entered!\n");
            //     printf("\n\n");
            //     goto keAccountNum;
            // }

            //dataKe = Search Function call

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
            printf("Current Payable amount: %.2f\n" /*Amount variable to be entered*/);

            billOptions:
            printf("\n\nEnter 1 to preview complete bill\n");
            printf("Enter 2 to print the bill\n");
            printf("Enter 3 to pay the bill\n");
            printf("Enter 4 to enter another account number\n");
            printf("Enter 5 to go to company selection\n");
            printf("Enter 6 to go to switch panel change");
            printf("Enter the selected option: ");
            scanf("%d", &userInput2);
            fflush(stdin);

            switch (userInput2) {
                case 1: {
                    // Preview Function
                    break;
                }

                case 2: {
                    // Print Function
                    system("cls");
                    goto clientTop;
                    break;
                }

                case 3: {
                    // selection = Pay Function  
                    if (selection = 1) {
                        goto billOptions;
                    }
                    else if (selection == 0) {
                        system("cls");
                        goto clientTop;
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
                }

                default: {
                    printf("Incorrect option selected!\n");
                    goto billOptions;
                    break;
                }
            }
            break;
        }

        case 2: {
            
        }

        case 3: {
            
        }

        default: {
            printf("Incorrect option selected!\n");
            system("cls");
            goto clientTop;
            break;
        }
    }
}