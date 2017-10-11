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

typedef CSTree SElemType;
typedef struct
{
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

typedef CSTree QElemType;
typedef struct QNode
{
	QElemType data;
	Struct QNode *next;
}QNode,*QueuePtr;

int Nodenum=0;
int Count=0;

int CSTreeDepth2(CSTree T) {         /* 非递归遍历求以孩子兄弟链表表示的树的深度 */
  CSTree Q[100], p;
  int front=0, rear=0;         /* front,rear是队列Q的队头队尾元素的指针 */
  int last, dep;                 /* last指向树中同层结点中最后一个结点，dep是树的深度 */
  if(T==NULL)  return 0;
  else { 
	last = 0;
	dep = 1;
    Q[rear++] = T;
    while(front<=last && front!=rear) { 
	  p=Q[front++];   /* 队头出列 */         
      while(p!=NULL) {   /* 层次遍历 */
		if(p->firstchild) Q[rear++] = p->firstchild;   /* 第一个孩子入队 */
        p = p->nextsibling;   /* 同层兄弟指针后移 */
      }
      if(front>last) {     /* 本层结束，深度加1（初始深度为0）*/
        dep++; last = rear;    /* last再移到指向当前层最右一个结点 */
	  }
    }
    return dep;
  }
} // CSTreeDepth2



Status LeafCountCSTree(CSTree T) {
	//输出树的叶子结点，并统计叶子结点个数
    CSTree s[100];       /* s是栈，栈中元素是树结点指针 */
	int top=0;
	while(T || top!=0)
	{
		if (T) {
			s[top++]=T; T=T->firstchild;   /* 沿左分支向下 */
		}  
		else {
			T=s[--top];
			if(T->firstchild==NULL) {
				printf("%c", T->data);
				Count++;      /* 叶子结点 */
			}
			T=T->nextsibling;
		}
	}
	return OK;
} // LeafCountCSTree
