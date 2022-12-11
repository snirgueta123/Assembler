#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX1 30/*The maximum possible symbol length*/
#define MAX2 80 /*Maximum line length */
#define MAX3 3 
#define MEMORY 100
#define base 32
#define d1 31
#define d2 5
#define d3 2
#define d4 1
#define d5 0
#define d6 6
#define d7 4

struct Symbol {
    char symbol[MAX1]; 
    int address;
   char InsOrGui[MAX3];  /*instruction='in',guidance='gu',not is and no is='no'*/
   char isExternOrEntry; /*extern='1',entry='2',not entry and not extern='0'*/
 
    struct Symbol* next;
};

typedef  struct cell  {
    int address;
    char symbol[MAX1];
    struct cell* next;
}ItemCell;

typedef struct ListCell {
   ItemCell* head;
}ItemListCell;

void  printentries(int i,char *argv[],struct Symbol *stail);
void  printexternals(int i,char *argv[],struct Symbol *stail,ItemListCell* listCell);

