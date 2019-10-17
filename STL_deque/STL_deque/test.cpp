
//STL_deque 常用接口练习使用
#include<iostream>
#include<deque>
#include<vector>
#include<algorithm>

using namespace std;


//范围for遍历访问deque
void PrintDeque(const deque<int>& d)
{
	for (const auto& e : d)
	{
		cout << e << " ";
	}
	cout << endl;
}

//测试deque的构造函数
void TestDeque1()
{
	//构造空的双端队列
	deque<int> d1;

	//用10个值为5的元素构造双端队列
	deque<int> d2(10, 5);
	PrintDeque(d2);

	//用vector的区间构造双端队列
	vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	deque<int> d3(v.begin(), v.end());
	PrintDeque(d3);

	//用d3拷贝构造d4
	deque<int> d4(d3);
	PrintDeque(d4);
}

//测试deque中的迭代器
void TestDeque2()
{
	//用数组区间构造deque
	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	deque<int> d(array, array + sizeof(array) / sizeof(array[0]));

	//利用正向迭代器打印deque中的元素
	//deque<int>::iterator it = d.begin();       //C++98 提供的定义迭代器的办法
    auto it = d.cbegin();                  //C++11 提供
	while (it != d.cend())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	/*
	//以上代码也可以简写
	for (auto it = d.cbegin(); it != d.cend(); ++it)
		cout << *it << " ";
	cout << endl;
	*/

	auto cit = d.cbegin();
	//*it = 100;    //该条语句变异不通过，it为const迭代器，其指向空间元素值不能修改

	//利用反向迭代器逆向打印deque中的元素
	for (auto rit = d.crbegin(); rit != d.crend(); ++rit)
		cout << *rit << " ";
	cout << endl;

}

//测试deque的元素修改问题以及其他操作
void TestDeque3()
{
	vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	deque<int> d1(v.begin(), v.end());

	//在deque头部插入1，尾部插入5，并打印
	d1.push_front(1);
	d1.push_back(5);
	PrintDeque(d1);
	cout << d1.size() << endl;
	cout << d1.front() << endl;
	cout << d1.back() << endl;

	//在deque的begin()位置插入元素0
	d1.insert(d1.begin(), 0);
	PrintDeque(d1);

	//删除deque首部与尾部元素
	d1.pop_front();
	d1.pop_back();
	d1.erase(d1.begin());
	PrintDeque(d1);

	//将deque中的元素清空
	d1.clear();
	cout << d1.size() << endl;
}


//对deque中的元素进行排序
void TestDequeSort()
{
	int array[] = { 5, 3, 21, 5, 12, -23, 43, 23, 0, 2 };
	deque<int> d(array, array + sizeof(array) / sizeof(array[0]));

	PrintDeque(d);

	//利用标准库中的算法对deque中的元素进行升序排序
	sort(d.begin(), d.end());
	PrintDeque(d);
}
/*
上述对deque中排序的操作效率是非常低的，当对deque进行排序时,需要多次对deque中的元素进行整体遍历，
而deque中的元素整体遍历效率比较低，这是因为deque底层空间不连续，如果要进行整体遍历，在某段空间
的默认或者首部时，必须要计算下一段或者前一段的空间位置，导致deque效率比较低下。
*/

int main()
{
	//TestDeque1();         //测试deque构造
	//TestDeque2();           //测试deque迭代器
	//TestDeque3();              //测试增删改插
	TestDequeSort();                  //测试排序
	return 0;
}