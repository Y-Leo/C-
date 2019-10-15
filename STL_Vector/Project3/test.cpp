//Vector的简单使用

// vector底层结构：动态类型的顺序表
// vector<char>  string

#include<iostream>
using namespace std;
#include<vector>

//constructing vectors 构造
void Test1()
{
	vector<int> first;                               //empty vector of ints
	vector<int>second(4, 100);                       //four ints with value 100
	vector<int>third(second.begin(), second.end());  //iterating through second
	vector<int>fourth(third);                        //a copy of third
}

//const对象使用const迭代器进行遍历打印
void PrintVector(const vector<int>& v)
{
	//vector<int>::const_iterator it = v.begin();   //C++98 定义迭代器办法
	auto it = v.begin();                            //C++11 定义迭代器办法
	while (it != v.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

//vector iterator 的使用
void Test2()
{
	vector<int> v;
	v.push_back(1);      //使用push_back插入4个数据
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	// 迭代器：类似是指针的一种类型，可以将迭代器定义的对象当成是指针的方式进行应用
	// 作用：帮助用户透明的(用户可以不用知道该容器的底层数据结构)遍历容器中的元素

	//使用迭代器进行遍历打印
	//vector<int>::iterator it = v.begin();      
	auto it = v.begin();
	while(it != v.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

    //使用迭代器进行修改
	it = v.begin();
	while (it != v.end())
	{
		*it *= 2;
		++it;
	}

	//使用反向迭代器进行遍历再打印
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

//vector容量增长问题
void Test3()
{
	//capacity 的相关使用
	vector<int> foo;
	size_t sz = foo.capacity();
	cout << "mking foo grow:\n";
	for (int i = 0; i < 100; ++i)
	{
		foo.push_back(i);    //SeqList 扩容方式：开辟新空间  拷贝元素 释放旧空间
		if (sz != foo.capacity())
		{
			sz = foo.capacity();
			cout << "capacity change : " << sz << '\n';
		}
	}
	//通过以上运行结果可看出vs编译环境下空间大小以1.5倍增长
	//注：linux编译环境下空间大小以2.0倍增长

	//reserve 的相关使用
	vector<int> bar;
	sz = bar.capacity();
	bar.reserve(100);          //相比上段代码来说，事先估算所需空间大小，只开辟一次空间，大大提高了代码效率
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

	//resize 的相关使用
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


//vector 增删改查
void Test4()
{
	int arr[] = { 1, 2, 3, 4 };
	vector<int> v(arr, arr + sizeof(arr) / sizeof(arr[0]));    //区间构造

	//vector<int>::iterator it = v.begin();
	auto it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	v.pop_back();    //尾删
	v.pop_back();

	it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	v.push_back(3);   //尾插
	v.push_back(4);

	//使用find查找3所在位置的iterator
	//vector<int>::iterator pos = find(v.begin(), v.end(), 3);
	auto pos = find(v.begin(), v.end(), 3);

	//在pos位置之前插入30
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

	//删除pos位置的值
	v.erase(pos);

	it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}


//vector元素访问
void Test5()
{
	//三种遍历访问方式
	int arr[] = { 1, 2, 3, 4, 5 };
	vector<int> v(arr, arr + sizeof(arr) / sizeof(arr[0]));   //区间构造

	// 1、通过[index]方式读写第0个位置
	v[0] = 10;
	cout << v[0] << endl;

	//2、通过[index]方式遍历vector
	for (size_t i = 0; i < v.size(); ++i)
	{
		cout << v[i] << " ";
	}
	cout << endl;

	//交换swapv和v的所有元素 ,重新各自开辟空间
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

	//C++11 支持的新式范围for遍历
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;

	//迭代器访问遍历
	//vector<int>::iterator it = v.begin();     // C++98
	auto it = v.begin();                        //  C++11
	while (it != v.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}


//vector迭代器失效问题
void Test6()
{
	int arr[] = { 1, 2, 3, 4, 5,};
	vector<int> v(arr, arr + sizeof(arr) / sizeof(arr[0]));    //区间构造

	//使用find查找3所在的位置的iterator
	vector<int>::iterator pos = find(v.begin(), v.end(), 3);   //find 方法在begin到end之间找值为3的元素,从begin开始返回第一个值为3的元素地址

	//删除pos位置的数据，导致pos迭代器失效
	v.erase(pos);
	//cout << *pos << endl;//此处会导致非法访问

	//pos位置插入数据，导致pos迭代器失效
	//insert会导致迭代器失效，是因为insert可能会导致增容，增容后pos还指向原来的空间，而原来的空间已经释放了
	pos = find(v.begin(), v.end(), 3);
	v.insert(pos, 30);
	//cout << *pos << endl;//此处会导致非法访问

	//实现删除v中所有偶数
	//下面程序会崩溃掉，如果是偶数，erase导致it失效
	//对失效的迭代器进行++it,会导致程序崩溃
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

	//对以上代码进行改进，erase会返回删除位置的下一个位置
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



// 将vector中所有元素清除掉
void Test7()
{
	vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	//四种办法
	// 第一种： 
	//v.resize(0);
	//第二种：
	//v.clear();
	//第三种：
	//v.erase(v.begin(), v.end());
	//第四种：使用迭代器
	auto it = v.begin();
	while (it != v.end())
	{
		it = v.erase(it);
	}

	cout << v.size() << endl;
}


int main()
{
	//Test1();       //constructing vectors  vector的构造
	//Test2();       //vector iterator 的使用
	//Test3();       //vector 容量增长问题
	//Test4();       //vector 增删改查
	//Test5();       //vector 元素访问
	//Test6();       //vector 迭代器失效问题
	Test7();         // 将vector中所有元素清除掉

	return 0;
}