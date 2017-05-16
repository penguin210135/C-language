#include<iostream>
#include<string.h>
using namespace std;

class ListNode
{
    friend class List_queue; //make List_queue a friend 夥伴函數，所以在queue裡可以用Node 
    public:
        ListNode( const int &info ) : data( info ), nextPtr( NULL ), prevPtr( NULL ) {} //end ListNode constructor
    private:
        int data; //data
        ListNode *nextPtr; // next node in list
        ListNode *prevPtr;
};

class List_queue {
    public:
        List_queue();
        ~List_queue();
        void enqueue(const int &);
        void dequeue();
        void print();
    private:
        ListNode *head;
        ListNode *tail;
};
List_queue::List_queue(){
	head = NULL;
	tail = NULL;	
}

List_queue::~List_queue(){
	head = NULL;
	tail = NULL;
}


void List_queue::enqueue(const int &val){
	ListNode *tmp = new ListNode(val);
	if(head==NULL){
		head = tmp;
		tail = tmp;
	}
	else{
		tail->nextPtr 	= tmp;
		tmp->prevPtr 	= tail;
		tail = tmp;
	}
}

void List_queue::dequeue(){
	if(head==NULL){
		return;
	}else{
		if(head->nextPtr != NULL)	head->nextPtr->prevPtr = NULL;
		head = head->nextPtr;
	}
}

void List_queue::print(){
	ListNode *t = head;
	if(t!=NULL){
		cout << t->data;
		t = t->nextPtr;	
	} 
	while(t!=NULL){
		cout <<" "<< t->data;
		t = t->nextPtr;
	}
}
int main(){
    List_queue L_queue;
    char command[10];
    int n;
    while(cin>>command){

        if(strcmp(command,"dequeue")==0){
            L_queue.dequeue();
        }else if(strcmp(command,"enqueue")==0){
            cin >> n;
            L_queue.enqueue(n);
        }else if(strcmp(command, "print") == 0){
            L_queue.print();
            cout << endl;
        }
    }
    return 0;
}
