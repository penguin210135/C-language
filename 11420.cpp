#include<iostream>
#include<cstdio>
#include<string>
#include<algorithm>
#ifndef FUNCTION_H
#define FUNCTION_H
#include<cstddef>
#include<iosfwd>

namespace oj
{
	class Memory_leak_count
	{
		friend void memory_leak_count_check();
		static unsigned count_;
	public:
		Memory_leak_count();
		~Memory_leak_count();
	};

	struct Int
	{
		int val;
		Int();
		Int(int val);
		Int(const Int &);
		operator int&()
		{
			return val;
		}
		operator int() const
		{
			return val;
		}
		Int& operator=(const Int &);
	private:
		Memory_leak_count count_;
	};

	typedef Int data_t;

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

		void pop_back();
		void push_back(data_t val);
		void insert(std::size_t pos,std::size_t count,data_t val);

		void reserve(std::size_t new_capacity);
		void resize(std::size_t new_size);

		~Vector();
	};
	/*overload*/ 
	std::ostream& operator<<(std::ostream &os,const Vector &vec);

	void memory_leak_count_check();
}

#endif
namespace oj
{
    Vector::Vector(): begin_{0}, last_{0}, end_{0} {}
    std::size_t Vector::capacity() const { return end_ - begin_; }
	std::size_t Vector::size() const { return last_ - begin_; }
	/*刪除*/ 
    void Vector::pop_back(){
        if( begin_ != last_ )
            last_--;
    }
    /*新增*/ 
    void Vector::push_back(data_t val) {
    	
        data_t size_ = last_ - begin_;
        data_t capacity_ = end_ - begin_;
        
        if( size_ >= capacity_ )
            reserve(std::max(capacity_+1, capacity_*3));
        begin_[last_-begin_] = val;
        last_++;
    }
    
    void Vector::insert(std::size_t pos,std::size_t count,data_t val){
        data_t size_ = last_ - begin_;
        data_t capacity_ = end_ - begin_;
        if( capacity_ < size_+ count )
            reserve(std::max(capacity_+capacity_/2, capacity_+(int)count));
        if( pos >= size_ ){
            while(count--) push_back(val);
        }
        else{
            for ( int i = last_-begin_+count-1 ; i >= (int)pos; i--){
                if( i < pos + count )
                    begin_[i] = val;
                else
                    begin_[i] = begin_[i-count];
            }
            last_ += count;
        }
    }
    void Vector::reserve(std::size_t new_capacity){
        if( end_ - begin_ < new_capacity ){
            data_t *new_begin_ = new data_t[new_capacity];
            for ( data_t i = 0; i < end_-begin_; i++){		/*複製*/
                new_begin_[i] = begin_[i];
            }
            delete[] begin_;								/*刪除原先的陣列*/
            last_ = new_begin_ + (last_-begin_);			
            end_ = new_begin_ + new_capacity;				/*讓last_ 和 end_ 符合新的差值*/
            begin_ = new_begin_;							/*給begin_ 新的開頭*/
        }
    }
    void Vector::resize(std::size_t new_size){
        data_t size_ = last_ - begin_;
        data_t capacity_ = end_ - begin_;
        if( size_ <= new_size ){
            if( capacity_ < new_size)
                reserve(new_size);
            while( new_size != size_ ){
                push_back(0);
                size_++;
            }
        }
        else{
            last_ = begin_ + new_size;
        }
    }
    Vector::~Vector(){
        delete[] begin_;
    }
}
namespace oj
{
	Int::Int()
		:val(0){}

	Int::Int(const int val_)
		:val(val_){}

	Int::Int(const Int &rhs)
		:val(rhs.val){}

	Int& Int::operator=(const Int &rhs)
	{
		val=rhs.val;
		return *this;
	}

	std::ostream& operator<<(std::ostream &os,const Vector &vec)
	{
		for(std::size_t i(0);i!=vec.size();++i)
			std::cout<<vec[i]<<' ';
		return os;
	}
}

int main()
{
	using namespace std;
	{
		oj::Vector v;
		string command;

		for(oj::data_t n;cin>>command;)
		{
			if(command=="pop_back")
			{
				v.pop_back();
				cout<<v<<endl;
			}
			else if(command=="push_back")
			{
				cin>>n;
				v.push_back(n);
				cout<<v<<endl;
			}
			else if(command=="insert")
			{
				size_t pos,count;
				cin>>pos>>count>>n;
				v.insert(pos,count,n);
				cout<<v<<endl;
			}
			else if(command=="capacity")
				cout<<v.capacity()<<endl;
			else if(command=="size")
				cout<<v.size()<<endl;
			else if(command=="reserve")
			{
				cin>>n;
				v.reserve(n);
				cout<<v<<endl;
			}
			else if(command=="resize")
			{
				cin>>n;
				v.resize(n);
				cout<<v<<endl;
			}
		}
		cout<<v<<endl;
	}
	oj::memory_leak_count_check();
	return 0;
}

namespace oj
{
	Memory_leak_count::Memory_leak_count()
	{
		++count_;
	}

	Memory_leak_count::~Memory_leak_count()
	{
		--count_;
	}

	unsigned Memory_leak_count::count_(0);

	void memory_leak_count_check()
	{
		if(Memory_leak_count::count_!=0)
			std::cout<<"memory leak"<<std::endl;
	}
}
