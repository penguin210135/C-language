#include<cstddef>
#include<cstdlib>
#include<iostream>
#include<iosfwd>
#include<new>
#include<stdexcept>
#include<string>
#include<utility>


namespace oj
{
	//this is only for OJ
	//do not design class like this (this is a very bad coding style)
	class Employee
	{
		friend struct God;
		static unsigned ID_;
		const std::string name_;
		const unsigned id_;
		Employee(const std::string &name);
	public:
		Employee(const Employee &);
	};

	typedef Employee data_t;

	class Vector
	{
		data_t *begin_;	//begin of array
		data_t *end_;	//end of array
		data_t *last_;	//end of current size
	public:
		Vector();
		
		std::size_t capacity() const;
		std::size_t size() const;
		
		inline data_t& operator[](const std::size_t pos)
		{
			return begin_[pos];
		}
		inline const data_t& operator[](const std::size_t pos) const
		{
			return begin_[pos];
		}
		
		void push_back(const data_t &val);
		void erase(std::size_t pos);
		void reserve(std::size_t new_capacity);
		
		~Vector();
	};

	struct God;
	void add_employee(Vector &vec,const std::string &name);
	void print(const Vector &vec);
	void quit(Vector &vec,unsigned id);
	void quit(Vector &vec,const std::string &name);
}

void* operator new(std::size_t count);
void* operator new[](std::size_t count);
void operator delete(void *p) noexcept;
void operator delete[](void *p) noexcept;

namespace
{
	std::size_t current_memory_size(0);
	bool monitor(false);
}

namespace oj
{
	Employee::Employee(const Employee &rhs)
		:name_(rhs.name_),id_(rhs.id_){}

	unsigned Employee::ID_(0);
}

int main()
{
	using namespace std;
	{
		monitor=true;
		oj::Vector vec;
		for(string command,name;cin>>command;)
		{
			if(command=="recruit")
			{
				cin>>name;
				add_employee(vec,name);
			}
			else if(command=="quit")
			{
				unsigned id;
				cin>>id;
				if(id)
				{
					cin>>id;
					quit(vec,id);
				}
				else
				{
					cin>>name;
					quit(vec,name);
				}
			}
			else if(command=="reserve")
			{
				size_t size;
				cin>>size;
				vec.reserve(size);
			}
			else if(command=="capacity")
				cout<<vec.capacity()<<endl;
			else if(command=="size")
				cout<<vec.size()<<endl;
			print(vec);
		}
	}
	monitor=false;
	if(current_memory_size!=0)
		cout<<"memory leak (leak "<<current_memory_size<<" byte)"<<endl;
}

namespace
{
	const std::size_t limited_memory_size(3072);	//byte
	std::size_t memory_status_index(0);
	std::pair<void *,std::size_t> memory_status[limited_memory_size]{};

	void *for_new(const std::size_t count)
	{
		if(monitor)
		{
			const auto left_size(limited_memory_size-current_memory_size);
			if(left_size&&count<=left_size)
			{
				current_memory_size+=count;
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
