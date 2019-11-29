#if 0
//丑数

#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>

class Solution {
public:
	int GetUglyNumber_Solution(int index) 
	{
		if (index < 7)
			return index;
		vector<int> v(index);
		v[0] = 1;
		int pos2 = 0, pos3 = 0, pos5 = 0, i = 0;
		for (i = 1; i < index; ++i)
		{
			v[i] = min(v[pos2] * 2, min(v[pos3] * 3, v[pos5] * 5));
			if (v[pos2] * 2 == v[i])pos2++;
			if (v[pos3] * 3 == v[i])pos3++;
			if (v[pos5] * 5 == v[i])pos5++;
		}
		return v[index - 1];
	}
};


int main()
{
	Solution A;
	int n = 0;
	while (cin >> n)
	{
		cout << A.GetUglyNumber_Solution(n) << endl;
	}
	return 0;
}

#endif

#if 0

//左旋字符串
#include<iostream>
using namespace std;
#include<string>


class Solution {
public:
	string LeftRotateString(string str, int n) {
		if (str.empty() || n > str.size())
			return "";
		string tmp = str.substr(0, n);
		str += tmp;
		str.erase(0, n);
		return str;
	}
	
};

int main()
{
	Solution A;
	string str = "abcXYZdef";
	int n = 3;
	cout << A.LeftRotateString(str, n) << endl;
	return 0;
}
#endif

#include<iostream>
using  namespace std;

int cmp(const void* a, const void* b)
{
	return (*(int*)a - *(int*)b);
}


bool duplicate(int numbers[], int length, int* duplication) {
	/*
	//方法一：哈希表计数法
	if(numbers==NULL || length<1)
		return false;
	int* array=new int[length]();//构建hash表，初始化为0
	for(int i=0;i<length;i++){
		++array[numbers[i]];//存储每一个数出现的次数，
		if(array[numbers[i]]>1){//出现的次数大于1，即第一个重复的数字
			*duplication=numbers[i];
			return true;
		}
	}
	return false;
	*/

	if (numbers == NULL || length < 1)
		return false;
	qsort(numbers, length, sizeof(int), cmp);
	for (int i = 0; i < length - 1; i++)
	{
		if (numbers[i] == numbers[i + 1])
		{
			*duplication = numbers[i];
			return true;
		}
	}
	return false;

}

int main()
{
	int arr[4] = { 3,4,3,1 };
	duplicate(arr, 4, arr);
	return 0;
}