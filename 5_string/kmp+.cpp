#include<stdio.h>
#include<stdlib.h>
#define MAXSTRLEN 255
typedef unsigned char SString[MAXSTRLEN+1];

void get_next(SString T,int next[]){
	int i=1,j=0;
	next[1]=0;
	while(i<T[0]){
		if(j==0||T[i]==T[j]) 
		{++i;++j;next[i]=j;}
		else j=next[j];
	}
}

int Index_KMP(SString S,SString T,int pos){
	int next[255];int i=pos,j=1;
	get_next(T,next);
	while(i<=S[0]&&j<=T[0]){
		if(j==0||S[i]==T[j]){++i;++j;}
		else j=next[j];
	}
	if(j>T[0]) return i-T[0];
	else return 0;
}

void main()
{
	SString S,T;int i,pos;
	printf("输入串S的长度：");
	scanf("%d",&S[0]);
	getchar();
	printf("输入串S的值：");
	for(i=1;i<=S[0];i++)
		scanf("%c",&S[i]);
	printf("输出串S的值：");
	for(i=1;i<=S[0];i++)
		printf("%c",S[i]);
	printf("\n");
	printf("输入串T的长度：");
	scanf("%d",&T[0]);
	getchar();
	printf("输入串T的值：");
	for(i=1;i<=T[0];i++)
		scanf("%c",&T[i]);
	printf("输出串T的值：");
	for(i=1;i<=T[0];i++)
		printf("%c",T[i]);
	printf("\n");
	printf("输入匹配主串的起始位置：");
	scanf("%d",&pos);
	if(Index_KMP(S,T,pos))
		printf("匹配成功！\n");
	else printf("匹配失败！\n");
}
