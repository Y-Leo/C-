//STL_List  list的常用接口简单使用
#include<iostream>
using namespace std;

//list:带头节点的双向循环链表

#include<list>
#include<vector>

//list构造

void TestList1()
{
	list<int> L1;    //构造空的L1
	list<int> L2(10,5);    //L2中放10个值为5的元素
	vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	list<int> L3(v.begin(), v.end());            //区间构造    vector 提供构造区间。
	//[begin(),end()),左闭右开
	list<int> L4(arr, arr + sizeof(arr) / sizeof(arr[0]));      //区间构造    数组提供构造区间。
	list<int> L5(L4);    //拷贝构造

	cout << L1.size() << endl;

	//迭代器访问L2
	//list<int>::iterator it = L2.begin();           //C++98  提供的办法
	auto  it = L2.begin();          //C++11 提供的办法
	while (it != L2.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	//范围for循环遍历L3     //C++11
	for (auto e : L3)
	{
		cout << e << " ";
	}
	cout << endl;

	cout << L4.front() << endl;
	cout << L4.back() << endl;

	//反向迭代器遍历L5
	auto rit = L5.rbegin();
	while (rit != L5.rend())
	{
		cout << *rit << " ";
		++rit;
	}
	cout << endl;
}

//List增删改查

void TestList2()
{
	list<int> L;
	L.push_back(1);            //尾插   插入五个元素
	L.push_back(2);
	L.push_back(3);
	L.push_back(4);
	L.push_back(5);

	cout << L.size() << endl;

	L.push_front(0);            //头插
	cout << L.front() << endl;

	L.pop_back();              //尾删
	cout << L.back() << endl;

	L.pop_front();               //头删
	cout << L.front() << endl;

	//1  2   3   4
	//list<int>::iterator it = L.begin();    //C++98
	auto it = L.begin();     //C++11  定义迭代器

	it = find(L.begin(), L.end(), 2);     //find()方法在区间内找第一个值为2的元素，返回值为该元素的迭代器
	if (it != L.end())    //判断条件保证L不为空
	{
		L.insert(it, 9);            //insert方法在it位置之前插入9
	}

	L.erase(it);            //删除it位置元素,要注意：此时it的含义--〉it指向第一次找到的值为2的元素，因此这里会删除之前找到的元素2

	cout << L.size() << endl;

	//IsOdd(int data);   操作同上
}
	
//remove()  ,  remove_if()

// 判断偶数操作
bool IsEven(int data)
{
	if (0 == data % 2)
		return true;
	return false;
}
//判断奇数操作
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

	//删除所有的2
	L.remove(2);            //remove()方法为删除所有和所传值相同的元素
	//1 3 4
	cout << L.size() << endl;

    //删除L中所有的偶数
	L.remove_if(IsEven);     //remove_if()方法为删除所有符合条件的元素，函数参数即为条件
	//1 3
	cout << L.size() << endl;

	//L.remove_if(IsOdd);   //删除L中所有的奇数
}

//unique()

void TestList4()
{
	list<int> L{ 1, 2, 3, 4, 9, 2, 2, 4, 2 };
	L.sort();      //排序
	for (auto e : L)
	{
		cout << e << " ";
	}
	cout << endl;

	//unique():去重，删掉重复的元素
	//使用unique()前提是保证链表是有序的
    L.unique();     
	auto it = L.begin();
	while (it != L.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

//迭代器失效问题
//list中迭代器失效----〉迭代器指向的节点不存在
void TestList5()
{
	list<int> L{ 1, 2, 3, 4 };
	//list<int>::iterator it = L.begin();    //C++98
	auto it = L.begin();    //C++11

	L.erase(it);   
	//it迭代器失效，erase之后，it所指向的节点已经被删除了
    //解决办法：重新给it赋值
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
	//TestList1();           //list构造
	//TestList2();           //List增删改查
	//TestList3();           //remove()  ,  remove_if()
	//TestList4();           //unique()
	TestList5();           //迭代器失效问题

	return 0;
}