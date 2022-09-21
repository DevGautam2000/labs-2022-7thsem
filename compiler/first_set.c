/*
          AUTHOR : GAUTAM CHANDRA SAHA
          DATE & TIME: Tue, September 20,2022 AT 10:37 
          DESCRIPTION: program to generate first set of a prod

*/


#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

char* prod[128];

void initializeProductions(){
    prod['E']="TG";
    prod['G']="+TG|$";
    prod['T']="FH";
    prod['H']="*FH|$";
    prod['F']="(E)|id";
}

const int LEN = sizeof(prod)/sizeof(prod[0]);

char* firstSet[128];

char* copy(char *alpha){
    int len = strlen(alpha) + 1;
    char* c = malloc(len);
    strncpy(c,alpha,len);
    return c;
}
void genFirstSet(){

    for(int i=0; i<LEN; i++){
        if(prod[i] != NULL){
            // firstSet[i] = prod[i];

            char *temp = copy(prod[i]);
            
            while(*temp != '\0'){
                if(*temp=='|'){
                    temp++;
                    //  strncat(firstSet[i], &temp[0], 1);
                }
                temp++;
            }
            printf("%s\n",temp);

            // if(isalpha(prod[i][0]) && isupper(prod[i][0])){
            //     //todo: 
            // }

            firstSet[i] = prod[i];
        }

    }
}

void showFirstSet(){
    for(int i=0; i<128; i++){
           if(firstSet[i] != NULL)
             printf("%c -> %s\n",i,firstSet[i]);
    }
}

int main(){
    
    printf("\nPROGRAM TO GENERATE FIRST SET FROM A GRAMMAR.\n\n");
    initializeProductions();
    genFirstSet();
    showFirstSet();
    
    return 0;
}

/* 

for(int i=LEN-1; i>=0; i--){
        // if(prod[i][1] == '\''){
        // firstSet[tolower(prod[i][0])]="abc";
        // }
        
        // firstSet[prod[i][0]]="ABC";


    }

    // for(int i=128; i>=0; i--){
    //     if(firstSet[i] != NULL)
    //     printf("%s\n",firstSet[i]);
    // }

 */