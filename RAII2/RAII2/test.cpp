#include<iostream>
using namespace std;

//shared_ptr,C++11�ṩ������ָ��

#if 0
//һ��������shared_ptr��

namespace lxy
{
	//��һ��ģ��shared_ptr��
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
			//ֻ�ж����������Դ�����Ҹö�����Ψһһ����Դ�����ߣ�����Ȩ���ͷŸ���Դ
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
		//��������
		shared_ptr(const shared_ptr<T>& sp)
			: _ptr(sp._ptr)
			, _pCount(sp._pCount)
		{
			if (_ptr)
				++*_pCount;
		}
		//��ֵ���������
		shared_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			if (this != &sp)//�ж��ǲ����Լ����Լ���ֵ
			{
				// 1. �����Դ�Ͽ���ϵ
				// this���ڲ������Լ�����Դ��Ҫ��sp��������Դ
				if (_ptr && 0 == --*_pCount)
				{
					// ��ǰ���������һ��ʹ����Դ�Ķ���
					delete _ptr;
					delete _pCount;
				}

				// 2. ��sp������Դ������
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
		int* _pCount;   //����ͳ����Դ����������
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
//�����Ľ�---->1���ͷ���Դ�ķ�ʽ������Ψһ�ġ�2��ʹ�̰߳�ȫ
// ����ɾ���������û����Կ�����Դ������ͷŲ���
//������ʹ�̸߳���ȫ
//�������̹߳�ϵ
// ���̣���˾
// �̣߳�Ա��


#include <mutex> //����ͷ�ļ�

template<class T>
//�ͷ���Դ��ʽģ����
class DFDef
{
public:
	//ͨ���º����ķ�ʽʵ��
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
	template<class T, class DF = DFDef<T>>//����Ĭ���ͷŷ�ʽ
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
				// 1. �����Դ�Ͽ���ϵ
				// this���ڲ������Լ�����Դ��Ҫ��sp��������Դ
				Release();

				// 2. ��sp������Դ������
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
				_pMutex->lock(); // ����
				++*_pCount;
				_pMutex->unlock();// ����
			}
		}

		int SubRef()
		{
			if (_pCount)
			{
				_pMutex->lock(); // ����
				--*_pCount;
				_pMutex->unlock();// ����
			}

			return *_pCount;
		}

		void Release()
		{
			if (_ptr && 0 == SubRef())
			{
				// ��ǰ���������һ��ʹ����Դ�Ķ���
				DF()(_ptr);
				delete _pCount;
			}
		}

	private:
		T* _ptr;
		int* _pCount;
		mutex* _pMutex;//������
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

// 1. shared_ptr�����ü����Ƿ�ȫ---mutex
// 2. shared_ptr��������û������Ƿ����̰߳�ȫ
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

#include <thread>  //�߳̿⣬�߳�ͷ�ļ�

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
//˫������ʽ

#include <memory>//�⺯������ָ��ͷ�ļ�

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
