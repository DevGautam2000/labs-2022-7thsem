/*
          AUTHOR : GAUTAM CHANDRA SAHA
          DATE & TIME: Thu, August 04,2022 AT 19:45 
          DESCRIPTION:  dfa to accept a string of length less than equal to 
                        10 and containing a and b
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define STRING_MAX_LEN 10

struct state{
    int prev;
    char inp;
};  

void printMessage(char* format,int msg){
    printf(format,msg);
}

void checkValidDfa(char* s){

    //check if length id valid
    if(strlen(s)-1 > STRING_MAX_LEN){
        printMessage("Invalid string: Length is greater than  %d\n" ,STRING_MAX_LEN);
        return;
    }


    //check if string contains only a and b
    for(int i=0; i<strlen(s)-1; i++){
        if( s[i] > 'b' || isdigit(s[i])){
            printf("Invalid string: Should only contain 'a' & 'b'. ");
            return;
        }
    }

    //check if valid dfa
    struct state st;
    st.prev=0;
    st.inp=' ';

    for(int i=0; i<strlen(s)-1; i++){
        printf("%d",st.prev);

        if(s[i]=='b')
            st.prev++;

        st.inp=s[i];
        printf(" on input %c -> %d \n",st.inp,st.prev);
    }


    printMessage("\nValid string : Accepted. The final state is: %d\n",st.prev);
}

void main(){
    char inp[20];
    printf("Enter a string: ");
    fgets(inp, 20, stdin);

    checkValidDfa(inp);
}

/* 
INPUT/OUTPUT: 

Enter a string: abb

0 on input a -> 0
0 on input b -> 1
1 on input b -> 2

Valid string : Accepted. The final state is: 2

 */