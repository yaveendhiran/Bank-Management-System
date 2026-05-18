#include <stdio.h>
#include <stdlib.h>
struct Account {
    int accNo;
    char name[20];
    float balance;
};
void insertRecord() {
    FILE *fp = fopen("bank.dat", "ab");
    struct Account a;
    if (fp == NULL) {
        printf("File open failed!\n");
        return;
    }
    printf("Enter Account No: ");
    scanf("%d", &a.accNo);
    printf("Enter Name: ");
    scanf("%19s", a.name);
    printf("Enter Balance: ");
    scanf("%f", &a.balance);
    fwrite(&a, sizeof(a), 1, fp);
    fclose(fp);
    printf("Record inserted successfully!\n");
}
void displayRecords() {
    FILE *fp = fopen("bank.dat", "rb");
    struct Account a;
    if (fp == NULL) {
        printf("File open failed!\n");
        return;
    }
    printf("\n--- Bank Records ---\n");
    while (fread(&a, sizeof(a), 1, fp) == 1) {
        if (a.accNo != -1) {
            printf("AccNo: %d  Name: %s  Balance: %.2f\n",
                   a.accNo, a.name, a.balance);
        }
    }
    fclose(fp);
}
void updateRecord() {
    FILE *fp = fopen("bank.dat", "rb+");
    struct Account a;
    int searchAcc, found = 0;
    float amount;
    if (fp == NULL) {
        printf("File open failed!\n");
        return;
    }
    printf("Enter Account No to Update: ");
    scanf("%d", &searchAcc);
    while (fread(&a, sizeof(a), 1, fp) == 1) {
        if (a.accNo == searchAcc) {
            found = 1;
            printf("Current Balance: %.2f\n", a.balance);
            printf("Enter Deposit Amount: ");
            scanf("%f", &amount);
            a.balance += amount;
            fseek(fp, -(long)sizeof(a), SEEK_CUR);
            fwrite(&a, sizeof(a), 1, fp);
            printf("Update Successful! New Balance: %.2f\n", a.balance);
            break;
        }
    }
    if (!found) {
        printf("Account not found!\n");
    }
    fclose(fp);
}
void deleteRecord() {
    FILE *fp = fopen("bank.dat", "rb+");
    struct Account a;
    int searchAcc, found = 0;
    if (fp == NULL) {
        printf("File open failed!\n");
        return;
    }
    printf("Enter Account No to Delete: ");
    scanf("%d", &searchAcc);
    while (fread(&a, sizeof(a), 1, fp) == 1) {
        if (a.accNo == searchAcc) {
            found = 1;

            a.accNo = -1;  // logical delete
            fseek(fp, -(long)sizeof(a), SEEK_CUR);
            fwrite(&a, sizeof(a), 1, fp);
            printf("Record deleted successfully!\n");
            break;
        }
    }
    if (!found) {
        printf("Account not found!\n");
    }
    fclose(fp);
}
void searchRecord() {
    FILE *fp = fopen("bank.dat", "rb");
    struct Account a;
    int searchAcc, found = 0;
    if (fp == NULL) {
        printf("File open failed!\n");
        return;
    }
    printf("Enter Account No to Search: ");
    scanf("%d", &searchAcc);
    while (fread(&a, sizeof(a), 1, fp) == 1) {
        if (a.accNo == searchAcc) {
            found = 1;
            printf("\nAccount Found:\n");
            printf("AccNo: %d\nName: %s\nBalance: %.2f\n",
                   a.accNo, a.name, a.balance);
            break;
        }
    }
    if (!found) {
        printf("Account not found!\n");
    }
    fclose(fp);
}
int main() {
    int choice;
    while (1) {
        printf("\n==== BANK MENU ====\n");
        printf("1. Insert\n");
        printf("2. Display\n");
        printf("3. Update (Deposit)\n");
        printf("4. Delete\n");
        printf("5. Search\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 1) {
            insertRecord();
        } else if (choice == 2) {
            displayRecords();
        } else if (choice == 3) {
            updateRecord();
        } else if (choice == 4) {
            deleteRecord();
        } else if (choice == 5) {
            searchRecord();
        } else if (choice == 6) {
            printf("Exiting...\n");
            break;
        } else {
            printf("Invalid choice!\n");
        }
    }
    return 0;
}