#include "oneCheck.h"

/*
The method goes over the current line and checks if the line is
entry or extern
*/
ItemList* createList()/*Create a linked list*/
{
  ItemList* list=NULL;
  list=(ItemList*)malloc(sizeof(ItemList*));
  list->head=NULL;
  return list;
}
void freeList(ItemList*  list)/*The method frees the methods table from perusing the possibilities of each action*/
{
  ItemNode* p;
  while(list)
  {
   p=list->head;
   list->head=list->head->next;
   free(p); 
  }  
}
void addToList(ItemList* list, int actionNumber1, char OpradSource1[],char Opradtarget1[])
/*The method adds a new member to the table of addressing methods*/
{
  ItemNode* temp=NULL;
 temp = (ItemNode*)malloc(sizeof(ItemNode));
  temp->actionNumber=0;
  memset(temp->OpradSource, '\0' ,SIZE3);
  memset(temp->Opradtarget , '\0' ,SIZE3);
  temp->actionNumber=actionNumber1;
  strcpy(temp->OpradSource,OpradSource1);
  strcpy(temp->Opradtarget,Opradtarget1);
  temp->next=list->head;
  list->head=temp;
  

}

int IsLegalNumber(char sname[])/*Is the number valid*/
{
  int i=0;
  char line[MAX2];
   memset(line , '\0' , MAX2);
   strcpy(line,sname);
  while(line[i]!='\0')
  {   
    if(line[i]=='.' )
       return 0;
    if(line[i]!='-' && !(isdigit(line[i])))
        return 0;
    i++;
  }
  return 1;

}
int EntryOrExtern(char line[],int index)/*The method goes over the current line and checks if the line isentry or extern*/
{
  int j;
  char line1[MAX2];
  memset(line1, '\0' , MAX2);
  while(isspace(line[index]))
     index++; 
  for(j=0;!(isspace(line[index])) && line[index] != '\n';j++,index++)
         line1[j]=line[index];
  if(strcmp(".entry",line1)==0)
        return 1;
  else if(strcmp(".extern",line1)==0)
     return 2;
  return 0;
}
int legalSymbolExtern(char line[], int index, struct Symbol *tail,char nameSymbol[],int flagError,int sumLine)/*Has the .extern guidance been set correctly*/
{
  int j;
   char sname[MAX2];
  memset(sname, '\0' , MAX2);
   while(isspace(line[index]))
       index++; 
 for(j=0;!(isspace(line[index])) && line[index]!='\n';index++,j++)
       sname[j]=line[index];
if(line[index]!='\0' || line[index]!='\n')
  {
  
    printf("\nError Extern guidance Cannot accept more than one parameter :line:%d\n",sumLine);
    flagError=ON;
    return 0;
 }
 else
 {
    if(!(isalpha(sname[0])) || !(legalName(sname)) || IsNotExistSymbol(tail,sname))
    {
       printf("\nError Character name, invalid for guidance .external :line:%d\n",sumLine);
       flagError=ON;
       return 0;
  
   }

   strcpy(nameSymbol,sname);
   return 1;
 }
}
int IsNotExistSymbol(struct Symbol *tail,char nameSymbol[])
{
/*
The method checks if the current symbol does not exist in the list of symbol so far
*/
  struct Symbol *temp=NULL;
  temp=(struct Symbol*)malloc(sizeof(struct Symbol));
  temp=tail;
  while(temp!=NULL)
 {
   if(strcmp(nameSymbol,temp->symbol)==0)
     return 0;
   temp=temp->next;
 }
 return 1;
}
int legalName(char sname[])/*The method checks whether the name is valid, that is, there is no name of an action or prompt or register*/
{ 
  int i=0;
  char ReservedWords[][10]={"mov","cmp","add","sub","not","clr","lea","inc","dec","jmp","bne","get","prn",
"jsr","rts","hlt",".entry",".extern","r0","r1","r2","r3","r4","r5","r6","r7",".data",".string",".struct"};
  while(i<SIZE4)
  {
    if(strcmp(ReservedWords[i],sname)==0)
     {
       
        
        return 0;
     }
      
    i++;
   }
  return 1;
}

int IsExsistSymbol(struct Symbol *temp,struct Symbol *stail,int sumLine,char nameSymbol[])
{
/*
  Is the current symbol set correctly

*/  
    if(nameSymbol[0]=='\n')
    {
      printf("error:After the .extern guidance there must be one parameter:%d",sumLine);
      
       return 0;
    }
     if(!(isalpha(nameSymbol[0])))
    {
       printf("error:A label must begin with a letter big or small row:%d",sumLine);
       return 0;
    }
     if(strlen(nameSymbol)>LENGTHMAX)
    {
       printf("error:The maximum label length is 30:%d",sumLine);
       return 0;
    }
    if(!(legalName(nameSymbol)))
    {
         printf("error:Reserved words of the language cannot be label names:%d",sumLine);
    }
   else if(IsNotExistSymbol(stail,nameSymbol))
    {
      strcpy(temp->symbol,nameSymbol);
      return 1;
    }
   else
      printf("Error :is symbol exsist %d\n",sumLine); 
     return 0;
   
}
int isSymbol(char line[],char nameSymbol[],int index)/*Is the current line a symbol*/
{
  int j;
  char sname[MAX2];
  memset(sname, '\0' , MAX2);
 for(j=0;!(isspace(line[index])) && line[index]!='\n' && line[index]!=':';j++,index++)
      sname[j]=line[index]; 
      
 if(line[index]==':')
{
    strcpy(nameSymbol,sname);
     index++;
    return index;
}
  return 0;
} 

int GuidanceSentence(char line[],int index)/*Is the current line the Guidance line*/

{
  int j;
  char line1[MAX2];
  memset(line1, '\0' , MAX2);
  if(line[index]=='\n')
     return 0;
  while(isspace(line[index]))
     index++;
  for(j=0;!(isspace(line[index])) && line[index]!='\n';j++,index++)
      line1[j]=line[index];
   if(strcmp(".data",line1)==0)
     return 1;
  else if(strcmp(".string",line1)==0)
     return 2;
  else if(strcmp(".struct",line1)==0)
     return 3;
  return 0;

}

int isLegalAction(char line[],int index)/*The method checks whether the operating name is legal*/
{
   int j;
  char sname[MAX2];
  char *GuidanceOrInstructional[]={"mov","cmp","add","sub","not","clr","lea","inc","dec","jmp","bne","get","prn","jsr","rts","hlt",NULL};
  int k=0;
  char** name;
  memset(sname, '\0' , MAX2);
  name=GuidanceOrInstructional;
  for(j=0;!(isspace(line[index])) && line[index]!='\n' ;j++,index++)
      sname[j]=line[index];
  while(name[k]!=NULL)
  {
  
    if(strcmp(sname,name[k])==0)
    {
      return k;
    }
   k++;
  }
  return -1;
}
void UpdateValues(struct Symbol *stail,int IC)/*Updates in the symbol table the value of the data type symbols, by adding the final value of IC*/
{
  struct  Symbol* temp = NULL;
 temp = (struct Symbol*)malloc(sizeof(struct Symbol));
 IC=IC+MEMORY;
 temp=stail;
 while(temp!=NULL)
 {
   if(strcmp(temp->InsOrGui,"in")==0  )
      temp->address= temp->address+MEMORY;
   temp=temp->next;
 }
 temp=stail;
  while(temp!=NULL)
 {
   if(strcmp(temp->InsOrGui,"gu")==0)
      temp->address= temp->address+IC;
   temp=temp->next;
 }
}
int HowManydataRow(char line[],int index,int sumLine,int dataType,int DC)
{
  int j,i, count=0;
  int num;
  char sname[MAX2];
  int flagError=OFF;
  memset(sname, '\0' , MAX2);
  if(dataType==1)/*if  guidance ".data"*/
  {
     
       while(isspace(line[index]))
           index++;
         
        if(line[index]=='\n' || line[index]=='\0')
        {
          printf("Error:After the guidance .data There must be at least one paramete :line:%d\n",sumLine);
          flagError=ON;
       }  
       else if(line[index]==',')
       {
          printf("Error:The character ',' cannot appear before the first number:line:%d\n",sumLine);
          flagError=ON;
       }
       else
       {
         for(j=0;!(isspace(line[index])) && line[index]!='\n' && line[index]!=',';j++,index++)
         sname[j]=line[index];
         num=atoi(sname);
        
         if((IsLegalNumber(sname)==0))
         {
           printf("Error:Invalid parameter The .data directive must accept an integer as a parameter :line:%d\n",sumLine);
           flagError=ON;
         } 
         else
         {
           TableData[DC]=num;
           count++;
           while(isspace(line[index]))
                 index++;
        
          while(line[index]!='\n' && line[index]!='\0' )
          {
             
             if(line[index]!=',')
            {
              printf("Error:Between any two parameters there must be character ',' :line:%d\n",sumLine);
              flagError=ON;
              break;/*To exit the loop not to enter an infinite loop*/
            }
            else
            {
                
               index++;/*skip the character,*/
               while(isspace(line[index]))
                 index++;
                
               if(line[index]=='\n' || line[index]=='\0')
                {   
                printf("Error:After the last number the comma cannot appear :line:%d\n",sumLine);
                flagError=ON;
                }
                else if(line[index]==',')
                {
                   printf("Error:Two consecutive commas are not given without a parameter between them :line:%d\n",sumLine);
                   flagError=ON;
                }
                else
               {
                 memset(sname, '\0' , MAX2);
                for(j=0;!(isspace(line[index])) && line[index]!='\n' && line[index]!=',' && line[index]!='\0';j++,index++)
                sname[j]=line[index];
                while(isspace(line[index]))
                   index++;
                num=atoi(sname);
                if((IsLegalNumber(sname)==0))
                {
                  printf("Error:The number is invalid :line:%d\n",sumLine);
                  flagError=ON;
                }
                TableData[DC+count]=num;
                count++;
              }
           }
       }
    }
  
 }
 return count;
 }
 else if(dataType==2)/*if  guidance ".string"*/
 {
       while(isspace(line[index]))
            index++;
       memset(sname, '\0' , MAX2);
       if(line[index]!='"')
       {
          printf("Error: After a Guidance sentence .string must have a   string :line:%d\n",sumLine);
          flagError=ON;
       }
       index++;
       for(j=0; line[index]!='\n' && line[index]!='"' &&line[index]!='\0'  ;j++,index++)
         sname[j]=line[index];
      sname[j]='\0';
      if(line[index]=='\n' || line[index]=='\0')
      {
          printf("Error: After a Guidance sentence .string must have a valid  string :line:%d\n",sumLine);
          flagError=ON;
      }
      else
      {
        while(!isspace(line[index]) || line[index]!='\n'  )
            index++;
        if(line[index]!='\n' && line[index]!='\0')
        {
          printf("Error: Too many guidance parameters .string The directive should have only one parameter :line:%d\n",sumLine);
          flagError=ON;
        }
        i=0;
       while(sname[i]!='\0')
       {
         TableData[DC+count]=sname[i];
         i++;
         count++;
       }
       count++;/*A cell to mark the end of a string*/
     }
}
else/*if  guidance ".struct"*/
{
   while(isspace(line[index]))
            index++;
    if(line[index]=='\n')
   {
      printf("Error: Too few guideline statement parameters.struct takes two parameters, the first is a number and the second is a string :line:%d\n",sumLine);
      flagError=ON;
   }
    else if(line[index]==',')
   {
      printf("Error:The character ',' cannot appear before the first number guidance .struct :line:%d\n",sumLine);
      flagError=ON;
   }
   else
   {
      memset(sname, '\0' , MAX2);
      for(j=0;!(isspace(line[index])) && line[index]!='\n' && line[index]!=',';j++,index++)
         sname[j]=line[index];
     num=atoi(sname);
     if( (IsLegalNumber(sname)==0))
     {
       printf("Error:Number is invalid the first parameter of a guideline statement.struct must be a valid  number :line:%d\n",sumLine);
        flagError=ON;
     }
     else
     {
       TableData[DC+count]=num;
       count++;
        while(isspace(line[index]))
              index++;
        
       if(line[index]!=',')
       {
         printf("Error:Among the parameters of a guideline sentence.struct must be separated :line:%d\n",sumLine);
         flagError=ON;
       }
       else
       {
         index++;
          while(isspace(line[index]))
              index++;
          memset(sname, '\0' , MAX2);
          if(line[index]!='"')
          {
            printf("Error:The second parameter of a guideline sentence.struct must be a string :line:%d\n",sumLine);
            flagError=ON;
         }
         else
         {
           index++;
           for(j=0; line[index]!='\n' && line[index]!='"';j++,index++)
              sname[j]=line[index];
           if(line[index]!='"'  )
           {
              printf("Error:Invalid string :line:%d\n",sumLine);
              flagError=ON;
           }
           else
          {
               
              index++;
              while(isspace(line[index]))
              index++;
              if(line[index]!='\n' && line[index]!='\0')
              {
                printf("Error:Too many guideline statement parameters .struct Gets only one parameter :line:%d\n",sumLine);
                flagError=ON;
              }
              index=0;
              while(sname[index]!='\0')
              {
                TableData[DC+count]=sname[index];
                index++;
                count++;
             }
           count++;/*A cell to mark the end of a string*/
          }
       }
    }   
   }
 }
}
  if(flagError==OFF)
     return count;
  return 0;
}
int AddressingMethod(char sname[])/*The method checks which addressing method it is*/
{
    int i=0;
    if(sname[0]=='#')
       return 0;
    if(sname[0]=='r'&&  sname[1]>='0' && sname[1]<='9')
    {
     if( sname[1]>='0' && sname[1]<='7')/*Checking whether the register name is valid*/ 
        return 3;
     return -1;
    }
    while(sname[i]!='\0' && !(isspace(sname[i])) && sname[i]!='.' && sname[i]!=',' )
    {
      i++;
    }
    if(sname[i]=='.')
        return 2;
    return 1;
}
int IsLegalSourceAddressingMethod(int typeAddresssource ,int typeAction,ItemList* list)/*Is the operand a valid source*/
{
   int i=0; 
    char sname[SIZE3];
   ItemNode* temp =NULL;
  temp=(ItemNode*)malloc(sizeof(ItemNode));
   temp = list->head;
   memset(sname, '\0' , SIZE3); 
   while(i<typeAction )
   {
     temp=temp-> next;
     i++;
  }
  strcpy(sname,temp->OpradSource);
  i=0;
  while(sname[i]!='\0')
  {
     
    if((sname[i]-'0')==typeAddresssource)
    {
       return 1;
     }
  i++;
  }
  return 0;
}
int isExsistExtern(struct Symbol *stail)/*The method checks if there is an external prompt in the current file*/
{
 struct Symbol *temp =NULL;
  temp = (struct Symbol*)malloc(sizeof(struct Symbol));
  temp = stail->next;
  while(temp != NULL)
  {
    if(temp->isExternOrEntry=='1')
    {
      return 1;
     }
    temp=temp->next;
  }
 return 0;
}
int IsLegaltargetAddressingMethod(int typeAddresstarget ,int typeAction,ItemList* list)/*Is the target a valid source*/
{
 int i=0;  
 char sname[MAX2];
  ItemNode* temp=NULL;
  temp=(ItemNode*)malloc(sizeof(ItemNode));
  temp = list->head;
  memset(sname, '\0' , SIZE3);
   while(i<typeAction  )
  {
     temp=temp-> next;
     i++;
  }
  strcpy(sname,temp->Opradtarget);
  i=0;
  while(sname[i]!='\0')
  { 
     if((sname[i]-'0')==typeAddresstarget)
     {
       
       return 1;
     }
   i++;
 
  }
 return 0;
}

int HowManyInstructionsRow(char line[],int sumLine,int IC,int index,int typeAction,ItemList* list ) 
/*The method receives an instruction line and encodes the first line into the instruction table and checks how many additional words this line adds to the instruction table. If there are errors in an instruction sentence, the method informs about them.*/
{
  int j;
int typeAddresssource=4,typeAddresstarget=4;
  int count=1;
  int flagError=OFF;
  int NumberWords[SIZE3]={1,1,2,1,0};/*An array that holds a few more rows each of the addressing methods adds*/
 char sname[MAX2];
 memset(sname, '\0' , MAX2);
 if(line[index]=='\n' || line[index]=='\0'  )
  {
       if(typeAction!=14 && typeAction!=15)
       {
          printf("\nError: Incorrect number of operands  :line:%d\n",sumLine);
          flagError=ON;
       }
       else
       {
          TableInstructional[IC]=TableInstructional[IC]|(typeAction<<d6);
           TableInstructional[IC]=TableInstructional[IC]|(d5<<d7);
          TableInstructional[IC]=TableInstructional[IC]|(d5<<d3);
          TableInstructional[IC]=TableInstructional[IC]|(d5<<d5);
       }
       
  } 
  else if(line[index]==',')
  {
     printf("Error: Before the first operand of an action there can be no character,:%d\n",sumLine);
            flagError=ON;
  }
  else
  {
      memset(sname, '\0' , MAX2);
      for(j=0;!(isspace(line[index])) && line[index]!='\n' && line[index]!=',';j++,index++)/* Reads the next word and inserts it into the character set */  
         sname[j]=line[index];
      while(isspace(line[index]))
              index++;
      if(line[index]=='\n' ||line[index]=='\0' )
      {
         if(typeAction==0 || typeAction==1 || typeAction==2 || typeAction==3 || typeAction==6)
        {
          printf("Error: Too few operands :line:%d\n",sumLine);
          flagError=ON;
        } 
        typeAddresstarget=AddressingMethod(sname);
        if(typeAddresstarget==-1)
        {
          printf("Error: The register name is invalid  :line:%d\n",sumLine);
          flagError=ON;
        }
        else if(IsLegaltargetAddressingMethod(typeAddresstarget,typeAction,list)!=1)
        {
          printf("Error: Type of operator target that is not suitable  :line:%d\n",sumLine);
          flagError=ON;
        }
        else
        {
          
           TableInstructional[IC]=TableInstructional[IC]|(typeAction<<d6);
           TableInstructional[IC]=TableInstructional[IC]|(d5<<d7);
          TableInstructional[IC]=TableInstructional[IC]|(typeAddresstarget<<d3);
          TableInstructional[IC]=TableInstructional[IC]|(d5<<d5);    
          
        }
      
     }
         
     else if(line[index]!=',')
     {
         printf("Error: Between two operands of action must be the character, :line:%d\n",sumLine);
          flagError=ON;  
     }
     else
      {
         index++;/*Skip the character,*/
         typeAddresssource=AddressingMethod(sname);
          while(isspace(line[index]))
              index++; 
         if(line[index]=='\n')
         {
             printf("Error: After the last parameter the character must not be, :line:%d\n",sumLine);
          flagError=ON;  
         }
         else if(line[index]==',')
         {
            printf("Error: It is not possible to define two characters, consecutively one after the other without a word in them, :line:%d\n",sumLine);
          flagError=ON;       
        }
        else
        {
           memset(sname, '\0' , MAX2); 
           for(j=0;!(isspace(line[index])) && line[index]!='\n' && line[index]!=',';j++,index++)/* Reads the next word and inserts it into the character set */  
             sname[j]=line[index];
           while(isspace(line[index]))
              index++;
           if(line[index]!='\n' && line[index]!='\0' )
           {   
             printf("Error: No more than two parameters can be defined in a action sentence :line:%d\n",sumLine);
             flagError=ON;
           } 
           else 
           { 
              if(typeAction!=0 && typeAction!=1 && typeAction!=2 && typeAction!=3 && typeAction==6)
              {
                   printf("Error: Too many operands  :line:%d\n",sumLine);
                   flagError=ON;
              }
            typeAddresstarget=AddressingMethod(sname);
            if(typeAddresstarget==-1)
            {
              printf("Error: The register name is invalid  :line:%d\n",sumLine);
              flagError=ON;
            }
            else if(IsLegaltargetAddressingMethod(typeAddresstarget,typeAction,list)!=1)
             {
              printf("Error: Type of operator target  that is not suitable  :line:%d\n",sumLine);
              flagError=ON;
             }
             else
             {
               
                if(IsLegalSourceAddressingMethod(typeAddresssource,typeAction,list)!=1)
                {                
                  printf("Error: Type of operator Source that is not suitable  :line:%d\n",sumLine);
                   flagError=ON;
                }
                else
                {
                   TableInstructional[IC]=TableInstructional[IC]|(typeAction<<d6);
                   TableInstructional[IC]=TableInstructional[IC]|(typeAddresssource<<d7);
                   TableInstructional[IC]=TableInstructional[IC]|(typeAddresstarget<<d3);
                   TableInstructional[IC]=TableInstructional[IC]|(d5<<d5);
                   
                }

             }
           }
      }
 
   }
 }
if(flagError==ON)
     return 0;
count+=NumberWords[typeAddresssource]+NumberWords[typeAddresstarget];/*Adds the number of additional words*/
if(typeAddresssource==3 && typeAddresstarget==3)
   count--;
  return count;
}
/*The first pass over the file*/
int oneCheck(int i, char *argv[],struct Symbol *shead)
{
  int flagError=OFF,typpExOrEn,L,index=0,j;
  int flagSymbol=0,typeAction=0;
  int sumLine=0,DC=0,IC=0,dataType=0;
  FILE *fpr;
  char str[MAX3];
  char line[MAX2];
  char fname[MAX2];
  char nameSymbol[MAX2];
  char nameExtern[MAX2];
 ItemList* list=createList();
  struct Symbol *stail=NULL; 
  struct Symbol *temp=NULL;
  stail = (struct Symbol*)malloc(sizeof(struct  Symbol));
  stail=shead;
  strcpy(fname,argv[i]);
  strncat(fname, ".am", 3);
  fpr = fopen(fname,"r");
  memset(line, '\0' , MAX2);
 addToList(list,15,"","");
  addToList(list,14,"","");
addToList(list,13,"","123");
 addToList(list,12,"","0123");
addToList(list,11,"","123");
addToList(list,10,"","123");
 addToList(list,9,"","123");
 addToList(list,8,"","123");
addToList(list,7,"","123");
 addToList(list,6,"12","123");
addToList(list,5,"","123");
 addToList(list,4,"","123");
addToList(list,3,"0123","123");
addToList(list,2,"0123","123");
addToList(list,1,"0123","0123");
 addToList(list,0,"0123","123");
  while (fgets(line, MAX2, fpr))
  { 
    sumLine++;
    if(line[0] == '\n' || line[0]==';' || line[0] == '\0' );
    else
    {
      L=0;   
      index=0;
      temp=(struct Symbol*)malloc(sizeof(struct Symbol));
       memset( nameSymbol, '\0' , MAX2);
        memset( str, '\0' , MAX3);
        memset( nameExtern, '\0' , MAX2);
     while(isspace(line[index]))
          index++;
      flagSymbol=isSymbol(line,nameSymbol,index);
      if(flagSymbol!=0)
      {
      
        while(line[index]!=':')
          index++;
         index++;/*Skip the character:*/
      }
     if((dataType=GuidanceSentence(line,index))!=0)
       {
            while(isspace(line[index]))
              index++;
            if(flagSymbol!=0)
            {
               if(IsExsistSymbol(temp,stail,sumLine,nameSymbol)==0)
               {
                   flagError=ON;
               }
              else
               {
                shead->next=temp;
                 shead= shead->next;
                temp->address=DC;
                strcpy(temp->InsOrGui,"gu");
                temp->isExternOrEntry='0';
              }
           }
            while(!(isspace(line[index])))
              index++;
            if(((L=(HowManydataRow(line,index,sumLine,dataType,DC)))==0))
               flagError=ON;
             DC=DC+L; 
             
      }
       else if((typpExOrEn=EntryOrExtern(line,index)))
       {
           
            while(!isspace(line[index]))
              index++;
            while(isspace(line[index]))
              index++;
            if(typpExOrEn==2)
            {  
              j=0;
              for(j=0;!(isspace(line[index])) && line[index]!='\n' && line[index]!=':';j++,index++)
               nameExtern[j]=line[index];
              if(!(IsNotExistSymbol(stail,nameExtern)))
              {
                 printf("Error: Too many parameters The .extern directive can only accept one parameter,:%d\n",sumLine);
                  flagError=ON;
               }
               else
               {
                
                 shead->next=temp;
                 shead= shead->next;
                 temp->address=-1;
                 strcpy(temp->symbol,nameExtern);
                 strcpy(temp->InsOrGui,"no");
                 temp->isExternOrEntry='1';    
                 while(!isspace(line[index]))
                   index++;
                 while(isspace(line[index]))
                    index++;
                if(line[index]!='\n' && line[index]!='\0')
                {
                  printf("Error: Too many parameters The .extern directive can only accept one parameter,:%d\n",sumLine);
                  flagError=ON;
                 }
               }
             }
       }
       else 
       {
          if(flagSymbol!=0)
          {
              if(IsExsistSymbol(temp,stail,sumLine,nameSymbol)==0)
                {
                    
                    flagError=ON;
                 }
              else
              { 
               shead->next=temp;
              shead= shead->next;
              temp->address=IC;
              strcpy(str,"in");
              strcpy(temp->InsOrGui,str);
              temp->isExternOrEntry='0';
             }
          }
          while(isspace(line[index]))
              index++;
          if((typeAction=isLegalAction(line,index))==-1)
          {   
           printf("Error:The action does not exist:line:%d\n",sumLine);
            flagError=ON;
          }
           while(!(isspace(line[index])))
                index++;
           while((isspace(line[index])))
                index++;
          if((L=HowManyInstructionsRow(line, sumLine,IC, index, typeAction,list))==0)
              flagError=ON;  
          IC=IC+L; 
     }
   }
  
 }
 fclose(fpr); 
 if(flagError==OFF)
 {
     UpdateValues(stail,IC);
 }
  free(list);
  if(flagError==ON)
   return flagError;
 return DC;
}



