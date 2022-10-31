/*

* Productions:

A -> aSD #
B -> SaC hC #
C -> Sf g
D -> aBD #
S -> aAbCD #

* First:

A -> { a,#, }
B -> { h,#,a, }
C -> { g,f, }
D -> { a,#, }
S -> { a,#, }

* Follow:

A -> { b, }
B -> {  }
C -> {  }
D -> { $,a,f, }
S -> { $,a,f, }

*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 128
#define null '\0'
#define EPSILON '#'

char *prod[LEN][20];
char *first[LEN];
char *follow[LEN];
char nonT[LEN];

struct progress {

  int no_of_prods;
  int firstLen;
  int follLen;
  int hasEpsilon;
};

struct progress prog[LEN] = {-1, 0, 0, 0,-1};

char startSymbol;

void setProductions();
void showProductions();
void generateFirst();
char *copy(const char *alpha) {
  int len = strlen(alpha) + 1;
  char *c = malloc(len);
  strncpy(c, alpha, len);
  return c;
}

char *substring(const char *source) {
  char *c = copy(source);
  char *final = malloc(20);
  for (int i = 2, j = 0; c[i] != null; i++, j++)
    final[j] = c[i];
  return final;
}

void getProductions() {

  for (int i = 0; i < LEN; ++i) {
    prog[i].no_of_prods = -1;
  }

  int tot = 0;
  printf("\nEnter total productions: ");
  scanf("%d", &tot);

  int ind=0;
  char *inp = malloc(20);
  for (int i = 0; i < tot; i++) {
    printf("Enter production %d : ", i + 1);
    scanf(" %s", inp);
    if (i == 0)
      startSymbol = inp[0];

    if(prog[inp[0]].no_of_prods==-1) nonT[ind++] = inp[0];


    int ind = ++prog[inp[0]].no_of_prods;
    prod[inp[0]][ind] = substring(inp);
  }
}

void setProductions() {
  for (int i = 0; i < LEN; ++i) {
    prog[i].no_of_prods = -1;
  }

  prod['S'][0] = "aAbCD";
  prod['S'][1] = "#";
  prod['A'][0] = "aSD";
  prod['A'][1] = "#";
  prod['B'][0] = "SaC";
  prod['B'][1] = "hC";
  prod['B'][2] = "#";
  prod['C'][0] = "Sf";
  prod['C'][1] = "g";
  prod['D'][0] = "aBD";
  prod['D'][1] = "#";

  prog['S'].no_of_prods = 2;
  prog['A'].no_of_prods = 2;
  prog['B'].no_of_prods = 3;
  prog['C'].no_of_prods = 2;
  prog['D'].no_of_prods = 2;

  nonT[0] = 'S';
  nonT[1] = 'A';
  nonT[2] = 'B';
  nonT[3] = 'C';
  nonT[4] = 'D';

  startSymbol = 'S';
}


void showProductions() {
  printf("Productions: \n");
  for (int i = 0; i < LEN; ++i) {
    if (nonT[i] != null) {
      printf("%c -> ", nonT[i]);
      for (int j = 0; j <= prog[nonT[i]].no_of_prods; j++)
        if (prod[nonT[i]][j] != NULL)
          printf("%s ", prod[nonT[i]][j]);

      printf("\n");
    }
  }
}

void generateFirst() {

  for (int i = 0; i < LEN; ++i) {
    if (prog[i].no_of_prods > -1) {
      first[i] = malloc(20);

      for (int j = 0; j <= prog[i].no_of_prods; j++) {

        if (prod[i][j] != NULL) {

          char str = prod[i][j][0];

          if (islower(str) || str == EPSILON) {

            if (str == EPSILON) {
              //                printf("the character is: %c\n",i);
              prog[i].hasEpsilon = 1;
            }

            //              printf("For %c str : %c len : %d FIRST=%s\n",i,str,
            //              ind,first[i]);
            first[i][prog[i].firstLen++] = str;
            first[i][prog[i].firstLen++] = ',';
          }
        }
      }
    }
  }

  for (int i = 0; i < LEN; ++i) {
    if (prog[i].no_of_prods > -1) {

      for (int j = 0; j <= prog[i].no_of_prods; j++) {

        if (prod[i][j] != NULL) {

          char str = prod[i][j][0];

          if (isupper(str)) {

            if (prog[str].hasEpsilon == 1) {
              first[i][prog[i].firstLen++] = prod[i][0][1];
              first[i][prog[i].firstLen++] = ',';
            } else {
              first[i][prog[i].firstLen++] = first[str][0];
              first[i][prog[i].firstLen++] = ',';
            }
          }
        }
      }
    }
  }
}

void showFirst() {

  printf("\nFirst: \n");
  for (int i = 0; i < LEN; ++i) {
    if (nonT[i] != null)
      printf("%c -> { %s }\n", nonT[i], first[nonT[i]]);
  }
}

void showFollow() {

  printf("\nFollow: \n");
  for (int i = 0; i < LEN; ++i) {
    if (nonT[i] != null)
      printf("%c -> { %s }\n", nonT[i], follow[nonT[i]]);
  }
}
void generateFollow() {

  follow[startSymbol] = malloc(20);
  follow[startSymbol][prog[startSymbol].follLen++] = '$';
  follow[startSymbol][prog[startSymbol].follLen++] = ',';

  for (int i = 0; i < LEN; ++i) {
    if (prog[i].no_of_prods > -1) {

      int hasDup[LEN] = {0};
      for (int j = 0; j <= prog[i].no_of_prods; j++) {

        if (prod[i][j] != NULL) {
          char *str = copy(prod[i][j]);

          while (*str != null) {
            if (isupper(*str)) {
              // this is a variable

              if (*str == i) {
                str++;
                continue;
              }

              if (prog[*str].follLen == 0)
                follow[*str] = malloc(20);

              char next = *(str + 1) == null ? i : *(str + 1);
              if (hasDup[next])
                break;

              hasDup[next] = 1;
              follow[*str][prog[*str].follLen++] = next;
              follow[*str][prog[*str].follLen++] = ',';

//              if (*(str + 1) == null) {
//                // find follow
//                follow[*str] = follow[i];
//              }
//
//              if (islower(*(str + 1))) {
//                // find first
//                follow[*str][prog[*str].follLen++] = next;
//                follow[*str][prog[*str].follLen++] = ',';
//              }
            }
            str++;
          }
        }
      }
    }
  }
}
int main() {

    getProductions();

//  setProductions();
  showProductions();

  generateFirst();
  generateFollow();

  showFirst();
  showFollow();
}
