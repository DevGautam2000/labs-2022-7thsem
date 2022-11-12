/*
          AUTHOR : GAUTAM CHANDRA SAHA
          DATE & TIME: Sat, November 12,2022 AT 22:48 
          DESCRIPTION:

*/


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define null 'e'
#define LEN 128
#define EMPTY -1
#define NA '\0'
size_t len = 0;

char *inp;
char terminals[9] = {'+', '-', '*', '/', '^', 'i', '(', ')', '$'};
char table[9][9] = {

    /*input*/

    /*stack    +    -   *   /   ^   i   (   )   $  */

    /*  + */ '>', '>', '<', '<', '<', '<',  '<',  '>', '>',

    /*  - */ '>', '>', '<', '<', '<', '<',  '<',  '>', '>',

    /*  * */ '>', '>', '>', '>', '<', '<',  '<',  '>', '>',

    /*  / */ '>', '>', '>', '>', '<', '<',  '<',  '>', '>',

    /*  ^ */ '>', '>', '>', '>', '<', '<',  '<',  '>', '>',

    /*  i */ '>', '>', '>', '>', '>', null, null, '>', '>',

    /*  ( */ '<', '<', '<', '<', '<', '<',  '<',  '=', '>',

    /*  ) */ '>', '>', '>', '>', '>', null, null, '>', '>',

    /*  $ */ '<', '<', '<', '<', '<', '<',  '<',  null, null,

};

int getIndex(char c) {

  switch (c) {
  case '+':return 0;
  case '-':return 1;
  case '*':return 2;
  case '/':return 3;
  case '^':return 4;
  case 'i':return 5;
  case '(':return 6;
  case ')':return 7;
  case '$':return 8;
  default:return -1;
  }
}

struct stack {
  int top;
  char buff[LEN];
};

// initialize the stack var
struct stack st = {EMPTY, ""};

// to push into stack
void push(char c) {
  if (st.top == LEN - 1)
    return;
  st.buff[++st.top] = c;
}

// to pop from stack
void pop() {
  if (st.top == EMPTY)
    return;
  st.buff[st.top] = NA;
  st.top--;
}

// to peek from stack
char peek() {
  if (st.top == EMPTY)
    return NA;
  return st.buff[st.top];
}

// function to display the operator precedence table
void dispTable() {
  printf("Operator Precedence Table:\n\n");
  for (int i = 0; i < 9; ++i)
    printf("%4c", terminals[i]);

  printf("\n_______________________________________\n");
  for (int i = 0; i < 9; ++i) {
    printf("%-2c| ", terminals[i]);
    for (int j = 0; j < 9; ++j)
      printf("%-4c", table[i][j]);
    printf("\n_______________________________________\n");
  }
}

void shift() {
  push(*inp);
  inp++;
}

void check() {

  //  for (int i = 0; i < len;i++) {

  while (1) {
    // stack top has < precedence value then shift
    char top = peek();
    int indOfTop = getIndex(top);
    int indOfInp = getIndex(*inp);
    int flag = 0;
    char sym = table[indOfTop][indOfInp];

    if ((top == '$' && *inp == '$') || sym == null) {

      printf("%-15s", st.buff);
      printf("%-20s", inp);

      if (peek() == '$' && *inp == '$') {
        printf("%-10s \n", "ACCEPT");
        printf("\nSTRING IS ACCEPTED.\n");
      } else {
        printf("%-10s \n", "REJECT");
        printf("\nSTRING IS REJECTED.\n");
      }
      break;
    }

    if (sym == '<' || sym == '=' || top == '$') {
      shift();
      flag = 1;
    } else if (sym == '>') {
      pop();
      flag = 0;
    }

    printf("%-15s", st.buff);
    printf("%-20s", inp);
    printf("%-10s  -> [%c %c %c]\n", flag == 1 ? "SHIFT" : "REDUCE", top, sym,
           flag == 1 ? *(inp - 1) : *inp);
  }
}

int main() {
  dispTable();

  // take a string as an input
  inp = malloc(30);
  printf("\nEnter a string: ");
  fgets(inp, 30, stdin);

  len = strlen(inp);
  inp[len - 1] = '$';

  push('$'); // push the end marker to the stack

  printf("\n%-15s %-20s %-25s", "stack", "input", "action");
  printf("\n__________________________________________________________\n");
  check();
  return 0;
}


/* 

INPUT/OUTPUT

EXECUTION 1:

Operator Precedence Table:

   +   -   *   /   ^   i   (   )   $
_______________________________________
+ | >   >   <   <   <   <   <   >   >   
_______________________________________
- | >   >   <   <   <   <   <   >   >   
_______________________________________
* | >   >   >   >   <   <   <   >   >   
_______________________________________
/ | >   >   >   >   <   <   <   >   >   
_______________________________________
^ | >   >   >   >   <   <   <   >   >   
_______________________________________
i | >   >   >   >   >   e   e   >   >   
_______________________________________
( | <   <   <   <   <   <   <   =   >   
_______________________________________
) | >   >   >   >   >   e   e   >   >   
_______________________________________
$ | <   <   <   <   <   <   <   e   e   
_______________________________________

Enter a string: i*i+(i/i)

stack           input                action                   
__________________________________________________________
$i             *i+(i/i)$           SHIFT       -> [$ < i]
$              *i+(i/i)$           REDUCE      -> [i > *]
$*             i+(i/i)$            SHIFT       -> [$ < *]
$*i            +(i/i)$             SHIFT       -> [* < i]
$*             +(i/i)$             REDUCE      -> [i > +]
$              +(i/i)$             REDUCE      -> [* > +]
$+             (i/i)$              SHIFT       -> [$ < +]
$+(            i/i)$               SHIFT       -> [+ < (]
$+(i           /i)$                SHIFT       -> [( < i]
$+(            /i)$                REDUCE      -> [i > /]
$+(/           i)$                 SHIFT       -> [( < /]
$+(/i          )$                  SHIFT       -> [/ < i]
$+(/           )$                  REDUCE      -> [i > )]
$+(            )$                  REDUCE      -> [/ > )]
$+()           $                   SHIFT       -> [( = )]
$+(            $                   REDUCE      -> [) > $]
$+             $                   REDUCE      -> [( > $]
$              $                   REDUCE      -> [+ > $]
$              $                   ACCEPT     

STRING IS ACCEPTED.


EXECUTION 2:

Operator Precedence Table:

   +   -   *   /   ^   i   (   )   $
_______________________________________
+ | >   >   <   <   <   <   <   >   >   
_______________________________________
- | >   >   <   <   <   <   <   >   >   
_______________________________________
* | >   >   >   >   <   <   <   >   >   
_______________________________________
/ | >   >   >   >   <   <   <   >   >   
_______________________________________
^ | >   >   >   >   <   <   <   >   >   
_______________________________________
i | >   >   >   >   >   e   e   >   >   
_______________________________________
( | <   <   <   <   <   <   <   =   >   
_______________________________________
) | >   >   >   >   >   e   e   >   >   
_______________________________________
$ | <   <   <   <   <   <   <   e   e   
_______________________________________

Enter a string: i)*i

stack           input                action                   
__________________________________________________________
$i             )*i$                SHIFT       -> [$ < i]
$              )*i$                REDUCE      -> [i > )]
$              )*i$                REJECT     

STRING IS REJECTED.

 */