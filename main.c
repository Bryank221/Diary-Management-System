#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

struct DiaryEntry {
    char date[20];
    char content[500];
};

struct DiaryEntry entries[500];
int count = 1;

void addEntry();
void viewEntries();
void editEntry();
void deleteEntry();
void saveToFile();
void loadFromFile();



void addEntry() {
    time_t raw;
    time(&raw);
    char leave;

    struct tm *time_ptr;
    time_ptr = localtime(&raw);

    strftime(entries[count].date, sizeof(entries[count].date), "%m/%d/%y", time_ptr);
    printf("Enter your entry here (Maximum of 500 words):\n");
    scanf(" %[^\n]s", entries[count].content);
    printf("------------------------------\nDate: %s\nEntry No: %d\nYour Entry: %s\n------------------------------\n", entries[count].date, count, entries[count].content);
    printf("Please Enter anything to continue: ");
    scanf("%s", &leave);
    count++;
    printf("------------------------------\n");
}

void editEntry() {
    int entry_selection;
    char selection1;
    char selection2;
    char *line = NULL;
    size_t len = 0;
    int result;
    int length,i;
    char none;
    char input[100] = "";
    int error;

    while (1) {
        while (1) {
            printf("Which entry would you like to edit: ");
            scanf("%s", input);
            length = strlen (input);
            for (i=0;i<length; i++) {
                if (!isdigit(input[i]))
                {
                    printf ("Entered input is not a number\n");
                    error = 1;
                    break;
                } else {
                    error = 0;
                    break;
                }
            }
            if (error == 0) {
                break;
            } else {
                continue;
            }
        }

        sscanf(input, "%d", &entry_selection);

        while (1) {
            printf("You have selected entry no: %d, is that correct? (Enter Y to continue and N to choose again): ", entry_selection);
            scanf("%s", &selection1);
            if (selection1 != 'Y' && selection1 != 'N') {
                printf("Incorrect choice entered, Please Try Again!\n");
                continue;
            } else {
                break;
            }
        }
        if (selection1 == 'Y') {
            break;
        } else if (selection1 == 'N'){
            continue;
        }
    }

    sscanf(input, "%d", &entry_selection);
    
    while (1) {
        printf("Entry No: %d\nPlease enter modified entry here:\n", entry_selection);
        scanf(" %[^\n]s", entries[entry_selection].content);
        while (1) {
            printf("Modified Entry: %s, are you sure you want to save?: ", entries[entry_selection].content);
            scanf("%s", &selection2);
            if (selection2 != 'Y' && selection2 != 'N') {
                printf("Incorrect choice entered, Please Try Again!\n");
                continue;
            } else {
                break;
            } 
        }
        if (selection2 == 'Y') {
            break;
        } else if (selection2 == 'N'){
            continue;
        }
    }
    
    printf("------------------------------\nModified entry successfully saved!\n------------------------------\n");
    
}

void viewEntries() {
    int i;
    char leave;

    printf("Number Of Entries in total: %d\n", count-1);
    for (i = 1; i < count; i++) {
        printf("Date: %s\nContent: %s\n", entries[i].date, entries[i].content);
    }
    printf("Enter anything to continue: ");
    scanf("%s", &leave);
}

void deleteEntry() {
    char none;
    char *line = NULL;
    size_t len = 0;
    int result;
    int entry_selection;
    char selection1;
    int length,i;
    char input[100] = "";
    int error;

    printf("Number Of Entries in total: %d\n", count-1);
    for (i = 1; i < count; i++) {
        printf("Date: %s\nContent: %s\n", entries[i].date, entries[i].content);
    }

    while (1) {
        while (1) {
            printf("Which entry would you like to delete: ");
            scanf("%s", input);
            length = strlen (input);
            for (i=0;i<length; i++) {
                if (!isdigit(input[i]))
                {
                    printf ("Entered input is not a number\n");
                    error = 1;
                    break;
                } else {
                    error = 0;
                    break;
                }
            }
            if (error == 0) {
                break;
            } else {
                continue;
            }
        }
        
        sscanf(input, "%d", &entry_selection);

        while (1) {
            printf("You have selected entry no: %d, are you sure? (Enter Y to confirm and N to enter another entry): ", entry_selection);
            scanf("%s", &selection1);
            if (selection1 != 'Y' && selection1 != 'N') {
                printf("Incorrect choice entered, Please Try Again!\n");
                continue;
            } else {
                break;
            } 
        }
        if (selection1 == 'Y') {
            break;
        } else if (selection1 == 'N'){
            continue;
        }
            
        }

    sscanf(input, "%d", &entry_selection);

    for (i = entry_selection; i < count; i++) {
        entries[i] = entries[i + 1];
    }
    count--;

    printf("------------------------------\nEntry successfully deleted!\n------------------------------\n");
}

int main() {
    int choice;
    FILE *inputfile;
    FILE *acc;
    FILE *saved;
    FILE *inputaccount;
    
    inputfile = fopen("user_number.dat","rw");
    inputaccount = fopen("account_saved.dat", "rw");
    fread(&count, sizeof(count), 1, inputfile);
    fread(&entries, sizeof(struct DiaryEntry), 500, inputaccount);
    
    while(1) {
        acc = fopen("user_number.dat", "w");
        fwrite(&count, sizeof(count), 1, acc);
        fclose(acc);
        saved = fopen("account_saved.dat", "w");
        fwrite(&entries, sizeof(struct DiaryEntry), 500, saved);
        fclose(saved);
        printf("Hello, welcome to the Diary Management System\n");
        printf("Please select a option below to start:\n");
        printf("1. Add Entry to Diary\n");
        printf("2. Edit Entries\n");
        printf("3. View Entries\n");
        printf("4. Delete Entires\n");
        printf("0. Exit\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case (1):
            addEntry();
            break;

        case (2):
            editEntry();
            break;

        case (3):
            viewEntries();
            break;

        case (4):
            deleteEntry();
            break;

        case (0):
            printf("Exiting Program, Have a nice day!");
            exit(1);
            
        
        default:
            printf("Invalid choice. Please enter a valid option.\n");
            break;
        }
    }
} 

