
//ģ��ʵ��vector
//vector----���Դ���������͵Ķ�̬˳���
#include<iostream>
#include<assert.h>

using namespace std;

namespace lxy    //�Զ���һ�������ռ�
{
	template<class T>   //д��ģ����ʽ���Թ��������ʹ��
	class vector
	{
	public:
		//vector �ĵ�����ʵ���Ͼ���ԭ��̬��ָ��
		typedef T* iterator;
	public:
		/////////////////////////////////////////////////////////
		//����������
		vector()      //�޲ι���
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

		//[first,last)���乹��
		template<class Iterator>
		vector(Iterator first, iterator last)
		{
			//��������֮���Ԫ�ظ���
			size_t n = 0;
			auto it = first;
			while (it != last)
			{
				++it;
				++n;
			}
			_start = new T[n];
			//��[first,last�������е�Ԫ�ط��õ�_start�Ŀռ���
			for (size_t i = 0; i < n; ++i)
			{
				_start[i] = *first++;
			}
			_finish = _start + n;
			_endofstorage = _finish;
		}

		vector(const vector<T>& vv)    //��������
			:_start(new T[vv.capacity()])    //Ϊ�����������ռ�
		{
			//�������ݣ����������ʹ��memcpy(),��������ͷŵ��������
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

		~vector()    //��������
		{
			if (_start)     //�����Ϊ��
			{
				delete[] _start;    //���ٿռ�
				_start = _finish = _endofstorage = nullptr;    //�ͷ�ָ��
			}
		}


		/////////////////////////////////////////////////////////
		//��������
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
		//���T�����������ͣ�T()----0
		//���T�����Զ������ͣ�T()----���ø����޲ι��캯��
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
				//1�������¿ռ�
				T* temp = new T[newcapacity];
				//2������Ԫ��
				//mencpy(temp, _start, size(*sizeof(T)));    //���Ƽ�ʹ�ô˷���,Ӧ��ʹ���������������ͷŵ��������
				size_t n = size();
				if (_start)
				{
					for (size_t i = 0; i < n; ++i)
					{
						temp[i] = _start[i];
					}
					//3���ͷžɿռ�
					delete[] _start;
				}
				_start = temp;
				_finish = _start + n;
				_endofstorage = _start + newcapacity;
			}
		}

		/////////////////////////////////////////////////////////
		//������
		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}


		/////////////////////////////////////////////////////////
		//Ԫ�ط��ʲ���  (��඼�ǳɶԴ���)
		//v[0] = 10;   //v�������ͨ����
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
			return *(_finish - 1);//������ò�Ҫʹ��_finish--,������޸�_finish��λ��
		}
		const T& back()const
		{
			return *(_finish - 1);
		}

		///////////////////////////////////////////////////////////
		//Ԫ���޸�
		//ʱ�临�Ӷ�O(1)
		void push_back(const T& data)
		{
			//����֮ǰ����Ƿ���Ҫ����
			if (_finish == _endofstorage)
			{
				reserve(capacity() * 2 + 3);  //*2  Ĭ�ϼ���ÿ�����ݵ�������+3  ��Ϊ�˷�ֹԭ��capacity()Ϊ0
			}
			*_finish++ = data;   
		}

		void pop_back()
		{
			--_finish;
		}

		//����ֵ���壺�����²���Ԫ�ص�λ��
		iterator insert(iterator pos, const T& data)
		{
			//����֮ǰ����Ƿ���Ҫ����
			if (_finish == _endofstorage)
			{
				reserve(capacity() * 2 + 3);  //*2  Ĭ�ϼ���ÿ�����ݵ�������+3  ��Ϊ�˷�ֹԭ��capacity()Ϊ0
			}
			//��[pos,_finish)֮���Ԫ������������һ��λ��
			auto it = _finish;
			while (it > pos)
			{
				*it = *(it - 1);
				it--;
			}
			//������Ԫ��
			*pos = data;
			++_finish;
			return pos;
		}

		iterator erase(iterator pos)
		{
			//�п�
			if (pos == end())
			{
				return pos;
			}
			//it���������Ԫ�ص�λ��
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