/*
          AUTHOR : GAUTAM CHANDRA SAHA
          DATE & TIME: Thu, August 11,2022 AT 23:19 
          DESCRIPTION: lexical analyzer for the string "for(i=10;i<100;i++);"

*/

#include<stdio.h>
#include<string.h>
#include <ctype.h>

//syntax to be parsed
// const char* inp = "for(i=10;i<100;i++);";
const char* inp = "int a=10*2*(3+5);";
// const char* inp = "char a='2';";

//enum storing token types
enum TokenType { 
    OP, //operator
    ID, //identifier
    STC, //special token class
    KW, //keyword
    NUM, //number
    WS //white space
};

//string equvalents to enum types
const char *tokenTypeStrings[] = {
    "OPERATOR",
    "IDENTIFIER",
    "SPECIAL TOKEN CLASS",
    "KEYWORD",
    "NUMBER",
    "WHITESPACE"
};

//list of keywords,operators,numbers,etc., to be parsed
const char* KEYWORDS[] = {"for","int","if","else","const","double","char","float","struct"};
const char OPERATORS[] = {'<','=','+','*','-','/','%','>'};
const char NUMBERS[] = {'0','1','2','3','4','5','6','7','8','9'};
const char SPECIAL_CHAR[]= {'(',')',';','{','}','\''};
const char COMMA=',';
const char WHITE_SPACE=' ';

const int kw_l = sizeof(KEYWORDS)/sizeof(KEYWORDS[0]);
const int op_l = sizeof(OPERATORS)/sizeof(OPERATORS[0]);
const int num_l = sizeof(NUMBERS)/sizeof(NUMBERS[0]);
const int sc_l = sizeof(SPECIAL_CHAR)/sizeof(SPECIAL_CHAR[0]);

//buffer to store the keywords and identifiers
char buffer[20];
int buffInd=0;

//token structure
struct Token{
    const char *tokenType;
    int tokenNum;
};

//function to end a token
void endTokenWithCharacter(struct Token *token,  char inp){
    printf("Token %d: < %s , %c >\n",token->tokenNum++,token->tokenType,inp);
}

//function to end a token
void endToken(struct Token *token,  char *inp){
    printf("Token %d: < %s , %s >\n",token->tokenNum++,token->tokenType,inp);
}

//function to empty the buffer after a keyword, identifier, etc., is parsed
void emptyBuffer(struct Token *token){
    char temp[10]="";
    //concat the buffer characters into a single string stream
    for(int i=0; i<buffInd; i++)
        strncat(temp, &buffer[i], 1);
    
    //check if the string is a keyword
    for(int i=0; i<kw_l; i++)
        if(strcmp(KEYWORDS[i],temp)==0){
            token->tokenType=tokenTypeStrings[KW];
            endToken(token,temp);
            buffInd=0;
            return;
        }

    //check if the string is a number
    for(int j=0; j<buffInd; j++)
        for(int i=0; i<num_l; i++)
            if(NUMBERS[i] == buffer[j]){

                char innTemp[10]="";

                for(int k=0; k<buffInd; k++)
                    if(isdigit(buffer[k]))
                        strncat(innTemp, &buffer[k], 1);

                token->tokenType=tokenTypeStrings[NUM];
                endToken(token,innTemp);
                buffInd=0;
                return;
            }
        
     //else the string is an identifier
    token->tokenType=tokenTypeStrings[ID];
    endToken(token,temp);
    buffInd=0;
}

//function to parse the given syntax
void parse(const char *s){
        static struct Token currToken;
       
        currToken.tokenNum=1;
        
        for(int i=0;i <strlen(inp); i++){
            if(s[i] == COMMA ) continue;
            if(s[i] == WHITE_SPACE && buffInd>0)
                emptyBuffer(&currToken);
            
            int flag=0;
            //check for special token class
            for(int j=0; j<sc_l; j++){
                if(s[i] == SPECIAL_CHAR[j]){
                    
                    if(buffInd > 0)
                        emptyBuffer(&currToken);

                    currToken.tokenType = tokenTypeStrings[STC];
                    endTokenWithCharacter(&currToken,s[i]);  
                    flag=1;
                }
            }

            //check for operators
            for(int j=0; j<op_l; j++)
                if(s[i] == OPERATORS[j]){
                    
                    if(buffInd > 0)
                        emptyBuffer(&currToken);
                    
                    currToken.tokenType=tokenTypeStrings[OP];
                    if(s[i] == '+' && s[i+1]=='+'){
                        i++;
                        endToken(&currToken,"++");  
                    }
                    else     
                        endTokenWithCharacter(&currToken,s[i]);  
                    
                    flag=1;
                }
            
            //if no above conditions are matching then fill the buffer
            if(flag==0)
                buffer[buffInd++] = s[i];
        }
}

int main(){

    printf("LEXICAL ANALYZER \nSYNTAX: %s\n\n",inp);
    parse(inp);   

    return 0;
}


/* 

INPUT/OUPUT

LEXICAL ANALYZER 
SYNTAX: for(i=10;i<100;i++);

Token 1: < KEYWORD , for >
Token 2: < SPECIAL TOKEN CLASS , ( >
Token 3: < IDENTIFIER , i >
Token 4: < OPERATOR , = >
Token 5: < NUMBER , 10 >
Token 6: < SPECIAL TOKEN CLASS , ; >
Token 7: < IDENTIFIER , i >
Token 8: < OPERATOR , < >
Token 9: < NUMBER , 100 >
Token 10: < SPECIAL TOKEN CLASS , ; >
Token 11: < IDENTIFIER , i >
Token 12: < OPERATOR , ++ >
Token 13: < SPECIAL TOKEN CLASS , ) >
Token 14: < SPECIAL TOKEN CLASS , ; >

 */