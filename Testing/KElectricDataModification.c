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
struct KElectricData KElectricDataModification(struct KElectricData KE);
struct KElectricData KElectricIDSearch(unsigned long long int id);
int KElectricRecordUpdate(struct KElectricData dataNew);
bool ContactNumberVerification(unsigned long long int number);
int main()
{ 
    int response;
    char answer;
    unsigned long long int accountNumber;
    struct KElectricData data;
    struct KElectricData ModifiedData;

    printf("Enter the account number of that person whose data you want to modify: ");
    scanf("%llu", &accountNumber);
    fflush(stdin);

    data = KElectricIDSearch(accountNumber);
    ModifiedData=KElectricDataModification(data);
    response=KElectricRecordUpdate(ModifiedData);

    if (response == 404) {
        printf("Error");
    }
    else if (response = 1) {
        printf("Successful\n");
        printf("Do you want to modify another one?\n");
        printf("Press Y for yes and press N for no\n");
        printf("Your answer:");
        scanf("%c",&answer);
        fflush(stdin);
        
        if(answer=='Y'||answer=='y')
        {
            printf("Enter the account number of that person whose data you want to modify: ");
            scanf("%llu", &accountNumber);
            fflush(stdin);

            data = KElectricIDSearch(accountNumber);
            ModifiedData=KElectricDataModification(data);
            response=KElectricRecordUpdate(ModifiedData);
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
struct KElectricData KElectricDataModification(struct KElectricData KE)
{
    int choice, ch, year, month;
    char selection1;
    
    jump:
    printf("Which one you want to modify?\n");
    printf("Press 1 to modify the Name\n");
    printf("Press 2 to modify the Contact Number\n");
    printf("Press 3 to modify the Alloted Load\n");
    printf("Press 4 to modify the Number of TVs\n");
    printf("Press 5 to modify the Number of Units\n");
    printf("Your choice:\n");
    scanf("%d",&choice);
    fflush(stdin);

    switch (choice) {
        case 1: {
            printf("Enter the new Name:");
            gets(KE.name);
            fflush(stdin);
            while (strlen(KE.name) <= 0) {
                printf("\nName field cannot be empty!\n");
                printf("Enter the new Name again:");
                gets(KE.name);
                fflush(stdin);
            }
            break;
        }

        case 2: {
            printf("Enter the new Contact Number:");
            scanf("%llu", &KE.contactNumber);
            fflush(stdin);
            while (!ContactNumberVerification(KE.contactNumber)) {
                printf("Incorrect value!\n");
                printf("Enter the new Contact Number again: ");
                scanf("%llu", &KE.contactNumber);
                fflush(stdin);
            }
            break;
        }

        case 3: {
            printf("Enter the new Alloted Load: ");
            scanf("%f", &KE.allotedLoad);
            fflush(stdin);
            while (KE.allotedLoad <= 0) {
                printf("Incorrect number!\n");
                printf("Enter the new Alloted Load again: ");
                scanf("%f", &KE.allotedLoad);
                fflush(stdin);
            }
            break;
        }

        case 4: {
            printf("Enter the new Number of TVs: ");
            scanf("%d", &KE.numberOfTV);
            fflush(stdin);
            while (KE.numberOfTV < 0) {
                printf("\nNumber of Tvs is required!\n");
                printf("Enter the new Number of TVs again: ");
                scanf("%d", &KE.numberOfTV);
                fflush(stdin);
            }
            break;
        }

        case 5: {
            printf("Enter the month of the bill:\n");
            printf("Enter 1 for january, 2 for february and so on...\n");
            scanf("%d",&month);
            fflush(stdin);
            while(month < 0 && month > 12) {
                printf("Incorrect month!\n");
                printf("Enter the month of the bill again:");
                scanf("%d",&month);
                fflush(stdin);
            }

            printf("Enter the year of bill:");
            scanf("%d",&year);
            fflush(stdin);
            if(year != KE.billYear[month-1]) {
                printf("The record for %d year does not exist!\n", year);
                goto jump;
            }
            
            printf("Which units you want to change?\n");
            printf("press 0 to modify off peak units\n");
            printf("Press 1 to modify on peak units\n");
            printf("Your choice:");
            scanf("%d",&ch);
            fflush(stdin);

            while(ch != 0 && ch != 1) {
                printf("\nIncorrect choice!\n");
                printf("Enter your choice again:");
                scanf("%d",&ch);
                fflush(stdin);
            }

            if(ch == 0) {
                printf("Enter the new off peak units:");
                scanf("%f",&KE.unitsAndPayment[0][month-1]);
                fflush(stdin);
            }
            else if(ch==1) {
                printf("Enter the new on peak units:");
                scanf("%f",&KE.unitsAndPayment[1][month-1]);
                fflush(stdin);
            }
        }

        default: {
            printf("\nIncorrect option selected!\n");
            goto jump;
            break;
        }
    }

    exit:
    printf("\n\nDo you want to modify anything else? (Yes or No)\n");
    scanf("%c", &selection1);
    fflush(stdin);

    switch (selection1) {
        case 'Y':
        case 'y': {
            printf("\n\n");
            goto jump;
            break;
        }

        case 'N':
        case 'n': {
            return KE;
            break;
        }

        default: {
            printf("\nIncorrect option entered!\n");
            goto exit;
            break;
        }
    }    
}

int KElectricRecordUpdate(struct KElectricData dataNew) {
    struct KElectricData dataFromFile;
    FILE* pointer;
    int counter1, sizeFromFile, size, found = 0;

    pointer = fopen("../DataFiles/KElectricData.txt", "rb+");

    if (pointer == NULL) {
        return 404;
    }

    sizeFromFile = ArraySize(pointer, sizeof(struct KElectricData));    

    for (counter1 = 0; counter1 < sizeFromFile; counter1) {
        fread(&dataFromFile, sizeof(struct KElectricData), 1, pointer);
        if (dataFromFile.accountNumber == dataNew.accountNumber) {
            found = 1;
            break;
        }
    }

    if (found == 0) {
        return 404;
    }

    fseek(pointer, -(sizeof(struct KElectricData)), SEEK_CUR);
    fseek(pointer, 0L, SEEK_CUR);

    fwrite(&dataNew, sizeof(struct KElectricData), 1, pointer);

    fclose(pointer);

    return 1;
}

int ArraySize(FILE* pointer, int structSize) {
    int size;

    fseek(pointer, 0L, SEEK_END);
    size = ftell(pointer);
    size = size / structSize;
    fseek(pointer, 0L, SEEK_SET);

    return size;
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
