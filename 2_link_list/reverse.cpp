#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int ElemType;
typedef int Status;

typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;

Status InitList_L(LinkList &L) {
	L=(LinkList)malloc(sizeof(LNode));
	if(!L) exit(OVERFLOW);
	return OK;
 }

void CreateList_L(LinkList &L,int n){
	LinkList p;
	int i;
	L=(LinkList)malloc(sizeof(LNode));
	L->next=NULL;
	for(i=n;i>0;--i){
		p=(LinkList)malloc(sizeof(LNode));
		scanf("%d",&p->data);
		p->next=L->next;L->next=p;
	}
}

void ReserveList_L(LinkList &L){
	LinkList p=L->next;LinkList q;
	L->next=NULL;
	while(p)
	{
		q=p;p=p->next;
		q->next=L->next;
		L->next=q;
	}
}

Status OutputList_L(LinkList L)
{
	LinkList p=L->next;
	if(!p) return ERROR;
	while(p!=NULL)
	{	printf("%d ",p->data);
		p=p->next;
	}
	printf("\n");
	return OK;
}

int main()
{
	LinkList L;
	InitList_L(L);
	printf("创建单链表，输入五个元素：\n");
	CreateList_L(L,5);
	printf("输出单链表L所有元素：\n");
	OutputList_L(L);
	ReserveList_L(L);
	printf("输出倒序操作后单链表所有元素：\n");
	OutputList_L(L);
	printf("\n");
	return 0;
}

