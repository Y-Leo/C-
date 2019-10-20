#include<iostream>
using namespace std;
#include<stack>
#include<vector>

class Solution
{
public:
	int evalRPN(vector<string>& tokens)
	{
		stack<int> s;
		for (size_t i = 0; i < tokens.size(); ++i)
		{
			string& str = tokens[i];

			if (!("+" == str || "-" == str || "*" == str || "/" == str))
			{
				s.push(atoi(str.c_str()));
			}
			else
			{
				int right = s.top();
				s.pop();
				int left = s.top();
				s.pop();

				switch (str[0])
				{
				case'+':
					s.push(left + right);
					break;
				case'-':
					s.push(left - right);
					break;
				case'*':
					s.push(left*right);
					break;
				case'/':
					s.push(left / right);
					break;
				}
			}
		}
		return s.top();

	}
};

int main()
{
	Solution str;
	
	return 0;
}