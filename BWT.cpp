#include <iostream>
#include <map>
#include "BWT.h"

void BWT(int *T,int n,int K,int *L)
{
	int *SA = new int[n+1];
	suffixArray( T, SA+1,n, K);
	SA[0] = n;
	for (int i = 0; i < n+1; i++)
		L[i] = (SA[i] - 1+n+1) % (n+1);				//该处bwt变换保存的是字符在原字符的位置，从0开始
	return;
}

void BWT(int *T, int n, int K, int *L, char *text, int *LF,int *I)
{
	int *SA = new int[n + 1];
	int *rank = new int[n + 1];					//该处的rank(L,L[i],i-1)即在L数组中前i-1(包括i-1)中共出现次数，
	int *C = new int[n + 1];					//因为第i个位置刚好是L[i]，只需对其建立一个对应数组即可，记录字符L[i]在前面共出现几次
	suffixArray(T, SA + 1, n, K);
	SA[0] = n;
	for (int i = 0; i < n + 1; i++)
	{
		L[i] = (SA[i] - 1 + n + 1) % (n + 1);				//该处bwt变换保存的是字符在原字符的位置，从0开始
		if (L[i]==n)
			*I = i;
	}

	std::map<char, int> count;
	char temp = text[SA[0]];
	int tempint=0;
	for (int i = 0; i < n + 1; i++)					//计算C表，此处非传统意义的C表，而是对元字符的每一个位置都记录了在C表中的位置
	{
		if (text[SA[i]] == temp)
		{
			C[SA[i]] = tempint;
			continue;
		}
		else
		{
			tempint = i;
			C[SA[i]] = tempint;
		}
		temp = text[SA[i]];
	}

	for (int i = 0; i < n + 1; i++)                         //计算rank
		rank[i] = count[text[L[i]]]++;

	for (int i = 0; i < n + 1; i++)							//计算LF
		LF[i] = C[L[i]] + rank[i];

	std::cout << "输出I：" << *I << std::endl;
	std::cout << "输出C[i]" << std::endl;
	for (int i = 0; i < n + 1; i++)
		std::cout << C[i] << " ";
	std::cout << std::endl;
	std::cout << "输出rank[i]" << std::endl;
	for (int i = 0; i < n + 1; i++)
		std::cout << rank[i] << " ";
	std::cout << std::endl;
	std::cout << "输出LF[i]" << std::endl;
	for (int i = 0; i < n + 1; i++)
		std::cout << LF[i] << " ";
	std::cout << std::endl;
	delete[] SA;
	delete[] rank;
	delete[] C;
	return;
}

void reconstructT(char *text,char *retext, int *T,int n, int *L, int *LF,int *I)
{
	/*
	int I;
	for (int i = 0; i < n + 1;i++)
		if (L[i] == n)
		{
			I = i;
			break;
		}
	*/
	int j = *I;
	for (int k = n; k >= 0; k--)
	{
		T[k] = L[j];
		retext[k] = text[T[k]];
		j = LF[j];
	}
	return;
}