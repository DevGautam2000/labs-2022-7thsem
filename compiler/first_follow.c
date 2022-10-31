/*
          AUTHOR : GAUTAM CHANDRA SAHA
          DATE & TIME: Tue, September 20,2022 AT 10:37 
          DESCRIPTION: program to generate first set of a prod


    Enter total productions: 7
    Enter production 1 : S=aAbCD|#
    Enter production 2 : A=A'
    Enter production 3 : A'=SDA'|#
    Enter production 4 : B=SaC|hC|#
    Enter production 5 : C=SfC'
    Enter production 6 : C'=gC'|#
    Enter production 7 : D=aBD|#

    FIRST(A) -> {a,#} | {b}
    FIRST(B) -> {a,h,#} | {First(D) U Follow(D)} = {a,b}
    FIRST(C) -> {a,f} | {Follow(B)} =  {a,b}
    FIRST(D) -> {a,#} | {First(A') U Follow(A)} = {a,b}
    FIRST(A') -> {a,#} | {Follow(A)}={b}
    FIRST(C') -> {g,#} | {Follow(C)}= {a,b}
    FIRST(S) -> {a,#} | {$,a,f,First(D) U Follow(D)} = {$,a,b,f}
*/

#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

#define EPSILON '#'
#define PIPE '|'
#define null '\0'

const int LEN = 128;
char startSymbol=' ';
char* prod[LEN];
char* firstSet[LEN];
char* followSet[LEN];

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
                                    if(prog[prod[i][1]-'a'])
                                        break;

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

                        if(isupper(firstSet[i][0]))
                            firstSet[i][0] = firstSet[firstSet[i][0]][0];

                    }
                 temp++;
                 ind++;
                }
            }
    }

    for(int i=0; i<LEN; i++){
        if(firstSet[i] != NULL && isupper(firstSet[i][0])){
            firstSet[i] = firstSet[firstSet[i][0]];
        }
    }

}


void genFollowSet(){
    struct remaining{
        char ch;
        char prod;
    };

    struct remaining rem[128] = {'\0','\0'};

    int visited[26]={0};
    
    for(int i=0; i<LEN; i++){
        int ind=0;
        
        if(prod[i] != NULL){
            char* temp = copy(prod[i]);

           if(i == startSymbol){
                followSet[i]= malloc(20);
                followSet[i][ind++] = '$';
           }

            while(*temp != null){
                if(isupper(*temp)){
                    followSet[*temp]= malloc(2);
                    ind = strlen(followSet[*temp]);
                    char ch= *(temp+1);
                    // if(ch == PIPE || ch == null){
                    //     if(followSet[i] != NULL){
                    //         if(strlen(followSet[i])!=0)
                    //             followSet[*temp]=followSet[i];
                    //         else{
                    //             rem[*temp].ch = ch;
                    //             rem[*temp].prod = i;
                    //         }
                    //     }

                    // }else{
                    //     followSet[*temp][ind++] = ch;
                    //     followSet[*temp][ind++] = ',';
                    // }

                     if(visited[*temp-'A']){
                        temp++;
                        continue;
                     }

                     if(*temp != i){

                        visited[*temp-'A']=1;
                        followSet[*temp][ind++] = ch;
                     followSet[*temp][ind++] = ',';

                     if(ch == null || ch == PIPE){
                        if(followSet[i] != NULL && strlen(followSet[i])) {
                     printf("This is: %c with follow: %c and prod: %c\n",*temp,ch,i);
                            followSet[*temp] = followSet[i];
                        }
                        else{
                            rem[*temp].ch = ch;
                            rem[*temp].prod = i;
                        }
                     }else{
                        if(isupper(ch)){
                            // rem[*temp].ch = ch;
                            // rem[*temp].prod = i;

                            char* ep = copy(firstSet[i]);
                            followSet[*temp] = firstSet[i];

                            while(*ep!=null){
                                if(*ep == EPSILON){
                                     int ind = strlen(followSet[*temp])-1;
                                     followSet[*temp] = malloc(20);
                                     followSet[*temp][ind++] = followSet[i][0];
                                }
                                ep++;
                            }

                        }
                     }
                     }


                }

                temp++;
            }



        }
    }

     for(int i=0; i<LEN; i++){
          if(rem[i].prod != null){
                printf("\n_________________________\n\n");
                         printf("This is: %c with follow: %c and prod: %c\n",i,rem[i].ch,rem[i].prod);
                if(rem[i].ch == null || rem[i].ch == PIPE){
                    char* foll = followSet[rem[i].prod];
                    if(foll != NULL && strlen(foll)) {

                        followSet[i] = foll;
                        rem[i].ch = null;
                        rem[i].prod = null;
                    }

                }



          }
     }
}

void showFirstFollow(){
    printf("%s %20s %20s","VARIABLE","FIRST()","FOLLOW()");
    printf("\n______________________________________________________\n\n");
    for(int i=0; i<LEN; i++){
        if(firstSet[i] != NULL || followSet[i] != NULL){
            printf("%5c %15s {%s} %15s {%s}",i,"",firstSet[i],"",followSet[i]);
            printf("\n______________________________________________________\n\n");
        }
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
        if(i==0)
            startSymbol=inp[i][0];
        
        prod[inp[i][0]] = substring(inp[i]);
    }
}

int main(){
    
    printf("\nPROGRAM TO GENERATE FIRST AND FOLLOW SET FROM A GRAMMAR.\n\n");

    // getProductions();
    // prod['E'] = "TR";
    // prod['R'] = "+TR|#";
    // prod['T'] = "FY";
    // prod['Y'] = "*FY|#";
    // prod['F'] = "(E)|i";

    // prod['A']="aB|#";
    // prod['B']="SAf|b";
    // prod['S']="s";


    startSymbol='S';
    prod['S']="aAbCD|#";
    prod['A']="G";
    prod['G']="SDG|#";
    prod['B']="SaC|hC|#";
    prod['C']="SfH";
    prod['H']="gH|#";
    prod['D']="aBD|#";
    

    genFirstSet();
    genFollowSet();
    printf("\n");
    showFirstFollow();
    
    return 0;
}