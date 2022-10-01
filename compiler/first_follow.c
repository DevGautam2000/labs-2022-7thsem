/*
          AUTHOR : GAUTAM CHANDRA SAHA
          DATE & TIME: Tue, September 20,2022 AT 10:37 
          DESCRIPTION: program to generate first set of a prod

*/


#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

#define EPSILON '$'
#define PIPE '|'
#define null '\0'

const int LEN = 128;
char* prod[LEN];
char* firstSet[LEN];

char* copy(const char *alpha){
    int len = strlen(alpha) + 1;
    char* c = malloc(len);
    strncpy(c,alpha,len);
    return c;
}

char* substring(const char* source){
    char *c = copy(source);
    char *final=malloc(20);
    for(int i=2,j=0; c[i]!=null ;i++,j++)
        final[j] = c[i] ;
    return final;
}

void genFirstSet(){
    
    for(int i=0; i<LEN; i++){
            if(prod[i] != NULL){
                
                // scan the whole input
                char* temp = copy(prod[i]);
                int ind=0;
                firstSet[i]= malloc(20);
                firstSet[i][ind++] = *temp++;

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
                int prog[26]={0};
                while(*temp != null){
                    if(isupper(*temp)){
                        

                        
                        char* ep = copy(firstSet[*temp]);
                        while(*ep!=null){
                            if(isalpha(*ep) && islower(*ep)){
                                prog[*ep-'a'] = 1;
                            }
                            if(*ep == EPSILON){
                                if(islower(prod[i][1])){
                                    if(prog[prod[i][1]-'a']){
                                        break;;
                                    }
                                    firstSet[i][ind++]=',';
                                    firstSet[i][ind]=prod[i][1];
                                }

                            }
                            ep++;
                        }


                        if(ind<2){
                            firstSet[i]=firstSet[*temp];
                            break;
                        }

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

void showFirstSet(){
    for(int i=0; i<LEN; i++){
           if(firstSet[i] != NULL)
             printf("FIRST(%c) -> {%s}\n",i,firstSet[i]);
    }
}

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
    
    printf("\nPROGRAM TO GENERATE FIRST AND FOLLOW SET FROM A GRAMMAR.\n\n");

    getProductions();
    
    // prod['S']="aAbCD|$";
    // prod['A']="G";
    // prod['G']="SDG|$";
    // prod['B']="SaC|hC|$";
    // prod['C']="SfH";
    // prod['H']="gH|$";
    // prod['D']="aBD|$";
    
    genFirstSet();
    printf("\n");
    showFirstSet();
    
    return 0;
}