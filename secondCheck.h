#include "oneCheck.h"

ItemListCell* createListCell();
void addToListCell(ItemListCell* listCell,  char symbol1[],int address1);
void arrayReset(short TableInstructional[],short TableData[]);
int updatingEntry(struct Symbol *stail,char nameSymbol[]);
int exsistEntry(struct Symbol *stail);
int insertOperand(char line[],int index,int IC,short TableInstructional[],struct Symbol *stail,ItemListCell* listCell);
int secondCheck(int i, char *argv[],struct Symbol *stail,int DC,ItemListCell* listCell);
void  UpdateSymbolAsEntry(struct Symbol *stail,char nameSymbol[]);
void printObject(int i, char *argv[],int DC,int IC);
char* base32(short number);

