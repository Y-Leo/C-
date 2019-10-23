#include<queue>
#include<iostream>
using namespace std;

namespace lxy
{
	template < class T, class Con = deque<T> >
	class queue
	{
	public:
		queue(){}
		void push(const T& x)
		{
			_c.push_back(x);
		}
		void pop()
		{
			_c.pop_back();
		}
		T& back()
		{
			return _c.back();
		}
		const T& back()const
		{
			return _c.back();
		}
		T& front()
		{
			return _c.front();
		}
		const T& front()const
		{
			return _c.front();
		}
		size_t size()const
		{
			return _c.size();
		}
		bool empty()const
		{
			return _cempty();
		}
	private:
		Con _c;
	};
}

void TestQueue()
{
	//适配体现在第二个模板参数可以使用不同的容器,然后适配生成的queue效果是一样的
	//lxy::queue<int,deque<int>> q;
	//lxy::queue<int,list<int>> q;

	lxy::queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	cout << q.size() << endl;
	cout << q.front() << endl;
	cout << q.back() << endl;

	q.pop();
	q.pop();
	cout << q.size() << endl;
	cout << q.front() << endl;
	cout << q.back() << endl;
}

int main()
{
	TestQueue();
	return 0;
}