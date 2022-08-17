#include<stdio.h>
#include<string.h>

const char *grammar = "S->cAd\nA->ab|a";
const char *lookahead="";

int A(){
    if(*lookahead == 'a'){
        lookahead++;
        if(*lookahead == 'b'){
            lookahead++;
            return 1;
        }
        return 1;
    }

    return 0;
}

int S(){

    if(*lookahead == 'c'){
        lookahead++;
        if(A()){
            if(*lookahead=='d'){
                lookahead++;
                if(*lookahead=='\n')
                    return 1;
            }
        }
    }

    return 0;
}
void main(){
    printf("RECURSIVE DESCENT PARSING\nGRAMMAR:\n%s\n\n",grammar);
    
    char inp[20];
    printf("Enter a string: ");
    fgets(inp, 20, stdin);

    lookahead = inp;

    if(S()){
        printf("String is accepted by grammar\n");
    }else printf("String is not accepted by grammar\n");

}

/* 
INPUT/OUTPUT

RECURSIVE DESCENT PARSING
GRAMMAR:
S->cAd
A->ab|a

Enter a string: cad
String is accepted by grammar

 */