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
  // ��֪�������Ա�La��Lb��Ԫ�ذ�ֵ�ǵݼ����С�
  // �鲢La��Lb�õ��µĵ������Ա�Lc��Lc��Ԫ��Ҳ��ֵ�ǵݼ����С�
  LinkList pa, pb, pc;
  pa = La->next;    pb = Lb->next;
  Lc = pc = La;             // ��La��ͷ�����ΪLc��ͷ���
  while (pa && pb) {
    if (pa->data <= pb->data) {
      pc->next = pa;   pc = pa;   pa = pa->next;
    }
    else { pc->next = pb;   pc = pb;   pb = pb->next; }
  }
  pc->next = pa ? pa : pb;  // ����ʣ���
  free(Lb);                 // �ͷ�Lb��ͷ���
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
	printf("�����������������Ԫ�أ�\n");
	CreateList_L(La,5);
	printf("���������La����Ԫ�أ�\n");
	OutputList_L(La);
	printf("�����������������Ԫ�أ�\n");
	CreateList_L(Lb,5);
	printf("���������Lb����Ԫ�أ�\n");
	OutputList_L(Lb);
	MergeList_L(La,Lb,Lc);
	printf("����ϲ�����������Ԫ�أ�\n");
	OutputList_L(Lc);
	printf("\n");
	return 0;
}

