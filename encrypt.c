/* Jake Gary ||||| 25347105

gcc -Wall -Werror -ansi -o encrypt.out encrypt.c -lm
*/

#include<stdio.h>   /*	fgets()  */
#include<stdlib.h>  /*	printf()  */
#include<time.h>    /* srand()  */
#include"ass3.h"

void encrypt(char *pwrd, int KEY){ /*Users a variable caesar cipher to encrypt a string*/
    while(*pwrd){
        if (*pwrd >='A' && *pwrd <='Z'){ /*checks that input is a capital letter*/
            *pwrd = ((*pwrd -'A' +KEY)%26) +'A';/*uses a caesar cipher to encrypt input*/
            *pwrd = tolowerALT(*pwrd); /*decapitalises uppercase letters*/
        }
        else if(*pwrd >='a' && *pwrd <='z'){ /*checks that input is a lowercase letter*/
            *pwrd = ((*pwrd -'a' +KEY)%26) +'a';/*uses a caesar cipher to encrypt input*/
            *pwrd = toupperALT(*pwrd); /*capitalises lowercase letters*/
        }
        pwrd++;/*updates password*/
    }
}

void decrypt(char *pwrd, int KEY){ /*Users a variable caesar cipher to decrypt a string*/
    while(*pwrd){
            if (*pwrd >= 'A' && *pwrd <= 'Z'){ /*checks that input is a capital letter*/
                *pwrd = ((*pwrd - 'A' - KEY + 26)%26) + 'A';/*uses a caesar cipher to decrypt input*/
                *pwrd = tolowerALT(*pwrd);/*decapitalises uppercase letters*/
            }
            else if (*pwrd >= 'a' && *pwrd <= 'z'){/*checks that input is a lowercase letter*/
                *pwrd = ((*pwrd - 'a' - KEY + 26)%26) + 'a';/*uses a caesar cipher to decrypt input*/
                *pwrd = toupperALT(*pwrd);/*capitalises lowercase letters*/
            }
            pwrd++;/*updates password*/
        }
    }


char toupperALT(char c) { /*function to capitalise letters in absence of ctype.h*/
    if ( c < 123 && c > 96) {
        c = c - 32;/*shifts across ASCI characters (lowercase to uppercase)*/
    }

    return c; /*returns new character value*/
}

char tolowerALT(char c) { /*function to decapitalise letters in absence of ctype.h*/
    if (c < 91 && c > 64) {
        c = c + 32;/*shifts across ASCI characters ( uppercase to lowercase)*/
    }

    return c; /*returns new character value*/
}


int createKEY(int min, int max){ /*Function to create a key between set parameters*/
 
    return rand() % (max - min +1) + min; /*returns random key value between 1 and 25*/
}



/*
int main(){

    char pwrd[128]; max password length
    int KEY;
    int minKEY = 1;
    int maxKEY = 25;

    srand(time(NULL));  takes random integer value using time as a seed (ensures randomness)

    printf("Enter a password to store; \n");    asks for user input
    fgets(pwrd, sizeof(pwrd), stdin);   stores user input

    KEY=createKEY(minKEY, maxKEY);  creates a KEY value using createKEY function
 
    encrypt(pwrd, KEY);     encrypt function

    printf("The encrypted password is; \n%s", pwrd);    prints encrypted password

    decrypt(pwrd, KEY);     decryption function

    printf("The decrypted password is: \n%s", pwrd);    prints decrypted password (same as original input)


return 0;
}
*/
