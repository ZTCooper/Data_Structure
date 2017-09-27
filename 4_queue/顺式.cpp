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

Status InitQueue(SqQueue &Q){//初始化队列 
	Q.base=(QElemType*)malloc(MAXSIZE*sizeof(QElemType));
	if(!Q.base) exit(OVERFLOW);
	Q.front=Q.rear=0;
	return OK;
}

Status ClearQueue(SqQueue &Q){//清空队列 
	if(!Q.base) exit(OVERFLOW);
	Q.front=Q.rear=0;
	return OK;
}

Status QueueEmpty(SqQueue &Q){//1为空，0为不空 
	if(Q.front==Q.rear==0) return TRUE;
	else return FALSE;
}

int QueueLength(SqQueue &Q){//队列长度 
	return (Q.rear-Q.front+MAXSIZE)%MAXSIZE;
}

Status GetHead(SqQueue Q,QElemType &e){//队头赋e 
	if(Q.front==Q.rear) return ERROR;
	e=Q.base[Q.front];
	return OK;
}

Status EnQueue(SqQueue &Q,QElemType e){//入队 
	if((Q.rear+1)%MAXSIZE==Q.front) return ERROR;
	Q.base[Q.rear]=e;
	Q.rear=(Q.rear+1)%MAXSIZE;
	return OK;
}

Status DeQueue(SqQueue &Q,QElemType &e){//出队 
	if(Q.front==Q.rear) return ERROR;
	e=Q.base[Q.front];
	Q.front=(Q.front+1)%MAXSIZE;
	return OK;
}

Status QueueTraverse(SqQueue &Q)//遍历 
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
	printf("创建一个空队列！\n");
	InitQueue(Q);
	printf("判断队列是否为空！\n");
	printf("QueueEmpty(Q)=%d\n",QueueEmpty(Q));
	printf("创建队列的元素个数：\n");
	scanf("%d",&n);
	printf("输入%d个插入队列的元素值：\n",n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&k);
		EnQueue(Q,k);
	}
	printf("输出队列元素的值：\n");
	QueueTraverse(Q);
	printf("输入插入队列的元素的值：");
	scanf("%d",&h);
	EnQueue(Q,h);
	printf("输出插入一个队列元素后队列元素的值：\n");
	QueueTraverse(Q);
	DeQueue(Q,a);
	printf("输出第1个删除的队头元素的值：%d\n",a);
	DeQueue(Q,a);
	printf("输出第2个删除的队头元素的值：%d\n",a);
	printf("输出两次删除队头元素后队列的元素值：");
	QueueTraverse(Q);
	if(!GetHead(Q,f))
		printf("输出队头元素的值：%d\n",f);
	printf("输出队列元素的个数：%d\n",QueueLength(Q));
	printf("将Q清为空队列！\n");
	ClearQueue(Q);
	printf("输出队列元素的个数：%d\n",QueueLength(Q));
	printf("判断队列是否为空！\n");
	printf("QueueEmpty(Q)=%d\n",QueueEmpty(Q));
}


