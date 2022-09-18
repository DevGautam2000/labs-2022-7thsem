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
#include<ctype.h>

char* lookahead="";


int A(){
    // printf("String rejected by parser. %s",lookahead);
    if(*lookahead == 'b'){
        lookahead++;
        if(*lookahead == 'd'){
            lookahead++;
            
            

        }
    }

    return 0;
}

//function to check if the string is a valid string according to the grammar
void checkValidString(){
    if(A())
        printf("String accepted by parser.");
    else
        printf("String rejected by parser.");
}   

int main(){

    printf("\nRECURSIVE PREDICTIVE PARSER.\n\n");
    printf("Enter a string: ");
    char inp[20];
    fgets(inp,20,stdin);
    lookahead=inp;
    checkValidString();
    return 0;
}