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

class Derived : public Base   //���࣬��֤�̳й�ϵ
{

};

int main()
{
	cout << sizeof(Derived) << endl;  //���������С����ȷ���Ƿ�ȫ���̳л����Ա

	Derived d;               //������������󣬷���ͨ�������������Ե��û�����������������Ѿ�ȫ���̳л����Ա
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

//public�̳�

//1������ĳ�Աȷʵ�Ѿ�ȫ���̳е���������
//2��public/protected  �������Ȩ�����������в���
//3��private  ����Ȩ�����������в��ɼ�

class Derived : public Base   
{
public:
	void setBase(int pubD, int proD, int priD)
	{
		_pubD = pubD;
		_proD = proD;
		_priD = priD;

		_pro = 10;
		//_pri = 20;    //����������private����Ȩ�����������в��ɷ���
	}

	// ����Ȩ�ޣ��޶��ó�Ա�����Ƿ����ֱ����������е���
public:
	int _pubD;
protected:
	int _proD;
private:
	int _priD;
};

int main()
{
	cout << sizeof(Derived) << endl;      //24  ˵�����Ѿ�ȫ���̳л����Ա����

	Derived d;
	d._pub = 10;             //public����Ȩ�޿�������ֱ�ӷ���
	//d._pro = 20;         //����protected����Ȩ�޲���������ֱ�ӷ���

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

//protected�̳�

//1������ĳ�Աȷʵ�Ѿ�ȫ���̳е���������
//2��public �������Ȩ�����������н�ΪprotectedȨ��
//3��protected  �������Ȩ�����������в���
//4��private  ����Ȩ�����������в��ɼ�


class Derived : protected Base
{
public:
	void setBase(int pubD, int proD, int priD)
	{
		_pubD = pubD;
		_proD = proD;
		_priD = priD;

		_pub = 10;       //��ʱpublicȨ��ΪprotectedȨ��
		_pro = 20;       
		//_pri = 20;    //����������private����Ȩ�����������в��ɷ���
	}

	// ����Ȩ�ޣ��޶��ó�Ա�����Ƿ����ֱ����������е���
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
		_pub = 10;    //˵��������publi����Ȩ�����������б�ΪprotectedȨ�ޣ�������protectedȨ�ޣ����������в���
		_pro = 20;
	}

};

int main()
{
	cout << sizeof(Derived) << endl;      //24  ˵�����Ѿ�ȫ���̳л����Ա����

	Derived d;
	//d._pub = 10;             //����public����Ȩ�޲���������ֱ�ӷ��ʣ��ѽ�Ȩ�޽�ΪprotectedȨ��
	//d._pro = 20;         //����protected����Ȩ�޲���������ֱ�ӷ���

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

//private�̳�

//1������ĳ�Աȷʵ�Ѿ�ȫ���̳е���������
//2��public/protected �������Ȩ�����������н�ΪprivateȨ��
//3��private  ����Ȩ�����������в��ɼ�

class Derived : private Base
{
public:
	void setBase(int pubD, int proD, int priD)
	{
		_pubD = pubD;
		_proD = proD;
		_priD = priD;

		_pub = 10;       //��ʱpublicȨ��ΪprivateȨ��,�����ڱ���֮�����
		_pro = 20;        //��ʱprotectedȨ��ΪprivateȨ��,�����ڱ���֮�����
		//_pri = 30;    //����������private����Ȩ�����������в��ɷ���
	}

	// ����Ȩ�ޣ��޶��ó�Ա�����Ƿ����ֱ����������е���
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
		//_pub = 10;    //����˵��������publi����Ȩ�����������б�ΪprivateȨ�ޣ�	                    
		//_pro = 20;     //��������protectedȨ�����������б�ΪprivateȨ�ޣ�	
	}

};

int main()
{
	cout << sizeof(Derived) << endl;      //24  ˵�����Ѿ�ȫ���̳л����Ա����

	Derived d;
	//d._pub = 10;             //��������public����Ȩ�޲���������ʣ��ѽ�Ȩ�޽�ΪprivateȨ��
	//d._pro = 20;         //����protected����Ȩ�޲������������

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

// class �� struct��Ĭ�ϼ̳�Ȩ��
// classĬ�ϼ̳�Ȩ��---priavet
// structĬ�ϼ̳�Ȩ��---public

struct Derived : Base
{
public:
	void setDerived(int pubD,int proD,int priD)
	{
		_pubD = pubD;
		_proD = proD;
		_priD = priD;

		_pro = 10;    //���������пɷ��ʣ����������ⲻ�ɷ��ʣ�˵��Ϊ public �̳�
		//_pri = 20;  //��������˽�г�Ա�������಻�ɼ�

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
	cout << sizeof(Derived) << endl;      //24  ˵�����Ѿ�ȫ���̳л����Ա����

	Derived d;
	d._pub = 10;             //public����Ȩ�޿�������ֱ�ӷ���
	//d._pro = 20;         //����protected����Ȩ�޲���������ֱ�ӷ���

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

// class �� struct��Ĭ�ϼ̳�Ȩ��
// classĬ�ϼ̳�Ȩ��---priavet
// structĬ�ϼ̳�Ȩ��---public

class Derived : Base
{
public:
	void setDerived(int pubD, int proD, int priD)
	{
		_pubD = pubD;
		_proD = proD;
		_priD = priD;

		//_pro = 10;    //���������пɷ��ʣ����������ⲻ�ɷ��ʣ�˵��Ϊ public �̳�
		//_pri = 20;  //��������˽�г�Ա�������಻�ɼ�

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
		//_pub = 10;  //�������в��ɷ��ʣ�����Ϊprivate�̳�
	}
};

int main()
{
	cout << sizeof(Derived) << endl;      //24  ˵�����Ѿ�ȫ���̳л����Ա����

	Derived d;
	//d._pub = 10;             //public����Ȩ�޲���������ֱ�ӷ��ʣ�˵������public�̳�
	//d._pro = 20;         //����protected����Ȩ�޲���������ֱ�ӷ���

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

// ��ֵ���ݹ���ǰ��---->public�̳�
// �����public�̳з�ʽ����������������֮����--is-a�Ĺ�ϵ
// is-a: ��һ�������Խ�һ��������󿴳���һ���������
// �����õ���������λ�ö�����ʹ�����������д���
int main()
{
	B b;
	b.SetB(10);

	D d;
	d.SetB(10);   //���û����Ա����b.SetB(10);����һ��
	d.SetD(20, 30);   //�����������Ա

	// ����������������������������и�ֵ
	b = d;
	// �������û���������������������и�ֵ
	//d = b;

	// һ������ָ�����ָ���������
	B* pb = &d;

	// һ�������ָ�벻��ֱ��ָ��һ������Ķ���
	//D* pd = &b;
	//pd->_d = 10;

	//����ͨ��ǿת�ķ�ʽ���������ָ��������,��������������
	D* pd = (D*)&b;
	
	//����������������������󣬵�����������󲻿������û������
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

// ͬ�����أ�������������о�����ͬ���Ƶĳ�Ա(��Ա���� || ��Ա����)
// ���ͨ�����������ֱ�ӷ���ͬ����Ա�����ȷ��ʵ������������Լ���
// �����ͬ����Ա����ֱ�ӷ��ʵ�(�����ཫ�����е�ͬ����Ա����)

// ��Ա����������������Ƿ���ͬ�޹�
// ��Ա���������Ա����ԭ���Ƿ���ͬ�޹�
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
	//d._b = '1';   //���ȷ���������ͬ����Ա����������������û�й�ϵ

	d.B::_b = '2';    //Ҫ���ʻ����Ա������������ϻ���������

	//d.Test(10);      //���ȷ����������Ա�������뺯��ԭ���޹�

	d.B::Test(10);     //Ҫ���ʻ����Ա������������ϻ���������

	d.SetD(1, 2);
	return 0;
}
#endif

#if 0
// �������Ĺ��캯�����޲λ���ȫȱʡ�Ĺ��캯����
// �������๹�캯����ʼ���б��λ�õ��û򲻵��ö�����
// ����û�û�е��ã����������Ĭ�ϵ���
class B
{
public:
	B()    //�޲ι��캯��
	{
		cout << "B()" << endl;
	}

protected:
	int _b;
};

class D : public B
{
public:
	D()   //�޲ι��캯��
	{
		cout << "D()" << endl;
	}

protected:
	int _d;
};

int main()
{
	D d;   //��������������ȵ��������๹�캯�����ڳ�ʼ���б�λ�õ��û��๹�캯������������û�е��ã��Ǳ�����Ĭ�ϵ���
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

// �������Ĺ��캯�����в����Ĺ��캯����
// �û������������๹�캯����ʼ���б��λ����ʽ���ã�����ɻ���
// ����ɻ��ಿ�ֳ�Ա�ĳ�ʼ��
class D : public B
{
public:
	D()
		: B(1)   // ���๹�캯�����в���������������������๹�캯��ʱ�������ֶ��ڳ�ʼ���б�λ�õ��û��๹�캯��
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
	B(int b)     //���ι��캯��
 		: _b(b)    //��ʼ���б�
	{
		cout << "B()" << endl;
	}

	B(const B& b)     //�������캯��
		: _b(b._b)
	{}

	B& operator=(const B& b)      //��ֵ���������
	{
		if (this != &b)    //�ж��Ƿ��Լ����Լ���ֵ
		{
			_b = b._b;
		}

		return *this;
	}

protected:
	int _b;
};

// �������Ĺ��캯�����в����Ĺ��캯����
// �û������������๹�캯����ʼ���б��λ����ʽ���ã�
// ����ɻ��ಿ�ֳ�Ա�ĳ�ʼ��
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








