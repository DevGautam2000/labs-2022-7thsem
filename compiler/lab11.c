//#include <stdio.h>
//
//#include <stdlib.h>
//
//#include <string.h>
//
//#include "gra.h"
//
//char precedence[] = "$(-+*/)\0";
//
//int opCompare(char a, char b)
//{
//
//    if (b == '\0')
//    {
//
//        // printf("\t Result: >\n");
//
//        return 1;
//    }
//
//    printf("Compare: %c and %c", a, b);
//
//    if (a >= 'a' && a <= 'z')
//    {
//
//        if (b >= 'a' && b <= 'z')
//        {
//
//            printf("\t Result: =\n");
//
//            return 0;
//        }
//
//        printf("\t Result: >\n");
//
//        return 1;
//    }
//
//    if (a >= 'A' && a <= 'Z')
//    {
//
//        if (b >= 'A' && b <= 'Z')
//        {
//
//            printf("\t Result: =\n");
//
//            return 0;
//        }
//
//        printf("\t Result: >\n");
//
//        return 1;
//    }
//
//    size_t apos = 0, bpos = 0, curr = 0;
//
//    for (char *c = precedence; *c != '\0'; c++, curr++)
//    {
//
//        if (*c == a)
//        {
//
//            apos = curr;
//        }
//
//        if (*c == b)
//        {
//
//            bpos = curr;
//        }
//    }
//
//    if (apos > bpos)
//    {
//
//        printf("\t Result: >\n");
//
//        return 1;
//    }
//    else if (apos == bpos)
//    {
//
//        printf("\t Result: =\n");
//
//        return 0;
//    }
//
//    printf("\t Result: <\n");
//
//    return -1;
//}
//
//size_t matchStr(String *a, String *b)
//{
//
//    if (a == NULL || b == NULL)
//    {
//
//        printf("Invalid strings\n");
//
//        return 0;
//    }
//
//    if (a->str[0] == '#' || b->str[0] == '#')
//    {
//
//        return 0;
//    }
//
//    int matched = -1;
//
//    for (size_t i = 0; i < a->len && i < b->len; i++)
//    {
//
//        if (a->str[i] != b->str[i])
//        {
//
//            break;
//        }
//
//        ++matched;
//    }
//
//    return matched + 1;
//}
//
//typedef struct Stack
//{
//
//    char arr[1024];
//
//    size_t len;
//
//} Stack;
//
//void push(Stack *stk, Node *node)
//{
//
//    size_t curr = node->data->len;
//
//    while (stk->len < 1024 && curr >= 1)
//    {
//
//        stk->arr[stk->len] = node->data->str[curr - 1];
//
//        stk->len++;
//
//        curr--;
//    }
//}
//
//void pushChar(Stack *stk, char c)
//{
//
//    if (stk->len < 1024)
//    {
//
//        stk->arr[stk->len] = c;
//
//        stk->len++;
//    }
//    else
//    {
//
//        printf("STACK FULL!\n");
//    }
//}
//
//char extract(Stack *stk)
//{
//
//    if (stk->len == 0)
//    {
//
//        return '\0';
//    }
//
//    stk->len--;
//
//    return stk->arr[stk->len];
//}
//
//char top(Stack *stk)
//{
//
//    if (stk->len == 0)
//    {
//
//        return '\0';
//    }
//
//    return stk->arr[stk->len - 1];
//}
//
//void printStk(Stack *stk)
//{
//
//    printf("The stack is: ");
//
//    for (size_t curr = 0; curr < stk->len; curr++)
//    {
//
//        printf("%c ", stk->arr[curr]);
//    }
//
//    printf("\n");
//}
//
//int main(void)
//{
//
//    Grammar *gmr = newGrammar();
//
//    printf("\n\n\nOperator Precedence\n\n");
//
//    // char input[] = "(a+a)-(a*a)\0";
//
//    printf("Enter the string to be evaluated: ");
//
//    char input[1024];
//
//    fgets(input, 1023, stdin);
//
//    size_t len = strlen(input);
//
//    input[len] = '\0';
//
//    if (input[len - 1] == '\n')
//    {
//
//        input[len - 1] = '\0';
//    }
//
//    char *matched = NULL;
//
//    char *curr = input;
//
//    Stack stk;
//
//    stk.len = 0;
//
//    for (size_t i = 0; i < 1024; i++)
//    {
//
//        stk.arr[i] = '\0';
//    }
//
//    pushChar(&stk, '$');
//
//    while (true)
//    {
//
//        printf("\n\n--------------------------------------------------------------\n");
//
//        printStk(&stk);
//
//        printf("The input string is: %s\n", curr);
//
//        // check if the stack can be reduced
//
//        if (opCompare(top(&stk), *curr) == 1)
//        {
//
//            bool reduced = false;
//
//            for (size_t seeker = 0; seeker < gmr->n_prods; seeker++)
//            {
//
//                Node *head = gmr->p[seeker];
//
//                while (head)
//                {
//
//                    if (head->data->len > stk.len - 1)
//                    {
//
//                        head = head->next;
//
//                        continue;
//                    }
//
//                    size_t checkoffset = stk.len - head->data->len;
//
//                    bool match = true;
//
//                    for (size_t check = 0; check < head->data->len; check++)
//                    {
//
//                        if (stk.arr[checkoffset + check] != head->data->str[check])
//                        {
//
//                            match = false;
//
//                            break;
//                        }
//                    }
//
//                    if (match == true)
//                    {
//
//                        printf("Action: Reduce with %s -> %s\n", head->label->str, head->data->str);
//
//                        for (size_t pop_ind = 0; pop_ind < head->data->len; pop_ind++)
//                        {
//
//                            extract(&stk);
//                        }
//
//                        pushChar(&stk, head->label->str[0]);
//
//                        reduced = true;
//
//                        break;
//                    }
//
//                    head = head->next;
//                }
//
//                if (reduced == true)
//                {
//
//                    break;
//                }
//            }
//
//            if (reduced)
//            {
//
//                continue;
//            }
//
//            printf("Info: No reduction could be made, switching to Shift\n");
//        }
//
//        if (*curr == '\0')
//        {
//
//            break;
//        }
//
//        // shift
//
//        pushChar(&stk, *curr);
//
//        printf("Action: Shift %c\n", *curr);
//
//        curr++;
//    }
//
//    if (stk.len == 2 && top(&stk) == gmr->s && *curr == '\0')
//    {
//
//        printf("String accepted\n");
//    }
//    else
//    {
//
//        printf("String rejected\n");
//    }
//
//    return 0;
//}




#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char *input;
int i=0;
char lasthandle[6],stack[50],handles[][5]={")E(","E*E","E+E","i","E^E"};
//(E) becomes )E( when pushed to stack

int top=0,l;
char prec[9][9]={

    /*input*/

    /*stack    +    -   *   /   ^   i   (   )   $  */

    /*  + */  '>', '>','<','<','<','<','<','>','>',

    /*  - */  '>', '>','<','<','<','<','<','>','>',

    /*  * */  '>', '>','>','>','<','<','<','>','>',

    /*  / */  '>', '>','>','>','<','<','<','>','>',

    /*  ^ */  '>', '>','>','>','<','<','<','>','>',

    /*  i */  '>', '>','>','>','>','e','e','>','>',

    /*  ( */  '<', '<','<','<','<','<','<','>','e',

    /*  ) */  '>', '>','>','>','>','e','e','>','>',

    /*  $ */  '<', '<','<','<','<','<','<','<','>',

};

int getindex(char c)
{
  switch(c)
  {
  case '+':return 0;
  case '-':return 1;
  case '*':return 2;
  case '/':return 3;
  case '^':return 4;
  case 'i':return 5;
  case '(':return 6;
  case ')':return 7;
  case '$':return 8;
  }
}


int shift()
{
  stack[++top]=*(input+i++);
  stack[top+1]='\0';
}


int reduce()
{
  int i,len,found,t;
  for(i=0;i<5;i++)//selecting handles
  {
    len=strlen(handles[i]);
    if(stack[top]==handles[i][0]&&top+1>=len)
    {
      found=1;
      for(t=0;t<len;t++)
      {
        if(stack[top-t]!=handles[i][t])
        {
          found=0;
          break;
        }
      }
      if(found==1)
      {
        stack[top-t+1]='E';
        top=top-t+1;
        strcpy(lasthandle,handles[i]);
        stack[top+1]='\0';
        return 1;//successful reduction
      }
    }
  }
  return 0;
}



void dispstack()
{
  int j;
  for(j=0;j<=top;j++)
    printf("%c",stack[j]);
}



void dispinput()
{
  int j;
  for(j=i;j<l;j++)
    printf("%c",*(input+j));
}



void main()
{
  int j;

  input=(char*)malloc(50*sizeof(char));
  printf("\nEnter the string\n");
  scanf("%s",input);
  input=strcat(input,"$");
  l=strlen(input);
  strcpy(stack,"$");
  printf("\nSTACK\tINPUT\tACTION");
  while(i<=l)
  {
    shift();
    printf("\n");
    dispstack();
    printf("\t");
    dispinput();
    printf("\tShift");
    if(prec[getindex(stack[top])][getindex(input[i])]=='>')
    {
      while(reduce())
      {
        printf("\n");
        dispstack();
        printf("\t");
        dispinput();
        printf("\tReduced: E->%s",lasthandle);
      }
    }
  }

  if(strcmp(stack,"$E$")==0)
    printf("\nAccepted;");
  else
    printf("\nNot Accepted;");
}
