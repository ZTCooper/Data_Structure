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

void OrderList_L(LinkList &L){
	LinkList r,pre,p,q;
	r=L;
	while(r->next)
	{
		pre=r;p=r->next;
		while(p->next)
			if(pre->next->data>p->next->data)
			{
				pre=p;p=p->next;
			}
			else p=p->next;
			q=pre->next;pre->next=q->next;
			q->next=r->next;r->next=q;
			r=q;
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
	printf("�����������������Ԫ�أ�\n");
	CreateList_L(L,5);
	printf("���������L����Ԫ�أ�\n");
	OutputList_L(L);
	OrderList_L(L);
	printf("��������������������Ԫ�أ�\n");
	OutputList_L(L);
	printf("\n");
	return 0;
}

