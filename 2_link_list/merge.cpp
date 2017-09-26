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

void MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc) {
  // 已知单链线性表La和Lb的元素按值非递减排列。
  // 归并La和Lb得到新的单链线性表Lc，Lc的元素也按值非递减排列。
  LinkList pa, pb, pc;
  pa = La->next;    pb = Lb->next;
  Lc = pc = La;             // 用La的头结点作为Lc的头结点
  while (pa && pb) {
    if (pa->data <= pb->data) {
      pc->next = pa;   pc = pa;   pa = pa->next;
    }
    else { pc->next = pb;   pc = pb;   pb = pb->next; }
  }
  pc->next = pa ? pa : pb;  // 插入剩余段
  free(Lb);                 // 释放Lb的头结点
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
	LinkList La,Lb,Lc;
	InitList_L(La);InitList_L(Lb);InitList_L(Lc);
	printf("创建单链表，输入五个元素：\n");
	CreateList_L(La,5);
	printf("输出单链表La所有元素：\n");
	OutputList_L(La);
	printf("创建单链表，输入五个元素：\n");
	CreateList_L(Lb,5);
	printf("输出单链表Lb所有元素：\n");
	OutputList_L(Lb);
	MergeList_L(La,Lb,Lc);
	printf("输出合并后单链表所有元素：\n");
	OutputList_L(Lc);
	printf("\n");
	return 0;
}

