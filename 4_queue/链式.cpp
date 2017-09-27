#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;
typedef int QElemType;
typedef struct QNode
{
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr;
typedef struct
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

Status InitQueue(LinkQueue &Q){
	Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
	if(!Q.front) exit(OVERFLOW);
	Q.front->next=NULL;
	return OK;
}

Status DestroyQueue(LinkQueue &Q){
	while(Q.front){
		Q.rear=Q.front->next;
		free(Q.front);
		Q.front=Q.rear;
	}
	return OK;
}

Status ClearQueue(LinkQueue &Q){
	QueuePtr p,q;
	if(!Q.front) exit(OVERFLOW);
	p=Q.front->next;
	Q.front->next=NULL;
	while(p){
		q=p;
		p=p->next;
		free(q);
	}
	Q.rear=Q.front;
	return OK;
}

Status QueueEmpty(LinkQueue &Q){
	if(Q.front==Q.rear) return TRUE;
	else return FALSE;
}

int QueueLength(LinkQueue &Q){
	QueuePtr p;
	int n=0;
	p=Q.front->next;
	while(p){
		n++;
		p=p->next;
	}
	return n;
}

Status GetHead(LinkQueue &Q,QElemType &e){
	QueuePtr p;
	if(Q.front==Q.rear) return ERROR;
	p=Q.front->next;
	e=p->data;
	return OK;
}

Status EnQueue(LinkQueue &Q,QElemType e){
	QueuePtr p;
	p=(QueuePtr)malloc(sizeof(QNode));
	if(!p) exit(OVERFLOW);
	p->data=e;	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
	return OK;
}

Status DeQueue(LinkQueue &Q,QElemType &e){
	QueuePtr p;
	if(Q.front==Q.rear) return ERROR;
	p=Q.front->next;
	e=p->data;
	Q.front->next=p->next;
	if(Q.rear==p) Q.rear=Q.front;
	free(p);
	return OK;
}

Status QueueTraverse(LinkQueue &Q){
	QueuePtr p=Q.front->next;
	if(p==NULL) return ERROR;
	while(p){
		printf("%d ",p->data);
		p=p->next;
	}
	printf("\n");
	return OK;
}

void main()
{
	int i,n;
	QElemType k,h,a,f;
	LinkQueue Q;
	printf("����һ���ն��У�\n");
	InitQueue(Q);
	printf("�ж϶����Ƿ�Ϊ�գ�\n");
	printf("QueueEmpty(Q)=%d\n",QueueEmpty(Q));
	printf("�������е�Ԫ�ظ�����\n");
	scanf("%d",&n);
	printf("����%d��������е�Ԫ��ֵ��\n",n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&k);
		EnQueue(Q,k);
	}
	printf("�������Ԫ�ص�ֵ��\n");
	QueueTraverse(Q);
	printf("���������е�Ԫ�ص�ֵ��");
	scanf("%d",&h);
	EnQueue(Q,h);
	printf("�������һ������Ԫ�غ����Ԫ�ص�ֵ��\n");
	QueueTraverse(Q);
	DeQueue(Q,a);
	printf("�����1��ɾ���Ķ�ͷԪ�ص�ֵ��%d\n",a);
	DeQueue(Q,a);
	printf("�����2��ɾ���Ķ�ͷԪ�ص�ֵ��%d\n",a);
	printf("�������ɾ����ͷԪ�غ���е�Ԫ��ֵ��");
	QueueTraverse(Q);
	if(!GetHead(Q,f))
		printf("�����ͷԪ�ص�ֵ��%d\n",f);
	printf("�������Ԫ�صĸ�����%d\n",QueueLength(Q));
	printf("��Q��Ϊ�ն��У�\n");
	ClearQueue(Q);
	printf("�������Ԫ�صĸ�����%d\n",QueueLength(Q));
	printf("�ж϶����Ƿ�Ϊ�գ�\n");
	printf("QueueEmpty(Q)=%d\n",QueueEmpty(Q));
}