#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define EQ(a,b) (a==b)
#define LT(a,b) (a<b)
typedef int Status;
typedef char TElemType;
typedef int KeyType;
typedef struct{
	KeyType key;//关键字域
}ElemType;
typedef struct BiTNode{
	ElemType data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

BiTree SearchBSTa(BiTree T,KeyType key){
	if((!T)||EQ(key,T->data.key)) return(T);
	else if LT(key,T->data.key) return(SearchBSTa(T->lchild,key));
	else return(SearchBSTa(T->rchild,key));
}

Status SearchBST(BiTree T,KeyType key,BiTree f,BiTree &p){
	if(!T) {p=f;return FALSE;}
	else if EQ(key,T->data.key) {p=T; return TRUE;}
	else if LT(key,T->data.key) return SearchBST(T->lchild,key,T,p);
	else return SearchBST(T->rchild,key,T,p);
}

Status InsertBST(BiTree &T,ElemType e){
	BiTree p,s;
	if(!SearchBST(T,e.key,NULL,p)){
		s=(BiTree)malloc(sizeof(BiTNode));
		s->data=e;s->lchild=s->rchild=NULL;
		if(!p) T=s;
		else if LT(e.key,p->data.key) p->lchild=s;
		else p->rchild=s;
		return TRUE;
	}
	else return FALSE;
}

Status PreOrderTraverse(BiTree T){
	if(T){
		printf("%d ",T->data);
		if(PreOrderTraverse(T->lchild))
			if(PreOrderTraverse(T->rchild)) return OK;
		return ERROR;
	}else return OK;
}

Status InOrderTraverse(BiTree T){
	int m=0;
	if(T){
		if(InOrderTraverse(T->lchild)) m=1;
		printf("%d ",T->data);
		if(m)
			if(InOrderTraverse(T->rchild)) return OK;
		return ERROR;
	}else return OK;
}

Status PostOrderTraverse(BiTree T){
	if(T){
		if(PostOrderTraverse(T->lchild))
			if(PostOrderTraverse(T->rchild)){
				printf("%d ",T->data);return OK;
			}
		return ERROR;
	}else return OK;
}

Status Delete(BiTree &p){
	BiTree q,s;
	if(!p->rchild){
		q=p;p=p->lchild; free(q);
	}
	else if(!p->lchild){
		q=p;p=p->rchild; free(q);
	}else{
		q=p;s=p->lchild;
		while(s->rchild) {q=s;s=s->rchild;}p->data=s->data;
		if(q!=p) q->rchild=s->lchild;
		else q->lchild=s->lchild;
		delete s;
	}
	return TRUE;
}

Status DeleteBST(BiTree &T,KeyType key){
	if(!T) return FALSE;
	else{
		if(EQ(key,T->data.key)) return Delete(T);
		else if(LT(key,T->data.key)) return DeleteBST(T->lchild,key);
		else return DeleteBST(T->rchild,key);
	}
}

void main()
{
	BiTree T=NULL,s;
	int n,i;
	ElemType e;
	printf("输入二叉排序树的结点数：");
	scanf("%d",&n);
	printf("输入%d个结点的值：\n",n);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&e.key);
		InsertBST(T,e);
	}
	printf("先序遍历二叉树，结果是：\n");
	PreOrderTraverse(T);
	printf("\n");
	printf("中序遍历二叉树，结果是：\n");
	InOrderTraverse(T);
	printf("\n");
	printf("后序遍历二叉树，结果是：\n");
	PostOrderTraverse(T);
	printf("\n");
	printf("输入查找结点的值：\n");
	scanf("%d",&e.key);
	s=SearchBSTa(T,e.key);
	if(s) printf("已找到！结点的八进制地址为：%o\n",s);
	else printf("没找到！");
	printf("输入插入结点的值：\n");
	scanf("%d",&e.key);
	InsertBST(T,e);
	printf("先序遍历二叉树，结果是：\n");
	PreOrderTraverse(T);
	printf("\n");
	printf("中序遍历二叉树，结果是：\n");
	InOrderTraverse(T);
	printf("\n");
	printf("后序遍历二叉树，结果是：\n");
	PostOrderTraverse(T);
	printf("\n");
	printf("输入删除结点的值：\n");
	scanf("%d",&e.key);
	DeleteBST(T,e.key);
	printf("先序遍历二叉树，结果是：\n");
	PreOrderTraverse(T);
	printf("\n");
	printf("中序遍历二叉树，结果是：\n");
	InOrderTraverse(T);
	printf("\n");
	printf("后序遍历二叉树，结果是：\n");
	PostOrderTraverse(T);
	printf("\n");
}

