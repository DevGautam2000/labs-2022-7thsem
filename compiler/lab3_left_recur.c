/*
		  AUTHOR : GAUTAM CHANDRA SAHA
		  DATE & TIME: Fri, August 26,2022 AT 16:01 
		  DESCRIPTION: program to remove left recursion 
	
	grammar:  S->Sad | d | ce
	
	after removal of left recursion

	S -> dS' | ceS'
	S' -> adS' | $

*/

#include<stdio.h>
#include<ctype.h>
#include<string.h>

#define LEN 26

// grammar structure
struct Grammar{
	char V[LEN]; //variables
	char T[LEN]; //terminals
	char S; //starting symbol
	char P[LEN]; //productions
};


struct Grammar grammar = {"","",' ',"S -> Sad|d|ce"} ;
struct Grammar newGrammar ;
int ngInd=0,gl=0,vInd=0,tInd=0;


//function to set the terminal and variables in the grammar
void setVarsAndTerminals(const char* g){
	grammar.S = g[0]; //set the starting symbol

	//check and set terminals
	for(int i=0; i<gl; i++)
		if(islower(g[i]))
			grammar.T[g[i]-'a'] = g[i];

	//check and set variables
	for(int i=0; i<gl; i++)
		if(isupper(g[i]))
			grammar.V[g[i]-'A'] = g[i];
}

//function to display vars and terminals in grammar
void printVarsAndTerminals(){
	
	//display the variables in grammar
	printf("\nV: ");
	for(int i=0; i<LEN; i++)
		if(grammar.V[i] && isupper(grammar.V[i]))
			printf("%c, ",grammar.V[i]);
	
	//display the terminals in grammar
	printf("\nT: ");
	for(int i=0; i<LEN; i++)
		if(grammar.T[i] && islower(grammar.T[i]))
			printf("%c, ",grammar.T[i]);
}

//function to push literals into newGrammar production
void push(char *arr){
	while(*arr != '\0')
		newGrammar.P[ngInd++] = *arr++;
}

//function to remove left recusrion from the grammar
void removeLeftRecursion(const char* g){
	ngInd=0;
	for(int i=1; i<gl; i++)
		if(g[i] == grammar.S){
			
			char t = g[i];
			push(&t);
			push(" -> ");

			//check for next production
			for(int j=i; j<gl ;j++)
				if(g[j] == '|'){
					t = g[j+1];
					push(&t);

					if(islower(g[j+2])){
						t= g[j+2];
						push(&t);
					}
						
					t=grammar.S;
					push(&t);
					push("' | ");
				}
			newGrammar.P[ngInd-2] = ' ';	//remove extra pipe	
			push("\n");
		}
	
	// for new Variable to avoid left recusrion
	for(int i=1; i<gl; i++)
		if(g[i] == grammar.S){
			char t=g[i];
			push(&t);
			push("' -> ");

			//push productions for the prime variable
			for(int j=i+1; j<gl ;j++){
				if(g[j] == '|') break;
				t = g[j];
				push(&t);
			} 	

			t=grammar.S;
			push(&t);
			push("' | $"); 
		}
	
}

int main(){
	
	gl=strlen(grammar.P);
	
	setVarsAndTerminals(grammar.P);
	
	printf("\nGRAMMAR:\n");
	printVarsAndTerminals();
	printf("\nS: %c \nP: %s ",grammar.S,grammar.P);
	
	removeLeftRecursion(grammar.P);
	
	printf("\n\nGrammar after removing left recursion: \n");
	printf("\n%s\n",newGrammar.P);
	
	return 0;
}


/* 

INPUT/OUTPUT: 

GRAMMAR:

V: S, 
T: a, c, d, e, 
S: S 
P: S->Sad | d | ce 

Grammar after removing left recursion: 

S -> dS' | ceS'   
S' -> adS' | $


 */