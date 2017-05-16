#include<algorithm>
#include<cstddef>
#include<cstdlib>
#include<iostream>
#include<new>
#include<stdexcept>
#include<string>
#include<utility>

namespace oj
{
	class List
	{
		friend std::ostream& operator<<(std::ostream &,const List &);
	public:
		typedef std::size_t size_type;
		typedef int value_type;
		typedef const value_type &const_reference;
	private:
		struct Node
		{
			Node *next;
			Node *prev;
			value_type data;
		};
		Node *begin_;
		
	public:
		List();
		~List();

		void erase(size_type pos);
		void insert(size_type pos,const_reference val);
	};

	std::ostream& operator<<(std::ostream &,const List &);
}

//you don't have to pay attention on these 4 functions
void* operator new(std::size_t count);
void* operator new[](std::size_t count);
void operator delete(void *p) noexcept;
void operator delete[](void *p) noexcept;

namespace
{
	extern std::size_t current_memory_size;
	extern std::size_t peak_current_memory_size;
	extern bool monitor;
}

namespace oj
{
	List::List(){
		begin_ = NULL;
	}
	List::~List(){
		Node *np=begin_;
        while(np){
            Node *tmp=np;
            np=np->next;
            delete tmp;
        }
        return;
	} 

	void List::insert(size_type pos,const_reference val){
	
		if(begin_ == NULL){
			Node *node = new Node{NULL,NULL,val};
			begin_ = node;
			return;
		}
		if(pos==0){
			Node *node = new Node{begin_,NULL,val};
			begin_->prev = node;
			begin_ = node;
			return;
		}else{
			Node *tmp =begin_;
			for(size_type c = 1;c<pos && tmp!=NULL ;c++){
				tmp = tmp->next;
			}
			Node *node = new Node{tmp->next,tmp->prev,val};
			tmp->next = node;
		}
	}

	void List::erase(size_type pos){
		Node *tmp = begin_,*np;
		if(tmp == NULL){
			return ;
		}
		if(pos==0){
			begin_ = tmp->next;
			delete tmp;
			return;
		}else{
			for(size_type c = 1; c<pos;c++){
				if(tmp->next == NULL)	return;
				tmp = tmp->next;
			}
			if(tmp->next == NULL)	return;
			np = tmp->next->next;
			delete tmp->next;
			tmp->next = np;
			return ;
		}
	}

	std::ostream& operator<<(std::ostream &str,const oj::List &list){
		List::Node *tmp= list.begin_;
		if(tmp == NULL){
			return str;
		}
		else{
			while(tmp!=NULL){
				std::cout<<tmp->data<<" ";
				tmp = tmp->next;
			}
			return str;
		}
	}
}


int main()
{
	using namespace std;
	{
		monitor=true;
		oj::List lst;
		for(string command;cin>>command;)
			if(command=="erase")
			{
				oj::List::size_type pos;
				cin>>pos;
				lst.erase(pos);
			}
			else if(command=="insert")
			{
				oj::List::size_type pos;
				oj::List::value_type val;
				cin>>pos>>val;
				lst.insert(pos,val);
			}
			else if(command=="show")
						cout<<lst<<endl;
	}
	monitor=false;
	if(current_memory_size!=0)
		cout<<"memory leak (leak "<<current_memory_size<<" byte)"<<endl;
	//cout<<"maximum memory usage "<<peak_current_memory_size<<" byte"<<endl;
}

namespace
{
	std::size_t current_memory_size(0);
	std::size_t peak_current_memory_size(0);
	bool monitor(false);
	const std::size_t limited_memory_size(1536);	//byte
	std::size_t memory_status_index(0);
	std::pair<void *,std::size_t> memory_status[limited_memory_size]{};

	void* for_new(const std::size_t count)
	{
		if(monitor)
		{
			const auto left_size(limited_memory_size-current_memory_size);
			if(left_size&&count<=left_size)
			{
				current_memory_size+=count;
				peak_current_memory_size=std::max(peak_current_memory_size,current_memory_size);
				if(void *p=malloc(count))
				{
					while(memory_status[memory_status_index].first)
						memory_status_index=(memory_status_index+1)%limited_memory_size;
					memory_status[memory_status_index]=std::pair<void *,std::size_t>(p,count);
					return p;
				}
			}
		}
		else
			if(void *p=malloc(count))
				return p;
		throw std::bad_alloc();
	}

	void for_delete(void *p)
	{
		if(p)
			if(monitor)
			{
				while(memory_status[memory_status_index].first!=p)
					memory_status_index=(memory_status_index+1)%limited_memory_size;
				free(p);
				current_memory_size-=memory_status[memory_status_index].second;
				memory_status[memory_status_index]=std::pair<void *,std::size_t>(nullptr,0);
			}
			else
				free(p);
	}
}

void* operator new(std::size_t count)
{
	return for_new(count);
}

void* operator new[](std::size_t count)
{
	return for_new(count);
}

void operator delete(void *p) noexcept
{
	for_delete(p);
}

void operator delete[](void *p) noexcept
{
	for_delete(p);
}
