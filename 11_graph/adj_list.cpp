#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20//最大顶点个数
typedef int Status;
typedef int InfoType;
typedef enum{DG,DN,UDG,UDN}GraphKind;

typedef struct ArcNode{
	int adjvex;//该弧所指向对的顶点位置 
	struct ArcNode *nextarc;//指向下一条弧的指针 
	InfoType *info;//该弧相关信息指针 
}ArcNode;

typedef char VertexType;
typedef struct VNode{
	VertexType data;//顶点信息 
	ArcNode *firstarc;//指向第一条依附该顶点的弧的指针 
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct{
	AdjList vertices;
	int vexnum,arcnum;//图的当前顶点数和弧数 
	int kind;//图的种类标志 
}ALGraph;

int LocateVex(ALGraph G,char v){
	int i;
	for(i=0;i<G.vexnum;++i)
		if(G.vertices[i].data==v) return i;
	return -1;
}

Status CreateDG(ALGraph &G){
	int i,j,k;   
	ArcNode *p;
	char v1,v2;
	printf("输入顶点数G.vexnum:");	scanf("%d",&G.vexnum);
	printf("输入边数G.arcnum:");	scanf("%d",&G.arcnum);/* 输入结点数目和边数 */
 	getchar();
 	for(i=0;i<G.vexnum;i++)     /* 输入顶点 */
 	{   
 		printf("输入顶点G.vertices[%d].data:",i);
  		scanf("%c",&G.vertices[i].data);   /* 输入顶点 */
  		getchar();
  		G.vertices[i].firstarc=NULL;   /* 首先初始化为NULL */
 	}   
 	for(k=0;k<G.arcnum;k++)   
 	{   
	 	printf("请输入第i条边的两个顶点：\n",k+1); 
  		scanf("%c%c",&v1,&v2);      /* 输入一条边依附的起点序号和终点序号 */
  		getchar();
  		i=LocateVex(G,v1);	j=LocateVex(G,v2);
  		if(!(p=(ArcNode*)malloc(sizeof(struct ArcNode)))); exit(OVERFLOW);  
  		p->adjvex=j;       /* 保存该弧所指向的终点位置 */
  /* 这两句代码相当于单链表的插入操作 */
  		p->nextarc=G.vertices[i].firstarc; /* 保存顶点所对应的终点位置 */
  		G.vertices[i].firstarc=p;   
 	}
 	return OK;
}

Status CreateDN(ALGraph &G){
	int i,j,k,w;   
 	ArcNode *p;
	char v1,v2; 
	printf("输入顶点数G.vexnum:");	scanf("%d",&G.vexnum);
	printf("输入边数G.arcnum:");	scanf("%d",&G.arcnum);/* 输入结点数目和边数 */
 	getchar();
 	for(i=0;i<G.vexnum;i++)     /* 输入顶点 */
 	{   
 		printf("输入顶点G.vertices[%d].data:",i);
  		scanf("%c",&G.vertices[i].data);   /* 输入顶点 */
  		getchar();
  		G.vertices[i].firstarc=NULL;   /* 首先初始化为NULL */
 	}      
 	for(k=0;k<G.arcnum;k++)   
 	{   
 		printf("输入第%d条边的两顶点和权值w(int):",k+1);
  		scanf("%c%c%d",&v1,&v2,&w);      /* 输入一条边依附的起点序号和终点序号 */
  		getchar();
  		i=LocateVex(G,v1);	j=LocateVex(G,v2);
  		if(!(p=(ArcNode*)malloc(sizeof(struct ArcNode)))); exit(OVERFLOW);  
  		p->adjvex=j;       /* 保存该弧所指向的终点位置 */
		p->info=(InfoType*)malloc(sizeof(InfoType));
  		*(p->info)=w;
  /* 这两句代码相当于单链表的插入操作 */
  		p->nextarc=G.vertices[i].firstarc; /* 保存顶点所对应的终点位置 */
  		G.vertices[i].firstarc=p;   
 	}
 	return OK;
}

Status CreateUDG(ALGraph &G){//邻接表(G.kind=UDG) 
	int i,j,k,IncInfo;
	ArcNode *pi,*pj;
	char v1,v2;
	printf("输入顶点数G.vexnum:");	scanf("%d",&G.vexnum);
	printf("输入边数G.arcnum:");	scanf("%d",&G.arcnum);
	printf("输入边包含其他信息情况(1--包含，0--不包含):");	scanf("%d",&IncInfo);
	getchar();
	for(i=0;i<G.vexnum;++i){//构造表头向量 
		printf("输入顶点G.vertices[%d].data:",i);
		scanf("%c",&G.vertices[i].data);//输入顶点值 
		getchar();
		G.vertices[i].firstarc=NULL;//初始化链表头指针为空 
	}
	for(k=0;k<G.arcnum;++k){//输入各边 
		printf("请输入第%d条边的两个顶点：",k+1);
		scanf("%c%c",&v1,&v2);//输入一条边的始点和终点 
		getchar();
		i=LocateVex(G,v1);	j=LocateVex(G,v2);//确定v1v2在G中位值，即序号 
		if(!(pi=(ArcNode*)malloc(sizeof(ArcNode))))	exit(OVERFLOW);
		pi->adjvex=j;//对弧结点赋邻接点“位置”信息 
		pi->nextarc=G.vertices[i].firstarc;
		G.vertices[i].firstarc=pi;//插入链表G.vertices[i] 
		if(!(pj=(ArcNode*)malloc(sizeof(ArcNode))))	exit(OVERFLOW);
		pj->adjvex=i;
		pj->nextarc=G.vertices[j].firstarc;
		G.vertices[j].firstarc=pj;
	}
	return OK;
}//构造无向图 

Status CreateUDN(ALGraph &G){//邻接表(G.kind=UDN) 
	int i,j,k,IncInfo;
	ArcNode *pi,*pj;
	char v1,v2;
	printf("输入顶点数G.vexnum:");	scanf("%d",&G.vexnum);
	printf("输入边数G.arcnum:");	scanf("%d",&G.arcnum);
	printf("输入边包含其他信息情况(1--包含，0--不包含):");	scanf("%d",&IncInfo);
	getchar();
	for(i=0;i<G.vexnum;++i){//构造表头向量 
		printf("输入顶点G.vertices[%d].data:",i);
		scanf("%c",&G.vertices[i].data);//输入顶点值 
		getchar();
		G.vertices[i].firstarc=NULL;//初始化链表头指针为空 
	}
	for(k=0;k<G.arcnum;++k){//输入各边 
		printf("请输入第%d条边的两个顶点：",k+1);
		scanf("%c%c",&v1,&v2);//输入一条边的始点和终点 
		getchar();
		i=LocateVex(G,v1);	j=LocateVex(G,v2);//确定v1v2在G中位值，即序号 
		if(!(pi=(ArcNode*)malloc(sizeof(ArcNode))))	exit(OVERFLOW);
		pi->adjvex=j;//对弧结点赋邻接点“位置”信息 
		pi->nextarc=G.vertices[i].firstarc;
		G.vertices[i].firstarc=pi;//插入链表G.vertices[i] 
		if(!(pj=(ArcNode*)malloc(sizeof(ArcNode))))	exit(OVERFLOW);
		pj->adjvex=i;
		pj->nextarc=G.vertices[j].firstarc;
		G.vertices[j].firstarc=pj;
		if(IncInfo){
			printf("请输入权值：");
			scanf("%d",pj->info);
			pi->info=pj->info; 
		} 
	}
 	return OK;
}//构造无向网 

Status CreateGraph(ALGraph &G){
	printf("请输入图的种类：0表示DG，1表示DN，2表示UDG，3表示UDN\n");
	scanf("%d",&G.kind);
	switch(G.kind){
	case DG:return CreateDG(G);
	case DN:return CreateDN(G);
	case UDG:return CreateUDG(G);
	case UDN:return CreateUDN(G);
	default:return ERROR;
	}
}

void list(ALGraph G){
	int i;
	ArcNode *p;
	printf("输出邻接表：\n");
	for(i=0;i<G.vexnum;++i){
		printf("%d:%c--->",i,G.vertices[i].data);
		p=G.vertices[i].firstarc;
		while(p){
			printf("%3d",p->adjvex);
			p=p->nextarc;
		}
		printf("\n");
	}
}

bool visited[MAX_VERTEX_NUM];
Status(*VisitFunc)(int v);

void DFS(ALGraph G,int v){
	visited[v]=TRUE; printf("%c ",G.vertices[v].data);
	ArcNode *p;
	for(p=G.vertices[v].firstarc; p!=NULL; p=p->nextarc)
	if(!visited[p->adjvex]) DFS(G,p->adjvex);
}

void DFSTraverse(ALGraph G){
	//VisitFunc=Visit;
	int v;
	for(v=0;v<G.vexnum;++v) visited[v]=FALSE;
	for(v=0;v<G.vexnum;++v)
	if(!visited[v]) DFS(G,v);
}

typedef int QElemType;
typedef struct QNode
{
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr;
typedef struct
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;


Status InitQueue(LinkQueue &Q){
	Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
	if(!Q.front) exit(OVERFLOW);
	Q.front->next=NULL;
	return OK;
}

Status QueueEmpty(LinkQueue &Q){
	if(Q.front==Q.rear) return TRUE;
	else return FALSE;
}

Status EnQueue(LinkQueue &Q,QElemType e){
	QueuePtr p;
	p=(QueuePtr)malloc(sizeof(QNode));
	if(!p) exit(OVERFLOW);
	p->data=e;	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
	return OK;
}

Status DeQueue(LinkQueue &Q,QElemType &e){
	QueuePtr p;
	if(Q.front==Q.rear) return ERROR;
	p=Q.front->next;
	e=p->data;
	Q.front->next=p->next;
	if(Q.rear==p) Q.rear=Q.front;
	free(p);
	return OK;
}

void BFSTraverse(ALGraph G){
	int v,u;
	LinkQueue Q;
	for(v=0;v<G.vexnum;++v) visited[v]=FALSE;
	InitQueue(Q);
	for(v=0;v<G.vexnum;++v)
	if(!visited[v]){
		visited[v]=TRUE;printf("%c ",G.vertices[v].data);
		EnQueue(Q,v);
		while(!QueueEmpty(Q)){
			DeQueue(Q,u);
			ArcNode *p;
			for(p=G.vertices[v].firstarc; p!=NULL; p=p->nextarc)
			if(!visited[p->adjvex]){
				visited[p->adjvex]=TRUE;
				printf("%c ",G.vertices[p->adjvex].data);
				EnQueue(Q,p->adjvex);
			}
		}
	}
}

int main(){
	ALGraph G;
	CreateGraph(G);
	list(G);
	DFSTraverse(G);
	printf("\n");
	BFSTraverse(G);
}
