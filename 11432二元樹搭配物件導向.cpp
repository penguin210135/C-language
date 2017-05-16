#include <iostream>
#include <string.h>
#include <math.h>
using namespace std;

class BST{
public:
    BST():Height(0){}
    virtual ~BST() {}
    virtual void insert(const int &) = 0;
    virtual bool search(const int &) const = 0;
    virtual void print() const = 0;
    int height() const { return Height; }// An empty tree has height of 0. A tree with only root node has height of 1.

protected:
    int Height;
};

class Array_BST : public BST{
public:
    Array_BST();
    virtual ~Array_BST() {}
    virtual void insert(const int &) override; //root node is stored at index 1.
    virtual bool search(const int &) const override;
    virtual void print() const override{
        int k = pow(2, height());
        for (int i = 1; i <= k-1; i++) {
            if (array[i] != 0)
                cout << array[i] << " ";
        }
    }

private:
    int array[1025];
};


class ListNode{
    friend class List_BST; //make List_BST a friend

public:
    ListNode(const int &info):key( info ),left( NULL ),right( NULL ) //constructor
    {
    }//end ListNode constructor

private:
    int key;
    ListNode *left;
    ListNode *right;
};//end class ListNode

class List_BST : public BST{
public:
    List_BST();
    virtual ~List_BST()
    {
        deleteTree(root);
    }
    virtual void insert(const int &) override;
    virtual bool search(const int &) const override;
    virtual void print() const override{
        int i;
        for(i = 1; i <= Height; i++){
            printGivenLevel(root, i);
        }
    }

private:
    ListNode *root;
    // private member functions
    ListNode* createLeaf(int key) const; //new a ListNode and return its address
    /* clean a tree.*/
    void deleteTree(ListNode *root);

    void printGivenLevel(ListNode* Ptr, int level) const {
        if (Ptr == NULL)
            return;
        if (level == 1)
            cout << Ptr->key << " ";
        else if (level > 1)
        {
            printGivenLevel(Ptr->left, level-1);
            printGivenLevel(Ptr->right, level-1);
        }
    }
};

Array_BST::Array_BST(){
	for(int i=0;i<1025;i++)	array[i] = 0;
}

void Array_BST::insert(const int &value){
	if(array[1] == 0 ){
		array[1] = value;
		Height = 1;
		return;
	}else{
		int pos = 1,End = 0,level = 0;
		while(!End){
			
			if(array[pos] == 0){
				array[pos] = value;
				End = 1;
			}
			
			if(value >= array[pos]){
				pos = pos*2 +1;
				level++;
			}else{
				pos = pos*2;
				level++;
			}
		}
		Height = max(Height,level);
	}
}

bool Array_BST::search(const int &value)const{
	for(auto c : array){
		if(c == value)	return true;
	}
	return false;
}

List_BST::List_BST(){
	root = new ListNode(0);
}

void List_BST::insert(const int &value){
	ListNode *tmp = new ListNode(value);
	if(root->key == 0){
		root = tmp;
		Height = 1;
	}else{
		ListNode *cmp = root;
		int End = 0,level = 0;
		while(!End){
			level++;
			if(value >= cmp->key){
				if(cmp->right == NULL){
					cmp->right = tmp;
					End = 1;
				}
				else cmp = cmp->right;
			}else{
				if(cmp->left == NULL){
					cmp->left = tmp;
					End = 1;
				}else cmp = cmp->left;
			}

		}
		Height = level+1;
	} 
}

void List_BST::deleteTree(ListNode *root){
	if(root == NULL)	return;
	
	deleteTree(root->left);
	deleteTree(root->right);
	delete root;
}

bool List_BST::search(const int &value)const{
	if(root==NULL)	return false;
	
	ListNode *cmp = root;
	int Find = 0;
	while(!Find){
		if(cmp->key == value){
			Find = 1;
			return true;
		}
		
		else if(value >= cmp->key){
			cmp = cmp->right;
			if(cmp==NULL)	return false;	
		}else{
			cmp = cmp->left;
			if(cmp==NULL)	return false;
		}
		
	}
}

void BSTManipulator(BST& bstobj1,BST& bstobj2, char cmd ){
    int n;
    if (cmd == 'I') {
        cin >> n;
        bstobj1.insert(n);
        bstobj2.insert(n);
    }else if (cmd == 'S'){
        cin >> n;
        if (bstobj1.search(n)) {
            cout << "yes" << endl;
        }else{
            cout << "no" << endl;
        }

        if (bstobj2.search(n)) {
            cout << "yes" << endl;
        }else{
            cout << "no" << endl;
        }

    }else if (cmd == 'H'){
        cout << bstobj1.height() << endl;;
        cout << bstobj2.height() << endl;;

    }else if (cmd == 'P'){
        bstobj1.print();
        cout << endl;
        bstobj2.print();
        cout << endl;
    }
}
int main(){
    Array_BST A_bst;
    List_BST B_bst;
    char cmd;

    while (cin >> cmd)
        BSTManipulator(A_bst, B_bst, cmd);

    return 0;
}
