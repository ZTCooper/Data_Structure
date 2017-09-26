#include<stdio.h>
#define MaxSize 50
typedef int ElemType;
typedef struct
{	ElemType data[MaxSize];
	int length;
}SqList;

void InitList(SqList &L)
{
	L.length=0;
}

void CreatList(SqList&L,int n)
{
	int i;
	printf("输入%d个元素：\n",n);
	for(i=0;i<n;i++)
		scanf("%d",&L.data[i]);
	printf("\n");
	L.length=n;
}

int ListEmpty(SqList L)
{
	return (L.length==0);
}

int ListLength(SqList L)
{
	return (L.length);
}

void DispList(SqList L)
{
	int i;
	if(L.length==0) return;
	for(i=0;i<L.length;i++)
		printf("%d",L.data[i]);
	printf("\n");
}

int GetElem(SqList L,int i,ElemType &e)
{
	if (i<1||i>L.length) return 0;
	e=L.data[i-1];	
	return 1;
}

int LocateElem(SqList L,ElemType e)
{
	int i=1;
	while(i<=L.length&&L.data[i-1]!=e) i++;
	if(i<L.length)
		return i;
	else
		return 0;
}

int ListInsert(SqList &L,int i,ElemType e)
{
	int j;
	if (i<1||i>L.length+1) return 0;
	for(j=L.length-1;j>=i-1;j--)
		L.data[j+1]=L.data[j];
	L.data[i-1]=e;
	++L.length;
	return 1;
}

int ListDelete(SqList &L,int i,ElemType &e)
{
	int j;
	if(i<1||i>L.length) return 0;
	e=L.data[i-1];
	for(j=i-1;j<L.length-1;j++)
		L.data[j]=L.data[j+1];
	--L.length;
	return 1;
}

void main()
{
	ElemType dd,a,b;
	SqList L;
	InitList(L);
	if(ListEmpty(L))
		printf("顺序表为空！\n");
	printf("创建顺序表！");
	CreatList(L,5);
	printf("输出顺序表所有元素！\n");
	DispList(L);
	printf("输出顺序表长度！\n");
	printf("ListLength=%d\n",ListLength(L));
	printf("判断顺序表是否为空！\n");
	printf("ListEmpty(L)=%d\n",ListEmpty(L));
	printf("输出顺序表第3个位置元素到dd！\n");
	GetElem(L,3,dd);
	printf("dd=%d\n",dd);
	printf("查找元素a:");
	scanf("%d",&a);
	printf("元素%d在顺序表的位置为：%d\n",a,LocateElem(L,a));
	printf("插入元素b：");
	scanf("%d",&b);
	printf("在顺序表第4个位置插入%d！\n",b);
	ListInsert(L,4,b);
	printf("输出插入操作后顺序表所有元素！\n");
	DispList(L);
	printf("删除顺序表第3个位置的元素！\n");
	ListDelete(L,3,dd);
	printf("输出删除操作后顺序表所有元素！\n");
	DispList(L);
}


