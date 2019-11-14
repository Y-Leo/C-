#include <iostream>
using namespace std;

/*
// C/C++
bool Test1()
{
// �ɹ�����true��ʧ�ܷ���false
return false;
}

void Test2()
{
// ..

// ����˴������Ƿ����
throw 1;
}


// �������ԭ��ָ̬��(T*)������Դ�����������Դй©�ķ��վͱȽϴ�

void TestFunc()
{
int* p = new int[10];
FILE* pf = fopen("2222.txt", "rb");
if (nullptr == pf)
{
delete[] p;
return;
}

// ...
if (!Test1())
{
delete[] p;
fclose(pf);
return;
}

try
{
Test2();
}
catch (...)
{
delete[] p;
fclose(pf);
throw;
}

// ...

delete[] p;
fclose(pf);
}
*/

// �ܷ��ó������Ҹ�֪������������ʱ�Զ��ͷ���Դ

// RAII---��Դ��ȡ����ʼ��
//  �ڹ��캯���з���Դ
//  �������������ͷ���Դ


#if 0
// ����ָ��ļ�ģ��ʵ��
template<class T>
class SmartPtr
{
public:
	// RAII: ����--->�û����ÿ���ʲô�Ǹ��ͷ���Դ
	//              ���ͷ���Դ��ʵ�ʽ���������
	SmartPtr(T* ptr = nullptr)
		: _ptr(ptr)
	{
		cout << "SmartPtr(T*)" << endl;
	}

	~SmartPtr()
	{
		cout << "~SmartPtr()" << endl;

		if (_ptr)
		{
			delete _ptr;
			_ptr = nullptr;
		}
	}

	// �ø���Ķ���߱�ָ��������Ϊ
	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}
private:
	T* _ptr;
};

struct A
{
	int a;
	int b;
	int c;
};

void TestSmartPtr()
{
	SmartPtr<int> sp1(new int);
	*sp1 = 10;
	// sp1

	SmartPtr<A> sp2(new A);
	sp2->a = 1;
	sp2->b = 2;
	sp2->c = 3;
}

int main()
{
	TestSmartPtr();
	return 0;
}
#endif

#if 0
// ȱ��: ǳ����
// ǰ��String-->����ǳ��������--->���
// ���ǵ�Ŀ�������Ե����飬�����ǰ���������
// ���ܲ�������ķ�ʽ���н��
template<class T>
class SmartPtr
{
public:
	// RAII: ����--->�û����ÿ���ʲô�Ǹ��ͷ���Դ
	//              ���ͷ���Դ��ʵ�ʽ���������
	SmartPtr(T* ptr = nullptr)
		: _ptr(ptr)
	{
		cout << "SmartPtr(T*)" << endl;
	}

	~SmartPtr()
	{
		cout << "~SmartPtr()" << endl;

		if (_ptr)
		{
			delete _ptr;
			_ptr = nullptr;
		}
	}

	// �ø���Ķ���߱�ָ��������Ϊ
	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}
private:
	T* _ptr;
};

void TestSmartPtr()
{
	int a = 10;
	int* pa = &a;
	int* pb(pa);

	SmartPtr<int> sp1(new int);
	SmartPtr<int> sp2(sp1);  // ʹ��sp1��������sp2
}


int main()
{
	TestSmartPtr();
	return 0;
}
#endif

// ���в�ͬ���͵�����ָ�룺
// RAII: ��Դ�����Զ��ͷ�
// ��������ָ�����Ƶ���Ϊ��operator*()/operator->()
// ǳ�����Ľ����ʽ


#if 0
// c++98 ---- 
// auto_ptr
// ���ǳ������ʽ����Դת��--->��ǰ����
namespace lxy
{
	template<class T>
	class auto_ptr
	{
	public:
		// RAII
		auto_ptr(T* ptr = nullptr)
			: _ptr(ptr)
		{}

		~auto_ptr()
		{
			if (_ptr)
			{
				delete _ptr;
				_ptr = nullptr;
			}
		}

		// ����ָ��������Ϊ
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		// ���ǳ����
		auto_ptr(auto_ptr<T>& ap)
			: _ptr(ap._ptr)
		{
			ap._ptr = nullptr;
		}

		// ap3 = ap2;
		auto_ptr<T>& operator=(auto_ptr<T>& ap)
		{
			if (this != &ap)
			{
				// �����ǰ���������Դ�����ͷ�
				if (_ptr)
					delete _ptr;

				_ptr = ap._ptr;  // ��Դת��
				ap._ptr = nullptr;  // ap����Դ�Ͽ���ϵ
			}

			return *this;
		}
	private:
		T* _ptr;
	};
}
#endif

#if 0
// ����bool _owner: ����ͷŶ���Դ���ͷŵ�Ȩ��
// �Ľ�֮���auto_ptr��ʵ��ԭ��:
// RAII + operator*()/operator->() + ���ǳ��������Դ����Ȩ��(����Դ�ͷŵ�Ȩ��)ת��
namespace lxy
{
	template<class T>
	class auto_ptr
	{
	public:
		// RAII
		auto_ptr(T* ptr = nullptr)
			: _ptr(ptr)
			, _owner(false)
		{
			if (_ptr)
				_owner = true;
		}

		~auto_ptr()
		{
			if (_ptr && _owner)
			{
				delete _ptr;
				_ptr = nullptr;
			}
		}

		// ����ָ��������Ϊ
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		// ���ǳ����
		auto_ptr(const auto_ptr<T>& ap)
			: _ptr(ap._ptr)
			, _owner(ap._owner)
		{
			ap._owner = false;
		}

		// ap3 = ap2;
		auto_ptr<T>& operator=(const auto_ptr<T>& ap)
		{
			if (this != &ap)
			{
				// �����ǰ���������Դ�����ͷ�
				if (_ptr && _owner)
					delete _ptr;

				_ptr = ap._ptr;  // ��Դת��
				_owner = ap._owner;
				ap._owner = false;  // ap�����ͷ�Ȩ��--->ת�Ƹ�this
			}

			return *this;
		}
	private:
		T* _ptr;
		mutable bool _owner;
	};
}


void TestAutoPtr1()
{
	int a = 10;
	int* pa = &a;
	int* pb = pa;

	*pa = 100;
	*pb = 200;

	lxy::auto_ptr<int> ap1(new int);
	lxy::auto_ptr<int> ap2(ap1);

	// ��Դת�Ƶ�ȱ�ݣ� ap1�Ѻ���Դ�Ͽ���ϵ�������ٲ�����Դ
	*ap2 = 200;
	*ap1 = 100;

	lxy::auto_ptr<int> ap3(new int);
	ap3 = ap2;
}

// ��_owner�汾��auto_ptrȱ�ݣ����ܻ����Ұָ��--�����´������
void TestAutoPtr2()
{
	lxy::auto_ptr<int> ap1(new int);

	if (true)
	{
		lxy::auto_ptr<int> ap2(ap1);
		*ap2 = 20;
	}

	// ap1��Ұָ��
	*ap1 = 10;
}

int main()
{
	// TestAutoPtr1();

	TestAutoPtr2();
	return 0;
}

#endif


#if 0

// ���飺ʲô����¶���Ҫʹ��auto_ptr

#include <memory>


int main()
{
	auto_ptr<int> ap1(new int);
	auto_ptr<int> ap2(ap1);
	return 0;
}
#endif

// C++11: auto_ptr--->��������Դת��ʵ�ֵ�
// �ṩ�����׵�����ָ��

// ����ָ��ԭ��RAII(�Զ��ͷ���Դ) + operator*()/operator->()(����ָ��������Ϊ) + �ṩ���ǳ������ʽ

// ǳ��������ԭ��Ĭ�Ͽ������캯�� �� Ĭ�ϵĸ�ֵ���������

// unique_ptr

#if 0
#include <memory>

int main()
{
	unique_ptr<int> up1(new int);
	//unique_ptr<int> up2(up1);

	unique_ptr<int> up3(new int);
	// up3 = up1;

	return 0;
}
#endif


#if 0
// ���ǳ������ʽ����Դ��ռ(ֻ��һ������ʹ�ã����ܹ���)--->ʵ�֣���ֹ���ÿ�������͸�ֵ���������
namespace bite
{
	template<class T>
	class unique_ptr
	{
	public:
		// RAII
		unique_ptr(T* ptr = nullptr)
			: _ptr(ptr)
		{}

		~unique_ptr()
		{
			if (_ptr)
			{
				delete _ptr; // �ͷ���Դ�ķ�ʽ�̶����ˣ�ֻ�ܹ���new����Դ�����ܴ����������͵���Դ
				_ptr = nullptr;
			}
		}

		// ����ָ��������Ϊ
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		// ���ǳ��������ֹ���ÿ������캯���͸�ֵ���������

		// C++98:
		/*
		private:  // ���������Ȩ��һ��Ҫ���ó�private��ԭ��Ϊ�˷�ֹ�û��Լ������ⶨ��
		unique_ptr(const unique_ptr<T>& up);
		unique_ptr<T>& operator=(const unique_ptr<T>&);
		*/

		// C++11 ��ֹ���ÿ�������͸�ֵ���������
		unique_ptr(const unique_ptr<T>&) = delete;  // 1. �ͷ�new�Ŀռ�  2.Ĭ�ϳ�Ա���� = delete �� ���߱�������ɾ����Ĭ�ϳ�Ա����
		unique_ptr<T>& operator=(const unique_ptr<T>&) = delete;
	private:
		T* _ptr;
	};

	// �û����ⲿʵ��
	// 	template<class T>
	// 	unique_ptr<T>::unique_ptr(const unique_ptr<T>& up)
	// 	{}
}




void TestUniquePtr()
{
	lxy::unique_ptr<int> up1(new int);
	lxy::unique_ptr<int> up2(up1);

	lxy::unique_ptr<int> up3(new int);
	//up3 = up1;
}
#endif

#if 0
#include <memory>
#include <malloc.h>

int main()
{
	unique_ptr<int> up1(new int);
	unique_ptr<int> up2((int*)malloc(sizeof(int)));
	return 0;
}
#endif

template<class T>
class DFDef
{
public:
	void operator()(T*& p)
	{
		if (p)
		{
			delete p;
			p = nullptr;
		}
	}
};

template<class T>
class Free
{
public:
	void operator()(T*& p)
	{
		if (p)
		{
			free(p);
			p = nullptr;
		}
	}
};


class FClose
{
public:
	void operator()(FILE*& p)
	{
		if (p)
		{
			fclose(p);
			p = nullptr;
		}
	}
};

namespace lxy
{
	template<class T, class DF = DFDef<T>>
	class unique_ptr
	{
	public:
		// RAII
		unique_ptr(T* ptr = nullptr)
			: _ptr(ptr)
		{}

		~unique_ptr()
		{
			if (_ptr)
			{
				//delete _ptr; // �ͷ���Դ�ķ�ʽ�̶����ˣ�ֻ�ܹ���new����Դ�����ܴ����������͵���Դ
				//DF()(_ptr);
				DF df;
				df(_ptr);
				_ptr = nullptr;
			}
		}

		// ����ָ��������Ϊ
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		unique_ptr(const unique_ptr<T>&) = delete;  // 1. �ͷ�new�Ŀռ�  2.Ĭ�ϳ�Ա���� = delete �� ���߱�������ɾ����Ĭ�ϳ�Ա����
		unique_ptr<T>& operator=(const unique_ptr<T>&) = delete;

	private:
		T* _ptr;
	};
}

void TestUniquePtr()
{
	lxy::unique_ptr<int> up1(new int);
	lxy::unique_ptr<int, Free<int>> up2((int*)malloc(sizeof(int)));
	lxy::unique_ptr<FILE, FClose> up3(fopen("1.txt", "w"));
}

int main()
{
	TestUniquePtr();
	return 0;
}