
//模拟实现vector
//vector----可以存放任意类型的动态顺序表
#include<iostream>
#include<assert.h>

using namespace std;

namespace lxy    //自定义一个命名空间
{
	template<class T>   //写成模板形式，以供多个类型使用
	class vector
	{
	public:
		//vector 的迭代器实际上就是原生态的指针
		typedef T* iterator;
	public:
		/////////////////////////////////////////////////////////
		//构造与销毁
		vector()      //无参构造
			:_start(nullptr)
			,_finish(nullptr)
			,_endofstorage(nullptr)
		{}

		vector(int n, const T& data)
			:_start(new T[n])
		{
			for (size_t i = 0; i < n; ++i)
			{
				_start[i] = data;				
			}
			_finish = _start + n;
			_endofstorage = _finish;
		}

		//[first,last)区间构造
		template<class Iterator>
		vector(Iterator first, iterator last)
		{
			//计算区间之间的元素个数
			size_t n = 0;
			auto it = first;
			while (it != last)
			{
				++it;
				++n;
			}
			_start = new T[n];
			//将[first,last）区间中的元素放置到_start的空间中
			for (size_t i = 0; i < n; ++i)
			{
				_start[i] = *first++;
			}
			_finish = _start + n;
			_endofstorage = _finish;
		}

		vector(const vector<T>& vv)    //拷贝构造
			:_start(new T[vv.capacity()])    //为构造对象申请空间
		{
			//拷贝内容：深拷贝，不能使用memcpy(),避免二次释放的情况发生
			for (size_t i = 0; i < vv.size(); ++i)
			{
				_start[i] = vv[i];
			}
			_finish = _start + vv.size();
			_endofstorage = _start + vv.capacity();
		}

		void Swap(vector<T> v)
		{
			swap(_start, v._start);
			swap(_finish, v._finish);
			swap(_endofstorage, v._endofstorage);
		}

		vector<T>& operator=(const vector<T>& v)
		{
			Swap(v);
			return *this;
		}

		~vector()    //析构函数
		{
			if (_start)     //如果不为空
			{
				delete[] _start;    //销毁空间
				_start = _finish = _endofstorage = nullptr;    //释放指针
			}
		}


		/////////////////////////////////////////////////////////
		//容量操作
		size_t size()const
		{
			return _finish - _start;
		}

		size_t capacity()const
		{
			return _endofstorage - _start;
		}

		bool emoty()const
		{
			return _start == _finish;
		}

		//T():
		//如果T代表内置类型，T()----0
		//如果T代表自定义类型，T()----调用该类无参构造函数
		void resize(size_t newsize, const T&data = T())
		{
			size_t oldsize = size();
			if (newsize > oldsize)
			{
				size_t cap = capacity();
				if (newsize > cap)
				{
					reserve(newsize);
				}
				for (; oldsize < newsize; ++oldsize)
				{
					_start[oldsize] = data;
				}
			}
			_finish = _start + newsize;
		}

		void reserve(size_t newcapacity)
		{
			size_t oldcapacity = capacity();
			if (newcapacity > oldcapacity)
			{
				//1、申请新空间
				T* temp = new T[newcapacity];
				//2、拷贝元素
				//mencpy(temp, _start, size(*sizeof(T)));    //不推荐使用此方法,应该使用深拷贝，避免二次释放的情况发生
				size_t n = size();
				if (_start)
				{
					for (size_t i = 0; i < n; ++i)
					{
						temp[i] = _start[i];
					}
					//3、释放旧空间
					delete[] _start;
				}
				_start = temp;
				_finish = _start + n;
				_endofstorage = _start + newcapacity;
			}
		}

		/////////////////////////////////////////////////////////
		//迭代器
		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}


		/////////////////////////////////////////////////////////
		//元素访问操作  (大多都是成对存在)
		//v[0] = 10;   //v如果是普通类型
		T& operator[](size_t index)
		{
			assert(index < size());
			return _start[index];
		}
		const T& operator[](size_t index)const
		{
			assert(index < size());
			return _start[index];
		}

		T& front()
		{
			return *_start;
		}
		const T& front()const
		{
			return *_start;
		}

		T& back()
		{
			return *(_finish - 1);//这里最好不要使用_finish--,否则会修改_finish的位置
		}
		const T& back()const
		{
			return *(_finish - 1);
		}

		///////////////////////////////////////////////////////////
		//元素修改
		//时间复杂度O(1)
		void push_back(const T& data)
		{
			//插入之前检测是否需要扩容
			if (_finish == _endofstorage)
			{
				reserve(capacity() * 2 + 3);  //*2  默认假设每次扩容到两倍，+3  是为了防止原本capacity()为0
			}
			*_finish++ = data;   
		}

		void pop_back()
		{
			--_finish;
		}

		//返回值含义：返回新插入元素的位置
		iterator insert(iterator pos, const T& data)
		{
			//插入之前检测是否需要扩容
			if (_finish == _endofstorage)
			{
				reserve(capacity() * 2 + 3);  //*2  默认假设每次扩容到两倍，+3  是为了防止原本capacity()为0
			}
			//将[pos,_finish)之间的元素整体向后搬移一个位置
			auto it = _finish;
			while (it > pos)
			{
				*it = *(it - 1);
				it--;
			}
			//插入新元素
			*pos = data;
			++_finish;
			return pos;
		}

		iterator erase(iterator pos)
		{
			//判空
			if (pos == end())
			{
				return pos;
			}
			//it代表待搬移元素的位置
			auto it = pos + 1;
			while (it != _finish)
			{
				*(it - 1) = *it;
				++it;
			}
			--_finish;
			return pos;
		}

		void clear()
		{
			_finish = _start;
		}
	private:
		T* _start;
		T* _finish;
		T* _endofstorage;
	};
}


void Test1()
{
	lxy::vector<int> v1;
	lxy::vector<int> v2(10, 5);
	lxy::vector<int> v4(v2);
	lxy::vector<int> v5 = v2;

	int array[] = { 0, 2, 4, 6, 8 };
	lxy::vector<int> v3(array, array + sizeof(array) / sizeof(array[0]));

	cout << v2.size() << endl;
	cout << v2.capacity() << endl;
	cout << v3.front() << endl;
	cout << v3.back() << endl;

	for (size_t i = 0; i < v5.size(); ++i)
	{
		cout << v5[i] << " ";
	}
	cout << endl;

	//lxy::vector<int>::iterator it = v3.begin(); 
	auto it = v3.begin();
	while (it != v3.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	for (auto& e : v4)
	{
		cout << e << " ";
	}
	cout << endl;
}


void Test2()
{
	lxy::vector<int> v;
	v.push_back(1);
	v.push_back(3);
	v.push_back(6);
	v.push_back(9);

	cout << v.size() << endl;
	cout << v.capacity() << endl;
	cout << v.back() << endl;

	v.pop_back();
	cout << v.back() << endl;
	cout << v.size() << endl;

	cout << v.front() << endl;
	v.insert(v.begin(), 0);
	cout << v.front() << endl;
	cout << v.size() << endl;
}


void Test3()
{
	lxy::vector<int> v(10, 5);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.resize(5);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.resize(8);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.resize(20,5);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

}

int main()
{
	Test1();
	//Test2();
	//Test3();
	return 0;
}