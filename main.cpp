#include <iostream>
#include "BWT.h"
#define Path "d:\\test.txt"
const int maxn = 100000;
int main()
{
	char *text;
	char *retext;
	int *T;
	int *L;                           //bwt变换以整数编码输出，即在原文本中的位置
	int *LF;
	int I;                           //记录#在L中出现的位置，即循环移动时与原字符串相等的一行，用于重建文本
	text = new char[maxn];
	retext = new char[maxn];
	T = new int[maxn];
	L = new int[maxn];
	LF = new int[maxn];

	FILE*fp = NULL;              //需要注意
	fp = fopen(Path, "r");
	if (NULL == fp)
	{
		printf("Can't open file!\n");
		return -1;            //要返回错误代码
	}
	char current;
	int totalNumber = 0;            //在类未实例化之前，要么把类中的全局变量设为static，要么在后面再初始化
	while (fscanf(fp, "%c", &current) != EOF)
	{
		text[totalNumber] = current;
		T[totalNumber] = current - 'a' + 1;
		totalNumber++;
	}
	std::cout << "Finish Reading!" << std::endl;

	text[totalNumber] = '#';
	T[totalNumber] = 0;                  //用于DC3构造SA使用，最后加一个最小字符,从0到totalNumber实际totalNumber+1个字符
	T[totalNumber + 1] = 0;
	T[totalNumber + 2] = 0;

	fclose(fp);
	fp = NULL;			//需要指向空，否则会指向原文件打开地址

	BWT(T,totalNumber,27,L,text,LF,&I);

	std::cout << "输出L[i]"<< std::endl;
	for (int i = 0; i < totalNumber+1; i++)
		std::cout << L[i] << " ";
	std::cout << std::endl;

	reconstructT(text,retext, T, totalNumber,L, LF,&I);

	std::cout << "输出retext[i]:" << std::endl;
	for (int i = 0; i < totalNumber + 1; i++)
		std::cout << retext[i] << " ";
	std::cout << std::endl;
	return 0;
}