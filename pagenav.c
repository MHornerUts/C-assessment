#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ass3.h"
/*******************************************************************************
 * Prints the the menu
*******************************************************************************/

void printMenu(void){
    printf("\nPassword Manager\n"
        "1. Add Password\n"
        "2. Delete password\n"
        "3. Display passwords\n"
        "4. Edit a password\n"
        "5. Save and Exit\n"
        "6. Exit without Saving\n");
}

/*******************************************************************************
 * Displays a single password
*******************************************************************************/
void displayPassword(password_t password) {
    printf("%s %s %s\n", password.email, password.account, password.password);
}
/************************************************a*******************************
 * Edits a password
*******************************************************************************/

void editPassword(password_t passwordlist[], int * amount) {
    int i, choice;
    char temp[255]; 

    if (*amount > 0) {
        printf("Select a password!\n");

        for (i = 0; i < MAX_PASSWORD_LIBARY_SIZE;i++) {
            if (i < (*amount)) {
                printf("%d ",(i+1));

                displayPassword(passwordlist[i]);
            }			
        }

        fgets(temp, sizeof(temp), stdin);
        sscanf(temp, " %d", &choice);

        printf("Please enter new values\n");
        
        if (choice > 0 && choice <= (*amount)) {

            printf("Current Email: %s\n", passwordlist[choice-1].email);
            printf("New Email> ");

            fgets(temp, sizeof(temp), stdin);

            while(1) {
                if (strcmp(temp, "\n") != 0 && strlen(temp) <= MAX_EMAIL_SIZE && emailFormatValidation(temp) == 1) {
                    sscanf(temp, " %s", passwordlist[choice-1].email);
                    break; 
                } else {
                    printf("Email Invalid. Requires @ symbol\n");
                    printf("New Email> ");
                    fgets(temp, sizeof(temp), stdin);     
                }
            }

            printf("Current Account: %s\n", passwordlist[choice-1].account);
            printf("New Account> ");
            fgets(temp, sizeof(temp), stdin);  

            while(1) {
                if (strcmp(temp, "\n") != 0 && strlen(temp) <= MAX_ACCOUNT_SIZE && formatValidation(temp) == 1) {
                    sscanf(temp, " %s", passwordlist[choice-1].account);
                    break;    
                } else {
                    printf("Account Invalid\n");
                    printf("New Account> ");
                    fgets(temp, sizeof(temp), stdin);  
                }
            }

            printf("Current Password: %s\n", passwordlist[choice-1].password);
            printf("New Password> ");
            fgets(temp, sizeof(temp), stdin);

            while(1) {
                if (strcmp(temp, "\n") != 0 && strlen(temp) <= MAX_PASSWORD_SIZE && formatValidation(temp) == 1) {
                    sscanf(temp, " %s", passwordlist[choice-1].password);
                    break;
                } else {
                    printf("Password Invalid\n");
                    printf("New Password> ");
                    fgets(temp, sizeof(temp), stdin);
                }
            }
            
            
        } else {
            printf("Doesn't exist.\n");
        }
    } else {
        printf("No passwords!\n\n");
    }
}

/*******************************************************************************
 * Displays the passwords
*******************************************************************************/
void displayPasswords(password_t passwordlist[], int *amount) {
    int i;
    int maxEmail = 5;  /*Start with "Email" length*/
    int maxAccount = 6; /*Start with "Account" length*/
    int maxPassword = 7; /*Start with "Password" length*/

    /*Find the maximum length of each field*/
    for (i = 0; i < *amount; i++) {
        if (strlen(passwordlist[i].email) > maxEmail) {
            maxEmail = strlen(passwordlist[i].email);
        }
        if (strlen(passwordlist[i].account) > maxAccount) {
            maxAccount = strlen(passwordlist[i].account);
        }
        if (strlen(passwordlist[i].password) > maxPassword) {
            maxPassword = strlen(passwordlist[i].password);
        }
    }

    /*Print the headers with the right padding*/
    printf("%-*s %-*s %-*s\n", maxEmail, "Email", maxAccount, "Account", maxPassword, "Password");

    /* Print the underline for each column*/
    for (i = 0; i < maxEmail; i++) printf("-");
    printf(" ");
    for (i = 0; i < maxAccount; i++) printf("-");
    printf(" ");
    for (i = 0; i < maxPassword; i++) printf("-");
    printf("\n");

    /*Print the data rows*/
    for (i = 0; i < *amount; i++) {
        printf("%-*s %-*s %-*s\n", maxEmail, passwordlist[i].email, maxAccount, passwordlist[i].account, maxPassword, passwordlist[i].password);
    }

    if (*amount == 0) {
        printf("No Passwords!\n");
    }
}

/*******************************************************************************
 * Adds a password to the passwordlist array

 #define MAX_PASSWORD_SIZE 20
#define MAX_ACCOUNT_SIZE 100 
#define MAX_EMAIL_SIZE 100
*******************************************************************************/
void addPassword(password_t passwordlist[], int * amount) {
    printf("Note, you cannot use , or $ symbols.\n");
    char temp[100];  /* Increase to 21 to accommodate for the null terminator */
    if ((*amount) < MAX_PASSWORD_LIBARY_SIZE) {
        while(1){
            printf("Email> ");
            fgets(temp, sizeof(temp), stdin);
            temp[strcspn(temp, "\n")] = 0;  
   
            if (strcmp(temp, "") == 0 || strlen(temp) > MAX_EMAIL_SIZE || emailFormatValidation(temp) == 0){
                printf("Email invalid, please enter less than 30 characters or requires @ symbol.\n");
                continue;
            }

            sscanf(temp, "%s", passwordlist[*amount].email );
            break;
    
        }
     while (1) {
        printf("Account> ");
        fgets(temp, sizeof(temp), stdin);
        temp[strcspn(temp, "\n")] = 0; 

        if (strcmp(temp, "") == 0 || strlen(temp) > MAX_ACCOUNT_SIZE || formatValidation(temp) == 0) {
                printf("Account invalid. Please enter no more than 30 characters.\n");
                continue;
        }
          sscanf(temp, "%s", passwordlist[*amount].account);
          break;
     }


        while (1) {
            printf("Password (not more than 20 characters)> ");
            fgets(temp, sizeof(temp), stdin);
            temp[strcspn(temp, "\n")] = 0;  /*Remove newline character if present*/

            if (strcmp(temp, "") == 0 || strlen(temp) > MAX_PASSWORD_SIZE || formatValidation(temp) == 0) {
                printf("Password invalid. Please enter no more than 20 characters.\n");
                continue;  /* Continue the loop if the password is too long*/
            }
            /*If the password is within the length limit, store it and break the loop*/
            sscanf(temp, "%s", passwordlist[*amount].password);
            break;
        }
        (*amount)++;
    } else {
        printf("Password list is full\n");
    }
}
/*******************************************************************************
 * Deletes a password from the password list array
*******************************************************************************/

void deletePassword(password_t passwordlist[], int * amount) {
    int i, choice;
    char temp[255]; 

    if (*amount > 0) {
        printf("Select a password to delete!\n");

        for (i = 0; i < MAX_PASSWORD_LIBARY_SIZE;i++) {
            if (i < (*amount)) {
                printf("%d. ",(i+1));

                displayPassword(passwordlist[i]);
            }			
        }

        fgets(temp, sizeof(temp), stdin);
        sscanf(temp, " %d", &choice);

        if (choice > 0 && choice <= (*amount)) {

            while(choice < (*amount)) { /*Moves password to be deleted to the top of the array*/
                passwordSwap(passwordlist, choice-1, choice);
                choice++;
            }

            (*amount)--; /*Deletes the password on the top of the array*/
            strcpy(passwordlist[(*amount)].account,"");
            strcpy(passwordlist[(*amount)].email,"");
            strcpy(passwordlist[(*amount)].password,"");
            
            
        } else {
            printf("Doesn't exist.\n");
        }
    } else {
        printf("No passwords!\n\n");
    }
}

/*******************************************************************************
 * Swaps the positions of two passwords in the passwordList
*******************************************************************************/

void passwordSwap(password_t passwordlist[], int index1, int index2) {
    password_t temp;

    strcpy(temp.password, passwordlist[index1].password);
    strcpy(temp.account, passwordlist[index1].account);
    strcpy(temp.email, passwordlist[index1].email);

    strcpy(passwordlist[index1].password, passwordlist[index2].password);
    strcpy(passwordlist[index1].account, passwordlist[index2].account);
    strcpy(passwordlist[index1].email, passwordlist[index2].email);

    strcpy(passwordlist[index2].password, temp.password);
    strcpy(passwordlist[index2].account, temp.account);
    strcpy(passwordlist[index2].email, temp.email);

}

/*******************************************************************************
 * Sets all the fields for functionality reasons.
*******************************************************************************/

void setEmpty(password_t passwordlist[]) {
    int i;
    for (i=0;i<MAX_PASSWORD_LIBARY_SIZE;i++) {
        strcpy(passwordlist[i].password,"");
		strcpy(passwordlist[i].email, "");
		strcpy(passwordlist[i].account, "");    
    }
}

/*******************************************************************************
 * Test formatting functions. Returns 1 for good and 0 for bad
*******************************************************************************/

int formatValidation(char * str) {
    int i;

    for (i = 0; i < strlen(str)+1; i++) {
        if (str[i] == '$' || str[i] == ',') {
            return 0;
        }
    }

    return 1;
}

/*email is different from the rest because it ensures that @ symbol is found once
*/
int emailFormatValidation(char * str) {
    int i, counter = 0;

    for (i = 0; i < strlen(str)+1; i++) {
        if (str[i] == '$' || str[i] == ',') {
            return 0;
        }

        if (str[i] == '@') {
            counter++; 
        }
    }

    if (counter < 1 || counter > 1) {
        return 0;
    }

    return 1;
}
