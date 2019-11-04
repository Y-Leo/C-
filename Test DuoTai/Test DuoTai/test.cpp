//多态相关练习

#include<iostream>
using namespace std;

//多态构成条件
//1、必须通过基类的指针或者引用调用虚函数
//2、被调用的函数必须是虚函数，而且派生类必须对基类的虚函数进行重写

//虚函数：被virtual修饰的类成员函数

//重写：派生类中有一个和基类完全相同的虚函数（返回值类型、函数名字、参数列表完全相同）

#if 0

class Person
{
public:
	virtual void BuyTicket()
	{
		cout << "全价票" << endl;
	}
};

class Student :public Person
{
public:
	virtual void BuyTicket()
	{
		cout << "半价票" << endl;
	}
};

class Soldier : public Person
{
public:
	virtual void BuyTicket()
	{
		cout << "免费" << endl;
	}
};

void FunC(Person& p)
{
	p.BuyTicket();
}

int main()
{
	Person per;
	Student stu;
	Soldier sol;

	FunC(per);
	FunC(stu);
	FunC(sol);

	return 0;
}

#endif


#if 0
// 买票
// 普通人
class Person
{
public:
	Person(const string& name, const string& gender, int age)
		: _name(name)
		, _gender(gender)
		, _age(age)
	{}

	// 虚函数
	virtual void BuyTicket()
	{
		cout << "全价票" << endl;
	}

protected:
	string _name;
	string _gender;
	int _age;
};

class Student : public Person
{
public:
	Student(const string& name, const string& gender, int age, int stuId)
		: Person(name, gender, age)
		, _stuId(stuId)
	{}

	virtual void BuyTicket()
	{
		cout << "半价票" << endl;
	}
protected:
	int _stuId;
};

class Soldier : public Person
{
public:
	Soldier(const string& name, const string& gender, int age, const string& rank)
		: Person(name, gender, age)
		, _rank(rank)
	{}
	 
	void BuyTicket()           //虚函数重写时，不要virtual关键字也可以，但不建议这样做
	{
		cout << "免费" << endl;
	}

protected:
	string _rank;
};


// 必须通过基类的指针或引用来调用
// 多态的体现：代码编译时，不能确定到底调用那个类的虚函数
//           在代码运行时，根据p所指向的实际对象选择调用对应类的虚函数
// 如果多态的实现条件没有完全满足：1. 重写失败(基类函数不是虚函数，函数原型不一致)
//                                 2. 没有通过基类的指针或者引用调用虚函数 
//   
void TestBuyTicket(Person& p)
{
	p.BuyTicket();
}


/*
void TestBuyTicket(Student& p)   //报错，因为虚函数只能通过基类的指针或者引用来实现
{
p.BuyTicket();
}

void TestBuyTicket(Soilder& p)    //报错，因为虚函数只能通过基类的指针或者引用来实现
{
p.BuyTicket();
}
*/

int main()
{
	Person p("Peter", "男", 18);
	Student st("小帅", "女", 19, 1000);
	Soldier so("威武", "男", 23, "班长");

	TestBuyTicket(p);
	TestBuyTicket(st);
	TestBuyTicket(so);
	return 0;
}
#endif


#if 0
struct A{};
struct B :public A{};

class Base
{
public:
	virtual void TestFunc1()
	{
		cout << "Base::TestFunc1()" << endl;
	}

	virtual void TestFunc2(int)
	{
		cout << "Base::TestFunc2()" << endl;
	}

	void TestFunc3()
	{
		cout << "Base::TestFunc3()" << endl;
	}

	virtual void TestFunc4()
	{
		cout << "Base::TestFunc4()" << endl;
	}

	virtual Base* TestFunc5()
	{
		cout << "Base::TestFunc5()" << endl;
		return this;
	}

	virtual A& TestFunc6(A& a)
	{
		cout << "Base::TestFunc6()" << endl;
		return a;
	}
};

class Derived : public Base
{
public:
	virtual void TestFunc1()
	{
		cout << "Derived::TestFunc1()" << endl;
	}

	virtual void TestFunc2()
	{
		cout << "Derived::TestFunc2()" << endl;
	}

	virtual void TestFunc3()
	{
		cout << "Derived::TestFunc3()" << endl;
	}

	void TestFunc4()
	{
		cout << "Derived::TestFunc4()" << endl;
	}

	virtual Derived* TestFunc5()
	{
		cout << "Derived::TestFunc5()" << endl;
		return this;
	}

	virtual B& TestFunc6(A& a)
	{
		cout << "Derived::TestFunc6()" << endl;
		return *(new B);
	}
};


void TestVirtualFunc(Base* pb)
{
	pb->TestFunc1();
	pb->TestFunc2(10);
	pb->TestFunc3();
	pb->TestFunc4();
	pb->TestFunc5();

	A a;
	pb->TestFunc6(a);
}

int main()
{
	Base b;
	Derived d;

	TestVirtualFunc(&b);
	TestVirtualFunc(&d);
	return 0;
}
#endif

#if 1
class Base
{
public:
	Base(int b)
		: _b(b)
	{
		cout << "Base::Base()" << endl;
	}

	virtual ~Base()
	{
		cout << "Base::~Base()" << endl;
	}

	int _b;
};

class Derived : public Base
{
public:
	Derived(int b)
		: Base(b)
		, _p(new int[10])
	{
		cout << "Derived::Derived(int)" << endl;
	}

	~Derived()
	{
		delete[] _p;
		cout << "Derived::~Derived()" << endl;
	}

protected:
	int* _p;
};

void TestDestroy()
{
	Base* pb = new Derived(10);
	delete pb;
}

int main()
{
	TestDestroy();
	return 0;
}
#endif