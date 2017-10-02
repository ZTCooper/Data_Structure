#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;
typedef char TElemType;
typedef struct BiTNode
{	
	TElemType data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
int Nodenum=0;
int Count=0;

Status CreateBiTree(BiTree &T){
	char ch;
	scanf("%c",&ch);
	if(ch=='#') T=NULL;
	else{
		if(!(T=(BiTNode*)malloc(sizeof(BiTNode)))) exit(OVERFLOW);
		T->data=ch;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
	return OK;
}

Status PreOrderTraverse(BiTree T){
	if(T){
		printf("%c ",T->data);
		if(PreOrderTraverse(T->lchild))
			if(PreOrderTraverse(T->rchild)) return OK;
		return ERROR;
	}else return OK;
}

Status InOrderTraverse(BiTree T){
	int m=0;
	if(T){
		if(InOrderTraverse(T->lchild)) m=1;
		printf("%c ",T->data);
		if(m)
			if(InOrderTraverse(T->rchild)) return OK;
		return ERROR;
	}else return OK;
}

Status PostOrderTraverse(BiTree T){
	if(T){
		if(PostOrderTraverse(T->lchild))
			if(PostOrderTraverse(T->rchild)){
				printf("%c ",T->data);return OK;
			}
		return ERROR;
	}else return OK;
}

int Depth(BiTree T)
{
	int leftDepth,rightDepth;
	if(T==NULL) return 0;
	else{
		leftDepth=Depth(T->lchild);
		rightDepth=Depth(T->rchild);
		if(leftDepth>=rightDepth) return leftDepth+1;
		else return rightDepth+1;
	}
}

Status NodeCount(BiTree T){
	if(T){
		Nodenum++;
		if(NodeCount(T->lchild))
			if(NodeCount(T->rchild)) return OK;
			return ERROR;
	}else return OK;
}

Status LeafCount(BiTree T){
	if(T){
		if(T->lchild==NULL&&T->rchild==NULL){
			printf("%c ",T->data); Count++;
		}
		if(LeafCount(T->lchild))
			if(LeafCount(T->rchild)) return OK;
			return ERROR;
	}else return OK;
}

Status ExchangeBiTree(BiTree &T){
	BiTree p;
	if(T){
		if(T->lchild||T->rchild){
			p=T->lchild;T->lchild=T->rchild;T->rchild=p;
		}
		if(ExchangeBiTree(T->lchild))
			if(ExchangeBiTree(T->rchild)) return OK;
			return ERROR;
	}else return OK;
}

Status CopyBiTree(BiTree T,BiTree &B){
	if(T==NULL)
		B=NULL;
	else{
		if(!(B=(BiTNode*)malloc(sizeof(BiTNode)))) exit(OVERFLOW);
		B->data=T->data;
		CopyBiTree(T->lchild,B->lchild);
		CopyBiTree(T->rchild,B->rchild);
	}
	return OK;
}

Status DestroyTree(BiTree &T){
	if(T){
		DestroyTree(T->lchild);
		DestroyTree(T->rchild);
		free(T);
	}
	return OK;
}

Status ClearTree(BiTree &T){
	if(T){
		T=NULL;
	}
	return OK;
}

int main()
{
	BiTree T,B;
	printf("�������������������������������н���ֵ��\n");
	CreateBiTree(T);
	NodeCount(T);
	printf("�������Ľ�����Ϊ��%d\n",Nodenum);
	printf("�����������Ϊ��%d\n",Depth(T));
	printf("�������������������ǣ�\n");
	PreOrderTraverse(T);
	printf("\n");
	printf("�������������������ǣ�\n");
	InOrderTraverse(T);
	printf("\n");
	printf("�������������������ǣ�\n");
	PostOrderTraverse(T);
	printf("\n");
	printf("�����������Ҷ�ӽ�㣺\n");
	LeafCount(T);
	printf("\n");
	printf("ͳ�ƶ�������Ҷ�ӽ�������%d\n",Count);
	printf("���������������н�������������\n");
	ExchangeBiTree(T);
	if(CopyBiTree(T,B)==OK) printf("�ɹ����ƶ�����T��������B��\n");
	if(DestroyTree(T)==OK) printf("�ɹ����ٶ�����T��\n");
	if(ClearTree(T)==OK) printf("��������T��Ϊ������\n");
	printf("�������������B������ǣ�\n");
	PreOrderTraverse(B);
	printf("\n");
	printf("�������������B������ǣ�\n");
	InOrderTraverse(B);
	printf("\n");
	printf("�������������B������ǣ�\n");
	PostOrderTraverse(B);
	printf("\n");
}
