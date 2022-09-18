#include<stdio.h>
#include<stdlib.h>

typedef struct Tree{
    char val;
    struct Tree* left;
    struct Tree* right;
}treenode;


treenode* createNode(char val,treenode* left, treenode* right){
    treenode* new = malloc(sizeof(treenode));
    if(new){
        new->val=val;
        if(left) new->left=left;
        if(right) new->right=right;
    }
    return new;
}

int main(){

    treenode* n2 = createNode('2',NULL,NULL);
    treenode* n1 = createNode('1',NULL,n2);

    printf("THe value is: n2:  %c\n\n", n1->val);
    printf("THe value is: n1: %c\n\n", n1->right->val);
    return 0;
}