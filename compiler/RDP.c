/*
          AUTHOR : GAUTAM CHANDRA SAHA
          DATE & TIME: Wed, August 17,2022 AT 11:34 
          DESCRIPTION: recursice descent parser for the 
            
            GRAMMAR: 

            E->TE'
            E'->+TE'|e
            T->FT'
            T'->*FT'|e
            F->(E)|id

*/

#include<stdio.h>
#include<ctype.h>
#include<stdio.h>

const char * grammar = "\nE->TE'\nE'->+TE'|e\nT->FT'\nT'->*FT'|e\nF->(E)|id\n\n";
char *lookahead="";
int E();

int F(){
    if(*lookahead=='('){
        lookahead++;

        if(E()){
            if(*lookahead==')'){
                lookahead++;
                return 1;
            } else return 0;
        } 
        else return 0;
        
    }
    else if((*lookahead >= 'a' && *lookahead <= 'z') || (*lookahead >= 'A' && *lookahead <= 'Z')){
         lookahead++;
         return 1;
    }
       

    return 0;
}

int T_(){
    if(*lookahead == '*'){
        lookahead++;
        if(F()){
            if(T_())
                return 1;
            else return 0;
        }else return 0;
    }
    
    return 1;
}

int T(){
    if(F())
        if(T_())
            return 1;
        else return 0;
    else return 0;
    return 0;
}

int E_(){
    if(*lookahead == '+'){
        lookahead++;
        if(T()){
            if(E_())
                return 1;
            else return 0;
        }else return 0;       
    }
    return 1;
}

int E(){
    if(T())
        if(E_())
            return 1;
        else return 0;
    else return 0;
    
    return 0;
}

void main(){
    
    printf("RECURSIVE DESCENT PARSING\nGRAMMAR:\n%s\n\n",grammar);
    
    char inp[20];
    printf("Enter a string: ");
    fgets(inp, 20, stdin);

    lookahead = inp;
    if(E()){
        lookahead++;
        if(*lookahead == '\0')
            printf("String is accepted by grammar\n");
        else printf("String is not accepted by grammar\n");
    }
    else printf("String is not accepted by grammar\n");

}

/* 

INPUT/OUTPUT

RECURSIVE DESCENT PARSING
GRAMMAR:

E->TE'
E'->+TE'|e
T->FT'
T'->*FT'|e
F->(E)|id



Enter a string: a+b*c
String is accepted by grammar

 */