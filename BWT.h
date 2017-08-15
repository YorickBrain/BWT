#include "Sa.h"
void BWT(int *T, int n, int K, int *L);								//单纯的bwt变换获得L
void BWT(int *T, int n, int K, int *L,char *text,int *LF,int *I);			//记录C表与rank用于获得LF以重建文本text
void reconstructT(char *text,char *retext,int *T,int n,int *L,int *LF,int *I);