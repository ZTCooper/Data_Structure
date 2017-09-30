#include<stdio.h>
#include<stdlib.h>
#define MAXSTRLEN 255
typedef unsigned char SString[MAXSTRLEN+1];

int Index(SString S,SString T,int pos){
	int i=pos,j=1;
	while(i<=S[0]&&j<=T[0]){
		if(S[i]==T[j]){++i;++j;}
		else{i=i-j+2;j=1;}
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
	if(Index(S,T,pos))
		printf("匹配成功！\n");
	else printf("匹配失败！\n");
}
