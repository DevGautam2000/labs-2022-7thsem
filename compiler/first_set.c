/*
          AUTHOR : GAUTAM CHANDRA SAHA
          DATE & TIME: Tue, September 20,2022 AT 10:37 
          DESCRIPTION: program to generate first set of a prod

*/


#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

//macros
#define EPSILON '#'
#define PIPE '|'
#define null '\0'

const int LEN = 128;
char* prod[LEN];
char* firstSet[LEN];

//funciton to copy a string pointed by a pointer
char* copy(const char *alpha){
    int len = strlen(alpha) + 1;
    char* c = malloc(len);
    strncpy(c,alpha,len);
    return c;
}

//function to extract the production from the given variable
char* substring(const char* source){
    char *c = copy(source);
    char *final=malloc(20);
    for(int i=2,j=0; c[i]!=null ;i++,j++)
        final[j] = c[i] ;
    return final;
}

//function to generate the first set from grammar
void genFirstSet(){
    
    for(int i=0; i<LEN; i++){
            if(prod[i] != NULL){
                
                // scan the whole input
                char* temp = copy(prod[i]);
                int ind=0;

                firstSet[i]= malloc(20);

                //assign the first variables/terminals in the production
                firstSet[i][ind++] = *temp++;

                //check if there is more than one production
                //for a given variable
                while (*temp != null){

                    if(*temp == PIPE){
                        firstSet[i][ind++]=',';
                        firstSet[i][ind++] = *++temp;
                    }
                    temp++;
                }
                

            }
    }

    for(int i=0; i<LEN; i++){
            if(firstSet[i] != NULL){
                char* temp = copy(firstSet[i]);
                int ind=strlen(temp);
                int prog[26]={0}; //to keep track so duplicates
                while(*temp != null){
                    if(isupper(*temp)){// if the first set contains a variable
                        
                        char* ep = copy(firstSet[*temp]);
                        while(*ep!=null){

                            //add the variable to a progress array to filter dupliates
                            if(isalpha(*ep) && islower(*ep))
                                prog[*ep-'a'] = 1;
                            
                            
                            //if the variable has a epsilon in its first set
                            if(*ep == EPSILON){
                                if(islower(prod[i][1])){
                                    
                                    //if a duplicate
                                    if(prog[prod[i][1]-'a'])
                                        break;
                                    
                                    //add it to the set
                                    firstSet[i][ind++]=',';
                                    firstSet[i][ind]=prod[i][1];
                                }

                            }
                            ep++;
                        }

                        //if the current set has only one variable then
                        //replace with the firstset of the variable in the 
                        //set of the current set
                        if(ind<2){
                            firstSet[i]=firstSet[*temp];
                            break;
                        }

                        //still if variable exists in set
                        //then replace with the production 
                        //of the variable in the set
                        char* p = firstSet[i];
                        if(isupper((p[0]))){
                            p[0] = firstSet[p[0]][0];
                        }

                    }
                 temp++;
                 ind++;
                }
            }
    }
}

//function to show the first set
void showFirstSet(){
    for(int i=0; i<LEN; i++){
           if(firstSet[i] != NULL)
             printf("FIRST(%c) -> {%s}\n",i,firstSet[i]);
    }
}

//function to get the production as input
void getProductions(){
    int tot=0;
    printf("\nEnter total productions: ");
    scanf("%d",&tot);

    for(int i=0;i<tot;i++){
        char inp[20][20];
        printf("Enter production %d : ",i+1);
        scanf(" %s",inp[i]);
        prod[inp[i][0]] = substring(inp[i]);
    }
}

int main(){
    
    printf("\nPROGRAM TO GENERATE FIRST SET FROM A GRAMMAR.\n\n");

    getProductions();
    genFirstSet();
    printf("\n");
    showFirstSet();
    
    return 0;
}

/* 

INPUT/OUTPUT

EXECUTION 1

PROGRAM TO GENERATE FIRST SET FROM A GRAMMAR.


Enter total productions: 7
Enter production 1 : S=aAbCD|#
Enter production 2 : A=G
Enter production 3 : G=SDG|#
Enter production 4 : B=SaC|hC|#
Enter production 5 : C=SfH
Enter production 6 : H=gH|#
Enter production 7 : D=aBD|#

FIRST(A) -> {a,#} 
FIRST(B) -> {a,h,#} 
FIRST(C) -> {a,f}
FIRST(D) -> {a,#}
FIRST(G) -> {a,#}
FIRST(H) -> {g,#}
FIRST(S) -> {a,#}


EXECUTION 2

PROGRAM TO GENERATE FIRST SET FROM A GRAMMAR.

Enter total productions: 3
Enter production 1 : A=aB|#
Enter production 2 : B=SAf|b
Enter production 3 : S=s

FIRST(A) -> {a,#}
FIRST(B) -> {s,b}
FIRST(S) -> {s}

*/