//Vector�ļ�ʹ��

// vector�ײ�ṹ����̬���͵�˳���
// vector<char>  string

#include<iostream>
using namespace std;
#include<vector>

//constructing vectors ����
void Test1()
{
	vector<int> first;                               //empty vector of ints
	vector<int>second(4, 100);                       //four ints with value 100
	vector<int>third(second.begin(), second.end());  //iterating through second
	vector<int>fourth(third);                        //a copy of third
}

//const����ʹ��const���������б�����ӡ
void PrintVector(const vector<int>& v)
{
	//vector<int>::const_iterator it = v.begin();   //C++98 ����������취
	auto it = v.begin();                            //C++11 ����������취
	while (it != v.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

//vector iterator ��ʹ��
void Test2()
{
	vector<int> v;
	v.push_back(1);      //ʹ��push_back����4������
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	// ��������������ָ���һ�����ͣ����Խ�����������Ķ��󵱳���ָ��ķ�ʽ����Ӧ��
	// ���ã������û�͸����(�û����Բ���֪���������ĵײ����ݽṹ)���������е�Ԫ��

	//ʹ�õ��������б�����ӡ
	//vector<int>::iterator it = v.begin();      
	auto it = v.begin();
	while(it != v.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

    //ʹ�õ����������޸�
	it = v.begin();
	while (it != v.end())
	{
		*it *= 2;
		++it;
	}

	//ʹ�÷�����������б����ٴ�ӡ
	//vector<int>::reverse_iterator rit = v.rbegin();
	auto rit = v.rbegin();
	while (rit != v.rend())
	{
		cout << *rit << " ";
		++rit;
	}
	cout << endl;

	PrintVector(v);
}

//vector������������
void Test3()
{
	//capacity �����ʹ��
	vector<int> foo;
	size_t sz = foo.capacity();
	cout << "mking foo grow:\n";
	for (int i = 0; i < 100; ++i)
	{
		foo.push_back(i);    //SeqList ���ݷ�ʽ�������¿ռ�  ����Ԫ�� �ͷžɿռ�
		if (sz != foo.capacity())
		{
			sz = foo.capacity();
			cout << "capacity change : " << sz << '\n';
		}
	}
	//ͨ���������н���ɿ���vs���뻷���¿ռ��С��1.5������
	//ע��linux���뻷���¿ռ��С��2.0������

	//reserve �����ʹ��
	vector<int> bar;
	sz = bar.capacity();
	bar.reserve(100);          //����϶δ�����˵�����ȹ�������ռ��С��ֻ����һ�οռ䣬�������˴���Ч��
	cout << "making bar grow : \n";
	for (int i = 0; i < 100; ++i)
	{
		bar.push_back(i);
		if (sz != bar.capacity())
		{
			sz = bar.capacity();
			cout << "capacity change: " << sz << '\n';
		}
	}

	//resize �����ʹ��
	vector<int> myvector;
	for (int i = 1; i < 10; ++i)
	{
		myvector.push_back(i);
	}
	myvector.resize(5);
	myvector.resize(8, 100);
	myvector.resize(12);
	cout << "myvector contains :";
	for (int i = 0; i < myvector.size(); i++)
	{
		cout << ' ' << myvector[i];
	}
	cout << endl;

}


//vector ��ɾ�Ĳ�
void Test4()
{
	int arr[] = { 1, 2, 3, 4 };
	vector<int> v(arr, arr + sizeof(arr) / sizeof(arr[0]));    //���乹��

	//vector<int>::iterator it = v.begin();
	auto it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	v.pop_back();    //βɾ
	v.pop_back();

	it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	v.push_back(3);   //β��
	v.push_back(4);

	//ʹ��find����3����λ�õ�iterator
	//vector<int>::iterator pos = find(v.begin(), v.end(), 3);
	auto pos = find(v.begin(), v.end(), 3);

	//��posλ��֮ǰ����30
	v.insert(pos, 30);

	//vector<int>::iterator it = v.begin();
	it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	pos = find(v.begin(), v.end(), 3);

	//ɾ��posλ�õ�ֵ
	v.erase(pos);

	it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}


//vectorԪ�ط���
void Test5()
{
	//���ֱ������ʷ�ʽ
	int arr[] = { 1, 2, 3, 4, 5 };
	vector<int> v(arr, arr + sizeof(arr) / sizeof(arr[0]));   //���乹��

	// 1��ͨ��[index]��ʽ��д��0��λ��
	v[0] = 10;
	cout << v[0] << endl;

	//2��ͨ��[index]��ʽ����vector
	for (size_t i = 0; i < v.size(); ++i)
	{
		cout << v[i] << " ";
	}
	cout << endl;

	//����swapv��v������Ԫ�� ,���¸��Կ��ٿռ�
	vector<int> swapv;
	swapv.swap(v);

	cout << "v data :";
	for (size_t i = 0; i < v.size(); ++i)
	{
		cout << v[i] << " ";
	}
	cout << endl;

	cout << "swapv data :";
	for (size_t i = 0; i < swapv.size(); ++i)
	{
		cout << swapv[i] << " ";
	}
	cout << endl;

	//C++11 ֧�ֵ���ʽ��Χfor����
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;

	//���������ʱ���
	//vector<int>::iterator it = v.begin();     // C++98
	auto it = v.begin();                        //  C++11
	while (it != v.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}


//vector������ʧЧ����
void Test6()
{
	int arr[] = { 1, 2, 3, 4, 5,};
	vector<int> v(arr, arr + sizeof(arr) / sizeof(arr[0]));    //���乹��

	//ʹ��find����3���ڵ�λ�õ�iterator
	vector<int>::iterator pos = find(v.begin(), v.end(), 3);   //find ������begin��end֮����ֵΪ3��Ԫ��,��begin��ʼ���ص�һ��ֵΪ3��Ԫ�ص�ַ

	//ɾ��posλ�õ����ݣ�����pos������ʧЧ
	v.erase(pos);
	//cout << *pos << endl;//�˴��ᵼ�·Ƿ�����

	//posλ�ò������ݣ�����pos������ʧЧ
	//insert�ᵼ�µ�����ʧЧ������Ϊinsert���ܻᵼ�����ݣ����ݺ�pos��ָ��ԭ���Ŀռ䣬��ԭ���Ŀռ��Ѿ��ͷ���
	pos = find(v.begin(), v.end(), 3);
	v.insert(pos, 30);
	//cout << *pos << endl;//�˴��ᵼ�·Ƿ�����

	//ʵ��ɾ��v������ż��
	//��������������������ż����erase����itʧЧ
	//��ʧЧ�ĵ���������++it,�ᵼ�³������
	//vector<int>::iterator it = v.begin();
	/*auto it = v.begin();
	while (it != v.end())
	{
		if (*it % 2 == 0)
		{
			v.erase(it);		
		}
		++it;
	}*/

	//�����ϴ�����иĽ���erase�᷵��ɾ��λ�õ���һ��λ��
	vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		if (*it % 2 == 0)
		{
			it = v.erase(it);
		}
		else
		    ++it;
	}
}



// ��vector������Ԫ�������
void Test7()
{
	vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	//���ְ취
	// ��һ�֣� 
	//v.resize(0);
	//�ڶ��֣�
	//v.clear();
	//�����֣�
	//v.erase(v.begin(), v.end());
	//�����֣�ʹ�õ�����
	auto it = v.begin();
	while (it != v.end())
	{
		it = v.erase(it);
	}

	cout << v.size() << endl;
}


int main()
{
	//Test1();       //constructing vectors  vector�Ĺ���
	//Test2();       //vector iterator ��ʹ��
	//Test3();       //vector ������������
	//Test4();       //vector ��ɾ�Ĳ�
	//Test5();       //vector Ԫ�ط���
	//Test6();       //vector ������ʧЧ����
	Test7();         // ��vector������Ԫ�������

	return 0;
}