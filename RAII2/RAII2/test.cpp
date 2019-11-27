#include<iostream>
using namespace std;

//shared_ptr,C++11提供的智能指针

#if 0
//一：基本的shared_ptr类

namespace lxy
{
	//给一个模板shared_ptr类
	template<class T>
	class shared_ptr
	{
	public:
		shared_ptr(T* ptr = nullptr)
			: _ptr(ptr)
			, _pCount(nullptr)  
		{
			if (_ptr)
				_pCount = new int(1);
		}

		~shared_ptr()
		{
			//只有对象管理了资源，并且该对象是唯一一个资源管理者，才有权限释放该资源
			if (_ptr && 0 == --*_pCount)
			{
				delete _ptr;
				delete _pCount;
			}
		}

		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}
		//拷贝构造
		shared_ptr(const shared_ptr<T>& sp)
			: _ptr(sp._ptr)
			, _pCount(sp._pCount)
		{
			if (_ptr)
				++*_pCount;
		}
		//赋值运算符重载
		shared_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			if (this != &sp)//判断是不是自己给自己赋值
			{
				// 1. 与旧资源断开联系
				// this现在不是用自己的资源，要与sp对象共享资源
				if (_ptr && 0 == --*_pCount)
				{
					// 当前对象是最后一个使用资源的对象
					delete _ptr;
					delete _pCount;
				}

				// 2. 与sp共享资源及计数
				_ptr = sp._ptr;
				_pCount = sp._pCount;
				if (_ptr)
					++*_pCount;

			}

			return *this;
		}

		int use_count()
		{
			return *_pCount;
		}

	private:
		T* _ptr;
		int* _pCount;   //用来统计资源管理者数量
	};
}


void TestShradPtr()
{
	lxy::shared_ptr<int> sp1(new int);
	cout << sp1.use_count() << endl;

	lxy::shared_ptr<int> sp2(sp1);
	cout << sp1.use_count() << endl;
	cout << sp2.use_count() << endl;


	lxy::shared_ptr<int> sp3(new int);
	cout << sp3.use_count() << endl;

	lxy::shared_ptr<int> sp4(sp3);
	cout << sp3.use_count() << endl;
	cout << sp4.use_count() << endl;

	sp3 = sp2;
	cout << sp2.use_count() << endl;
	cout << sp3.use_count() << endl;

	sp4 = sp2;
	cout << sp2.use_count() << endl;
	cout << sp4.use_count() << endl;
}


int main()
{
	TestShradPtr();
	return 0;
}
#endif


#if 0
//二：改进---->1、释放资源的方式不再是唯一的。2、使线程安全
// 定制删除器：让用户可以控制资源具体的释放操作
//加锁，使线程更安全
//进程与线程关系
// 进程：公司
// 线程：员工


#include <mutex> //锁，头文件

template<class T>
//释放资源方式模板类
class DFDef
{
public:
	//通过仿函数的方式实现
	void operator()(T*& ptr)
	{
		if (ptr)
		{
			delete ptr;
			ptr = nullptr;
		}
	}
};

namespace lxy
{
	template<class T, class DF = DFDef<T>>//给出默认释放方式
	class shared_ptr
	{
	public:
		shared_ptr(T* ptr = nullptr)
			: _ptr(ptr)
			, _pCount(nullptr)
			, _pMutex(nullptr)
		{
			if (_ptr)
			{
				_pCount = new int(1);
				_pMutex = new mutex;
			}

		}

		~shared_ptr()
		{
			Release();
		}

		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		shared_ptr(const shared_ptr<T>& sp)
			: _ptr(sp._ptr)
			, _pCount(sp._pCount)
			, _pMutex(sp._pMutex)
		{
			AddRef();
		}

		shared_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			if (this != &sp)
			{
				// 1. 与旧资源断开联系
				// this现在不是用自己的资源，要与sp对象共享资源
				Release();

				// 2. 与sp共享资源及计数
				_ptr = sp._ptr;
				_pCount = sp._pCount;
				if (_ptr)
					AddRef();
			}

			return *this;
		}

		int use_count()
		{
			return *_pCount;
		}

	private:
		void AddRef()
		{
			if (_pCount)
			{
				_pMutex->lock(); // 加锁
				++*_pCount;
				_pMutex->unlock();// 解锁
			}
		}

		int SubRef()
		{
			if (_pCount)
			{
				_pMutex->lock(); // 加锁
				--*_pCount;
				_pMutex->unlock();// 解锁
			}

			return *_pCount;
		}

		void Release()
		{
			if (_ptr && 0 == SubRef())
			{
				// 当前对象是最后一个使用资源的对象
				DF()(_ptr);
				delete _pCount;
			}
		}

	private:
		T* _ptr;
		int* _pCount;
		mutex* _pMutex;//互斥锁
	};
}

struct Date
{
	Date()
	{
		_year = _month = _day = 0;
	}

	int _year;
	int _month;
	int _day;
};

// 1. shared_ptr的引用计数是否安全---mutex
// 2. shared_ptr所管理的用户数据是否是线程安全
void SharePtrFunc(lxy::shared_ptr<Date>& sp, size_t n)
{
	for (size_t i = 0; i < n; ++i)
	{
		lxy::shared_ptr<Date> copy(sp);

		copy->_year++;
		copy->_month++;
		copy->_day++;
	}
}

#include <thread>  //线程库，线程头文件

int main()
{
	lxy::shared_ptr<Date> sp(new Date);

	thread t1(SharePtrFunc, sp, 100000);
	thread t2(SharePtrFunc, sp, 100000);

	t1.join();
	t2.join();
	return 0;
}
#endif

#if 1
//双向链表方式

#include <memory>//库函数智能指针头文件

// struct ListNode
// {
// 	ListNode* _pPre;
// 	ListNode* _pNext;
// 	int _data;
// };

struct ListNode
{
	ListNode(int data = 0)
		: pre(nullptr)
		, next(nullptr)
		, _data(data)
	{
		cout << "ListNode(int):" << this << endl;
	}

	~ListNode()
	{
		cout << "~ListNode():" << this << endl;
	}

	shared_ptr<ListNode> pre;
	shared_ptr<ListNode> next;
	int _data;
};

void TestListNode()
{
	shared_ptr<ListNode> sp1(new ListNode(10));
	shared_ptr<ListNode> sp2(new ListNode(20));

	cout << sp1.use_count() << endl;
	cout << sp2.use_count() << endl;

	sp1->next = sp2;
	sp2->pre = sp1;

	cout << sp1.use_count() << endl;
	cout << sp2.use_count() << endl;
}

int main()
{
	TestListNode();
	return 0;
}

#endif
