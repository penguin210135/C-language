#include <iostream>
using namespace std;


class Node
{
   friend class Josephus;
   public:
        Node():next( NULL ){
        }
      	Node( const int &info ) : number( info ), next( NULL ){} //end ListNode constructor
   private:
      	Node *next;
        int number;
};

class Josephus
{
    public:
         Josephus();
         ~Josephus();
         Josephus(const int &);
         int kill() ; // return the survival's position

    private:
        void generatecircularlinkedList(const int &); // generate circular linked-list
        void generateFib(const int &); // generate a Fibonacci sequence table
        int sequence[50]; // store Fibonacci number
        int noOfPeople;
        Node *head;
};

void Josephus::generatecircularlinkedList(const int &num){
	Node *q = new Node(1);
	head = q;
	Node *tmp;
	for(int i=1;i<num;i++){
		tmp = new Node(i+1);
		q->next = tmp;
		q = tmp;
	}
	q->next = head;
}

void Josephus::generateFib(const int &num){
	int val;
	sequence[0] = 1;
	sequence[1] = 1;
	for(int i=2;i<num;i++){
		sequence[i] = (sequence[i-1] + sequence[i-2]);
	}
}

Josephus::Josephus(){
	for(int i=0;i<50;i++)	sequence[i] = 0;
	noOfPeople = 0;
	head = NULL;
}

Josephus::~Josephus(){
	delete head;
	for(int i=0;i<50;i++) sequence[i] = 0;
	
}
Josephus::Josephus(const int &num){
	generatecircularlinkedList(num);
	generateFib(num);
	noOfPeople = 0;
}

int Josephus::kill(){
	int num,pos=2,ans=0,peo;
	Node *tmp = head,*trash;
	
	peo = tmp->number;
	while(tmp->next->number != peo)	tmp = tmp->next;	//取得總人數
	
	peo = tmp->number;	//讓peo記錄總人數 
	if(tmp->number > 3) tmp->next = tmp->next->next->next;	//若總人數大於三人  先殺1 2  
	else return tmp->number;
	
	num = sequence[pos];
	
	while(!noOfPeople){
		num = num % (peo-pos) + peo - pos;	//要殺多少人 (peo-pos):剩多少人 ，多加一次是保險起見  
		for(int i=1;i<num;i++){
			tmp = tmp->next;
		}
		trash = tmp->next;
		tmp->next = tmp->next->next;
		delete trash;
		
		pos++;
		num = sequence[pos];
		
		//cout << tmp->number <<" " << num << endl;
		if(tmp->next == tmp){
			ans = tmp->number;
			noOfPeople = 1;
		}
		
	}
	
	return ans;
}
int main(){
	int numofpeople;

	while(cin>>numofpeople){
		Josephus Jose(numofpeople);
		int survival = Jose.kill();
		cout<<survival<<endl;
    }
}
