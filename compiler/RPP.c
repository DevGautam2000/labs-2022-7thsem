/*
          AUTHOR : GAUTAM CHANDRA SAHA
          DATE & TIME: Fri, September 16,2022 AT 19:32 
          DESCRIPTION: Recursive predictive parser

          grammar:
          A -> bdA'
          A' -> adA' | cA' | $

*/

#include<stdio.h>
#include<string.h>

char* lookahead="";

void showGrammar(){
    printf("GRAMMAR:\n\n");
    printf("V: %c , %s\n",'A',"A'");
    printf("T: %c , %c , %c, %c\n",'a','b','c','d');
    printf("S: %c\n",'A');
    printf("P: %c -> %s\n",'A',"bdA'");
    printf("%5s -> %s\n\n","A'","adA' | cA' | $");
}

int A_(){

    if(*lookahead == 'c'){
        lookahead++;
        if(A_())
            return 1;
        else return 0;
    }

    if(*lookahead == 'a'){
            lookahead++;
            if(*lookahead == 'd'){
                lookahead++;
                 if(A_())
                    return 1;
                else return 0;
            }
    }

    if(*lookahead == '\n') 
        return 1;

    return 0;
}

int A(){
    if(*lookahead == 'b'){
        lookahead++;
        if(*lookahead == 'd'){
            lookahead++;
            
            if(A_())
                return 1;
        }
    }

    return 0;
}

//function to check if the string is a valid string according to the grammar
void checkValidString(){
    if(A())
        printf("\nString accepted by parser.\n");
    else
        printf("\nString rejected by parser.\n");
}   

int main(){

    printf("\nRECURSIVE PREDICTIVE PARSER.\n\n");
    showGrammar();
    printf("Enter a string: ");
    char inp[20];
    fgets(inp,20,stdin);
    lookahead=inp;
    checkValidString();
    return 0;
}

/* 
INPUT/OUTPUT

EXECUTION 1:

RECURSIVE PREDICTIVE PARSER.

GRAMMAR:

V: A , A'
T: a , b , c, d
S: A
P: A -> bdA'
   A' -> adA' | cA' | $

Enter a string: bdcad

String accepted by parser.


EXECUTION 2:

RECURSIVE PREDICTIVE PARSER.

GRAMMAR:

V: A , A'
T: a , b , c, d
S: A
P: A -> bdA'
   A' -> adA' | cA' | $

Enter a string: bdcaddc

String rejected by parser.

 */