#include "Sa.h"
void BWT(int *T, int n, int K, int *L);								//������bwt�任���L
void BWT(int *T, int n, int K, int *L,char *text,int *LF,int *I);			//��¼C����rank���ڻ��LF���ؽ��ı�text
void reconstructT(char *text,char *retext,int *T,int n,int *L,int *LF,int *I);