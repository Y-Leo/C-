#include<iostream>
using namespace std;
#include<vector>
//有序数组找和为n的两个数
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
首先看十进制是如何做的： 5+7=12，三步走
第一步：相加各位的值，不算进位，得到2。
第二步：计算进位值，得到10. 如果这一步的进位值为0，那么第一步得到的值就是最终结果。
第三步：重复上述两步，只是相加的值变成上述两步的得到的结果2和10，得到12。
同样我们可以用三步走的方式计算二进制值相加： 5-101，7-111 第一步：相加各位的值，不算进位，
得到010，二进制每位相加就相当于各位做异或操作，101^111。
第二步：计算进位值，得到1010，相当于各位做与操作得到101，再向左移一位得到1010，(101&111)<<1。
第三步重复上述两步， 各位相加 010^1010=1000，进位值为100=(010&1010)<<1。
	 继续重复上述两步：1000^100 = 1100，进位值为0，跳出循环，1100为最终结果 */
int Add(int num1, int num2)
{
	return num2 ? Add(num1^num2, (num1&num2) << 1) : num1;
}