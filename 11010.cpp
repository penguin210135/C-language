#include <iostream>
#include <string>
using namespace std;
class ListNode
{
    friend class OWList; //make OWList a friend
    friend class TWList; //make TWList a friend

	public:
    	ListNode( const int &info ) //constructor
    	: data( info ), nextPtr( NULL )
    	{} //end ListNode constructor

	private:
    	int data; //data
    	ListNode *nextPtr; // next node in list
}; //end class ListNode


class OWList{
	public:
    	OWList();	//default constructor
    	~OWList(); 	//destructor
    	void insertAtFront( const int &value );    //insert node at front of list
    	void removeFromFront();   	 //remove node from front of list
    	bool isEmpty() const;	    //is List empty?
    	void print() const;	    //display contents of List
    

	protected:
    	ListNode *firstPtr; //pointer to first node
    	ListNode *lastPtr;  //pointer to last node
}; // end class List

class TWList:public OWList{
	public:
    	//default constructor
    TWList() :OWList()
    {
        /*It will still work correctly if you omit the constructor call of the base
          class in the above member initializer list. The compiler will invoke this
          default constructor of OWList implicitly.*/
    }
    //destructor
    ~TWList()
    {
        /*You don't need to delete the list again because the compiler
          will invoke the destructor of the base class OWList to do this.*/
    }
    
    //insert node at back of list
    void insertAtBack( const int &value );
    //delete node from back of list
    void removeFromBack();

};

OWList::OWList(){
	firstPtr = NULL;
	lastPtr = NULL;
}
OWList::~OWList(){
	firstPtr = NULL;
	lastPtr = NULL;
}

void OWList::insertAtFront(const int &value){
	ListNode *head = new ListNode(value);
	if(firstPtr==NULL){
		firstPtr = head;
		lastPtr = head;
	}else{
		head->nextPtr = firstPtr;
		firstPtr = head;
	}
	return;
}

void TWList::insertAtBack(const int &value){
	ListNode *final = new ListNode(value);
	if(lastPtr==NULL){
		firstPtr = final;
		lastPtr = final;
	}else{
		lastPtr->nextPtr = final;
		lastPtr = final;
	}
	
}

void OWList::removeFromFront(){
	if(firstPtr==NULL)	return;
	else if(lastPtr==firstPtr){
		firstPtr = NULL;
		lastPtr = NULL;
		return;
	}
	else{
		firstPtr = firstPtr->nextPtr;
		return;
	}
}

void TWList::removeFromBack(){
	if(lastPtr==NULL)	return;
	else if(lastPtr==firstPtr){
		firstPtr = NULL;
		lastPtr = NULL;
		return;
	}
	else{
		ListNode *tmp =  firstPtr;
		for(;tmp->nextPtr!=lastPtr;tmp=tmp->nextPtr){

		}
		tmp->nextPtr = NULL;
		lastPtr = tmp;
	}
}

void OWList::print()const{
	ListNode *tmp = firstPtr;
	//cout << firstPtr <<"  " <<lastPtr<<endl;
	
	if(firstPtr==NULL)	return;
	else{
		cout << tmp->data;
		tmp = tmp->nextPtr;
		while(tmp!=NULL){
			cout <<" " << tmp->data;
			tmp = tmp->nextPtr;
		}
		//cout<< endl;
		return;
	}
}

int main()
{
    TWList integerList;
    int command;
    int value; // store node value

    while (cin >> command)
    {
        switch(command)
        {
        case 1: // insert at beginning
            cin >> value;
            integerList.insertAtFront(value);
            break;
        case 2: // insert at end
            cin >> value;
            integerList.insertAtBack(value);
            break;
        case 3: // remove from beginning
            integerList.removeFromFront();
            break;
        case 4: // remove from end
            integerList.removeFromBack();
            break;
        }
        
    }
    integerList.print();
    cout<<endl;
}
