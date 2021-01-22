#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include "Functions.c"

// From Functions.c

void Header(char id);
int Admin();
int Client();

// Client Function Prototypes

void Header(char id);
int Admin();
int Client();
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
int Payment(float amount, char company, unsigned long long int id);
int KElectricRecordUpdate(struct KElectricData dataNew);
int SSGCRecordUpdate(struct SSGCData dataNew);
int PTCLRecordUpdate(struct PTCLData dataNew);
int KElectricPrintBill(struct KElectricData KE);
int SSGCPrintBill(struct SSGCData SSGC);
int PTCLPrintBill(struct PTCLData PTCL);
bool StarConsumer(bool timePayment[12]);
void PaymentSlip(float amount, char company, unsigned long long int id);
bool ContactNumberVerification(unsigned long long int number);

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
void KElectricRatesPreview();
void SSGCRatesPreview();
void PTCLRatesPreview();

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
    printf("\n\nAre you sure you want to exit the program? (Yes or No)\n");
    scanf("%c", &exitSelection);
    fflush(stdin);

    switch (exitSelection) {
        case 'y':
        case 'Y': {
            printf("\nThe programs is exiting...\nPress enter to continue...");
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