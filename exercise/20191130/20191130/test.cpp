#include<iostream>
using namespace std;
#include<vector>
//���������Һ�Ϊn��������
/*
class Solution {
public:
	vector<int> FindNumbersWithSum(vector<int> array, int sum) {
		int i = 0, j = array.size() - 1;
		vector<int> ret;
		vector<int> tmp;
		int mul = array[j] * array[j];
		// bool flag = true;
		for (i; i < j; ++i)
		{
			while (i < j)
			{
				if ((array[i] + array[j]) == sum)
				{
					tmp.push_back(array[i]);
					tmp.push_back(array[j]);

					if (array[i] * array[j] < mul)
					{
						mul = array[i] * array[j];
						ret.push_back(tmp[0]);
						ret.push_back(tmp[1]);
						tmp.clear();
					}
					break;
				}
				--j;
			}
			j = array.size() - 1;
		}
		return ret;
	}
};
int main()
{
	vector<int> v = { 1,2,4,7,11,15};
	int n = 15;
	Solution A;
	A.FindNumbersWithSum(v, n);
	return 0;
}

*/

//1+2+3+...+n

class Solution {
public:
	int Sum_Solution(int n) {
		/*
		bool a[n][n + 1];
		return sizeof(a) >> 1;
		*/
		/*
		int ret = n;
		n && (ret += Sum_Solution(n - 1));
		return ret;
		*/
		return (int)(pow(n, 2) + n) >> 1;
	}
};

int main()
{
	Solution A;
	int n = 5;
	cout << A.Sum_Solution(n) << endl;
	return 0;
}


/*
���ȿ�ʮ������������ģ� 5+7=12��������
��һ������Ӹ�λ��ֵ�������λ���õ�2��
�ڶ����������λֵ���õ�10. �����һ���Ľ�λֵΪ0����ô��һ���õ���ֵ�������ս����
���������ظ�����������ֻ����ӵ�ֵ������������ĵõ��Ľ��2��10���õ�12��
ͬ�����ǿ����������ߵķ�ʽ���������ֵ��ӣ� 5-101��7-111 ��һ������Ӹ�λ��ֵ�������λ��
�õ�010��������ÿλ��Ӿ��൱�ڸ�λ����������101^111��
�ڶ����������λֵ���õ�1010���൱�ڸ�λ��������õ�101����������һλ�õ�1010��(101&111)<<1��
�������ظ����������� ��λ��� 010^1010=1000����λֵΪ100=(010&1010)<<1��
	 �����ظ�����������1000^100 = 1100����λֵΪ0������ѭ����1100Ϊ���ս�� */
int Add(int num1, int num2)
{
	return num2 ? Add(num1^num2, (num1&num2) << 1) : num1;
}