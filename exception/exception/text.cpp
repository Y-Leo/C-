#include<iostream>
using namespace std;
#include<string>

//C���Է��ش���ʽ


//1��ֱ��exit(0)�˳�����
#if 0
// �Ƚϱ��������Ǻ��Ѻ�
int Div(int left, int right)
{
	if (0 == right)
		exit(0);

	return left / right;
}
#endif

//2�����ش�����

#if 0
#include <windows.h>

void Test()
{
	FILE* pf = fopen("2222.txt", "rb");
	if (nullptr == pf)
	{
		// ��ȡ�����������Ĵ�����(��windows����ϵͳά����)
		int errNo = GetLastError();
		cout << errNo << endl;

		return;
	}

	// ....
	fclose(pf);
}

int main()
{
	Test();
	//Test1();
	return 0;
}
#endif

#if 0
void Test()
{
	FILE* pf = fopen("2222.txt", "rb");
	if (nullptr == pf)
	{
		// ��ȡ�����������Ĵ�����(��windows����ϵͳά����)
		int errNo = GetLastError();
		cout << errNo << endl;

		goto L;
	}

	// ....
	fclose(pf);

L:
}
#endif


#if 0
int main()
{
https://www.baidu.com;
	//������벻�ᱨ����������//��Ϊ��ע�����ݣ�ǰ���https:�������������Ǳ�ǩ���൱��go to ���ı�ǩ
	return 0;
}
#endif

//3��ͨ��setjmp,longjmp��ʽ������

#if 0
#include <malloc.h>

#include <setjmp.h>

// ��ȫ�ֱ����н����������longjmp��������תλ��
jmp_buf buff;  // ��setjmp������buff����ת��Ϣ

void Test1()
{
	char* p = (char*)malloc(0x7fffffff);
	if (nullptr == p)
	{
		// һ������ռ�ʧ��ʱ��longjmp����ת��buffָ����λ��
		longjmp(buff, 1);
	}

	///��������
}

void Test2()
{
	FILE* pf = fopen("2222.txt", "rb");
	if (nullptr == pf)   //����ļ���ʧ��
	{
		longjmp(buff, 2);
	}

	// ....
	fclose(pf);
}

int main()
{
	// setjmp����longjmp��������ת��
	// ע�⣺setjmp���״ε���ʱ��һ���᷵��0����������ִ���
	int iState = 0;//setjmp(buff);
	if (0 == iState)
	{
		// ��������
		Test1();
		Test2();
	}
	else
	{
		// ���������Ƿ������longjmp��ת����λ��
		// һ�������д���ǳ���Ĵ��������
		switch (iState)
		{
		case 1:
			cout << "malloc����ռ�ʧ��" << endl;
			break;
		case 2:
			cout << "���ļ�ʧ��" << endl;
			break;
		default:
			cout << "δ֪����" << endl;
		}
	}

	iState = setjmp(buff);
	return 0;
}
#endif


#if 0
void Test1()
{
	FILE* pf = fopen("2222.txt", "rb");
	if (nullptr == pf)
	{
		throw 1;
	}

	// ...
	// ���г�����ļ�����

	fclose(pf);
}


//C++�쳣��

void Test2()
{
	char* p = (char*)malloc(0x7fffffff);
	if (nullptr == p)
	{
		throw 1.0;  //�׳��쳣
	}

	///��������
	free(p);
}


int main()
{
	int a = 10;
	double d = 12.34;
	a = d; // double��int֮����Է�����ʽ����ת��

	// �쳣�����ǰ������������в����
	// ����֮��������ᷢ������ת��
	try
	{
		Test2();
		Test1();
	}
	catch (int e)
	{
		// ��������int���͵��쳣
		// ����������
		cout << e << endl;
	}
	catch (double e)
	{
		cout << e << endl;
	}
	//...
	return 0;
}
#endif


#if 0
void Test1()
{
	FILE* pf = fopen("2222.txt", "rb");
	if (nullptr == pf)
		throw 1;

	// ...
	fclose(pf);
}


void Test2()
{
	int* p = new int[10];

	// ...
	try
	{
		Test1();
	}
	catch (int e)
	{
		delete[] p;
		cout << e << endl;
		return;
	}


	// ...
	delete[] p;
}

int main()
{
	try
	{
		Test2();
		Test1();
	}
	catch (int e)
	{
		cout << e << endl;
	}

	return 0;
}
#endif

#if 0
void Test()
{
	int a = 10;
	cout << &a << endl;

	// �����쳣ʱ�������ǽ�a�����׳��������׳���һ��a�ĸ���
	throw a;
}

int main()
{
	try
	{
		Test();
	}
	catch (int& ra)
	{
		cout << &ra << endl;
	}
	return 0;
}
#endif

//֤���׳�����һ������
#if 0
class A
{
public:
	A()
	{
		cout << "A::A()" << this << endl;
	}

	A(const A& a)//�׳��쳣ʱ����ÿ������캯����֤���׳��쳣���׳�����
	{
		cout << "AA::(const A&):" << this << endl;
	}

	~A()
	{
		cout << "A::~A()" << this << endl;
	}
};
void Test()
{
	A  a;
	cout << &a << endl;

	// �����쳣ʱ�������ǽ�a�����׳��������׳���һ��a�ĸ���
	throw a;  // ʵ���׵���a�ĸ���
}

int main()
{
	try
	{
		Test();
	}
	// 	catch (A& ra)
	// 	{
	// 		cout << &ra << endl;
	// 	}
	catch (...) // ���ܲ��񣬼����������͵��쳣�����Բ���catch(...)�ķ�ʽ���в���
	{
		cout << "A" << endl;
	}
	return 0;
}
#endif


//�쳣�������׳�
#if 0
void Test1()
{
	FILE* pf = fopen("2222.txt", "rb");
	if (nullptr == pf)
		throw 1;

	// ...
	fclose(pf);
}


void Test2()
{
	int* p = new int[10];

	// ...
	try
	{
		Test1();
	}
	catch (...)
	{
		// 1. ����Test2���ڸ�����֪��Test1�׳��쳣������
		// 2. ����Test2֪��Test1���׳��쳣�����ͣ�����Test2û�б�Ҫ����Ҫ���Test1�׳����쳣
		delete[] p;
		throw;   // �쳣�������׳�
	}

	// ...
	delete[] p;
}

int main()
{
	try
	{
		Test2();
	}
	catch (int e)
	{
		cout << e << endl;
	}

	return 0;
}
#endif

#if 0
void Test()
{
	throw 1;
}


template<class T>
void Test2(T a)
{
	throw a;
}

template<class T>
void Test3(T a)
{
	try
	{
		Test2(a);
	}
	catch (T a)
	{
		cout << a << endl;
	}
}

int main()
{
	Test3(10);
	return 0;
}
#endif

#if 0
// ������쳣��ֻ���׳����ε��쳣
// �����ڱ����ڼ�ͻᱨ��
void Test1()throw(int)
{
	throw 1.0;
}

// �ú���һ�������׳��쳣
// �����ڱ����ڼ�ͻᱨ��
void Test2()throw()
{
	throw 1;
}

int main()
{
	return 0;
}
#endif

//�쳣��

class Exception
{
public:
	Exception(const string& errInfo, int errNo)
		: _errInfo(errInfo)
		, _errNo(errNo)
	{}

	virtual void What() = 0;    //�º���

protected:
	string _errInfo;
	int _errNo;
};

//�����쳣�̳����쳣����

class NetException : public Exception
{
public:
	NetException(const string& errInfo, int errNo)
		: Exception(errInfo, errNo)
	{}

	virtual void What()   //�º���
	{
		cout << _errInfo << ":" << _errNo << endl;
	}
};


// ���ݿ��쳣��̳����쳣����
class DBException : public Exception
{
public:
	DBException(const string& errInfo, int errNo)
		: Exception(errInfo, errNo)
	{}

	virtual void What()  //�º���
	{
		cout << _errInfo << ":" << _errNo << endl;
	}
};

// ͨ�����紫������
void Test1()
{
	NetException e("�����ж�", 400);
	throw e;
}

// �������ݿ�
void Test2()
{
	DBException e("���ݿ�δ��", 500);
}

int main()
{
	try
	{
		char* p = new char[0x7fffffff];

		Test1();
		Test2();

	}
	catch (Exception& e)
	{
		e.What();
	}
	catch (exception& e)
	{
		e.what();
	}
	catch (...)
	{
		cout << "δ֪�쳣" << endl;
	}

	return 0;
}