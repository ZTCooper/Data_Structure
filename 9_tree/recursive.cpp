#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;
typedef char TElemType;
typedef struct CSNode
{	
	TElemType data;
	struct CSNode *firstchild,*nextsibling;
}CSNode,*CSTree;
int Nodenum=0;
int Count=0;

Status CreateCSTree(CSTree &T){
	char ch;
	scanf("%c",&ch);
	if(ch=='#') T=NULL;
	else{
		if(!(T=(CSNode*)malloc(sizeof(CSNode)))) exit(OVERFLOW);
		T->data=ch;
		CreateCSTree(T->firstchild);
		CreateCSTree(T->nextsibling);
	}
	return OK;
}

Status PreOrderTraverse(CSTree T){
	if(T){
		printf("%c ",T->data);
		if(PreOrderTraverse(T->firstchild))
			if(PreOrderTraverse(T->nextsibling)) return OK;
		return ERROR;
	}else return OK;
}//�ȸ�����

Status PostOrderTraverse(CSTree T){
	int m=0;
	if(T){
		if(PostOrderTraverse(T->firstchild)) m=1;
		printf("%c ",T->data);
		if(m)
			if(PostOrderTraverse(T->nextsibling)) return OK;
		return ERROR;
	}else return OK;
}//�������

int Depth(CSTree T)
{
	int leftDepth,rightDepth;
	if(T==NULL) return 0;
	else{
		leftDepth=Depth(T->firstchild);
		rightDepth=Depth(T->nextsibling);
		if(leftDepth+1>=rightDepth) return leftDepth+1;
		else return rightDepth+1;
	}
}

Status NodeCount(CSTree T){
	if(T){
		Nodenum++;
		if(NodeCount(T->firstchild))
			if(NodeCount(T->nextsibling)) return OK;
			return ERROR;
	}else return OK;
}

Status LeafCount(CSTree T){
	if(T){
		if(T->firstchild==NULL){
			printf("%c ",T->data); Count++;
		}
		if(LeafCount(T->firstchild))
			if(LeafCount(T->nextsibling)) return OK;
			return ERROR;
	}else return OK;
}

Status CopyCSTree(CSTree T,CSTree &B){
	if(T==NULL)
		B=NULL;
	else{
		if(!(B=(CSNode*)malloc(sizeof(CSNode)))) exit(OVERFLOW);
		B->data=T->data;
		CopyCSTree(T->firstchild,B->firstchild);
		CopyCSTree(T->nextsibling,B->nextsibling);
	}
	return OK;
}

Status DestroyTree(CSTree &T){
	if(T){
		DestroyTree(T->firstchild);
		DestroyTree(T->nextsibling);
		free(T);
	}
	return OK;
}//����

Status ClearTree(CSTree &T){
	if(T){
		T=NULL;
	}
	return OK;
}//���

void main()
{
	CSTree T,B;
	printf("������������������������н���ֵ��\n");
	CreateCSTree(T);
	NodeCount(T);
	printf("���Ľ�����Ϊ��%d\n",Nodenum);
	printf("�������Ϊ��%d\n",Depth(T));
	printf("�ȸ�������������ǣ�\n");
	PreOrderTraverse(T);
	printf("\n");
	printf("���������������ǣ�\n");
	PostOrderTraverse(T);
	printf("\n");
	printf("�������Ҷ�ӽ�㣺\n");
	LeafCount(T);
	printf("\n");
	printf("ͳ������Ҷ�ӽ�������%d\n",Count);
	if(CopyCSTree(T,B)==OK) printf("�ɹ�������T����B��\n");
	if(DestroyTree(T)==OK) printf("�ɹ�������T��\n");
	if(ClearTree(T)==OK) printf("����T��Ϊ������\n");
	printf("�ȸ�������B������ǣ�\n");
	PreOrderTraverse(B);
	printf("\n");
	printf("���������B������ǣ�\n");
	PostOrderTraverse(B);
	printf("\n");
}//ABC##DE#G##F###