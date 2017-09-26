#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef int Status;
typedef int ElemType;
typedef struct
{	ElemType *elem;
	int length;
	int listsize;
}SqList;

Status InitList_Sq(SqList &L)
{
	L.elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!L.elem) exit(OVERFLOW);
	L.length=0;
	L.listsize=LIST_INIT_SIZE;
	return OK;
}//InitList_Sq

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

Status ListInsert_Sq(SqList &L,int i,ElemType e)
{
	ElemType *p;
	if(i<1||i>L.length+1) return ERROR;
	if(L.length>=L.listsize){
		ElemType *newbase=(ElemType *)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
		if(!newbase) return ERROR;
		L.elem=newbase;
		L.listsize+=LISTINCREMENT;
	}
	ElemType *q=&(L.elem[i-1]);
	for(p=&(L.elem[L.length-1]);p>=q;--p) *(p+1)=*p;
	*q=e;
	++L.length;
	return OK;
}//ListInsert_Sq

Status ListDelete_Sq(SqList &L,int i,ElemType &e)
{
	ElemType *p,*q;
	if((i<1)||(i>L.length)) return ERROR;
	p=&(L.elem[i-1]);
	e=*p;
	q=L.elem+L.length-1;
	for(++p;p<=q;++p)*(p-1)=*p;
	--L.length;
	return OK;
}//ListDelete_Sq

int LocateElem(SqList L,ElemType e)
{
	int i=1;
	while(i<=L.length&&L.elem[i-1]!=e) i++;
	if(i<L.length)
		return i;
	else
		return 0;
}

void ListOutput_Sq(SqList L)
{
	int i;
	if(L.length==0) return;
	for(i=0;i<L.length;i++)
		printf("%d",L.elem[i]);
	printf("\n");
}

int main()
{
	ElemType b,dd;
	SqList L;
	printf("初始化顺序表！");
	InitList_Sq(L);
	if(L.length==0)
		printf("顺序表为空！\n");
	printf("创建顺序表！");
	ListCreate_Sq(L,5);
	printf("输出顺序表所有元素！\n");
	ListOutput_Sq(L);
	printf("在顺序表第4个位置插入%d！\n",b);
	scanf("%d",&b);
	ListInsert_Sq(L,4,b);
	printf("输出插入操作后顺序表所有元素！\n");
	ListOutput_Sq(L);
	printf("删除顺序表第3个位置的元素！\n");
	ListDelete_Sq(L,3,dd);
	printf("输出删除操作后顺序表所有元素！\n");
	ListOutput_Sq(L);
	return 0;
}
