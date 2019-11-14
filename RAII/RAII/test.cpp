#include <iostream>
using namespace std;

/*
// C/C++
bool Test1()
{
// 成功返回true，失败返回false
return false;
}

void Test2()
{
// ..

// 假设此处遇到非法情况
throw 1;
}


// 如果采用原生态指针(T*)管理资源，程序存在资源泄漏的风险就比较大

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

// 能否让程序自我感知：对象在销毁时自动释放资源

// RAII---资源获取即初始化
//  在构造函数中放资源
//  在析构函数中释放资源


#if 0
// 智能指针的简单模拟实现
template<class T>
class SmartPtr
{
public:
	// RAII: 作用--->用户不用考虑什么是该释放资源
	//              把释放资源的实际交给编译器
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

	// 让该类的对象具备指针类似行为
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
// 缺陷: 浅拷贝
// 前面String-->引出浅拷贝问题--->深拷贝
// 我们的目标是做对的事情，而不是把事情做对
// 不能采用深拷贝的方式进行解决
template<class T>
class SmartPtr
{
public:
	// RAII: 作用--->用户不用考虑什么是该释放资源
	//              把释放资源的实际交给编译器
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

	// 让该类的对象具备指针类似行为
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
	SmartPtr<int> sp2(sp1);  // 使用sp1拷贝构造sp2
}


int main()
{
	TestSmartPtr();
	return 0;
}
#endif

// 所有不同类型的智能指针：
// RAII: 资源可以自动释放
// 类对象具有指针类似的行为：operator*()/operator->()
// 浅拷贝的解决方式


#if 0
// c++98 ---- 
// auto_ptr
// 解决浅拷贝方式：资源转移--->当前对象
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

		// 具有指针类似行为
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		// 解决浅拷贝
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
				// 如果当前对象管理资源，先释放
				if (_ptr)
					delete _ptr;

				_ptr = ap._ptr;  // 资源转移
				ap._ptr = nullptr;  // ap与资源断开联系
			}

			return *this;
		}
	private:
		T* _ptr;
	};
}
#endif

#if 0
// 增加bool _owner: 标记释放对资源有释放的权利
// 改进之后的auto_ptr的实现原理:
// RAII + operator*()/operator->() + 解决浅拷贝：资源管理权限(对资源释放的权利)转移
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

		// 具有指针类似行为
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		// 解决浅拷贝
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
				// 如果当前对象管理资源，先释放
				if (_ptr && _owner)
					delete _ptr;

				_ptr = ap._ptr;  // 资源转移
				_owner = ap._owner;
				ap._owner = false;  // ap将其释放权利--->转移给this
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

	// 资源转移的缺陷： ap1已和资源断开联系，不能再操作资源
	*ap2 = 200;
	*ap1 = 100;

	lxy::auto_ptr<int> ap3(new int);
	ap3 = ap2;
}

// 带_owner版本的auto_ptr缺陷：可能会造成野指针--而导致代码崩溃
void TestAutoPtr2()
{
	lxy::auto_ptr<int> ap1(new int);

	if (true)
	{
		lxy::auto_ptr<int> ap2(ap1);
		*ap2 = 20;
	}

	// ap1是野指针
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

// 建议：什么情况下都不要使用auto_ptr

#include <memory>


int main()
{
	auto_ptr<int> ap1(new int);
	auto_ptr<int> ap2(ap1);
	return 0;
}
#endif

// C++11: auto_ptr--->保留：资源转移实现的
// 提供更靠谱的智能指针

// 智能指针原理：RAII(自动释放资源) + operator*()/operator->()(具有指针类似行为) + 提供解决浅拷贝方式

// 浅拷贝引起原因：默认拷贝构造函数 和 默认的赋值运算符重载

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
// 解决浅拷贝方式：资源独占(只能一个对象使用，不能共享)--->实现：禁止调用拷贝构造和赋值运算符重载
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
				delete _ptr; // 释放资源的方式固定死了，只能管理new的资源，不能处理任意类型的资源
				_ptr = nullptr;
			}
		}

		// 具有指针类似行为
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		// 解决浅拷贝：禁止调用拷贝构造函数和赋值运算符重载

		// C++98:
		/*
		private:  // 拷贝构造的权限一定要设置成private，原因：为了防止用户自己在类外定义
		unique_ptr(const unique_ptr<T>& up);
		unique_ptr<T>& operator=(const unique_ptr<T>&);
		*/

		// C++11 禁止调用拷贝构造和赋值运算符重载
		unique_ptr(const unique_ptr<T>&) = delete;  // 1. 释放new的空间  2.默认成员函数 = delete ： 告诉编译器，删除该默认成员函数
		unique_ptr<T>& operator=(const unique_ptr<T>&) = delete;
	private:
		T* _ptr;
	};

	// 用户在外部实现
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
				//delete _ptr; // 释放资源的方式固定死了，只能管理new的资源，不能处理任意类型的资源
				//DF()(_ptr);
				DF df;
				df(_ptr);
				_ptr = nullptr;
			}
		}

		// 具有指针类似行为
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		unique_ptr(const unique_ptr<T>&) = delete;  // 1. 释放new的空间  2.默认成员函数 = delete ： 告诉编译器，删除该默认成员函数
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