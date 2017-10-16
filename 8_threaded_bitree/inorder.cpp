#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;
typedef char TElemType;
typedef enum {Link,Thread} PointerTag;
typedef struct BiThrNode
{	
	TElemType data;
	struct BiThrNode *lchild,*rchild;
	PointerTag LTag,RTag;
}BiThrNode,*BiThrTree;
BiThrTree pre;

Status CreateBiThrTree(BiThrTree &T){
	char ch;
	scanf("%c",&ch);
	if(ch=='#') T=NULL;
	else{
		if(!(T=(BiThrNode*)malloc(sizeof(BiThrNode)))) exit(OVERFLOW);
		T->data=ch;	T->LTag=Link;	T->RTag=Link;
		CreateBiThrTree(T->lchild);
		CreateBiThrTree(T->rchild);
	}
	return OK;
}//CreateBiThrTree

void InThreading(BiThrTree p);

Status InOrderThreading(BiThrTree &Thrt,BiThrTree T){
	if(!(Thrt=(BiThrTree)malloc(sizeof(BiThrNode)))) exit(OVERFLOW);
	Thrt->LTag=Link;	Thrt->RTag=Thread;
	Thrt->rchild=Thrt;
	if(!T) Thrt->lchild=Thrt;
	else{
		Thrt->lchild=T;	pre=Thrt;
		InThreading(T);
		pre->rchild=Thrt;	pre->RTag=Thread;
		Thrt->rchild=pre;
	}
	return OK;
}//InOrderThreading

void InThreading(BiThrTree p){
	if(p){
		InThreading(p->lchild);
		if(!p->lchild){p->LTag=Thread; p->lchild=pre;}
		if(!pre->rchild){pre->RTag=Thread; pre->rchild=p;}
		pre=p;
		InThreading(p->rchild);
	}
}//InThreading

Status InOrderTraverse_Thr(BiThrTree T){
	BiThrTree p;
	p=T->lchild;
	while(p!=T)
	{
		while(p->LTag==Link) p=p->lchild;
		printf("%c ",p->data);
		while(p->RTag==Thread&&p->rchild!=T)
		{
			p=p->rchild;
			printf("%c ",p->data);
		}
		p=p->rchild;
	}
	return OK;
}//InOrderTraverse_Thr

int main()
{
	BiThrTree T,B,Thrt;
	//TElemType b,d,e;
	//char a;
	printf("创建二叉树，按先序次序输入二叉树中结点的值：\n");
	CreateBiThrTree(T);printf("成功建立\n");
	if(InOrderThreading(Thrt,T)==OK) printf("成功建立中序线索化链表！\n");
	printf("中序遍历线索二叉树，结果是：\n");
	InOrderTraverse_Thr(Thrt);
	printf("\n");
}//ABC##DE#G##F###
