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
	printf("创建二叉树，按先序次序输入二叉树中结点的值：\n");
	CreateBiTree(T);
	NodeCount(T);
	printf("二叉树的结点个数为：%d\n",Nodenum);
	printf("二叉树的深度为：%d\n",Depth(T));
	printf("先序遍历二叉树，结果是：\n");
	PreOrderTraverse(T);
	printf("\n");
	printf("中序遍历二叉树，结果是：\n");
	InOrderTraverse(T);
	printf("\n");
	printf("后序遍历二叉树，结果是：\n");
	PostOrderTraverse(T);
	printf("\n");
	printf("输出二叉树的叶子结点：\n");
	LeafCount(T);
	printf("\n");
	printf("统计二叉树的叶子结点个数：%d\n",Count);
	printf("交换二叉树中所有结点的左右子树！\n");
	ExchangeBiTree(T);
	if(CopyBiTree(T,B)==OK) printf("成功复制二叉树T到二叉树B！\n");
	if(DestroyTree(T)==OK) printf("成功销毁二叉树T！\n");
	if(ClearTree(T)==OK) printf("将二叉树T置为空树！\n");
	printf("先序遍历二叉树B，结果是：\n");
	PreOrderTraverse(B);
	printf("\n");
	printf("中序遍历二叉树B，结果是：\n");
	InOrderTraverse(B);
	printf("\n");
	printf("后序遍历二叉树B，结果是：\n");
	PostOrderTraverse(B);
	printf("\n");
}
