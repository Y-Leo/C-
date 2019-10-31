#include<iostream>
using namespace std;

#if 0

class Base
{
public:
	void setBase(int pub,int pro,int pri)
	{
		_pub = pub;
		_pro = pro;
		_pri = pri;
	}
	void printBase()
	{
		cout << _pub << endl;
		cout << _pro << endl;
		cout << _pri << endl;
	}
	
public:
	int _pub;
protected:
	int _pro;
private:
	int _pri;
};

class Derived : public Base   //空类，验证继承关系
{

};

int main()
{
	cout << sizeof(Derived) << endl;  //看派生类大小，来确定是否全部继承基类成员

	Derived d;               //创建派生类对象，发现通过派生类对象可以调用基类对象，所以派生类已经全部继承基类成员
	d.setBase(1, 2, 3);
	d.printBase();
	d._pub = 10;

	return 0;
}

#endif


#if 0

class Base
{
public:
	void setBase(int pub, int pro, int pri)
	{
		_pub = pub;
		_pro = pro;
		_pri = pri;
	}
	void printBase()
	{
		cout << _pub << endl;
		cout << _pro << endl;
		cout << _pri << endl;
	}

public:
	int _pub;
protected:
	int _pro;
private:
	int _pri;
};

//public继承

//1、基类的成员确实已经全部继承到派生类中
//2、public/protected  基类访问权限在派生类中不变
//3、private  访问权限在派生类中不可见

class Derived : public Base   
{
public:
	void setBase(int pubD, int proD, int priD)
	{
		_pubD = pubD;
		_proD = proD;
		_priD = priD;

		_pro = 10;
		//_pri = 20;    //报错，基类中private访问权限在派生类中不可访问
	}

	// 访问权限：限定该成员变量是否可以直接在类外进行调用
public:
	int _pubD;
protected:
	int _proD;
private:
	int _priD;
};

int main()
{
	cout << sizeof(Derived) << endl;      //24  说明，已经全部继承基类成员变量

	Derived d;
	d._pub = 10;             //public访问权限可在类外直接访问
	//d._pro = 20;         //报错，protected访问权限不可在类外直接访问

	return 0;
}

#endif;

#if 0

class Base
{
public:
	void setBase(int pub, int pro, int pri)
	{
		_pub = pub;
		_pro = pro;
		_pri = pri;
	}
	void printBase()
	{
		cout << _pub << endl;
		cout << _pro << endl;
		cout << _pri << endl;
	}

public:
	int _pub;
protected:
	int _pro;
private:
	int _pri;
};

//protected继承

//1、基类的成员确实已经全部继承到派生类中
//2、public 基类访问权限在派生类中降为protected权限
//3、protected  基类访问权限在派生类中不变
//4、private  访问权限在派生类中不可见


class Derived : protected Base
{
public:
	void setBase(int pubD, int proD, int priD)
	{
		_pubD = pubD;
		_proD = proD;
		_priD = priD;

		_pub = 10;       //此时public权限为protected权限
		_pro = 20;       
		//_pri = 20;    //报错，基类中private访问权限在派生类中不可访问
	}

	// 访问权限：限定该成员变量是否可以直接在类外进行调用
public:
	int _pubD;
protected:
	int _proD;
private:
	int _priD;
};

class D :public Derived
{
	void Test()
	{
		_pub = 10;    //说明基类中publi访问权限在派生类中变为protected权限，而基类protected权限，在派生类中不变
		_pro = 20;
	}

};

int main()
{
	cout << sizeof(Derived) << endl;      //24  说明，已经全部继承基类成员变量

	Derived d;
	//d._pub = 10;             //基类public访问权限不可在类外直接访问，已将权限降为protected权限
	//d._pro = 20;         //报错，protected访问权限不可在类外直接访问

	return 0;
}

#endif;

#if 0

class Base
{
public:
	void setBase(int pub, int pro, int pri)
	{
		_pub = pub;
		_pro = pro;
		_pri = pri;
	}
	void printBase()
	{
		cout << _pub << endl;
		cout << _pro << endl;
		cout << _pri << endl;
	}

public:
	int _pub;
protected:
	int _pro;
private:
	int _pri;
};

//private继承

//1、基类的成员确实已经全部继承到派生类中
//2、public/protected 基类访问权限在派生类中降为private权限
//3、private  访问权限在派生类中不可见

class Derived : private Base
{
public:
	void setBase(int pubD, int proD, int priD)
	{
		_pubD = pubD;
		_proD = proD;
		_priD = priD;

		_pub = 10;       //此时public权限为private权限,不可在本类之外访问
		_pro = 20;        //此时protected权限为private权限,不可在本类之外访问
		//_pri = 30;    //报错，基类中private访问权限在派生类中不可访问
	}

	// 访问权限：限定该成员变量是否可以直接在类外进行调用
public:
	int _pubD;
protected:
	int _proD;
private:
	int _priD;
};

class D :public Derived
{
	void Test()
	{
		//_pub = 10;    //报错，说明基类中publi访问权限在派生类中变为private权限，	                    
		//_pro = 20;     //报错，基类protected权限在派生类中变为private权限，	
	}

};

int main()
{
	cout << sizeof(Derived) << endl;      //24  说明，已经全部继承基类成员变量

	Derived d;
	//d._pub = 10;             //报错，基类public访问权限不可类外访问，已将权限降为private权限
	//d._pro = 20;         //报错，protected访问权限不可在类外访问

	d.setBase(1, 2, 3);

	return 0;
}

#endif;

#if 0
class Base
{
public:
	void SetBase(int pri, int pro, int pub)
	{
		_pri = pri;
		_pro = pro;
		_pub = pub;
	}

	void PrintBase()
	{
		cout << _pri << endl;
		cout << _pro << endl;
		cout << _pub << endl;
	}

private:
	int _pri;
protected:
	int _pro;
public:
	int _pub;
};

// class 和 struct的默认继承权限
// class默认继承权限---priavet
// struct默认继承权限---public

struct Derived : Base
{
public:
	void setDerived(int pubD,int proD,int priD)
	{
		_pubD = pubD;
		_proD = proD;
		_priD = priD;

		_pro = 10;    //在派生类中可访问，但是在类外不可访问，说明为 public 继承
		//_pri = 20;  //报错，基类私有成员在派生类不可见

	}
public:
	int _pubD;
protected:
	int _proD;
private:
	int _priD;
};

class D : public Derived
{
public:
	void Test()
	{
		_pub = 10;  
		_pro = 20;
		//_pri = 30;
	}
};

int main()
{
	D d;
	d._pub = 10;
	return 0;
}


int main()
{
	cout << sizeof(Derived) << endl;      //24  说明，已经全部继承基类成员变量

	Derived d;
	d._pub = 10;             //public访问权限可在类外直接访问
	//d._pro = 20;         //报错，protected访问权限不可在类外直接访问

	return 0;
}

#endif

#if 0
class Base
{
public:
	void SetBase(int pri, int pro, int pub)
	{
		_pri = pri;
		_pro = pro;
		_pub = pub;
	}

	void PrintBase()
	{
		cout << _pri << endl;
		cout << _pro << endl;
		cout << _pub << endl;
	}

private:
	int _pri;
protected:
	int _pro;
public:
	int _pub;
};

// class 和 struct的默认继承权限
// class默认继承权限---priavet
// struct默认继承权限---public

class Derived : Base
{
public:
	void setDerived(int pubD, int proD, int priD)
	{
		_pubD = pubD;
		_proD = proD;
		_priD = priD;

		//_pro = 10;    //在派生类中可访问，但是在类外不可访问，说明为 public 继承
		//_pri = 20;  //报错，基类私有成员在派生类不可见

	}
public:
	int _pubD;
protected:
	int _proD;
private:
	int _priD;
};

class D : public Derived
{
public:
	void Test()
	{
		//_pub = 10;  //派生类中不可访问，所以为private继承
	}
};

int main()
{
	cout << sizeof(Derived) << endl;      //24  说明，已经全部继承基类成员变量

	Derived d;
	//d._pub = 10;             //public访问权限不可在类外直接访问，说明不是public继承
	//d._pro = 20;         //报错，protected访问权限不可在类外直接访问

	return 0;
}

#endif

#if 0
class B
{
public:
	void SetB(int b)
	{
		_b = b;
	}

protected:
	int _b;
};

class D : public B
{
public:
	void SetD(int b, int d)
	{
		_b = b;
		_d = d;
	}

protected:
	int _d;
};

// 赋值兼容规则：前提---->public继承
// 如果是public继承方式：派生类与基类对象之间是--is-a的关系
// is-a: 是一个，可以将一个子类对象看成是一个基类对象
// 所有用到基类对象的位置都可以使用子类对象进行代替
int main()
{
	B b;
	b.SetB(10);

	D d;
	d.SetB(10);   //调用基类成员，和b.SetB(10);作用一样
	d.SetD(20, 30);   //调用派生类成员

	// 可以用派生类对象来给基类对象进行赋值
	b = d;
	// 不可以用基类对象来给派生类对象进行赋值
	//d = b;

	// 一个基类指针可以指向子类对象，
	B* pb = &d;

	// 一个子类的指针不能直接指向一个基类的对象
	//D* pd = &b;
	//pd->_d = 10;

	//可以通过强转的方式让子类对象指向基类对象,但不建议这样做
	D* pd = (D*)&b;
	
	//基类对象可以引用派生类对象，但是派生类对象不可以引用基类对象
	B& rb = d;
	//D& rd = b;

	return 0;
}
#endif

#if 0
class B
{
public:
	void SetB(int b)
	{
		_b = b;
	}

	void Test(int a)
	{}

//protected:
	char _b;
};

// 同名隐藏：基类和派生类中具有相同名称的成员(成员变量 || 成员函数)
// 如果通过派生类对象直接访问同名成员，优先访问到的是派生类自己的
// 基类的同名成员不能直接访问到(派生类将基类中的同名成员隐藏)

// 成员变量：与变量类型是否相同无关
// 成员函数：与成员函数原型是否相同无关
class D : public B
{
public:
	void SetD(int b, int d)
	{
		_b = b;
	}

	void Test()
	{}

protected:
	int _b;
};

int main()
{
	cout << sizeof(D) << endl;

	D d;
	//d._b = '1';   //优先访问派生类同名成员变量，跟变量类型没有关系

	d.B::_b = '2';    //要访问基类成员变量，必须加上基类作用域

	//d.Test(10);      //优先访问派生类成员函数，与函数原型无关

	d.B::Test(10);     //要访问基类成员函数，必须加上基类作用域

	d.SetD(1, 2);
	return 0;
}
#endif

#if 0
// 如果基类的构造函数是无参或者全缺省的构造函数，
// 在派生类构造函数初始化列表的位置调用或不调用都可以
// 如果用户没有调用，则编译器会默认调用
class B
{
public:
	B()    //无参构造函数
	{
		cout << "B()" << endl;
	}

protected:
	int _b;
};

class D : public B
{
public:
	D()   //无参构造函数
	{
		cout << "D()" << endl;
	}

protected:
	int _d;
};

int main()
{
	D d;   //创建派生类对象，先调用派生类构造函数，在初始化列表位置调用基类构造函数，这里我们没有调用，是编译器默认调用
	return 0;
}
#endif

#if 0
class B
{
public:
	B(int b)
	{
		cout << "B()" << endl;
	}

protected:
	int _b;
};

// 如果基类的构造函数带有参数的构造函数，
// 用户必须在派生类构造函数初始化列表的位置显式调用，以完成基类
// 以完成基类部分成员的初始化
class D : public B
{
public:
	D()
		: B(1)   // 基类构造函数带有参数，所以这里调用派生类构造函数时，必须手动在初始化列表位置调用基类构造函数
	   , _d(2)
	{
		cout << "D()" << endl;
	}

protected:
	int _d;
};

int main()
{
	D d;
	return 0;
}
#endif


class B
{
public:
	B(int b)     //带参构造函数
 		: _b(b)    //初始化列表
	{
		cout << "B()" << endl;
	}

	B(const B& b)     //拷贝构造函数
		: _b(b._b)
	{}

	B& operator=(const B& b)      //赋值运算符重载
	{
		if (this != &b)    //判断是否自己给自己赋值
		{
			_b = b._b;
		}

		return *this;
	}

protected:
	int _b;
};

// 如果基类的构造函数带有参数的构造函数，
// 用户必须在派生类构造函数初始化列表的位置显式调用，
// 以完成基类部分成员的初始化
class D : public B
{
public:
	D(int b, int d)
		: B(b)
		, _d(d)
	{
		cout << "D()" << endl;
	}

	D(const D& d)
		: B(d)
		, _d(d._d)
	{}

	D& operator=(const D& d)
	{
		if (this != &d)
		{
			//*this = d;
			B::operator=(d);
			_d = d._d;
		}

		return *this;
	}
protected:
	int _d;
};

int main()
{
	D d1(1, 2);
	D d2(d1);

	D d3(3, 4);
	d2 = d3;    
	return 0;
}








