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
}//����ʼ����������

BiTree CreateBiTree(TElemType x/*���ڵ�*/,BiTree lbt/*������*/,BiTree rbt/*������*/){
	BiTree p;
	if((p=(BiTree)malloc(sizeof(BiTNode)))==NULL)	return 0;
	p->data=x;
	p->lchild=lbt;
	p->rchild=rbt;
	return p;
} //CreateBiTree��������������

BiTree InsertL(BiTree bt,char x,BiTree parent)
{
    BiTree p;
    if(parent==NULL)
    {
        printf("\n�������\n");
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
}//InsertL���������ӣ� 

BiTree InsertR(BiTree bt,char x,BiTree parent)
{
    BiTree p;
    if(parent==NULL)
    {
        printf("\n�������");
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
}//InsertR�������Һ��ӣ� 
 
 
void PreOrderTraverse(BiTree T)
{
    BiTNode *stack[MAXSIZE],*p; 
    int top=-1;                     //ջ��ʼ��Ϊ��
    if(T==NULL) return;
    p=T;                           //pָ������
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
}//PreOrderTraverse�����������

void InOrderTraverse(BiTree T)
{
    BiTNode *stack[MAXSIZE],*p; 
    int top=-1;                     //ջ��ʼ��Ϊ��
    if(T==NULL) return;
    p=T;                           //pָ������
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
}//InOrderTraverse�����������
 
 Status PostOrderTraverse(BiTree &T){
 	StackElemtype stack[MAXSIZE];//����ջ 
 	BiTree p;//����Ѱ��ָ�� 
 	int top=0,sign;//ջ��ָ���ʼ�� 
 	p=T;//Ѱ��ָ��ָ������������ 
 	do
 		{
 			while(p!=NULL)
 				{
 					stack[++top].link=p;//����һ����ջ 
 					stack[top].flag=0;//��־Ϊ0 
 					p=p->lchild;//����������׼�� 
				 }
		 	if(top>0)
			 	{
			 		sign=stack[top].flag;//��־��ջ��sign 
			 		p=stack[top--].link;//����ջ��p 
			 		if(sign==0)//flagΪ0����һ�γ�ջ 
			 		{	stack[++top].link=p;//���ڶ�����ջ 
			 			stack[top].flag=1;//��־Ϊ1 
			 			p=p->rchild;//����������׼�� 
					 }
					else//flagΪ1���ڶ��γ�ջ 
					{	printf("%c ",p->data);
						p=NULL;//��pΪ�գ�Ϊ��һ����ջ׼�� 
					}
				}
		}while(top>0);
   }//PostOrderTraverse����������� 
    
Status LevelOrderTraverse(BiTree &T){
	BiTree queue[MAXSIZE];
	int front,rear;//�������ָ�� 
	if(T==NULL)	return 0;//�����򷵻� 
	front=0;	rear=0;//����ָ���ʼ�� 
	queue[++rear]=T;//���������� 
	while(front!=rear)//���в��� 
		{
			front=(front+1)%MAXSIZE;//��ͷ�������� 
			printf("%c ",queue[front]->data);
			if(queue[front]->lchild!=NULL)//��ͷ�������Ӳ��� 
				{
					rear=(rear+1)%MAXSIZE;//�޸Ķ�βָ�� 
					queue[rear]=queue[front]->lchild;//��ͷ������������� 
				}
			if(queue[front]->rchild!=NULL)//��ͷ�����Һ��Ӳ��� 
				{
					rear=(rear+1)%MAXSIZE;//�޸Ķ�βָ�� 
					queue[rear]=queue[front]->rchild;//��ͷ�����Һ�������� 
				}
		}
}//LevelOrderTraverse����α�����

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
    printf("���������");
    PreOrderTraverse(t);
    printf("\n");
    printf("���������");
    InOrderTraverse(t);
    printf("\n");
    printf("���������");
    PostOrderTraverse(t);
    printf("\n");
    printf("��α�����");
    LevelOrderTraverse(t);
    printf("\n");
    return 0;
}

