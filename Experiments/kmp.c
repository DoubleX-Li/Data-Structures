//Author: Double X Li
//Date: 2014-10-12

#include <stdio.h>

int num[20] = {0};

void findnext(char str[], int len)
{
	int i, j;
	num[0] = -1;
	for(j = 1; j < len; j++)
	{
		i = num[j-1];
		while(str[j] != str[i+1] && i >= 0)
		{
			i = num[i];
		}
		if(str[j] == str[i+1])
		{
			num[j] = i + 1;
		}
		else
		{
			num[j] = -1;
		}
	}
}

int kmp(char des[], int len1, char pat[], int len2)
{
	int p = 0, s = 0;
	findnext(pat, len2);
	while(p < len2 && s < len1)
	{
		if(pat[p] == des[s])
		{
			p++,s++;
		}
		else
		{
			if(p == 0)
			{
				s++;
			}
			else
			{
				p = num[p-1] + 1;
			}
		}
	}
	if(p < len2)
	{
		return -1;
	}
	return s - len2;
}

int main()
{
	char str1[] = "abcdeabcde";
	int len1 = 10;
	char str2[] = "eab";
	int len2 = 3;
	int x;
	x = kmp(str1,len1,str2,len2);
	printf("x = %d\n",x);
	return 0;
}
