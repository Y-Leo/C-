#include<iostream>
using namespace std;

#if 0
//设计一个类，不能被继承

//C++98
class Base
{
public:
	static Base GetObject(int b)
	{
		return Base(b);
	}
private:
	Base(int b)
	{
		_b = b;
	}
protected:
	int _b;
};

int main()
{
	Base b(Base::GetObject(1));
	return 0;
}
#endif

#if 0
//设计一个类，不能被继承

//C++11
class Base  final
{
public:
	Base(int b)
	{
		_b = b;
	}
protected:
	int _b;
};

class Derived :public Base
{

};

int main()
{
	return 0;
}

#endif

#if 0

//友元关系不可被继承

class Base 
{
	friend void Print();
public:
	Base(int b)
		:_b(b)
	{}

	int GetB()
	{
		return _b;
	}
protected:
	int _b;
};

void Print()
{
	Base b(10);
	cout << b.GetB() << endl;
	cout << b._b << endl;     //设为友元则可以访问
}

class Derived :public Base
{
public:
	Derived(int b, int _d)
		:Base(b)
		, _d(d)
	{

	}
protected:
	int _d;

};

int main()
{
	Derived d(10, 20);
	//cout << d._d << endl;     //友元不可被继承
	return 0;
}

#endif

#if 0
// 统计一个类创建了多少个对象
class Person
{
public:
	Person(const string& name, const string& gender, int age)
		: _name(name)
		, _gender(gender)
		, _age(age)
	{
		_count++;
	}

	Person(const Person& p)
		: _name(p._name)
		, _gender(p._gender)
		, _age(p._age)
	{
		++_count;
	}

	~Person()
	{
		--_count;
	}

protected:
	string _name;
	string _gender;
	int _age;

public:
	static size_t _count;
};

size_t Person::_count = 0;


class Student : public Person
{
public:
	Student(const string& name, const string& gender, int age, int stuId)
		: Person(name, gender, age)
		, _stuId(stuId)
	{}

	Student(const Student& s)
		: Person(s)
		, _stuId(s._stuId)
	{}


protected:
	int _stuId;
};

class Teacher : public Person
{
public:
	Teacher(const string& name, const string& gender, int age, int stuId)
		: Person(name, gender, age)
		, _stuId(stuId)
	{}

	Teacher(const Teacher& s)
		: Person(s)
		, _stuId(s._stuId)
	{}


protected:
	int _stuId;
};



void TestPerson()
{
	Person p("111", "男", 18);
	Student s("222", "女", 18, 20);

	cout << Person::_count << endl;
	cout << Student::_count << endl;

	cout << &Person::_count << endl;
	cout << &Student::_count << endl;
	cout << &Teacher::_count << endl;

	/*
	结论：
	1. 基类中静态成员变量可以被子类继承
	2. 在整个继承体系中，静态成员变量只有一份
	*/
}

int main()
{
	TestPerson();
	return 0;
}
#endif

#if 0
class B1
{
public:
	int _b1;
};

class B2
{
public:
	int _b2;
};

// 注意：每个基类前必须给出继承权限，否则就是默认的继承权限，注意继承顺序
class D : public B2, public B1
{
public:
	int _d;
};


int main()
{
	cout << sizeof(D) << endl;    //12，说明D既继承自B1也继承自B2

	D d;
	d._b1 = 1;
	d._b2 = 2;
	d._d = 3;
	return 0;
}
#endif

#if 0
class B
{
public:
	int _b;
};

class C1 : public B
{
public:
	int _c1;
};

class C2 : public B
{
public:
	int _c2;
};

class D : public C1, public C2
{
public:
	int _d;
};

int main()
{
	cout << sizeof(D) << endl;

	D d;
	//d._b = 1;  // 菱形继承缺陷：会存在二义性问题     _b有可能时C1的，也有可能是C2的

	d.C1::_b = 1;
	d._c1 = 2;

	d.C2::_b = 3;
	d._c2 = 4;

	d._d = 5;
	return 0;
}
#endif

#if 1

// 菱形虚拟继承
class B
{
public:
	int _b;
};

class C1 : virtual public B
{
public:
	int _c1;
};

class C2 : virtual public B
{
public:
	int _c2;
};

class D : public C1, public C2
{
public:
	int _d;
};

int main()
{
	cout << sizeof(D) << endl;

	D d;
	d._b = 1;  // 菱形继承缺陷：会存在二义性问题

	d.C1::_b = 1;
	d._c1 = 2;

	d.C2::_b = 3;
	d._c2 = 4;

	d._d = 5;
	return 0;
}

#endif