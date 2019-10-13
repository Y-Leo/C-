//STL_List  list�ĳ��ýӿڼ�ʹ��
#include<iostream>
using namespace std;

//list:��ͷ�ڵ��˫��ѭ������

#include<list>
#include<vector>

//list����

void TestList1()
{
	list<int> L1;    //����յ�L1
	list<int> L2(10,5);    //L2�з�10��ֵΪ5��Ԫ��
	vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	list<int> L3(v.begin(), v.end());            //���乹��    vector �ṩ�������䡣
	//[begin(),end()),����ҿ�
	list<int> L4(arr, arr + sizeof(arr) / sizeof(arr[0]));      //���乹��    �����ṩ�������䡣
	list<int> L5(L4);    //��������

	cout << L1.size() << endl;

	//����������L2
	//list<int>::iterator it = L2.begin();           //C++98  �ṩ�İ취
	auto  it = L2.begin();          //C++11 �ṩ�İ취
	while (it != L2.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	//��Χforѭ������L3     //C++11
	for (auto e : L3)
	{
		cout << e << " ";
	}
	cout << endl;

	cout << L4.front() << endl;
	cout << L4.back() << endl;

	//�������������L5
	auto rit = L5.rbegin();
	while (rit != L5.rend())
	{
		cout << *rit << " ";
		++rit;
	}
	cout << endl;
}

//List��ɾ�Ĳ�

void TestList2()
{
	list<int> L;
	L.push_back(1);            //β��   �������Ԫ��
	L.push_back(2);
	L.push_back(3);
	L.push_back(4);
	L.push_back(5);

	cout << L.size() << endl;

	L.push_front(0);            //ͷ��
	cout << L.front() << endl;

	L.pop_back();              //βɾ
	cout << L.back() << endl;

	L.pop_front();               //ͷɾ
	cout << L.front() << endl;

	//1  2   3   4
	//list<int>::iterator it = L.begin();    //C++98
	auto it = L.begin();     //C++11  ���������

	it = find(L.begin(), L.end(), 2);     //find()�������������ҵ�һ��ֵΪ2��Ԫ�أ�����ֵΪ��Ԫ�صĵ�����
	if (it != L.end())    //�ж�������֤L��Ϊ��
	{
		L.insert(it, 9);            //insert������itλ��֮ǰ����9
	}

	L.erase(it);            //ɾ��itλ��Ԫ��,Ҫע�⣺��ʱit�ĺ���--��itָ���һ���ҵ���ֵΪ2��Ԫ�أ���������ɾ��֮ǰ�ҵ���Ԫ��2

	cout << L.size() << endl;

	//IsOdd(int data);   ����ͬ��
}
	
//remove()  ,  remove_if()

// �ж�ż������
bool IsEven(int data)
{
	if (0 == data % 2)
		return true;
	return false;
}
//�ж���������
bool IsOdd(int data)
{
	if (0 == data % 2)
		return true;
	return false;
}

void TestList3()
{
	list<int> L{ 1, 2, 3, 2, 2, 4, 2 };
	for (auto e : L)
	{
		cout << e << " ";
	}
	cout << endl;

	//ɾ�����е�2
	L.remove(2);            //remove()����Ϊɾ�����к�����ֵ��ͬ��Ԫ��
	//1 3 4
	cout << L.size() << endl;

    //ɾ��L�����е�ż��
	L.remove_if(IsEven);     //remove_if()����Ϊɾ�����з���������Ԫ�أ�����������Ϊ����
	//1 3
	cout << L.size() << endl;

	//L.remove_if(IsOdd);   //ɾ��L�����е�����
}

//unique()

void TestList4()
{
	list<int> L{ 1, 2, 3, 4, 9, 2, 2, 4, 2 };
	L.sort();      //����
	for (auto e : L)
	{
		cout << e << " ";
	}
	cout << endl;

	//unique():ȥ�أ�ɾ���ظ���Ԫ��
	//ʹ��unique()ǰ���Ǳ�֤�����������
    L.unique();     
	auto it = L.begin();
	while (it != L.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

//������ʧЧ����
//list�е�����ʧЧ----��������ָ��Ľڵ㲻����
void TestList5()
{
	list<int> L{ 1, 2, 3, 4 };
	//list<int>::iterator it = L.begin();    //C++98
	auto it = L.begin();    //C++11

	L.erase(it);   
	//it������ʧЧ��erase֮��it��ָ��Ľڵ��Ѿ���ɾ����
    //����취�����¸�it��ֵ
	it = L.begin();
	while (it != L.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}
int main()
{
	//TestList1();           //list����
	//TestList2();           //List��ɾ�Ĳ�
	//TestList3();           //remove()  ,  remove_if()
	//TestList4();           //unique()
	TestList5();           //������ʧЧ����

	return 0;
}