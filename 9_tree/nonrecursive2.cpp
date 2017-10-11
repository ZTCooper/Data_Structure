#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;
typedef char TElemType;
typedef struct CSNode
{	
	TElemType data;
	struct CSNode *firstchild,*nextsibling;
}CSNode,*CSTree;

typedef CSTree SElemType;
typedef struct
{
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

typedef CSTree QElemType;
typedef struct QNode
{
	QElemType data;
	Struct QNode *next;
}QNode,*QueuePtr;

int Nodenum=0;
int Count=0;

int CSTreeDepth2(CSTree T) {         /* �ǵݹ�������Ժ����ֵ������ʾ��������� */
  CSTree Q[100], p;
  int front=0, rear=0;         /* front,rear�Ƕ���Q�Ķ�ͷ��βԪ�ص�ָ�� */
  int last, dep;                 /* lastָ������ͬ���������һ����㣬dep��������� */
  if(T==NULL)  return 0;
  else { 
	last = 0;
	dep = 1;
    Q[rear++] = T;
    while(front<=last && front!=rear) { 
	  p=Q[front++];   /* ��ͷ���� */         
      while(p!=NULL) {   /* ��α��� */
		if(p->firstchild) Q[rear++] = p->firstchild;   /* ��һ��������� */
        p = p->nextsibling;   /* ͬ���ֵ�ָ����� */
      }
      if(front>last) {     /* �����������ȼ�1����ʼ���Ϊ0��*/
        dep++; last = rear;    /* last���Ƶ�ָ��ǰ������һ����� */
	  }
    }
    return dep;
  }
} // CSTreeDepth2



Status LeafCountCSTree(CSTree T) {
	//�������Ҷ�ӽ�㣬��ͳ��Ҷ�ӽ�����
    CSTree s[100];       /* s��ջ��ջ��Ԫ���������ָ�� */
	int top=0;
	while(T || top!=0)
	{
		if (T) {
			s[top++]=T; T=T->firstchild;   /* �����֧���� */
		}  
		else {
			T=s[--top];
			if(T->firstchild==NULL) {
				printf("%c", T->data);
				Count++;      /* Ҷ�ӽ�� */
			}
			T=T->nextsibling;
		}
	}
	return OK;
} // LeafCountCSTree
