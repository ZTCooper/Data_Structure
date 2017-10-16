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
		T->data=ch;	 T->LTag=Link;	T->RTag=Link;
		CreateBiThrTree(T->lchild);
		CreateBiThrTree(T->rchild);
	}
	return OK;
}//CreateBiThrTree

void PostThreading(BiThrTree p); 

Status PostOrderThreading(BiThrTree &Thrt,BiThrTree T){
	if(!(Thrt=(BiThrTree)malloc(sizeof(BiThrNode)))) exit(OVERFLOW);
	Thrt->LTag=Link;	Thrt->RTag=Thread;
	Thrt->rchild=Thrt;
	if(!T) Thrt->lchild=Thrt;
	else{
		Thrt->lchild=T;	pre=Thrt;
		PostThreading(T);
		pre->rchild=Thrt;	pre->RTag=Thread;
		Thrt->rchild=pre;		
	}
	return OK;
}//PostOrderThreading

void PostThreading(BiThrTree p){
	if(p){
		PostThreading(p->lchild);
		PostThreading(p->rchild);
		if(!p->lchild){p->LTag=Thread; p->lchild=pre;}
		if(!pre->rchild) {pre->RTag=Thread; pre->rchild=p;}
		pre=p;
	}
}

BiThrTree Parent(BiThrTree &Thrt, BiThrTree &p)
{
	BiThrTree parent = Thrt;
	if (parent->lchild == p)return parent;
	else
	{
		parent = parent->lchild;
		while (parent->lchild != p&&parent->rchild != p)
		{
			if (parent->RTag == Link)parent = parent->rchild;
			else parent = parent->lchild;
		}
	}
	return parent;
}

Status PostOrderTraverse_Thr(BiThrTree T)
{
	BiThrTree p, par;
	p = T->lchild;
	while (true)
	{
		while (p->LTag == Link)p=p->lchild;
		if (p->RTag == Link)p=p->rchild;
		else break;
	}
	while (p!=T)
	{
		printf("%c ",p->data);
		par=Parent(T, p);
		if(par==T)p=T;
		else if(par->RTag==Thread||p==par->rchild)	p=par;
		else
		{
			while (par->RTag == Link)
			{
				par = par->rchild;
				while (par->LTag == Link)par = par->lchild;
			}
			p = par;
		}
	}
	return OK;
}

/*Status PostOrderTraverse_Thr(BiThrTree T){
	BiThrTree p;
	p=T->lchild;
	while(p!=T)
	{
		while(p->LTag==Link) p=p->lchild;
		printf("%c ",p->data);
		if(p->RTag==Link) p=p->rchild;
		while(p){
			if(p->LTag==Link) break;
			p=p->rchild;
			printf("%c ",p->data);
		}
	}
	return OK;
}//PostOrderTraverse_Thr

void PostOrderTraverse_Thr(BiThrTree T){
	BiThrTree p;
	p=T->lchild;
	while(p!=T){
		while(p->LTag==Link) p=p->lchild;
		while(p&&p->RTag==Thread){
			printf("%c ",p->data);
			pre=p;
			p=p->rchild;
		}
		if(p==T->lchild){
			printf("%c ",p->data);
			return; 
		}
		while(p&&p->rchild==pre){
			printf("%c ",p->data);
			pre=p;
			p=p->parent;
		}
		if(p&&p->RTag==Link){
			p=p->rchild;
		}
	}
}*/

int main()
{
	BiThrTree T,B,Thrt;
	//TElemType b,d,e;
	//char a;
	printf("创建二叉树，按先序次序输入二叉树中结点的值：\n");
	CreateBiThrTree(T);printf("成功建立\n");
	if(PostOrderThreading(Thrt,T)==OK) printf("成功建立后序线索化链表！\n");
	printf("后序遍历线索二叉树，结果是：\n");
	PostOrderTraverse_Thr(Thrt);
	printf("\n");
}//ABC##DE#G##F###
