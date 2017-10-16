#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
typedef char TElemType;
typedef enum PointerTag { Link, Thread };
typedef struct BiThrNode
{
	TElemType data;
	struct BiThrNode *lchild, *rchild;
	PointerTag LTag, RTag;
}BiThrNode, *BiThrTree;

BiThrTree pre;

Status CreateBiThrTree(BiThrTree&T)
{   //递归创建
	char ch;
	scanf("%c", &ch);
	if (ch == '#')T = NULL;
	else
	{
		if (!(T = (BiThrTree)malloc(sizeof(BiThrNode))))exit(OVERFLOW);
		T->data = ch;
		T->LTag = Link;
		T->RTag = Link;
		CreateBiThrTree(T->lchild);
		CreateBiThrTree(T->rchild);
	}
	return OK;
}

void PreThreading(BiThrTree p)
{   //先序线索
	if (p)
	{
		if (!p->lchild)
		{
			p->LTag = Thread;
			p->lchild = pre;
		}
		if (!pre->rchild)
		{
			pre->RTag = Thread;
			pre->rchild = p;
		}
		pre = p;
		if (p->LTag == Link)PreThreading(p->lchild);
		if (p->RTag == Link)PreThreading(p->rchild);
	}
}

Status PreOrderThreading(BiThrTree &Thrt, BiThrTree T)
{   //先序遍历二叉树T，并将其先序线索化
	if (!(Thrt = (BiThrTree)malloc(sizeof(BiThrNode))))exit(OVERFLOW);
	Thrt->LTag = Link;
	Thrt->RTag = Thread;
	Thrt->rchild = Thrt;
	if (!T)Thrt->lchild = Thrt;
	else
	{
		Thrt->lchild = T;
		pre = Thrt;
		PreThreading(T);
		pre->rchild = Thrt;
		pre->RTag = Thread;
		Thrt->rchild = pre;
	}
	return OK;
}

Status PreOrderTraverse_Thr(BiThrTree T, Status(*Visit)(TElemType e))
{   //先序遍历线索二叉树
	BiThrTree p;
	p = T->lchild;
	while (p != T)
	{
		if (!Visit(p->data))return ERROR;
		if (p->LTag == Link)p = p->lchild;
		else p = p->rchild;
	}
	return OK;
}

void InThreading(BiThrTree p)
{   //中序线索化
	if (p)
	{
		InThreading(p->lchild);
		if (!p->lchild)
		{
			p->LTag = Thread;
			p->lchild = pre;
		}
		if (!pre->rchild)
		{
			pre->RTag = Thread;
			pre->rchild = p;
		}
		pre = p;
		InThreading(p->rchild);
	}
}

Status InOrderThreading(BiThrTree &Thrt, BiThrTree T)
{   //中序遍历二叉树T，并将其中序线索化
	if (!(Thrt = (BiThrTree)malloc(sizeof(BiThrNode))))exit(OVERFLOW);
	Thrt->LTag = Link;
	Thrt->RTag = Thread;
	Thrt->rchild = Thrt;
	if (!T)Thrt->lchild = Thrt;
	else
	{
		Thrt->lchild = T;
		pre = Thrt;
		InThreading(T);
		pre->rchild = Thrt;
		pre->RTag = Thread;
		Thrt->rchild = pre;
	}
	return OK;
}

Status InOrderTraverse_Thr(BiThrTree T, Status(*Visit)(TElemType e))
{   //中序遍历线索二叉树
	BiThrTree p;
	p = T->lchild;
	while (p != T)
	{
		while (p->LTag == Link)p = p->lchild;
		if (!Visit(p->data))return ERROR;
		while (p->RTag == Thread&&p->rchild != T)
		{
			p = p->rchild;
			Visit(p->data);
		}
		p = p->rchild;
	}
	return OK;
}

void PostThreading(BiThrTree p)
{   //后序线索化
	if (p)
	{
		PostThreading(p->lchild);
		PostThreading(p->rchild);
		if (!p->lchild)
		{
			p->LTag = Thread;
			p->lchild = pre;
		}
		if (!pre->rchild)
		{
			pre->RTag = Thread;
			pre->rchild = p;
		}
		pre = p;
	}
}

Status PostOrderThreading(BiThrTree &Thrt, BiThrTree T)
{   //后序遍历二叉树T，并将其后序线索化
	if (!(Thrt = (BiThrTree)malloc(sizeof(BiThrNode))))exit(OVERFLOW);
	Thrt->LTag = Link;
	Thrt->RTag = Thread;
	Thrt->rchild = Thrt;
	if (!T)Thrt->lchild = Thrt;
	else
	{
		Thrt->lchild = T;
		pre = Thrt;
		PostThreading(T);
		pre->rchild = Thrt;
		pre->RTag = Thread;
		Thrt->rchild = pre;
	}
	return OK;
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

Status PostOrderTraverse_Thr(BiThrTree T, Status(*Visit)(TElemType e))
{   //后序遍历线索二叉树
	BiThrTree p, par;
	p = T->lchild;
	while (true)
	{
		while (p->LTag == Link)p = p->lchild;
		if (p->RTag == Link)p = p->rchild;
		else break;
	}
	while (p != T)
	{
		if (!Visit(p->data))return ERROR;
		par = Parent(T, p);
		if (par == T)p = T;
		else if (par->RTag == Thread || p == par->rchild)p = par;
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

Status PrintElement(TElemType e)
{
	printf("%c", e);
	return OK;
}

int main()
{
	BiThrTree T, Thrt;
	int m;
	printf("创建二叉树，按先序次序输入二叉树中结点的值:\n");
	CreateBiThrTree(T);
	if (PreOrderThreading(Thrt, T) == OK)printf("成功建立先序线索化链表！\n");
	PreOrderTraverse_Thr(Thrt, PrintElement);
	printf("\n");
	getchar();
	CreateBiThrTree(T);
	if (InOrderThreading(Thrt, T) == OK)printf("成功建立中序线索化链表！\n");
	InOrderTraverse_Thr(Thrt, PrintElement);
	printf("\n");
	getchar();
	CreateBiThrTree(T);
	if (PostOrderThreading(Thrt, T) == OK)printf("成功建立后序线索化链表！\n");
	PostOrderTraverse_Thr(Thrt, PrintElement);
	printf("\n");
}
