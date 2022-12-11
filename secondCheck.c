#include "secondCheck.h"
void arrayReset(short TableInstructional[],short TableData[])/*Resets the array of data and instructions*/
{
  int i;
  for(i=0;i<LENTGH3;i++)
    TableInstructional[i]=0;
  for(i=0;i<LENTGH3;i++)
     TableData[i]=0;
}
ItemListCell* createListCell()/*Create a linked list*/
{
  ItemListCell* listCell=NULL;
  listCell=(ItemListCell*)malloc(sizeof(ItemListCell*));
  listCell->head=NULL;
  return listCell;
}

void addToListCell(ItemListCell* listCell,  char symbol1[],int address1)
{
  ItemCell* temp=NULL;
 temp = (ItemCell*)malloc(sizeof(ItemCell));
  temp->address=address1;
  memset(temp->symbol, '\0' ,MAX1);
  strcpy(temp->symbol,symbol1);
  temp->next=listCell->head;
  listCell->head=temp;
  

}
int updatingEntry(struct Symbol *stail,char nameSymbol[])/*Updates the symbol table as a .entry symbol*/
{
  struct Symbol *temp =NULL;
  temp = (struct Symbol*)malloc(sizeof(struct Symbol));
  temp = stail->next;
  while(temp != NULL)
  {
    if(strcmp(temp->symbol,nameSymbol)==0)
    {
      if(temp->isExternOrEntry!='1')
      {
        temp->isExternOrEntry='2';
        return 1;
      }
      return 0;
     }
    temp = temp-> next;
  }
  return 0;
}
int exsistEntry(struct Symbol *stail)/*Is there an internal symbol*/
{
struct Symbol *temp =NULL;
  temp = (struct Symbol*)malloc(sizeof(struct Symbol));
  temp = stail->next;
  while(temp != NULL)
  {
    if(temp->isExternOrEntry=='2')
      return 1;
   temp=temp->next;
 }
 return 0;
}

int insertOperand(char line[],int index,int IC,short TableInstructional[],struct Symbol *stail,ItemListCell* listCell)/*The method continues to encode the additional words of the action sentences that were not encoded in the first pass*/
{
   int j,typeMathod,count=0,prevOperand,num,howManyRow=1,numberOperand=0,k;
   char *p;
   char sname[MAX2];
   char mname[MAX2];
  struct Symbol *temp =NULL;
  temp = (struct Symbol*)malloc(sizeof(struct Symbol));
  temp = stail->next;
 
  while(line[index]!='\0' )
  {
     memset(sname, '\0' , MAX2);
      memset(mname, '\0' , MAX2);
    temp=stail->next;
    p=NULL;
    numberOperand++;
    
    if(numberOperand==2)/*skip the character,*/
     index++;
    if(numberOperand==1)/*We have reached a new line, so we need to count again so that no double counting is created*/
     howManyRow=1;
   while(isspace(line[index]))
            index++;
    if(line[index]==',')
      index++;
    for(j=0;!(isspace(line[index])) && line[index]!='\n' && line[index]!=',' ;j++,index++)
      sname[j]=line[index];
    typeMathod=AddressingMethod(sname);
    if(typeMathod==0)
    {
       count++;
      for(j=1,k=0;sname[j]!='\0';j++,k++)
          mname[k]=sname[j];
       num=atoi(mname);
       TableInstructional[IC+count]=TableInstructional[IC+count]|(num<<d3);
       TableInstructional[IC+count]=TableInstructional[IC+count]|(d5<<d5);
       if(numberOperand==1)
          prevOperand=0;
      howManyRow++;/*The operand is address method number 0 so we will have to add another word*/
   }
   else if(typeMathod==1)
   {
      count++; 
      while(temp!=NULL)
      {
        if(strcmp(temp->symbol,sname)==0)
          break;
        temp=temp->next;
      }
      if(temp->isExternOrEntry=='1')/* symbol extern*/
      { 
            if(temp->address!=-1)
            {
                addToListCell(listCell,sname,IC+count);
                TableInstructional[IC+count]=/*TableInstructional[IC+count]|(1<<0)*/1;
            } 
           else
          {
             temp->address=IC+count;
            TableInstructional[IC+count]=/*TableInstructional[IC+count]|(1<<0)*/1; 
          }
         
                
      } 
      else
        {
        
        TableInstructional[IC+count]=TableInstructional[IC+count]|((temp->address)<<d3);
        TableInstructional[IC+count]=TableInstructional[IC+count]|(d3<<d5);
        }
      if(numberOperand==1)
        prevOperand=1;
       howManyRow++;/*The operand is address method number 1 so we will have to add another word*/
   }
    else if(typeMathod==2)
    {
       count++;
       
       strncpy(mname,sname,strlen(sname)-2);
      while(temp!=NULL)
      {
        if(strcmp(temp->symbol,mname)==0)
          break;
        temp=temp->next;
      }
      TableInstructional[IC+count]=TableInstructional[IC+count]|((temp->address)<<d3);
      TableInstructional[IC+count]=TableInstructional[IC+count]|(d3<<d5);
      count++;
      p=sname;
      while(*p!='.')
      {
       p++;
      }
      p++;
      if(*p=='1')   
      {
        TableInstructional[IC+count]=TableInstructional[IC+count]|(d4<<d3);
      }
      else
         TableInstructional[IC+count]=TableInstructional[IC+count]|(d3<<d3);
         TableInstructional[IC+count]=TableInstructional[IC+count]|(d5<<d5);
      if(numberOperand==1)
       prevOperand=2;
       howManyRow=howManyRow+2;/*The operand is address method number 2 so we will have to add another 2 word*/
   }
   else
   {
     if(numberOperand==1)
     {
        count++;
        howManyRow++;/*The operand is address method number 3 so we will have to add another word*/
        while(isspace(line[index]))
            index++;
       if(line[index]=='\0' )
       { 
         TableInstructional[IC+count]=TableInstructional[IC+count]|((sname[d4]-'0')<<d3);
         TableInstructional[IC+count]=TableInstructional[IC+count]|(d5<<d6);  
          TableInstructional[IC+count]=TableInstructional[IC+count]|(d3<<d5);  
       }
        else
       {
        TableInstructional[IC+count]=TableInstructional[IC+count]|((sname[d4]-'0')<<d6);
       } 
      prevOperand=3;
     }
    else
    {
       if(prevOperand==3)
       {
           TableInstructional[IC+count]=TableInstructional[IC+count]|((sname[d4]-'0')<<d3);
       }
       else
       {
           count++;
          TableInstructional[IC+count]=TableInstructional[IC+count]|((sname[d4]-'0')<<d3);
        howManyRow++;
       }
    }
  }
   while(isspace(line[index]))
            index++;
   
 }
 return howManyRow;
}
void  UpdateSymbolAsEntry(struct Symbol *stail,char nameSymbol[])/*The method updates the symbol in the symbol table as an entry symbol*/
{
   struct Symbol *temp =NULL;
  temp = (struct Symbol*)malloc(sizeof(struct Symbol));
  temp = stail->next;
   while(strcmp(temp->symbol,nameSymbol)!=0)
   {
    temp=temp->next;
   }
  temp->isExternOrEntry='2';
} 
void printObject(int i, char *argv[],int DC,int IC)/*The method prints the machine code so that the instructions come first followed by the data code to a file with an extension
.ob*/
{
   FILE *fpr;
  char name[MAX1];
  char number[d3];
  char number1[d3];
 char *p;
 int j,count;
 char symbols[base]={'!','@','#','$','%','^','&','*','<','>','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v'};
 int num,num1;
  strcpy(name,argv[i]);
  strncat(name, ".ob",3);
  fpr=fopen(name,"w");
  if(fpr == NULL)
     printf("error: cant open the file: %s  \n" , argv[i]); 
  
 fprintf(fpr,"       %c%c\n ",symbols[IC],symbols[DC]);
  for(i=0,count=MEMORY;i<IC;i++,count++)
  {
     memset(number1, '\0' ,d3);
     memset(number, '\0' ,d3);
     p=symbols;
     j=0;
     num= (TableInstructional[i]&(d1));
     num1=(count&(d1));
     while(j<num)
      {
       j++; 
       p++; 
      }
     number[d5]=*p;
     p=symbols;
     j=0;
     while(j<num1)
     {
       j++; 
       p++;
     }
      number1[d5]=*p;
      p=symbols;
     j=0;
     num=((TableInstructional[i]&(d1<<d2))>>d2);
     num1=((count&(d1<<d2))>>d2);
    while(j<num)
      {
       j++; 
       p++; 
      }
     number[d4]=*p;
      p=symbols;
     j=0;
     while(j<num1)
     {
       j++; 
       p++;
     }
     number1[d4]=*p;
     fprintf(fpr,"   %c%c    %c%c\n ",number1[d4],number1[d5],number[d4],number[d5]);
   }
  for(i=0,count=count;i<DC;i++,count++)
  {
     memset(number, '\0' ,d3);
     memset(number1, '\0' ,d3);
     p=symbols;
     j=0;
     num= (TableData[i]&(d1));
    num1=(count&(d1));
     while(j<num)
      {
       j++; 
       p++; 
      }
     number[d5]=*p;
     p=symbols;
     j=0;
     while(j<num1)
     {
       j++; 
       p++;
     }
      number1[d5]=*p;
       p=symbols;
       j=0;
        num=((TableData[i]&(d1<<d2))>>d2);
    num1=((count&(d1<<d2))>>d2);
     while(j<num)
     {
       j++; 
       p++;
     }  
     number[d4]=*p;
     p=symbols;
       j=0;
    while(j<num1)
     {
       j++; 
       p++;
     } 
     number1[d4]=*p; 
    fprintf(fpr,"   %c%c    %c%c\n ",number1[d4],number1[d5],number[d4],number[d5]);
   }
 fclose(fpr);
}
int secondCheck(int i, char *argv[],struct Symbol *stail,int DC,ItemListCell* listCell)
/*Second pass on the file*/
{
   int L,j, flagError=OFF, flagSymbol=0, sumLine=0,IC=0,index=0,dataType=0,typpExOrEn=0;
    char nameSymbol[MAX2];
   char line[MAX2];
   char fname[MAX2];
   FILE *fpr;
   memset(line, '\0' , MAX2);
   strcpy(fname,argv[i]);
  strncat(fname, ".am", 3);
  fpr = fopen(fname,"r"); 
  while (fgets(line, MAX2, fpr))
  {
   L=0;
   
     index=0;
     sumLine++;
      while(isspace(line[index]))
          index++;
  
   if(line[index] == '\n' || line[index]==';' || line[index] == '\0');
    else
    {
       memset(nameSymbol, '\0' , MAX2);
       flagSymbol=isSymbol(line,nameSymbol,index);
       if(flagSymbol!=0)
       {
        while(line[index]!=':')
          index++;
         index++;/*Skip the character:*/
       }
       if((dataType=GuidanceSentence(line,index))!=0 || (typpExOrEn=EntryOrExtern(line,index))==2 );
       else if((typpExOrEn=EntryOrExtern(line,index))==1)
       {
           while(isspace(line[index]))
              index++;
           while(!isspace(line[index]))
              index++;
           while(isspace(line[index]))
              index++;   
           for(j=0;!(isspace(line[index])) && line[index]!='\n' && line[index]!=':';j++,index++)
               nameSymbol[j]=line[index];
          if(!(updatingEntry(stail,nameSymbol)))
          {
             printf("Error:You cannot define similar names for the .extern guidance and the .entry guidance line:%d\n",sumLine);
              flagError=ON;
          }
          else
          {
            UpdateSymbolAsEntry(stail,nameSymbol);

          }
       } 
       else
       {
          while(isspace(line[index]))
            index++;
          while(!isspace(line[index]))
              index++;
           while(isspace(line[index]))
              index++;
          L=insertOperand(line, index, IC, TableInstructional,stail,listCell);
      }
     
   }
  IC=IC+L;
 }
 if(flagError==ON)
   return flagError;
 return IC;
}


     
