/*******************************************************************************
*Group Member names/ID number: Jake Gary (25347105), Matthew Horner (13524665),
 Chenran Hao (25348537), Solomon Howard (25472857) 
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/*******************************************************************************
 * Function prototypes for huffcoding. Created by Matthew.
*******************************************************************************/


typedef struct node node_t;

struct node
{
    int frequency;
    char character;
    node_t *right, *left, *head;
};

typedef struct bin bin_t;

struct bin 
{
    int * count, * size;
    node_t *heap;
};

typedef struct pair pair_t;

struct pair
{
    char character;
    char code [10];
} ;

typedef struct dictonary dictonary_t;

struct dictonary
{
    int * size, * size_str, *count, *bytes;
    pair_t * pairs;
};



void heap_insert(bin_t bin, char value, int amount);
void heap_insert_big(bin_t bin, node_t  node);
node_t * heap_extract(bin_t bin);
void heap_swap(bin_t bin, int index1, int index2);
void heap_heapify_down(bin_t  bin, int index);
void heap_heapify_up(bin_t bin, int index);
void print_heap(bin_t  bin);
void put_in(bin_t bin, char * str);
void huffcoding(bin_t bin);
void traversal(node_t * node, node_t * head, dictonary_t dic);
pair_t getcode(node_t * node);
char * print_coded(char str[], dictonary_t dic);
unsigned char * coding(char * str, int * ptr);
char * decoding(unsigned char * str, int * ptr);
char * re_str(char * str, dictonary_t dic);
unsigned char * build_huffman(char * str, dictonary_t dic);
int count_unique(char * str);
void print_dic(dictonary_t dic);

#define PARENT(X) floor((X-1)/2)



/*******************************************************************************
 * Function prototypes for main.
 * Includes test stuff that probably won't be used unless something goes wrong.
 * Done by Matthew and Chenrman.
*******************************************************************************/

void printMenu(void);
void get_passwords(void);
void save_passwors(void);
void delete_passwords(void);



void testcompress(char test[]);
void testdecompress(char test[]);
void testdecryption(char test[]);
void testencryption(char test[]);
char shiftfix(char a);
int numfix(char test[], int i);

/*******************************************************************************
 * Function prototypes for huffsman encoding.
 * Not 100 percent sure whats needed. 
 * Doesn't currently exist.
 * Probably will be created by matthew.
 * Pretty sure not used.
*******************************************************************************/

void encode(void);
void decode(void);

/*******************************************************************************
* Functions prototypes for encryption. Done by Jake. 
*******************************************************************************/

void encrypt(char *pwrd, int KEY);
void decrypt(char *pwrd, int KEY);
char tolowerALT(char c);
char toupperALT(char c);
int createKEY(int min, int max);

/*******************************************************************************
* Functions prototypes for navigation and saving. Done by Chenranm, Matthew 
* and Solomon. 
*******************************************************************************/

#define MAX_PASSWORD_SIZE 20
#define MAX_ACCOUNT_SIZE 30
#define MAX_EMAIL_SIZE 30
#define MAX_PASSWORD_LIBARY_SIZE 5

typedef struct password password_t;
struct password{
    char email[MAX_EMAIL_SIZE + 1];
    char password[MAX_PASSWORD_SIZE + 1];
    char account[MAX_ACCOUNT_SIZE + 1];
};


void printMenu(void);
void savePassword(password_t passwordlist[], char dbFileName[], char dbFileName2[], int KEY);
void readPassword(password_t passwordlist[], char dbFileName[], char dbFileName2[], int * amount, int KEY);
int fileCheck(char dbFileName1[], char dbFileName2[]);
void displayPassword(password_t password);
void displayPasswords(password_t passwordlist[], int * amount);
void addPassword(password_t passwordlist[], int * amount);
void deletePassword(password_t passwordlist[], int * amount);
void setEmpty(password_t passwordlist[]);
void editPassword(password_t passwordlist[], int * amount);
void passwordSwap(password_t passwordlist[], int index1, int index2);
int formatValidation(char * str);
int emailFormatValidation(char * str);

