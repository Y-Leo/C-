
//优先级队列默认使用vector作为其底层存储数据的容器，在vector上又使用了堆算法将vector中的元素构成队的结构，因此优先级队列就是堆。
#include<iostream>
using namespace std;
#include<vector>
#include<queue>
#include<functional>   //greater算法的头文件

void TestPriorityQueue1()
{
	//默认情况下，创建的是大堆，其底层按照小于号比较
	vector<int> v{ 4, 32, 4, 1, 67, 3, 211, 67, 8, 0, 1 };
	priority_queue<int> q1;
	for (auto& e : v)
	{
		q1.push(e);
	}
	cout << q1.top() << endl;

	//如果要建小堆，将第三个模板参数换成greater比较方式
	priority_queue < int, vector<int>, greater<int>> q2(v.begin(), v.end());
	cout << q2.top() << endl;
}

//如果在priority_queue中放自定义类型的数据，用户需要在自定义类型中提供>或<的重载
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
	//大堆，需要用户在自定义类型中提供<的重载
	priority_queue<Date> q1;
	q1.push(Date(2018, 10, 29));
	q1.push(Date(2018, 10, 28));
	q1.push(Date(2018, 10, 30));
	cout << q1.top() << endl;

	//如果要创建小堆，需要用户提供>的重载
	priority_queue<Date, vector<Date>, greater<Date>> q2;
	q2.push(Date(2018, 10, 29));
	q2.push(Date(2018, 10, 28));
	q2.push(Date(2018, 10, 30));
	cout << q2.top() << endl;
}

//有些情况下，用户可能需要提供比较器规则
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
	//自己制定比较的规则
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