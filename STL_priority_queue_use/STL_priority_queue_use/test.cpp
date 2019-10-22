
//���ȼ�����Ĭ��ʹ��vector��Ϊ��ײ�洢���ݵ���������vector����ʹ���˶��㷨��vector�е�Ԫ�ع��ɶӵĽṹ��������ȼ����о��Ƕѡ�
#include<iostream>
using namespace std;
#include<vector>
#include<queue>
#include<functional>   //greater�㷨��ͷ�ļ�

void TestPriorityQueue1()
{
	//Ĭ������£��������Ǵ�ѣ���ײ㰴��С�ںűȽ�
	vector<int> v{ 4, 32, 4, 1, 67, 3, 211, 67, 8, 0, 1 };
	priority_queue<int> q1;
	for (auto& e : v)
	{
		q1.push(e);
	}
	cout << q1.top() << endl;

	//���Ҫ��С�ѣ���������ģ���������greater�ȽϷ�ʽ
	priority_queue < int, vector<int>, greater<int>> q2(v.begin(), v.end());
	cout << q2.top() << endl;
}

//�����priority_queue�з��Զ������͵����ݣ��û���Ҫ���Զ����������ṩ>��<������
class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
		:_year(year)
		, _month(month)
		, _day(day)
	{}

	bool operator<(const Date& d)const
	{
		return(_year < d._year) ||
			(_year == d._year&&_month < d._month) ||
			(_year == d._year&_month == d._month&&_day < d._day);
	}

	bool operator>(const Date& d)const
	{
		return(_year > d._year) ||
			(_year == d._year&&_month > d._month) ||
			(_year == d._year&_month == d._month&&_day > d._day);
	}

	friend ostream& operator<<(ostream& _cout, const Date&d)
	{
		_cout << d._year << "-" << d._month << "-" << d._day;
		return _cout;
	}

private:
	int _year;
	int _month;
	int _day;
};

void TestPriorityQueue2()
{
	//��ѣ���Ҫ�û����Զ����������ṩ<������
	priority_queue<Date> q1;
	q1.push(Date(2018, 10, 29));
	q1.push(Date(2018, 10, 28));
	q1.push(Date(2018, 10, 30));
	cout << q1.top() << endl;

	//���Ҫ����С�ѣ���Ҫ�û��ṩ>������
	priority_queue<Date, vector<Date>, greater<Date>> q2;
	q2.push(Date(2018, 10, 29));
	q2.push(Date(2018, 10, 28));
	q2.push(Date(2018, 10, 30));
	cout << q2.top() << endl;
}

//��Щ����£��û�������Ҫ�ṩ�Ƚ�������
class Less
{
public:
	bool operator()(const Date* pLeft, const Date* pRight)
	{
		return *pLeft < *pRight;
	}
};

void TestPriorityQueue3()
{
	//�Լ��ƶ��ȽϵĹ���
	priority_queue<Date*, vector<Date*>, Less> q;
	q.push(&Date(2018, 10, 29));
	q.push(&Date(2018, 10, 28));
	q.push(&Date(2018, 10, 30));
	cout << *q.top() << endl;
}
int main()
{
	//TestPriorityQueue1();
	//TestPriorityQueue2();
	TestPriorityQueue3();
	return 0;
}