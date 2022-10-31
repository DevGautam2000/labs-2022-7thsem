#include<string.h>
#include<stdio.h>
#include<ctype.h>

/* 

A=aAB
A=aBC
A=aAc

 */


char* prods[128][20];

int main(){

    int inp[20];
    int tot=0;
    printf("Enter number of productions: ");
    scanf("%d",&tot);

    for(int i=0; i<tot; i++){
        printf("Enter production %i",i+1);
    }
    return 0;
}