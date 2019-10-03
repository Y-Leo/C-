/*
#include<stdio.h>
#include<windows.h>

void Find(int arr[], int len)
{
	int num1 = 0;
	int num2 = 0;
	int ret = 0;
	int n = 0;
	int i = 0;
	int bit = 0;
	for (i = 0; i < len; i++)
	{
		ret = ret ^ arr[i];
	}
	for (n = 0; n < 32; n++)
	{
		if ((ret >> n) & 1 == 1)
			break;
	}
	for (i = 0; i < len; i++)
	{
		if ((arr[i] >> n) & 1 == 1)
			num1 = num1 ^ arr[i];
		else
			num2 = num2 ^ arr[i];
	}
	printf(" num1=%d\n num2=%d\n", num1, num2);
}


void main()
{
	int a[] = { 1, 2, 3, 3, 2, 1, 4, 5 };
	int len = sizeof(a) / sizeof(a[0]);
	Find(a, len);
	system("pause");
	return 0;
}
*/
/*
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include<Windows.h>
int Drink_sum(int money, int price)
{
	int sum = 0;
	int temp = 0;
	int ret = 0;
	sum = money / price;
	ret = sum;
	while (ret / 2 != 0)
	{
		temp = ret;
		ret = ret / 2;
		sum += ret;
		ret = temp % 2 + ret;
	}
	return sum;
}
int main()
{
	int money = 0;
	int price = 0;
	printf("please enter money and price:\n");
	scanf("%d %d", &money, &price);
	int bottle = Drink_sum(money, price);
	printf("%d元可以喝汽水%d瓶\n", money, bottle);
	system("pause");
	return 0;
}
*/
/*
#include <stdio.h>
#include<Windows.h>
#include<assert.h>
char* My_strcpy(char* str1, char* str2)
{
	char* ret = str1;
	assert(str1 != NULL && str2 != NULL);
	while ((*str1++ = *str2++) != '\0')
	{
		;
	}
	return ret;
}
int main()
{
	char arr1[20] = "abcdef";
	char *arr2 = "gh";
	printf("%s\n", My_strcpy(arr1, arr2));
	system("pause");
	return 0;
}
*/
/*
#include <stdio.h>
#include<Windows.h>
#include<assert.h>
char* My_strcpy(char* str1, char* str2)
{
	char* ret = str1;
	assert(str1 != NULL && str2 != NULL);
	//拷贝的位置不同
	while (*str1 != '\0')
	{
		str1++;
	}
	while ((*str1++ = *str2++) != '\0')
	{
		;
	}
	return ret;
}
int main()
{
	char arr1[20] = "abcdef";
	char *arr2 = "gh";
	printf("%s\n", My_strcpy(arr1, arr2));
	system("pause");
	return 0;
}
*/
#include <stdio.h>
#include<Windows.h>
#include<assert.h>

void * memmove(void *dst, const void * src, size_t count)
{
	void * ret = dst;
	if (dst <= src || (char*)dst >= ((char*)src + count))
	{
		while (count--)
		{
			*(char*)dst = *(char*)src;
			dst = (char*)dst + 1;
			src = (char*)src + 1;
		}
	}
	else{
		dst = (char*)dst - 1;
		src = (char*)src - 1;
		while (count--)
		{
			*(char*)dst = *(char*)src;
			dst = (char*)dst - 1;
			src = (char*)src - 1;
		}
	}
	return(ret);
}

int main()
{
	char src[] = "hello";
	char dst[] = "hahha world";
	memmove(dst, src, strlen(src));
	printf("%s\n", dst);
	system("pause");
	return 0;
}