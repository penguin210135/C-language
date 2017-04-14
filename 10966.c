#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXEXPR 256
#define NUMSYM 6

char expr[MAXEXPR];  
int pos;             

typedef enum {ID_A, ID_B, ID_C, ID_D, OP_AND, OP_OR} TokenSet;
char sym[NUMSYM];

typedef struct _Node {
    TokenSet data;
    struct _Node *left, *right;
} BTNode;
BTNode* EXPR();
BTNode* FACTOR();
BTNode* makeNode(char c);
void printPrefix(BTNode *root);

BTNode* FACTOR(){
	BTNode *fac;
	/*ID*/
	if(expr[pos] >= 'A' && expr[pos] <= 'D'){
		fac =  makeNode(expr[pos]);
		return fac;
	}
	
	/*(EXPR)*/
	pos--;
	fac = EXPR();
	return fac;
}

BTNode* EXPR(){
	BTNode *root,*leaf;
	int i;
	
	if(pos < 0) return NULL;
	/*EXPR OP FACTOR*/ 
	if(expr[pos] >= 'A' && expr[pos] <= 'D'){
		
		leaf = FACTOR();
		pos--;
		root = EXPR();
		if(root==NULL) return leaf;
		root->right = leaf;
		pos--;
		root->left = EXPR();
		
		return root;
	}
	/*OP*/
	else if(expr[pos]=='&' || expr[pos] == '|'){
	
		root = makeNode(expr[pos]);
		return root;
	}
	/*FACTOR*/
	if(expr[pos]==')'){
		
		leaf = FACTOR();	/*(EXPR)*/
		pos--;
		root = EXPR();
		
		if(root==NULL) root = leaf;
		else{
			root->right = leaf;
			pos--;
			root->left = EXPR(); 
		}
		
		return root;
	}else return NULL;	

}

BTNode* makeNode(char c){
	BTNode *leaf;
	leaf = (BTNode*)malloc(sizeof(BTNode));
	int i;
	for(i=0;i<6;i++){
		if(c == sym[i]){
			leaf->data = i;
		}
	}
	leaf->left = leaf->right = NULL;
	return leaf;
}
void freeTree(BTNode *root);
void printPrefix(BTNode *root);

void printInfix(Node *root){
	
	if(root==NULL) return;
	printInfix(root->left);
	printf("%c",root->data);
	if(root->right!=NULL){
		if(root->right->data=='|' || root->right->data=='&'){
			printf("(");
			printInfix(root->right);
			printf(")");
		}else printInfix(root->right);
	}
	return;
}

int main(void){
    sym[0]='A';
    sym[1]='B';
    sym[2]='C';
    sym[3]='D';
    sym[4]='&';
    sym[5]='|';
    while (scanf("%s", expr)!=EOF)
    {
        pos = strlen(expr) - 1;
        BTNode *root = EXPR();
        printPrefix(root);
        printf("\n");
        printInfix(root);
        printf("\n");
        freeTree(root);
    }

    return 0;
}

/* print a tree by pre-order. */
void printPrefix(BTNode *root){
    if (root != NULL) {
        printf("%c",sym[root->data]);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}



/* clean a tree.*/
void freeTree(BTNode *root){
    if (root!=NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

