#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define LIST_INIT_SIZE 100
#define LISTINSTINCREMENT 10
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;
typedef int ElemType;
typedef struct{
	ElemType *elem;
	int length;
	int listsize;
}SqList;

Status InitList_Sq(SqList &L){
	L.elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!L.elem) exit(OVERFLOW);
	L.length=0;
	L.listsize=LIST_INIT_SIZE;
	return OK;
}

Status ListCreate_Sq(SqList &L,int n)
{
	int i;
	printf("输入%d个元素：\n",n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&L.elem[i]);
		++L.length;
	}//printf("\n");
	if(L.length==0) return ERROR;
}

void ListOrder_Sq(SqList &L)
{
	for(int i=0;i<=L.length-2;i++)
	{
		int k=i;
		for(int j=i+1;j<=L.length-1;j++)
			if(L.elem[j]<L.elem[k]) k=j;
			if(k!=i)
			{int temp=L.elem[k];L.elem[k]=L.elem[i];L.elem[i]=temp;
			}
	}
}

void ListOutput_Sq(SqList L)
{
	int i;
	if(L.length==0) return;
	for(i=0;i<L.length;i++)
		printf("%d ",L.elem[i]);
	printf("\n");
}

int main()
{
	SqList L;
	printf("初始化顺序表！");
	InitList_Sq(L);
	if(L.length==0)
		printf("顺序表为空！\n");
	printf("创建顺序表！");
	ListCreate_Sq(L,5);
	printf("输出顺序表所有元素！\n");
	ListOutput_Sq(L);
	ListOrder_Sq(L);
	printf("输出排序操作后顺序表所有元素：\n");
	ListOutput_Sq(L);
	return 0;
}