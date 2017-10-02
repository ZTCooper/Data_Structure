#include<stdio.h>
#include<stdlib.h> 
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define MAXSIZE 100
typedef int Status;
typedef int SElemType;
typedef char TElemType;
typedef struct BiTNode
{	
	TElemType data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
int Nodenum=0;
int Count=0;

typedef struct StackElem
{
	BiTree link;
	int flag;
}StackElemtype;

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

BiTree InitBiTree()
{
    BiTNode *bt;
    bt=NULL;
    return bt;
}//（初始化二叉树）

BiTree CreateBiTree(TElemType x/*根节点*/,BiTree lbt/*左子树*/,BiTree rbt/*右子树*/){
	BiTree p;
	if((p=(BiTree)malloc(sizeof(BiTNode)))==NULL)	return 0;
	p->data=x;
	p->lchild=lbt;
	p->rchild=rbt;
	return p;
} //CreateBiTree（建立二叉树）

BiTree InsertL(BiTree bt,char x,BiTree parent)
{
    BiTree p;
    if(parent==NULL)
    {
        printf("\n插入出错！\n");
        return NULL;
    }
    if((p=(BiTNode *)malloc(sizeof(BiTNode)))==NULL) return NULL;
    p->data=x;
    p->lchild=NULL;
    p->rchild=NULL;
    if(parent->lchild==NULL) parent->lchild=p;
    else
    {
        p->lchild=parent->lchild;
        parent->lchild=p;
    }
    return bt;
}//InsertL（插入左孩子） 

BiTree InsertR(BiTree bt,char x,BiTree parent)
{
    BiTree p;
    if(parent==NULL)
    {
        printf("\n插入出错！");
        return NULL;
    }
    if((p=(BiTNode *)malloc(sizeof(BiTNode)))==NULL) return NULL;
    p->data=x;
    p->lchild=NULL;
    p->rchild=NULL;
    if(parent->rchild==NULL) parent->rchild=p;
    else
    {
        p->rchild=parent->rchild;
        parent->rchild=p;
    }
    return bt;
}//InsertR（插入右孩子） 
 
 
void PreOrderTraverse(BiTree T)
{
    BiTNode *stack[MAXSIZE],*p; 
    int top=-1;                     //栈初始化为空
    if(T==NULL) return;
    p=T;                           //p指向根结点
    while(! (p == NULL && top == -1))
    {
        while(p!=NULL)
        {
            printf("%c ",T->data);
            top++;
            stack[top]=p;
            p=p->lchild;
        }
        if(top<0) return;
        else 
        {
            p=stack[top];
            top--;
            p=p->rchild;
        }
    }
}//PreOrderTraverse（先序遍历）

void InOrderTraverse(BiTree T)
{
    BiTNode *stack[MAXSIZE],*p; 
    int top=-1;                     //栈初始化为空
    if(T==NULL) return;
    p=T;                           //p指向根结点
    while(! (p == NULL && top == -1))
    {
        while(p!=NULL)
        {   
            top++;
            stack[top]=p;
            p=p->lchild;
        }
        if(top<0) return;
        else 
        {   
            p=stack[top];
            printf("%c ",T->data);
            top--;
            p=p->rchild;
        }
    }
}//InOrderTraverse（中序遍历）
 
 Status PostOrderTraverse(BiTree &T){
 	StackElemtype stack[MAXSIZE];//定义栈 
 	BiTree p;//定义寻访指针 
 	int top=0,sign;//栈顶指针初始化 
 	p=T;//寻访指针指向二叉树根结点 
 	do
 		{
 			while(p!=NULL)
 				{
 					stack[++top].link=p;//结点第一次入栈 
 					stack[top].flag=0;//标志为0 
 					p=p->lchild;//遍历左子树准备 
				 }
		 	if(top>0)
			 	{
			 		sign=stack[top].flag;//标志出栈赋sign 
			 		p=stack[top--].link;//结点出栈赋p 
			 		if(sign==0)//flag为0，第一次出栈 
			 		{	stack[++top].link=p;//结点第二次入栈 
			 			stack[top].flag=1;//标志为1 
			 			p=p->rchild;//遍历右子树准备 
					 }
					else//flag为1，第二次出栈 
					{	printf("%c ",p->data);
						p=NULL;//置p为空，为下一结点出栈准备 
					}
				}
		}while(top>0);
   }//PostOrderTraverse（后序遍历） 
    
Status LevelOrderTraverse(BiTree &T){
	BiTree queue[MAXSIZE];
	int front,rear;//定义队列指针 
	if(T==NULL)	return 0;//空树则返回 
	front=0;	rear=0;//队列指针初始化 
	queue[++rear]=T;//根结点入队列 
	while(front!=rear)//队列不空 
		{
			front=(front+1)%MAXSIZE;//队头结点出队列 
			printf("%c ",queue[front]->data);
			if(queue[front]->lchild!=NULL)//队头结点的左孩子不空 
				{
					rear=(rear+1)%MAXSIZE;//修改队尾指针 
					queue[rear]=queue[front]->lchild;//队头结点的左孩子入队列 
				}
			if(queue[front]->rchild!=NULL)//队头结点的右孩子不空 
				{
					rear=(rear+1)%MAXSIZE;//修改队尾指针 
					queue[rear]=queue[front]->rchild;//队头结点的右孩子入队列 
				}
		}
}//LevelOrderTraverse（层次遍历）

/*Status LeafCount(BiTree &T){
	if(T!=NULL)
		if((T->lchild==NULL&&T->rchild==NULL))	Count++;
		else Count=
} */

/*Status Depth(BiTree T){
	int depth=0;  SqStack S,tag;
    InitStack(S);  
    InitStack(tag);
    BiTree p=T;  
    while(p!=NULL||!StackEmpty(S)){  
        while(p!=NULL){  
            Push(S,p);  
            Push(tag,0);  
            p=p->lchild;  
        }  
        if(GetTop(tag)==1){  
            depth=depth>S.stacksize?depth:S.stacksize;  
            Pop(S);  
            Pop(tag,p);  
            p=NULL;  
        }
		else{  
            p=GetTop(S,p);  
            p=p->rchild;  
            Pop(tag);  
            Push(tag,1);  
        }  
    }  
    return depth;  
}  */

int main()
{
    BiTree t,lbt=NULL,rbt=NULL;
    t=InitBiTree();
    t=CreateBiTree('A',lbt,rbt);
    t=InsertL(t,'B',t);
    t=InsertR(t,'C',t);
    t=InsertL(t,'D',t->lchild);
    t=InsertR(t,'G',t->lchild->lchild);
    t=InsertL(t,'E',t->rchild);
    t=InsertR(t,'F',t->rchild);
    printf("先序遍历：");
    PreOrderTraverse(t);
    printf("\n");
    printf("中序遍历：");
    InOrderTraverse(t);
    printf("\n");
    printf("后序遍历：");
    PostOrderTraverse(t);
    printf("\n");
    printf("层次遍历：");
    LevelOrderTraverse(t);
    printf("\n");
    return 0;
}

