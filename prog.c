#include <stdio.h>
#include "secondCheck.h"

int main(int argc, char *argv[])
{
   
   int flagError,i, DC=0,IC=0;  
   for (i = 1; i < argc; i++)
   {
       struct  Macro* Mtail= NULL;
      struct  Macro* Mhead = NULL;
      struct  Symbol* stail= NULL;
      struct  Symbol* shead = NULL;
      ItemListCell* listCell;
      Mhead = (struct Macro*)malloc(sizeof(struct Macro));
      Mtail = (struct Macro*)malloc(sizeof(struct Macro));
      Mtail = Mhead;
      shead = (struct Symbol*)malloc(sizeof(struct Symbol));
      stail = (struct Symbol*)malloc(sizeof(struct Symbol));
      stail = shead;
      flagError=OFF;
     arrayReset(TableInstructional,TableData);
     flagError=ReadFileOne(i,argv,Mhead);
     if(flagError==ON) 
     { 
          PreWriteFile(i,argv,Mtail);
         flagError=oneCheck(i,argv,shead);
         if(flagError!=ON)
         {
            DC=flagError;
           listCell =createListCell();
            flagError=secondCheck(i,argv,stail, DC,listCell);
            if(flagError!=ON)
            {
              IC=flagError;
             printObject(i,argv,DC,IC);
             if(exsistEntry(stail))
                  printentries(i,argv,stail);
             if(isExsistExtern(stail))
               printexternals(i,argv,stail,listCell); 
            }
        }
      
    }
   
  }
      return  1 ;
}


