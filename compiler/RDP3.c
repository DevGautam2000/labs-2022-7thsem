/*
          AUTHOR : GAUTAM CHANDRA SAHA
          DATE & TIME: Thu, September 01,2022 AT 19:25 
          DESCRIPTION: implement a recursive descent parser for the following grammar

    GRAMMAR:
    V = {S,B,C}
    T = {a,b,c}
    S = S
    P = {   S->a|aB
            B->bC
            C->cC
        }

*/

#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define LEN 128
#define EMPTY -1
#define NA '\0'
#define NL '\n'
#define PIPE '|'

char *productions[LEN],*ip,*dp,currVar=' ';
int isStringAccepted=0, iter=1;

void checkValidString(const char*);
void func();

enum variables {
    V1 = 'S',
    V2 = 'B',
    V3 = 'C'
};

void initializeProductions(){
    productions[V1] = "a|aB";
    productions[V2] = "bC";
    productions[V3] = "c|cC";
}

struct stack { 
    int top;
    char buff[LEN];
};

struct stack st = {EMPTY,""};

void push(char c){
    if(st.top == LEN-1) return; 
    st.buff[++st.top] = c;
}

void pop(){
    if(st.top == EMPTY) return; 
    st.top--;
}

char peek(){
    if(st.top == EMPTY) return NA; 
    return st.buff[st.top];
}

void emptyStack(){
    while(st.top != EMPTY)
        pop();
}

//function to map appropriate productions to variables pointed by dp
void func(){
    switch (*dp){
    case V1:
        currVar=V1;
        dp = productions[V1];
        break;
    case V2:
        currVar=V2;
        dp = productions[V2];
        break;
    
    default:
        currVar=V3;
        dp = productions[V3];
        break;
    }
    checkValidString(ip);
}

//function to check if the given string is valid or not according to the grammar
void checkValidString(const char *s){

        push(*dp); //push the character pointed by dp
        char curr = peek(); //peek the pushed character

        if(isalpha(curr)){ // if the ch is an alphabet

            //show iterations
            printf("ITERATION %d :\tdp -> %c , ip -> %c \n\n",iter++,*dp,*ip);
            if(islower(curr)){ //if ch is a terminal

                //compare curr and ip
                if(curr == *ip){

                    dp++; //advance the descent pointer
                    push(*dp); //push ch to stack
                    ip++; //advance the input pointer

                    //string is accepted if ip is pointing to the last character
                    //and dp is either pointing to '|' or '\0'
                    if((*dp==NA || *dp==PIPE) && *ip==NL){
                            printf("\nSTRING ACCEPTED BY PARSER.\n");
                            isStringAccepted=1;
                    }else{
                        if(*dp == PIPE) {
                            //this condition satisfies then backtrack
                            printf("\nBacktracking and using next production of %c\n\n",currVar);
                            emptyStack(); 
                            dp++; //use next production of curr variable
                            push(*dp);
                            ip--; //decrement the input poiinter
                        }
                        checkValidString(ip); //recursively check if the string is valid
                    }
                }

            }else // if the ch is a variable
                func();
            
        }
}


int main(){
    printf("\nRECURSIVE DESCENT PARSER \n\n");
    initializeProductions(); //initialize the map
    
    //get input string
    char inp[LEN];
    printf("Enter a string: ");
    fgets(inp,LEN,stdin);
    
    //check if string is empty
    if(strlen(inp)==1) {
            printf("\nERROR:INVALID STRING.\n");
            return 1;
    }

    ip=inp; //point the input pointer to input string
 
    char str[] = {V1,'\0'};
    dp=str; //point the descent pointer to starting symbol

    printf("\n");

    checkValidString(ip); 

    if(!isStringAccepted)
        printf("\nSTRING NOT ACCEPTED BY PARSER.\n");

    return 0;
}

/* 
INPUT/OUTPUT

EXECUTION 1:

RECURSIVE DESCENT PARSER 

Enter a string: abcc

ITERATION 1 :   dp -> S , ip -> a 

ITERATION 2 :   dp -> a , ip -> a 


Backtracking and using next production of S

ITERATION 3 :   dp -> a , ip -> a 

ITERATION 4 :   dp -> B , ip -> b 

ITERATION 5 :   dp -> b , ip -> b 

ITERATION 6 :   dp -> C , ip -> c 

ITERATION 7 :   dp -> c , ip -> c 


Backtracking and using next production of C

ITERATION 8 :   dp -> c , ip -> c 

ITERATION 9 :   dp -> C , ip -> c 

ITERATION 10 :  dp -> c , ip -> c 


STRING ACCEPTED BY PARSER.


EXECUTION 2:

RECURSIVE DESCENT PARSER 

Enter a string: abd

ITERATION 1 :   dp -> S , ip -> a 

ITERATION 2 :   dp -> a , ip -> a 


Backtracking and using next production of S

ITERATION 3 :   dp -> a , ip -> a 

ITERATION 4 :   dp -> B , ip -> b 

ITERATION 5 :   dp -> b , ip -> b 

ITERATION 6 :   dp -> C , ip -> d 

ITERATION 7 :   dp -> c , ip -> d 


STRING NOT ACCEPTED BY PARSER.

 */