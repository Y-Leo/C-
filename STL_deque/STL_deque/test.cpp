
//STL_deque ���ýӿ���ϰʹ��
#include<iostream>
#include<deque>
#include<vector>
#include<algorithm>

using namespace std;


//��Χfor��������deque
void PrintDeque(const deque<int>& d)
{
	for (const auto& e : d)
	{
		cout << e << " ";
	}
	cout << endl;
}

//����deque�Ĺ��캯��
void TestDeque1()
{
	//����յ�˫�˶���
	deque<int> d1;

	//��10��ֵΪ5��Ԫ�ع���˫�˶���
	deque<int> d2(10, 5);
	PrintDeque(d2);

	//��vector�����乹��˫�˶���
	vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	deque<int> d3(v.begin(), v.end());
	PrintDeque(d3);

	//��d3��������d4
	deque<int> d4(d3);
	PrintDeque(d4);
}

//����deque�еĵ�����
void TestDeque2()
{
	//���������乹��deque
	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	deque<int> d(array, array + sizeof(array) / sizeof(array[0]));

	//���������������ӡdeque�е�Ԫ��
	//deque<int>::iterator it = d.begin();       //C++98 �ṩ�Ķ���������İ취
    auto it = d.cbegin();                  //C++11 �ṩ
	while (it != d.cend())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	/*
	//���ϴ���Ҳ���Լ�д
	for (auto it = d.cbegin(); it != d.cend(); ++it)
		cout << *it << " ";
	cout << endl;
	*/

	auto cit = d.cbegin();
	//*it = 100;    //���������첻ͨ����itΪconst����������ָ��ռ�Ԫ��ֵ�����޸�

	//���÷�������������ӡdeque�е�Ԫ��
	for (auto rit = d.crbegin(); rit != d.crend(); ++rit)
		cout << *rit << " ";
	cout << endl;

}

//����deque��Ԫ���޸������Լ���������
void TestDeque3()
{
	vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	deque<int> d1(v.begin(), v.end());

	//��dequeͷ������1��β������5������ӡ
	d1.push_front(1);
	d1.push_back(5);
	PrintDeque(d1);
	cout << d1.size() << endl;
	cout << d1.front() << endl;
	cout << d1.back() << endl;

	//��deque��begin()λ�ò���Ԫ��0
	d1.insert(d1.begin(), 0);
	PrintDeque(d1);

	//ɾ��deque�ײ���β��Ԫ��
	d1.pop_front();
	d1.pop_back();
	d1.erase(d1.begin());
	PrintDeque(d1);

	//��deque�е�Ԫ�����
	d1.clear();
	cout << d1.size() << endl;
}


//��deque�е�Ԫ�ؽ�������
void TestDequeSort()
{
	int array[] = { 5, 3, 21, 5, 12, -23, 43, 23, 0, 2 };
	deque<int> d(array, array + sizeof(array) / sizeof(array[0]));

	PrintDeque(d);

	//���ñ�׼���е��㷨��deque�е�Ԫ�ؽ�����������
	sort(d.begin(), d.end());
	PrintDeque(d);
}
/*
������deque������Ĳ���Ч���Ƿǳ��͵ģ�����deque��������ʱ,��Ҫ��ζ�deque�е�Ԫ�ؽ������������
��deque�е�Ԫ���������Ч�ʱȽϵͣ�������Ϊdeque�ײ�ռ䲻���������Ҫ���������������ĳ�οռ�
��Ĭ�ϻ����ײ�ʱ������Ҫ������һ�λ���ǰһ�εĿռ�λ�ã�����dequeЧ�ʱȽϵ��¡�
*/

int main()
{
	//TestDeque1();         //����deque����
	//TestDeque2();           //����deque������
	//TestDeque3();              //������ɾ�Ĳ�
	TestDequeSort();                  //��������
	return 0;
}