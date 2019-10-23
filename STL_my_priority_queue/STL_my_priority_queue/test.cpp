#include<iostream>
using namespace std;
#include<vector>

namespace lxy
{
	template<class T,class Sequence = vector<T>,class Compare = less<T>>
	class priority_queue
	{
	public:
		priority_queue() 
			:c()
		{}
		template<class InputIterator>
		priority_queue(InputIterator first, InputIterator last)
			: c(first, last)
		{
			make_heap(c.begin(), c.end(), comp);
		}

		bool empty()const
		{
			return c.empty();
		}
		size_t size()const
		{
			return c.size();
		}
		T& top()const
		{
			return c.front();
		}

		void push(const T& x)
		{
			c.push_back(x);
			push_heap(c.begin(), c.end(), comp);
		}
		void pop()
		{
			pop_heap(c.begin(), c.end(), comp);
			c.pop_back();
		}
	private:
		Sequence c;
		Compare comp;
	};  
}

void TestPriority_Queue()
{
	lxy::priority_queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	cout << q.size() << endl;
	cout << q.top() << endl;

	q.pop();
	q.pop();
	cout << q.size() << endl;
	cout << q.top() << endl;
}

int main()
{
	TestPriority_Queue();
	return 0;
}