#include <iostream>
#include <map>
#include "BWT.h"

void BWT(int *T,int n,int K,int *L)
{
	int *SA = new int[n+1];
	suffixArray( T, SA+1,n, K);
	SA[0] = n;
	for (int i = 0; i < n+1; i++)
		L[i] = (SA[i] - 1+n+1) % (n+1);				//�ô�bwt�任��������ַ���ԭ�ַ���λ�ã���0��ʼ
	return;
}

void BWT(int *T, int n, int K, int *L, char *text, int *LF,int *I)
{
	int *SA = new int[n + 1];
	int *rank = new int[n + 1];					//�ô���rank(L,L[i],i-1)����L������ǰi-1(����i-1)�й����ִ�����
	int *C = new int[n + 1];					//��Ϊ��i��λ�øպ���L[i]��ֻ����佨��һ����Ӧ���鼴�ɣ���¼�ַ�L[i]��ǰ�湲���ּ���
	suffixArray(T, SA + 1, n, K);
	SA[0] = n;
	for (int i = 0; i < n + 1; i++)
	{
		L[i] = (SA[i] - 1 + n + 1) % (n + 1);				//�ô�bwt�任��������ַ���ԭ�ַ���λ�ã���0��ʼ
		if (L[i]==n)
			*I = i;
	}

	std::map<char, int> count;
	char temp = text[SA[0]];
	int tempint=0;
	for (int i = 0; i < n + 1; i++)					//����C���˴��Ǵ�ͳ�����C�����Ƕ�Ԫ�ַ���ÿһ��λ�ö���¼����C���е�λ��
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

	for (int i = 0; i < n + 1; i++)                         //����rank
		rank[i] = count[text[L[i]]]++;

	for (int i = 0; i < n + 1; i++)							//����LF
		LF[i] = C[L[i]] + rank[i];

	std::cout << "���I��" << *I << std::endl;
	std::cout << "���C[i]" << std::endl;
	for (int i = 0; i < n + 1; i++)
		std::cout << C[i] << " ";
	std::cout << std::endl;
	std::cout << "���rank[i]" << std::endl;
	for (int i = 0; i < n + 1; i++)
		std::cout << rank[i] << " ";
	std::cout << std::endl;
	std::cout << "���LF[i]" << std::endl;
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