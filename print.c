#include "print.h"

void  printentries(int i,char *argv[],struct Symbol *stail)/*Prints all external symbols to a file with an extension .ext*/
{
 struct Symbol *temp=NULL;
  char fname[MAX1];
  FILE *fpr;
  char number[d3];
  char *p;
  char symbols[base]={'!','@','#','$','%','^','&','*','<','>','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v'};
  int num,j;
  temp=(struct Symbol *)malloc(sizeof(struct Symbol ));
  temp=stail->next;
  strcpy(fname,argv[i]);
  strncat(fname, ".ent",d7);
  fpr=fopen(fname,"w");
  if(fpr == NULL)
     printf("error: cant open the file: %s  \n" , argv[i]); 
   
  while(temp!=NULL)
  {
    if(temp->isExternOrEntry=='2')
    {
       memset(number, '\0' ,d3);
      p=symbols;
      j=0;
      num= ((temp->address)&(d1));
        while(j<num)
      {
       j++; 
       p++; 
      }
     number[d5]=*p;
      p=symbols;
      j=0;
     num=((temp->address&(d1<<d2))>>d2);
     while(j<num)
      {
       j++; 
       p++; 
      }
     number[d4]=*p;
      fprintf(fpr," %s   %c%c\n",temp->symbol,number[d4],number[d5]);
     }
      temp = temp->next;
 }
 fclose(fpr);
}
void  printexternals(int i,char *argv[],struct Symbol *stail,ItemListCell* listCell)/*Prints all external symbols to a file with an extension .ent*/
{
  struct Symbol *temp=NULL;
char fname[MAX1];
  FILE  *fpr;
 char number[d3];
  char *p;
  ItemCell* q;
  char symbols[base]={'!','@','#','$','%','^','&','*','<','>','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v'};
  int num,j;
  temp=(struct Symbol *)malloc(sizeof(struct Symbol ));
  temp=stail->next;
  strcpy(fname,argv[i]);
  strncat(fname, ".ext",4);
  fpr=fopen(fname,"w");
  if(fpr == NULL)
     printf("error: cant open the file: %s  \n" , argv[i]); 
  while(temp!=NULL)
  {
   if(temp->isExternOrEntry=='1')
   { 
      temp->address=temp->address+MEMORY;/* Address update
        */
       memset(number, '\0' ,d3);
      p=symbols;
      j=0;
      num= ((temp->address)&(d1));
        while(j<num)
      {
       j++; 
       p++; 
      }
     number[d5]=*p;
      p=symbols;
      j=0;
     num=((temp->address&(d1<<d2))>>d2);
     while(j<num)
      {
       j++; 
       p++; 
      }
     number[d4]=*p;
    fprintf(fpr," %s   %c%c\n",temp->symbol,number[d4],number[d5]);
    }
    temp = temp->next;
 }
  /*Go over the external characters that appear more than once and add them to the file
 .ext*/
 for(q=listCell->head;q!=NULL;q=q->next)
 {
   q->address=q->address+MEMORY;
   memset(number, '\0' ,d3);
   p=symbols;
   j=0;
   num= ((q->address)&(d1));
   while(j<num)
   {
     j++; 
     p++; 
   }
   number[d5]=*p;
   p=symbols;
   j=0;
   num=((q->address&(d1<<d2))>>d2);
   while(j<num)
   {
     j++; 
     p++; 
   }
   number[d4]=*p;
   fprintf(fpr," %s   %c%c\n",q->symbol,number[d4],number[d5]);
    
 }
 fclose(fpr);

}
