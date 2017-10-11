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
}//��ʼ�� 

CSTree CreateCSTree(char x,CSTree lbt,CSTree rbt)
{
    CSTree p;
    if((p=(CSNode *)malloc(sizeof(CSNode)))==NULL)return NULL;
    p->data=x;
    p->firstchild=lbt;
    p->nextsibling=rbt;
    return p;
}//���ɸ��ڵ� 

CSTree Insertf(CSTree T,char x,CSTree parent)
{
    CSTree p;
    if(parent==NULL)
    {
        printf("\n�������\n");
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
}//�������� 

CSTree Insertn(CSTree T,char x,CSTree parent)
{
    CSTree p;
    if(parent==NULL)
    {
        printf("\n�������");
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
}//�����Һ��� 

void Vist(CSTree T)
{
    printf("%c ",T->data);
}//���� 

void PreOrdertraverse(CSTree T)
{
    CSNode *stack[MAXSIZE],*p; 
    int top=-1;                     //ջ��ʼ��Ϊ��
    if(T==NULL) return;
    p=T;                           //pָ������
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
}//�ȸ����� 


void PostOrdertraverse(CSTree T)
{
    CSNode *stack[MAXSIZE],*p; 
    int top=-1;                     //ջ��ʼ��Ϊ��
    if(T==NULL) return;
    p=T;                           //pָ������
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
}//������� 

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
        Vist(Queue[front]);                     //���ӣ���ȡֵ���

        if(Queue[front]->firstchild!=NULL)          //��Ӳ���
        {
            rear++;
            Queue[rear]=Queue[front]->firstchild;

        }
        if(Queue[front]->nextsibling!=NULL)
        {
            rear++;
            Queue[rear]=Queue[front]->nextsibling;
        }
        if(Queue[front]->firstchild==NULL && Queue[front]->nextsibling==NULL)		//Ҷ�ӽ����� 
            Count++;														//Ҷ�ӽ����� 
    }
}//��α��� 

int Depth(CSTree T)
{
    CSNode *stack[MAXSIZE];
    int Frist[MAXSIZE];         //�ж���ջ�еĴ����������һ�Σ�����ڶ���
    CSNode *p;
    int deep = 0;
    int top=-1;             //ջ��ʼ��Ϊ��
    if(T==NULL) return 0;
    p=T;                   //pָ������
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
    int top=-1;                     //ջ��ʼ��Ϊ��
    if(T==NULL) return;
    p=T;                           //pָ������
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
    printf("��������\n");
    T=InitCSTree();
    T=CreateCSTree('A',tf,tn);
    T=Insertf(T,'B',T);
    T=Insertf(T,'C',T->firstchild);
    T=Insertn(T,'D',T->firstchild);
    T=Insertf(T,'E',T->firstchild->nextsibling);
    T=Insertn(T,'F',T->firstchild->nextsibling);
    T=Insertn(T,'G',T->firstchild->nextsibling->firstchild);
    printf("�ȸ�������");
    PreOrdertraverse(T);
    printf("\n");
    printf("���������"); 
    PostOrdertraverse(T);
    printf("\n");
    printf("��α���: ");
    LevelOrdertnaverse(T);
    printf("\n");
	printf("�������Ϊ��%d\n",Depth(T)); 
	printf("���Ľ�����Ϊ��%d\n",Nodenum);
	printf("Ҷ�ӽڵ�ĸ���Ϊ��%d\n",Count);
    printf("\n"); 
    return 0;
}//ABC##DE#G##F###
