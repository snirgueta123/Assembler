#include "macro.h"

int IsMarcoOrEndmacro(char line[])/* The method checks if the current line starts with a macro or ends with a endmacro */
{
 int i,j;
 char nameMacro[MAX];
 memset(nameMacro,'\0',MAX);
 for(i=0;isspace(line[i]);i++);/* Skips spaces and characters */
 for(j=0;!(isspace(line[i])) && line[i]!='\n';j++,i++)/* Reads the next word and inserts it into the character set */  
    nameMacro[j]=line[i];
  if (!strcmp(nameMacro, "macro"))
    return 1;
    if (!strcmp(nameMacro, "endmacro"))
    return  2;
  return 0;

} 
void freeList3(struct Macro *Mtail )/*Freeing the macro table*/
{
  int i=0;
  
  struct Macro *Mtemp;
  Mtemp = (struct Macro*)malloc(sizeof(struct Macro));
  Mtemp = Mtail->next;
  if(Mtemp!=NULL)
   Mtemp = Mtemp-> next;  
  while(Mtemp!=NULL)
  {
   i++;
   free(Mtemp);
    Mtemp = Mtemp-> next;  
  } 
 
} 
void contactOfMacro(struct Macro *cell,FILE *fp)/*The method inserts the contents of the macro contained in the file into an cell in the linked list of macros*/
{
  char line[MAX];
  char content1 [MAX];
  memset(line , '\0' , MAX);
  memset(content1 , '\0' , MAX);
  fgets(line, MAX, fp);
 while(IsMarcoOrEndmacro(line)!= 2)/*The loop goes through the file until you come across a word endmacro */
  {
    strncat(content1, line , MAX);   
    fgets(line, MAX, fp);
  }
  strcpy(cell->content,content1);
  
}

void nameOfMacro(struct Macro *cell,char line[])/* The method inserts the name of the macro into the macro table  */
{
  
  int i=0,j=0;
 char name1[MAX];
 memset(name1,'\0',MAX);
 while(isspace(line[i]))/*Skips spaces or characters and gets to the next word*/
    i++;
 while(!(isspace(line[i])) && line[i]!='\n')/*Skips the next word*/
       i++;
 while(isspace(line[i]))
   i++;
 for(j=0;!(isspace(line[i])) && line[i]!='\n';j++,i++)
    name1[j]=line[i];
  
  strcpy(cell->name,name1);
  
  
 
}
int ReadFileOne(int i, char *argv[],struct Macro *Mhead)/*First move on the file when a macro appears adds it as a cell to the linked list
 and continues to check if there are more macros*/ 
{
    
  char line [MAX];
  FILE *fp;
  int index=0;
  memset(line , '\0' , MAX);
  fp = fopen(argv[i],"r");
  if(fp==NULL)
  {
     printf("error: cant open the file: %s  \n" , argv[i]);  
     return 0;
  } 
    while(fgets(line, MAX, fp))
   {
     index=0;  
     while(isspace(line[index]))
         index++;
     if(line[index]=='\0' || line[index]=='\n');/*Skipping empty lines at the beginning of the file causes lots of runtime errors*/
    else
    {
      struct  Macro* cell = NULL;
      cell = (struct Macro*)malloc(sizeof(struct Macro));
      if( IsMarcoOrEndmacro(line) == 1 )
       {
         Mhead -> next = cell ;
         Mhead=Mhead->next;
        nameOfMacro(cell , line);
        contactOfMacro(cell , fp);
       }
     }
   } 
  return 1;
}
int IsMacro(char line[],FILE *fpw,struct Macro *Mtail)/*Copy the contents of the corresponding macro to the file from the table, if it is a macro command*/
{
 int i,j;
 char name1[MAX];
 struct  Macro* cell = NULL;
 cell = (struct Macro*)malloc(sizeof(struct Macro));
 cell=Mtail; 
 memset(name1 , '\0' , MAX); 
 for(i=0;isspace(line[i]);i++);
 for(j=0;!(isspace(line[i])) && line[i]!='\n';j++,i++)/* Reads the next word and inserts it into the character set */  
 {
    name1[j]=line[i];
 }
 while(cell!=NULL)
 {
    if((strcmp(cell->name,name1))==0 )
   {
     
     fprintf(fpw,"%s",cell->content);
     return 1;
   }
   cell=cell->next;
 } 
 return 0;
}
void PreWriteFile(int i, char *argv[],struct Macro *Mtail)/*Go through the file and when you come across a macro, copy its contents to the file and when you come across a line that is not a macro, copy it in its entirety*/
{
  int flag=OFF;
  FILE *fps;
  FILE *fpr;
  int index=0;
   char line [MAX];
  char fname[MAX];
  char fname1[MAX];
  memset(line , '\0' , MAX);
  memset(fname , '\0' , MAX);
  memset(fname1 , '\0' , MAX); 
  strcpy(fname,argv[i]);
  strcpy(fname1,argv[i]);
  strncat(fname1, ".am", 3);
  fpr = fopen(fname,"r");
  fps = fopen(fname1,  "w");
  if(fpr == NULL)
     printf("error: cant open the file: %s  \n" , argv[i]);  
  while(fgets(line, MAX, fpr))
  { 
     index=0;
     while(isspace(line[index]))
         index++;
     if(line[index]=='\0' || line[index]=='\n');/*Skipping empty lines at the beginning of the file causes lots of runtime errors*/
    else
    {
     if(!flag)
     {   
        if(!(IsMacro(line,fps,Mtail)))
        {
          if(IsMarcoOrEndmacro(line) == 0)
          {  
            fprintf(fps,"%s",line);
          }
          else 
          {
            flag = ON;
          }
         }
    }
    else
    {
       if(IsMarcoOrEndmacro(line)== 2)
        flag = OFF;
    }  
   }       
  }
  freeList3(Mtail);
  fclose(fps);
  fclose(fpr);

}
