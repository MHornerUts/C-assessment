/*******************************************************************************
*Group Member names/ID number: Jake Gary (25347105), Matthew Horner (13524665),
 Chenran Hao (25348537), Solomon Howard (25472857) 
*******************************************************************************/

/*******************************************************************************
 * The list header files.
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "ass3.h"

/*******************************************************************************
 * Function prototypes.
 * In the header
*******************************************************************************/


/*******************************************************************************
 * Structs.
*******************************************************************************/



/*******************************************************************************
 * Main.
*******************************************************************************/

int main (void) {
    char dbFileName[] = "database.bin";
    char dbFileName2[] = "dictonary.bin";
    password_t passwordlist[5];
    setEmpty(passwordlist);
    int choice, * amount;
    amount = (int*)malloc(sizeof(int));
    *amount = 0;
    int KEY;

    srand(time(NULL));/*sets the seed for a random number based on the current time*/
    
    if (fileCheck(dbFileName, dbFileName2) == 1) {
        printf("Please enter your key\n");
        scanf(" %d", &KEY);   
        readPassword(passwordlist,dbFileName, dbFileName2, amount, KEY);
    } else {
        KEY = createKEY(1, 25);
        printf("Note, your new key is %d.\n", KEY);
    }

    do {
        printMenu();
        printf("Enter your choice>\n");
        scanf("%d", &choice);
        while (getchar() != '\n');  

        switch (choice) {
            case 1:
                addPassword(passwordlist, amount);
                break;
            case 2:
                deletePassword(passwordlist, amount);
                break;
            case 3:
                displayPasswords(passwordlist, amount);
                break;
            case 4:
                editPassword(passwordlist, amount);
                break;
            case 5:
                savePassword(passwordlist, dbFileName, dbFileName2, KEY);
                break;
            case 6:
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 5 && choice != 6);


    free(amount);
    return 0;
}


/*******************************************************************************
 * Below are a number of test functions that I, Matthew created to see how easy
 * the most basic encryption and compression algorithms would be to implement.
 * 
 *******************************************************************************/

/*******************************************************************************
 * Encryption.
 *******************************************************************************/

void test_encryption (char test[]) {
    int i;
    char a;
    for (i=0;i<strlen(test);i++) {
        a = test[i];
        a = a + 3;
        test[i] = a;
    }

    test[i] = '\0';

    printf("%s\n",test);
}

/*******************************************************************************
 * Decryption.
 *******************************************************************************/

void test_decryption (char test[]) {
    int i;
    char a;
    for (i=0;i<strlen(test);i++) {
        a = test[i];
        a = a - 3;
        test[i] = a;
    }

    test[i] = '\0';

    printf("%s\n",test);
}



/*******************************************************************************
 * Run-length encoding test.
 * Uses ` to denote numbers so that the alorithym can compress numbers. This
 * means that strings with lots of none repeating numbers will be ineffiecent.
 * So the compression will only be used if it reduces text size. 
 *******************************************************************************/

void test_compress (char test[]) {
    char store = test[0], coded[100], fix[11];
    int b, counter2 = 0,y,counter = 1;

    for(b = 0;b < strlen(test); b++) {

        if (test[b]==store && b>0) {

            counter++;

        } else if (b>0) {         
            
            if (counter>1) {
                sprintf(fix,"%d",counter);

                for(y=0;y< strlen(fix);y++) {
                    coded[counter2] = fix[y];
                    counter2++;
                }
            }
            
            coded[counter2] = store;
            counter2++;  

            if(store=='1' || store=='2' || store=='3' || store=='4' || store=='5' || store=='6' || store=='7' || store=='8' || store=='9') {
                coded[counter2] = '`';
                counter2++;      
            }

            counter= 1;
            store = test[b];
        }      
    }

     if (counter>1) {
        sprintf(fix,"%d",counter);

        for(y=0;y< strlen(fix);y++) {
            coded[counter2] = fix[y];
            counter2++;
        }
    }

    

    coded[counter2] = store;
    counter2++;

    if(store=='1' || store=='2' || store=='3' || store=='4' || store=='5' || store=='6' || store=='7' || store=='8' || store=='9') {
        coded[counter2] = '`';
        counter2++;      
    }

    coded[counter2]='\0';

    printf("%s becomes %s\n",test,coded);
}

/*******************************************************************************
 * Run-length decoding test.
 * Will break on numbers
*******************************************************************************/

void test_decompress (char test[]) {
    int i, y, counter=0, z;
    char decoded[100], lazy[11];
    for (i=0;i<strlen(test);i++) {
        if(test[i]=='1' || test[i]=='2' || test[i]=='3' || test[i]=='4' || test[i]=='5' || test[i]=='6' || test[i]=='7' || test[i]=='8' || test[i]=='9') {
            z = numfix(test, i);
            sprintf(lazy,"%d",z);
            if(z==0){
                decoded[counter] = test[i];
                counter++;
                i++;
            } else {
                i = i + strlen(lazy);
                for(y=0;y<z;y++){
                    decoded[counter] = test[i];
                    counter++;
                }
            }      
        } else {
            if (test[i]!='`'){
                decoded[counter] = test[i];
                counter++;
            }
            
        }
    }

    decoded[counter] = '\0';
    printf("%s becomes %s\n",test, decoded);
}

/*******************************************************************************
 * NumberFix
*******************************************************************************/

int numfix (char test[], int a) {
    int y, number = 0, counter=0;
    char num[11];
    
    for (y=a;y<strlen(test);y++) {
        if(test[y]=='1' || test[y]=='2' || test[y]=='3' || test[y]=='4' || test[y]=='5' || test[y]=='6' || test[y]=='7' || test[y]=='8' || test[y]=='9') {
            num[counter] = test[y];
            counter++;
        } else if (test[y]=='`') {
            num[counter-1] = '\0';
            break;
        } else {
            break;
        }
    }

    if (strlen(num)>0) {
        number = atoi(num);
    }

    return number; 
}


