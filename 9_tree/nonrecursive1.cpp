#include<stdio.h>
#include<malloc.h>
#define MAXSIZE 255
int Nodenum=0,Count=0;
typedef struct CSNode
{
    char data;
    struct CSNode *firstchild,*nextsibling;
}CSNode,*CSTree;

CSTree InitCSTree()
{
    CSTree T;
    T=NULL;
    return T;
}//初始化 

CSTree CreateCSTree(char x,CSTree lbt,CSTree rbt)
{
    CSTree p;
    if((p=(CSNode *)malloc(sizeof(CSNode)))==NULL)return NULL;
    p->data=x;
    p->firstchild=lbt;
    p->nextsibling=rbt;
    return p;
}//生成根节点 

CSTree Insertf(CSTree T,char x,CSTree parent)
{
    CSTree p;
    if(parent==NULL)
    {
        printf("\n插入出错！\n");
        return NULL;
    }
    if((p=(CSNode *)malloc(sizeof(CSNode)))==NULL) return NULL;
    p->data=x;
    p->firstchild=NULL;
    p->nextsibling=NULL;
    if(parent->firstchild==NULL) parent->firstchild=p;
    else
    {
        p->firstchild=parent->firstchild;
        parent->firstchild=p;
    }
    return T;
}//插入左孩子 

CSTree Insertn(CSTree T,char x,CSTree parent)
{
    CSTree p;
    if(parent==NULL)
    {
        printf("\n插入出错！");
        return NULL;
    }
    if((p=(CSNode *)malloc(sizeof(CSNode)))==NULL) return NULL;
    p->data=x;
    p->firstchild=NULL;
    p->nextsibling=NULL;
    if(parent->nextsibling==NULL) parent->nextsibling=p;
    else
    {
        p->nextsibling=parent->nextsibling;
        parent->nextsibling=p;
    }
    return T;
}//插入右孩子 

void Vist(CSTree T)
{
    printf("%c ",T->data);
}//访问 

void PreOrdertraverse(CSTree T)
{
    CSNode *stack[MAXSIZE],*p; 
    int top=-1;                     //栈初始化为空
    if(T==NULL) return;
    p=T;                           //p指向根结点
    while(p!=NULL||top!=-1)
    {
        while(p!=NULL)
        {
            Vist(p);Nodenum++;
            top++;
            stack[top]=p;
            p=p->firstchild;
        }
        if(top<0) return;
        else 
        {
            p=stack[top];
            top--;
            p=p->nextsibling;
        }
    }
}//先根遍历 


void PostOrdertraverse(CSTree T)
{
    CSNode *stack[MAXSIZE],*p; 
    int top=-1;                     //栈初始化为空
    if(T==NULL) return;
    p=T;                           //p指向根结点
    while(p!=NULL||top!=-1)
    {
        while(p!=NULL)
        {   
            top++;
            stack[top]=p;
            p=p->firstchild;
        }
        if(top<0) return;
        else 
        {   
            p=stack[top];
            Vist(p);
            top--;
            p=p->nextsibling;
        }
    }
}//后根遍历 

void LevelOrdertnaverse(CSTree T)
{
    CSNode *Queue[MAXSIZE];
    int front,rear;
    if(T==NULL)return;
    front=-1;
    rear=0;
    Queue[rear]=T;
    while(front!=rear)
    {
        front++;
        Vist(Queue[front]);                     //出队，并取值输出

        if(Queue[front]->firstchild!=NULL)          //入队操作
        {
            rear++;
            Queue[rear]=Queue[front]->firstchild;

        }
        if(Queue[front]->nextsibling!=NULL)
        {
            rear++;
            Queue[rear]=Queue[front]->nextsibling;
        }
        if(Queue[front]->firstchild==NULL && Queue[front]->nextsibling==NULL)		//叶子结点计数 
            Count++;														//叶子结点计数 
    }
}//层次遍历 

int Depth(CSTree T)
{
    CSNode *stack[MAXSIZE];
    int Frist[MAXSIZE];         //判断在栈中的次数，正则第一次，负则第二次
    CSNode *p;
    int deep = 0;
    int top=-1;             //栈初始化为空
    if(T==NULL) return 0;
    p=T;                   //p指向根结点
    while(p!=NULL||top!=-1)
    {
        while(p != NULL)
        {
            top++;
            stack[top]=p;
            Frist[top]=1;
            p=p->firstchild;
        }
        if(top > -1)
        {
            if(top+1>deep) deep=top+1;
            if(Frist[top] > 0)
            {
                p=stack[top]->nextsibling;
                Frist[top]=-Frist[top];
            }
            else
            {
                p=stack[top];
                top--;
                //Vist(p);
                p=NULL;
            }
        }
    }
    return deep;
}

void ExchangeCSTree(CSTree T)
{
    CSNode *stack[MAXSIZE],*p;
    int top=-1;                     //栈初始化为空
    if(T==NULL) return;
    p=T;                           //p指向根结点
    while(p!=NULL||top!=-1)
    {
        while(p!=NULL)
        {
            CSTree t = p->firstchild;
            p->firstchild = p->nextsibling;
            p->nextsibling = t;
            top++;
            stack[top]=p;
            p=p->firstchild;
        }
        if(top<0) return;
        else
        {
            p=stack[top];
            top--;
            p=p->nextsibling;
        }
    }
}

int main()
{
    CSTree T,tn=NULL,tf=NULL;
    printf("创建树！\n");
    T=InitCSTree();
    T=CreateCSTree('A',tf,tn);
    T=Insertf(T,'B',T);
    T=Insertf(T,'C',T->firstchild);
    T=Insertn(T,'D',T->firstchild);
    T=Insertf(T,'E',T->firstchild->nextsibling);
    T=Insertn(T,'F',T->firstchild->nextsibling);
    T=Insertn(T,'G',T->firstchild->nextsibling->firstchild);
    printf("先根遍历：");
    PreOrdertraverse(T);
    printf("\n");
    printf("后根遍历："); 
    PostOrdertraverse(T);
    printf("\n");
    printf("层次遍历: ");
    LevelOrdertnaverse(T);
    printf("\n");
	printf("树的深度为：%d\n",Depth(T)); 
	printf("树的结点个数为：%d\n",Nodenum);
	printf("叶子节点的个数为：%d\n",Count);
    printf("\n"); 
    return 0;
}//ABC##DE#G##F###
