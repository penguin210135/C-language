#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node{
	char data;
	struct Node *left,*right;
}Node;

char s[100];
int c[4];
int pos;
int num=0;
Node* makeNode(){
	Node *root;
	root = (Node*)malloc(sizeof(Node));
	root->data = s[num];
	root->left = root->right = NULL;
	return root;
}


void printTree(Node *head){
	
	if(head==NULL) return;
	printTree(head->left);
	printf("%c", head->data);
	printTree(head->right);
	return;
}

Node* createTree(){
	
	if(num > pos) return NULL;
	Node *root;
	if(s[num] == '|' || s[num] == '&'){
		root = makeNode();
		num++;
		root->left = createTree();
		num++;
		root->right = createTree();
		return root;
	}
	root = makeNode();
	return root;
}


int countTree(Node *root){
	int ans=0;
	switch(root->data){
		case '&':
			ans = countTree(root->left) & countTree(root->right);			
		break;
		case '|':
			ans = countTree(root->left) | countTree(root->right);
		break;
		case 'A':
			ans = c[3];
		break;
		case 'B':
			ans = c[2];
		break;
		case 'C':
			ans = c[1];
		break;
		case 'D':
			ans = c[0];
		break;
	}
	return ans;
}

void TruthTable(Node *root){
	int i,n,ans;
	
	for(i=0;i<16;i++){
		ans = 0;
		for(n=0;n<4;n++){
			c[n]=( i&(1<<n)) >> n; /*truth table Â²©ö°µªk*/ 
		}
		ans = countTree(root);
		printf("%d %d %d %d %d\n",c[3],c[2],c[1],c[0],ans);
	}
}

int main(void){
	
	Node *head;
	scanf("%s", s);
	pos = strlen(s)-1;
	head = createTree();	
	TruthTable(head);
	
	return 0;
} 
