#Makefile
#To run simply type "make" main file ass3.out

CC = gcc
CFLAGS = -Wall -Werror -ansi -lm
all: ass3

ass3: ass3.c huffmancoding.c savepassword.c pagenav.c
	$(CC) $(CFLAGS) -o ass3.out ass3.c savepassword.c huffmancoding.c pagenav.c encrypt.c

debug: ass3.c huffmancoding.c savepassword.c pagenav.c
	$(CC) $(CFLAGS) -o test.out ass3.c savepassword.c huffmancoding.c pagenav.c -g 

Heap: huffmancoding.c
	$(CC) $(CFLAGS) -o huff.out huffmancoding.c

save: savepassword.c
	$(CC) $(CFLAGS) -o save.out savepassword.c

nav: pagenav.c
	$(CC) $(CFLAGS) -o nav.out pagenav.c

encrypt: encrypt.c
	$(CC) $(CFLAGS) -o encrypt.out encrypt.c
