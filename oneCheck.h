#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include"print.h"
#include"macro.h"

#define SIZE3 5 /*Maximum possible addressing methods including the character /0 at the end of a string*/
#define SIZE4 29/*Number of reserved words of the language*/
#define LENGTHMAX 30/*The maximum label length*/
#define LENTGH3 256 /*Maximum memory size*/

short TableInstructional[LENTGH3];
short TableData[LENTGH3];
typedef  struct Node  {
    int actionNumber;
    char OpradSource[SIZE3];
    char Opradtarget[SIZE3];
    
    struct Node* next;
}ItemNode;

typedef struct List {
   ItemNode* head;
}ItemList;

ItemList* createList();
void freeList(ItemList*  list);
void addToList(ItemList* list, int actionNumber1, char OpradSource1[],char Opradtarget1[]);
int IsLegalNumber(char sname[]);
int EntryOrExtern(char line[],int index);
int legalSymbolExtern(char line[], int index, struct Symbol *stail,char nameSymbol[],int flagError,int sumLine);
int IsNotExistSymbol(struct Symbol *stail,char nameSymbol[]);
int legalName(char sname[]);
int Operands(char line[]);
int IsExsistSymbol(struct Symbol *temp,struct Symbol *stail,int sumLine,char nameSymbol[]);
int isSymbol(char line[],char nameSymbol[],int index);
int GuidanceSentence(char line[],int index);
int isLegalAction(char line[],int index);
void UpdateValues(struct Symbol *stail,int IC);
int HowManydataRow(char line[],int index,int sumLine,int dataType,int DC);
int AddressingMethod(char sname[]);
int isExsistExtern(struct Symbol *stail);
int IsLegalSourceAddressingMethod(int typeAddresssource ,int typeAction,ItemList* list);
int IsLegaltargetAddressingMethod(int typeAddresstarget ,int typeAction,ItemList* list);
int HowManyInstructionsRow(char line[],int sumLine,int IC,int index,int typeAction,ItemList* list) ;
int oneCheck(int i, char *argv[],struct Symbol *shead);





