#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 100
typedef int Status;
typedef int QElemType;
typedef struct{
	QElemType *base;
	int front;
	int rear;
}SqQueue;

Status InitQueue(SqQueue &Q){//��ʼ������ 
	Q.base=(QElemType*)malloc(MAXSIZE*sizeof(QElemType));
	if(!Q.base) exit(OVERFLOW);
	Q.front=Q.rear=0;
	return OK;
}

Status ClearQueue(SqQueue &Q){//��ն��� 
	if(!Q.base) exit(OVERFLOW);
	Q.front=Q.rear=0;
	return OK;
}

Status QueueEmpty(SqQueue &Q){//1Ϊ�գ�0Ϊ���� 
	if(Q.front==Q.rear==0) return TRUE;
	else return FALSE;
}

int QueueLength(SqQueue &Q){//���г��� 
	return (Q.rear-Q.front+MAXSIZE)%MAXSIZE;
}

Status GetHead(SqQueue Q,QElemType &e){//��ͷ��e 
	if(Q.front==Q.rear) return ERROR;
	e=Q.base[Q.front];
	return OK;
}

Status EnQueue(SqQueue &Q,QElemType e){//��� 
	if((Q.rear+1)%MAXSIZE==Q.front) return ERROR;
	Q.base[Q.rear]=e;
	Q.rear=(Q.rear+1)%MAXSIZE;
	return OK;
}

Status DeQueue(SqQueue &Q,QElemType &e){//���� 
	if(Q.front==Q.rear) return ERROR;
	e=Q.base[Q.front];
	Q.front=(Q.front+1)%MAXSIZE;
	return OK;
}

Status QueueTraverse(SqQueue &Q)//���� 
{
	int p;
	if(Q.front==Q.rear) return ERROR;
	p=Q.front;
	while(p<Q.rear){
		printf("%d ",Q.base[p]);
		p++;
	}
	printf("\n");
	return OK;
}

void main()
{
	int i,n;
	QElemType k,h,a,f;
	SqQueue Q;
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


