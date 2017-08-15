#include <iostream>
#include "BWT.h"
#define Path "d:\\test.txt"
const int maxn = 100000;
int main()
{
	char *text;
	char *retext;
	int *T;
	int *L;                           //bwt�任�������������������ԭ�ı��е�λ��
	int *LF;
	int I;                           //��¼#��L�г��ֵ�λ�ã���ѭ���ƶ�ʱ��ԭ�ַ�����ȵ�һ�У������ؽ��ı�
	text = new char[maxn];
	retext = new char[maxn];
	T = new int[maxn];
	L = new int[maxn];
	LF = new int[maxn];

	FILE*fp = NULL;              //��Ҫע��
	fp = fopen(Path, "r");
	if (NULL == fp)
	{
		printf("Can't open file!\n");
		return -1;            //Ҫ���ش������
	}
	char current;
	int totalNumber = 0;            //����δʵ����֮ǰ��Ҫô�����е�ȫ�ֱ�����Ϊstatic��Ҫô�ں����ٳ�ʼ��
	while (fscanf(fp, "%c", &current) != EOF)
	{
		text[totalNumber] = current;
		T[totalNumber] = current - 'a' + 1;
		totalNumber++;
	}
	std::cout << "Finish Reading!" << std::endl;

	text[totalNumber] = '#';
	T[totalNumber] = 0;                  //����DC3����SAʹ�ã�����һ����С�ַ�,��0��totalNumberʵ��totalNumber+1���ַ�
	T[totalNumber + 1] = 0;
	T[totalNumber + 2] = 0;

	fclose(fp);
	fp = NULL;			//��Ҫָ��գ������ָ��ԭ�ļ��򿪵�ַ

	BWT(T,totalNumber,27,L,text,LF,&I);

	std::cout << "���L[i]"<< std::endl;
	for (int i = 0; i < totalNumber+1; i++)
		std::cout << L[i] << " ";
	std::cout << std::endl;

	reconstructT(text,retext, T, totalNumber,L, LF,&I);

	std::cout << "���retext[i]:" << std::endl;
	for (int i = 0; i < totalNumber + 1; i++)
		std::cout << retext[i] << " ";
	std::cout << std::endl;
	return 0;
}