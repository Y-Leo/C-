#if 0
//��ˮƿ
#include<iostream>
using namespace std;

//ѭ��
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

//�ݹ�
//˼·����1��ƿ����һƿ�������ˣ��������������ϰ��һƿ������Ի�һƿ�ȡ�
int bottles(int n)
{
	if (n == 1)
		return 0;
	//���ϰ��һƿ�����Զ��һƿ
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

//���������ַ����е�������Ӵ�

#include<iostream>
using namespace std;
#include<string>

string CommonStr(string& s1, string& s2)
{
	//s�����������ս��
	string s;
	//ʹ��s2Ϊ����
	if (s1.size() > s2.size())
		swap(s1, s2);
	//���Ϊ�̴����ӳ������Ҷ̴�
	for (size_t i = 0; i < s1.size(); ++i)
	{
		//ret��������ʱ��
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
			//�����ʱ�����������մ���������ʱ���������մ�
			if (ret.size() > s.size())
				s = ret;
			//ÿ�������ʱ��
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