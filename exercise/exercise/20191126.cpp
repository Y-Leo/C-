#if 0
//汽水瓶
#include<iostream>
using namespace std;

//循环
int bottles1(int n)
{
	int ret = 0;
	while (n > 2)
	{
		ret += n / 3;
		n = n / 3 + n % 3;
	}
	if (n == 2)
		ret += 1;
	return ret;
}

//递归
//思路：有1个瓶盖则一瓶都换不了，有两个可以问老板借一瓶，则可以换一瓶喝。
int bottles(int n)
{
	if (n == 1)
		return 0;
	//向老板借一瓶，可以多喝一瓶
	if (n == 2)
		return 1;
	return n / 3 + bottles(n / 3 + n % 3);
}

int main()
{
	int n = 0;
	while (cin >> n)
	{
		cout << bottles1(n) << endl;
	}
	return 0;
}

#endif

//查找两个字符串中的最长公共子串

#include<iostream>
using namespace std;
#include<string>

string CommonStr(string& s1, string& s2)
{
	//s用来保存最终结果
	string s;
	//使得s2为长串
	if (s1.size() > s2.size())
		swap(s1, s2);
	//外层为短串，从长串中找短串
	for (size_t i = 0; i < s1.size(); ++i)
	{
		//ret用来存零时串
		string ret;
		for (size_t j = 0; j < s2.size(); ++j)
		{
			int tmp = i;
			while (s1[tmp] == s2[j])
			{
				ret += s1[tmp];
				tmp++;
				j++;
			}
			//如果零时串长大于最终串长，则零时串赋给最终串
			if (ret.size() > s.size())
				s = ret;
			//每次清空临时串
			ret.clear();
		}
	}
	return s;
}

int main()
{
	string s1, s2;
	while (cin >> s1 >> s2)
	{
		cout << CommonStr(s1, s2) << endl;
	}
	return 0;
}