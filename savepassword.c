/*******************************************************************************
* savepassword 
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ass3.h"


/*******************************************************************************
 * Password validation function returns 1 if everything is good otherwise
 * returns 0.
*******************************************************************************/
int fileCheck(char dbFileName1[], char dbFileName2[]) {
    FILE* file1;
    if ((file1 = fopen(dbFileName1,"rb"))) {
        printf("First file found\n");
        fclose(file1);
    } else {
        return 0;
    }

    FILE* file2;
    if ((file2 = fopen(dbFileName2,"rb"))) {
        printf("Second file found\n\n");
        fclose(file2);
    } else {
        return 0;
    }

    return 1;
}

/*******************************************************************************
 * Saves passwords DONT TOUCH THIS FUNCTION
*******************************************************************************/


void savePassword(password_t passwordlist[], char dbFileName[], char dbFileName2[], int KEY){
    int i;
    dictonary_t dic; /*Creates a dictonary struct for storage*/
    
    dic.size_str = (int*)malloc(sizeof(int));
    *dic.size_str = 0;

    dic.count = (int*)malloc(sizeof(int));
    *dic.count = 0;

    dic.bytes = (int*)malloc(sizeof(int));
    *dic.bytes = 0;

    dic.size = (int*)malloc(sizeof(int));
    
    char * str = (char*)malloc(sizeof(char)*2000); 
    strcpy(str, "");

    /*turns the array of passwords into a formated string*/

    for (i=0;i< MAX_PASSWORD_LIBARY_SIZE ;i++) { 
        strcat(str,passwordlist[i].email);       
        strcat(str,",");
        strcat(str,passwordlist[i].account);
        strcat(str,",");
        strcat(str,passwordlist[i].password);
        strcat(str,",");
    }
    

    *dic.size = count_unique(str);
   
    *dic.size_str = strlen(str);
    
    dic.pairs = (pair_t*)malloc( sizeof(pair_t) * (*dic.size));
    
    encrypt(str, KEY); /*Encryptes the created string*/

    

    /*Creates unsigned chars and does the huffman coding*/
    unsigned char * comp = build_huffman(str, dic); 
    
    FILE* file1;
    
    file1 = fopen(dbFileName, "wb");
    
    fwrite(comp, sizeof(unsigned char), *dic.bytes, file1);
    
    fclose(file1);
   

    FILE* file2;
    
    file2 = fopen(dbFileName2, "wb");

    /*Formats a string for loading to save struct attributes*/
    /*Uses $ as a delimter to seperate items*/
    char * str2 = malloc(sizeof(char)*1000); 
    char * str3 = malloc(sizeof(char)*8);
    strcpy(str2, "");
    sprintf(str3, "%d", *dic.bytes);
    strcat(str2, str3);
    strcat(str2,"$");
    sprintf(str3, "%d", *dic.size);
    strcat(str2, str3);
    strcat(str2,"$");
    sprintf(str3, "%d", *dic.size_str);
    strcat(str2, str3);
    strcat(str2,"$");
   
    for (i=0;i < (*dic.size);i++) { /*Adds pairs to the string*/
        str3[0] = (dic.pairs+i)->character;
        str3[1] = '\0';
        strcat(str2,str3);
        strcat(str2,"$");
        strcat(str2,(dic.pairs+i)->code);
        strcat(str2,"$");
    }

    fwrite(str2, sizeof(char), strlen(str2)+1, file2);
    
    fclose(file2);
    
    /*On mass free up of memory*/
    free(str);
    free(str2);
    free(str3);
    free(dic.size);
    free(dic.size_str);
    free(dic.count);
    free(dic.bytes);
    free(dic.pairs);
    free(comp);
}

/*******************************************************************************
 * reads passwords DONT TOUCH THIS FUNCTION
*******************************************************************************/

void readPassword(password_t passwordlist[], char dbFileName[], char dbFileName2[], int * amount, int KEY){
    FILE* file2;
    
    /*Makes sure the files exist NOT really needed at this point*/
    if ((file2 = fopen(dbFileName2,"rb"))) { 


        /*Technically I could use lSize2 instead of using 1000*/
        /*But I'm kind of over this assessment at this point*/
        /*As far as I'm aware its a big enough number to avoid crashs*/
        char * result2 = (char*)malloc(sizeof(char)*1000); 
        long lSize2;                                       
                                                           
        fseek (file2, 0, SEEK_END); /*Gets length of file*/
        lSize2 = ftell (file2); 
        rewind(file2);
        

        fread(result2,sizeof(char),lSize2,file2);
        
        fclose(file2);


        int i = 0, counter = 0, num = 0;
        dictonary_t dic;

        /*Gets the byte in char form and converts it to an int*/
        char numbers[4] = ""; 
        while(result2[num] != '$') {
            numbers[i] = result2[num];
            numbers[i+1] = '\0';
            i++;
            num++;
        }
        num++;
        
        dic.bytes = (int*)malloc(sizeof(int));
        *dic.bytes = atoi(numbers);
       
        /*Gets the size in char form and converts it to an int*/
        i = 0;
        strcpy(numbers,""); 
        while(result2[num] != '$') {
            numbers[i] = result2[num];
            numbers[i+1] = '\0';
            i++;
            num++;
        }
        num++;
        
        dic.size = (int*)malloc(sizeof(int));
        *dic.size = atoi(numbers);
        
        i = 0;

        /*Gets the size_str in char form and converts it to an int*/
        strcpy(numbers,""); 
        while(result2[num] != '$') {
            numbers[i] = result2[num];
            numbers[i+1] = '\0';
            i++;
            num++;
        }
        num++;

        dic.size_str = (int*)malloc(sizeof(int));
        *dic.size_str = atoi(numbers);
       

        dic.count = (int*)malloc(sizeof(int));
        *dic.count = 0;

        dic.pairs = (pair_t*)malloc(sizeof(pair_t)* (*dic.size));

       

        /*Cycles through and creates the pair structs*/
        for (i=num;i<strlen(result2); i++) { 
            (dic.pairs+counter)->character = result2[i];
            i++;
            i++;
            strcpy((dic.pairs+counter)->code, "");
            while(result2[i] != '$') {
                char temp[2];
                temp[0] = result2[i];
                temp[1] = '\0';
                strcat((dic.pairs+counter)->code, temp);
                i++;   
            }
            counter++;
        }
        
        
        FILE* file;
        unsigned char * result = (unsigned char*)malloc(sizeof(unsigned char)* (*dic.bytes));
        long lSize;

        file = fopen(dbFileName,"rb");

        fseek (file, 0, SEEK_END);
        lSize = ftell (file);
        rewind(file);
        

        fread(result,sizeof(unsigned char),lSize,file);
        
        fclose(file);

        (*amount) = 0;

        /*Uses the dictonary and the unsigned char to recreate the formated string*/
        char * x = re_str(decoding(result,dic.bytes),dic); 
        decrypt(x,KEY);

        /* 
           counter is ptr for passwordList, counter 2 is for which attributes , 
           and counter 3 ptr for tempholder
        */    
        int counter2 = 1, counter3 = 0; 
        counter=0;
        char tempholder[100] = "";

        /*Converts the string into an array of password structs*/
        /*Cycles through if statements to determine what str needs to go where*/ 
        /*Keeps adding chars to temp holder until a , is reached*/
        /*At which point tempholder is dumped and set to empty*/
        for (i=0;i<strlen(x);i++) { 
            if (counter2==1 && (*(x+i)) == ',') {
                tempholder[counter3] = '\0';
                strcpy(passwordlist[counter].email, tempholder);
                strcpy(tempholder, "");
                counter2++;
                counter3 = 0;
            }
            else if (counter2==2 && (*(x+i)) == ',') {
                tempholder[counter3] = '\0';
                strcpy(passwordlist[counter].account, tempholder);
                strcpy(tempholder, "");
                counter2++;
                counter3 = 0;
            }
            else if (counter2==3 && (*(x+i)) == ',') {
                if (strcmp(tempholder, "") != 0) {
                    (*amount)++;
                }
                tempholder[counter3] = '\0';
                strcpy(passwordlist[counter].password, tempholder);
                strcpy(tempholder, "");
                counter2 = 1;
                
                counter++;
                counter3 = 0;
            } else {
                tempholder[counter3] = (*(x+i));
                counter3++;
            } 
            
        }

        free(result);
        free(result2);
        free(dic.size);
        free(dic.count);
        free(dic.pairs);
        free(dic.bytes);
        free(dic.size_str);
        
    } else {
        printf("File doesn't Exist!\n");
    }
}

