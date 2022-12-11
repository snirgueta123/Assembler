#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 80


enum{OFF,ON};
struct Macro {
    char name[MAX];
    char content[MAX];
    struct Macro* next;
};
int IsMarcoOrEndmacro(char line[]);
void freeList3(struct Macro *Mtail );
void contactOfMacro(struct Macro *cell,FILE *fp);
void nameOfMacro(struct Macro *cell,char line[]);
int ReadFileOne(int i, char *argv[],struct Macro *Mhead);
int IsMacro(char line[],FILE *fpw,struct Macro *Mtail);
void PreWriteFile(int i, char *argv[],struct Macro *Mtail);

