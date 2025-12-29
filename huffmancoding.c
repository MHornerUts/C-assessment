/*******************************************************************************
 * The list header files.
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ass3.h"


/*******************************************************************************
 * Huffman coding functions
 * I acknowledge that I used an _ between words instead of capitalisation.
 * It's all way to tangled at this point for me to be stuffed to fix that.
 * I honestly dont remember why I started doing it this way in the first
 * place.
 * To be fair to me it is all consisant across this page.
*******************************************************************************/

/*******************************************************************************
 * Inserts a new element into the heap
 * This version is for when values want to be turned into a node thats then
 * put in the array.
 * Makes sure that each ptr contained within is set to null to avoid undefined
 * behaviour.
*******************************************************************************/

void heap_insert(bin_t bin, char value, int amount) {
    (bin.heap+(*bin.count))->frequency = amount;
    (bin.heap+(*bin.count))->character = value;
    (bin.heap+(*bin.count))->right = NULL;
    (bin.heap+(*bin.count))->left = NULL;
    (bin.heap+(*bin.count))->head = NULL;
    (*bin.count)++;
    heap_heapify_up(bin, (*bin.count)-1);
}

/*******************************************************************************
 * Inserts a node_t into the heap
 * This version is for when existing nodes want to be put in the array
*******************************************************************************/

void heap_insert_big(bin_t bin, node_t  node) {
    (bin.heap+(*bin.count))->frequency = node.frequency;
    (bin.heap+(*bin.count))->character = node.character;
    (bin.heap+(*bin.count))->left = node.left;
    (bin.heap+(*bin.count))->right = node.right;
    (bin.heap+(*bin.count))->head = NULL;
    (*bin.count)++;
    heap_heapify_up(bin, (*bin.count)-1);
}

/*******************************************************************************
 * Swaps two elements in the heap
*******************************************************************************/

void heap_swap(bin_t bin, int index1, int index2) {
    node_t temp = *(bin.heap + index1);
    *(bin.heap+index1) = *(bin.heap+index2);
    *(bin.heap+index2) = temp;
}

/*******************************************************************************
 * Sorts the heap from the top way down
 * smallest is whichever path down has a smaller frequency.
 * If smallest changes index (starting pos) and smallest are swapped
 * and then smallest is recursively put as the new index
*******************************************************************************/

void heap_heapify_down(bin_t  bin, int index) {
    int left = (2 * index)+ 1, right = (2 * index) + 2, smallest = index;

    if (left < *bin.count && (bin.heap+left)->frequency < (bin.heap+smallest)->frequency) {
        smallest = left;
    }

    if (right < *bin.count && (bin.heap+right)->frequency < (bin.heap+smallest)->frequency) {
        smallest = right;
    }

    if (index != smallest) {
        heap_swap(bin, index, smallest);
        heap_heapify_down(bin, smallest);
    }
}

/*******************************************************************************
 * Sorts the heap from the bottom
 * Since its a min heap it checks to see whether or not current index item
 * has a smaller frequency then its parent and then swaps itself with its parent
 * if it is, then recursivly puts the now location of the element in the same
 * function.
*******************************************************************************/

void heap_heapify_up(bin_t bin, int index) {
    if (index > 0 && (bin.heap+index)->frequency < (bin.heap+(int)(PARENT(index)))->frequency) {
        heap_swap(bin, index, (int)(PARENT(index)));
        heap_heapify_up(bin, (int)(PARENT(index)));
    }
}

/*******************************************************************************
 * Removes the head from the array and returns it 
*******************************************************************************/

node_t * heap_extract(bin_t bin) {

    node_t * node = (node_t*)malloc(sizeof(node_t));

    node->frequency = bin.heap->frequency;
    node->character = bin.heap->character;
    node->left = bin.heap->left;
    node->right = bin.heap->right;
    node->head = NULL;

    *bin.heap = *(bin.heap+(*bin.count-1));

    (*bin.count)--;

    heap_heapify_down(bin, 0);
    return node;
}

/*******************************************************************************
 * Prints the heap
*******************************************************************************/

void print_heap(bin_t bin) {
    int i;
    for(i = 0; i < *bin.count; i++) {
        printf("%c %d\n",(bin.heap+i)->character, (bin.heap+i)->frequency);
    }
}

/*******************************************************************************
 * Prints the diconary
*******************************************************************************/

void print_dic(dictonary_t dic) {
    int i;
    for (i=0;i<(*dic.size);i++) {
        printf("%c : %s\n",(dic.pairs+i)->character, (dic.pairs+i)->code);
    }
}

/*******************************************************************************
 * Puts the given string into the min heap
*******************************************************************************/

void put_in(bin_t bin, char * str) {
    int i, y, count = 0, addtions = 0;
    node_t temp [128];

    for(i = 0; i < strlen(str); i++) {
        for(y=0;y<count;y++) {
            if (str[i] == temp[y].character) {
                temp[y].frequency++;
                addtions++;
            }
        }

        if (addtions == 0) {
            temp[count].character = str[i];
            temp[count].frequency = 1;
            count++;
        }
        addtions = 0;
    }

    for (i=0;i < count; i++) {
        heap_insert(bin, temp[i].character, temp[i].frequency);
    }
}

/*******************************************************************************
 * Creates the huffman tree by extracting the back two nodes in the tree
 * and then putting them in a new node which is then placed back in the
 * min heap.
*******************************************************************************/


void huffcoding(bin_t bin) {
    node_t node, * ptr1, * ptr2;

    while ((*bin.count)>1) {

        ptr1 = heap_extract(bin);

        ptr2 = heap_extract(bin);   

        node.frequency = ptr1->frequency + ptr2->frequency;   
        node.character = '$';

        node.left = ptr1;

        node.right = ptr2;

        heap_insert_big(bin, node);  
    }

}

/*******************************************************************************
 * Runs through the tree and sets the heads of the leaves
*******************************************************************************/

void traversal(node_t * node, node_t * head, dictonary_t dic) {

    /*Populates the head ptr in the struct for nav purposes*/
    if (head) {
        node->head = head;
    }

    if (node->left) {     
        traversal(node->left, node, dic);
    }

    if (node->right) {
        
        traversal(node->right, node, dic);
    }
    
    /*Creates a new code each time a char is reached*/
    if (node->character != '$') { 
        *(dic.pairs+(*dic.count)) = getcode(node); 
        (*dic.count)++;
    }
    
}

/*******************************************************************************
 * Returns the code for a pair
*******************************************************************************/

pair_t getcode(node_t * node) {
    pair_t pair;
    pair.character = node->character;
    node_t *previous, *current = node;
    char str[30], rev[30];
    int i = 0, y = 0;
    
    /*Traverses through tree and adds 0 for left or 1 for right*/
    while(current->head) { 
        previous = current;
        current = current->head;
        if (current->left != NULL) {
            if (current->left == previous) {
                str[i] = '0';
            } else {
                str[i] = '1';
            }
            
        } else {
          str[i] = '1';
        }
        i++;
    }
    
    str[i] = '\0';

    /*Reverses code because its backwards*/
    for(i = strlen(str) - 1 ; i >= 0;i--) {  
        rev[y] = str[i];
        y++;
    }
    rev[y] = '\0';
    
    strcpy(pair.code, rev);
    
    return pair;
}

/*******************************************************************************
 * Translates the str into coded form
*******************************************************************************/

char * print_coded(char * str, dictonary_t dic) {
    int i, y, count = 0;

    /*Calculates how big str2 needs to be*/
    for (i=0;i<strlen(str);i++) { 
        for(y=0;y<*dic.size;y++) {
            if((dic.pairs+y)->character == *(str+i)) {
                count = count + (int)(strlen((dic.pairs+y)->code));
            }
        }
    }

    char * str2 = (char*)malloc(sizeof(char)*(count+1));
    strcpy(str2, "");
    
    /*Goes through the str and finds the correct code to add to the new str*/
    for (i=0;i<strlen(str);i++) {
        for(y=0;y<*dic.size;y++) {
            if((dic.pairs+y)->character == *(str+i)) {
                strcat(str2, (dic.pairs+y)->code);
            }
        }
    }
    return str2;
}

/*******************************************************************************
 * Takes the codes and writes them to unsigned chars.
 * This is techincally where the compression takes place
*******************************************************************************/

unsigned char * coding(char * str, int * ptr) {
    int i, y = 1, check = 0;
    int size = (int)(ceil((double)(strlen(str)/8)));
    unsigned char * compressed;
    compressed = (unsigned char*)malloc( sizeof(unsigned char) * (size));
    (*ptr)++;
    
    for(i=0; i < size; i++) { /*Sets each unsigned chars to 0  to fix a bug*/
        *(compressed+i) = 0;
    }

    
   
    for(i = 0; i < strlen(str); i++) {
        if (check > 7) { /* Increments in sets of 8 for byte pos*/
            check = 0;
            y++;
            (*ptr)++;
        }

        /*Uses OR and bit shift to change bits*/
        /*Equal sign saves the result*/
        if (str[i] == '0') {
            *(compressed+(y-1)) |= (0 << check); 

        }
        else {
            *(compressed+(y-1)) |= (1 << check);   
        }
        
        check++;
    }

    
    return compressed;
}

/*******************************************************************************
 * Takes the unsigned chars and converts the bits back into a string
*******************************************************************************/

char * decoding(unsigned char * str, int * ptr) {
    int i,y,x = 0;
    char * str2 = (char*)malloc(sizeof(char)*(((*ptr)*8)+1));
    strcpy(str2, "");
    
    /*Shifts y amount to the right and uses AND */
    /* Compares hex value and bit */
    /*bit 1 & 0x1 will return a 1 otherwise the bit is 0*/

    for (i = 0 ; i < (*ptr); i++) {
        for(y=0; y<8;y++) { 
            if ((((*(str+x)) >> y) & 0x1) == 1) { 
                strcat(str2,"1"); 
                
            } else {
                strcat(str2,"0");
                
            }
            
        }
        x++;
    }
    
    
    return str2;
}

/*******************************************************************************
 * Uses the dictonary to turn the 1s and 0s back into readable text, completing
 * the decompression process.
*******************************************************************************/

char * re_str(char * str, dictonary_t dic) {
    int i, y,z = 0, itr = 0;
    char str2[1000] = "";
    char * f = (char*)malloc(sizeof(char)*((*dic.size_str)+1));
    *f = '\0';
    strcpy(f, "");

    for (i=0 ; i<strlen(str) ;i++) {
        str2[z] = *(str+i);
        z++;
        str2[z] = '\0';  
        for (y=0; y < (*dic.size);y++) {
            if (itr < (*dic.size_str)) {
                if(strcmp((dic.pairs+y)->code, str2) == 0) {
                    *(f+itr) = (dic.pairs+y)->character;
                    itr = itr + 1;
                    strcpy(str2,"");
                    z = 0;
                }
            }  
        }
        
    }

    *(f+itr) = '\0'; 
    return f;
}

/*******************************************************************************
 * This is the main huffman code. It basically just runs all the functions.
*******************************************************************************/

unsigned char * build_huffman(char * str, dictonary_t dic) {
    

    bin_t bin; /*A struct to store the heap array*/
    
    bin.count = (int*)malloc(sizeof(int));
    *bin.count = 0;

    bin.size = (int*)malloc(sizeof(int));
    *bin.size = count_unique(str);

    bin.heap = (node_t*)malloc(sizeof(node_t)*(*bin.size));

    put_in(bin, str); /*Puts the given string into the heap*/

    huffcoding(bin); /*Removes all but the head of the heap and creates the tree*/
    
    traversal(bin.heap, NULL, dic); /*Populates the dictionary*/


    char * code = print_coded(str, dic); /*Converts the str to a coded string*/
    unsigned char * comp = coding(code, dic.bytes); /*Compresses the string*/
   
    
    free(bin.count);
    free(bin.size); 
    free(bin.heap);
    
    
    return comp;
}

/*******************************************************************************
 * Finds the total number of unique characters. This tells how big the Structs
 * need to be. Letting me avoid using realloc and the headaches it was creating.
 * it just loops through one str and adds a element to the other every time its
 * first seen.
*******************************************************************************/

int count_unique(char * str) {
    int i, y, count = 0, addtions = 0;
    char temp [128];

    for(i = 0; i < strlen(str); i++) {
        for(y=0;y<count;y++) {
            if (str[i] == temp[y]) {
                addtions++;
            }
        }

        if (addtions == 0) {
            temp[count] = str[i];
            count++;
        }
        addtions = 0;
    }
    temp[count] = '\0';
    return (int)(strlen(temp));
}
