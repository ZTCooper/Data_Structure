#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef int Status;
typedef int SElemType;
typedef struct {
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

Status InitStack(SqStack &S){
	S.base=(SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!S.base) exit(OVERFLOW);
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
	return OK;
}//InitStack

Status StackEmpty(SqStack &S){
	if (S.stacksize==0)
		return TRUE;
	else
		return FALSE;
}//StackEmpty

Status GetTop(SqStack &S,SElemType &e){
	if(S.top==S.base) return ERROR;
	e=*(S.top-1);
	return OK;
}//GetTop

Status Push(SqStack &S,SElemType &e){
	if(S.top-S.base>=S.stacksize){
		S.base=(SElemType*)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!S.base) exit(OVERFLOW);
		S.top=S.base+S.stacksize;
		S.stacksize+=STACKINCREMENT;
	}
	*S.top++=e;
	return OK;
}//Push

Status Pop(SqStack &S,SElemType &e){
	if(S.top==S.base) return ERROR;
	e=*--S.top;
	return OK;
}//Pop

Status StackOutput(SqStack &S){
	SElemType *p;
	if(S.top==S.base) return ERROR;
	p=S.top;
	while(p>S.base)
		printf("%d ",*--p);
	printf("\n");
	return OK;
}//StackOutput

Status StackTraverse(SqStack &S){
	SElemType *p;
	if(S.top==S.base) return ERROR;
	p=S.base;
	while(p<S.top)
		printf("%d ",*p++);
	printf("\n");
	return OK;
}//StackTraverse

void main()
{
	int i,n,k,h,a,b;
	SqStack S;
	printf("创建一个空栈！\n");
	InitStack(S);
	printf("判断栈是否为空！\n");
	printf("StackEmpty(S)=%d\n",StackEmpty(S));
	printf("创建栈的元素个数：\n");
	scanf("%d",&n);
	printf("输入%d个入栈元素的值：\n",n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&k);
		Push(S,k);
	}
	printf("逆序输出顺序栈元素值：\n");
	StackOutput(S);
	printf("输出顺序栈元素值:\n");
	StackTraverse(S);
	printf("输入入栈元素值：");
	scanf("%d",&h);
	Push(S,h);
	printf("输出入栈后顺序栈元素值：\n");
	StackTraverse(S);
	Pop(S,a);
	printf("输出第1个出栈元素值：%d\n",a);
	Pop(S,a);
	printf("输出第2个出栈元素值：%d\n",a);
	printf("输出两次出栈后顺序栈元素值：");
	StackTraverse(S);
	GetTop(S,b);
	printf("输出栈顶元素值：%d\n",b);
}
	
