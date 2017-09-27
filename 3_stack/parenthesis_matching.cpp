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
typedef char SElemType;
typedef struct
{
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

Status Correct(SElemType str[]){
	SqStack S;
	InitStack(S);
	int i,state=1;
	SElemType e;
	for(i=0;str[i]!='\0';i++)
	{
		switch(str[i])
		{
		case '(': Push(S,str[i]);break;
		case '[': Push(S,str[i]);break;
		case ')': Pop(S,e);
			if (!Pop(S, e) || e!='(') return ERROR;
			break;
		case ']': 
			if (!Pop(S, e) || e!='[') return ERROR;
			break;
		}
		if(!state) break;
	}
	if(S.top==S.base&&state==1)
		return OK;
	else
		return ERROR;
}//Correct

int main()
{
	SElemType str[100];
	printf("请输入带括号的表达式：\n");
	scanf("%s",str);
	if(Correct(str)==OK)
		printf("括号匹配正确！\n");
	else printf("括号匹配不正确！\n");
	return 0;
}
