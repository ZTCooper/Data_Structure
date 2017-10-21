#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20//��󶥵����
typedef int Status;
typedef int InfoType;
typedef enum{DG,DN,UDG,UDN}GraphKind;

typedef struct ArcNode{
	int adjvex;//�û���ָ��ԵĶ���λ�� 
	struct ArcNode *nextarc;//ָ����һ������ָ�� 
	InfoType *info;//�û������Ϣָ�� 
}ArcNode;

typedef char VertexType;
typedef struct VNode{
	VertexType data;//������Ϣ 
	ArcNode *firstarc;//ָ���һ�������ö���Ļ���ָ�� 
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct{
	AdjList vertices;
	int vexnum,arcnum;//ͼ�ĵ�ǰ�������ͻ��� 
	int kind;//ͼ�������־ 
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
	printf("���붥����G.vexnum:");	scanf("%d",&G.vexnum);
	printf("�������G.arcnum:");	scanf("%d",&G.arcnum);/* ��������Ŀ�ͱ��� */
 	getchar();
 	for(i=0;i<G.vexnum;i++)     /* ���붥�� */
 	{   
 		printf("���붥��G.vertices[%d].data:",i);
  		scanf("%c",&G.vertices[i].data);   /* ���붥�� */
  		getchar();
  		G.vertices[i].firstarc=NULL;   /* ���ȳ�ʼ��ΪNULL */
 	}   
 	for(k=0;k<G.arcnum;k++)   
 	{   
	 	printf("�������i���ߵ��������㣺\n",k+1); 
  		scanf("%c%c",&v1,&v2);      /* ����һ���������������ź��յ���� */
  		getchar();
  		i=LocateVex(G,v1);	j=LocateVex(G,v2);
  		if(!(p=(ArcNode*)malloc(sizeof(struct ArcNode)))); exit(OVERFLOW);  
  		p->adjvex=j;       /* ����û���ָ����յ�λ�� */
  /* ����������൱�ڵ�����Ĳ������ */
  		p->nextarc=G.vertices[i].firstarc; /* ���涥������Ӧ���յ�λ�� */
  		G.vertices[i].firstarc=p;   
 	}
 	return OK;
}

Status CreateDN(ALGraph &G){
	int i,j,k,w;   
 	ArcNode *p;
	char v1,v2; 
	printf("���붥����G.vexnum:");	scanf("%d",&G.vexnum);
	printf("�������G.arcnum:");	scanf("%d",&G.arcnum);/* ��������Ŀ�ͱ��� */
 	getchar();
 	for(i=0;i<G.vexnum;i++)     /* ���붥�� */
 	{   
 		printf("���붥��G.vertices[%d].data:",i);
  		scanf("%c",&G.vertices[i].data);   /* ���붥�� */
  		getchar();
  		G.vertices[i].firstarc=NULL;   /* ���ȳ�ʼ��ΪNULL */
 	}      
 	for(k=0;k<G.arcnum;k++)   
 	{   
 		printf("�����%d���ߵ��������Ȩֵw(int):",k+1);
  		scanf("%c%c%d",&v1,&v2,&w);      /* ����һ���������������ź��յ���� */
  		getchar();
  		i=LocateVex(G,v1);	j=LocateVex(G,v2);
  		if(!(p=(ArcNode*)malloc(sizeof(struct ArcNode)))); exit(OVERFLOW);  
  		p->adjvex=j;       /* ����û���ָ����յ�λ�� */
		p->info=(InfoType*)malloc(sizeof(InfoType));
  		*(p->info)=w;
  /* ����������൱�ڵ�����Ĳ������ */
  		p->nextarc=G.vertices[i].firstarc; /* ���涥������Ӧ���յ�λ�� */
  		G.vertices[i].firstarc=p;   
 	}
 	return OK;
}

Status CreateUDG(ALGraph &G){//�ڽӱ�(G.kind=UDG) 
	int i,j,k,IncInfo;
	ArcNode *pi,*pj;
	char v1,v2;
	printf("���붥����G.vexnum:");	scanf("%d",&G.vexnum);
	printf("�������G.arcnum:");	scanf("%d",&G.arcnum);
	printf("����߰���������Ϣ���(1--������0--������):");	scanf("%d",&IncInfo);
	getchar();
	for(i=0;i<G.vexnum;++i){//�����ͷ���� 
		printf("���붥��G.vertices[%d].data:",i);
		scanf("%c",&G.vertices[i].data);//���붥��ֵ 
		getchar();
		G.vertices[i].firstarc=NULL;//��ʼ������ͷָ��Ϊ�� 
	}
	for(k=0;k<G.arcnum;++k){//������� 
		printf("�������%d���ߵ��������㣺",k+1);
		scanf("%c%c",&v1,&v2);//����һ���ߵ�ʼ����յ� 
		getchar();
		i=LocateVex(G,v1);	j=LocateVex(G,v2);//ȷ��v1v2��G��λֵ������� 
		if(!(pi=(ArcNode*)malloc(sizeof(ArcNode))))	exit(OVERFLOW);
		pi->adjvex=j;//�Ի���㸳�ڽӵ㡰λ�á���Ϣ 
		pi->nextarc=G.vertices[i].firstarc;
		G.vertices[i].firstarc=pi;//��������G.vertices[i] 
		if(!(pj=(ArcNode*)malloc(sizeof(ArcNode))))	exit(OVERFLOW);
		pj->adjvex=i;
		pj->nextarc=G.vertices[j].firstarc;
		G.vertices[j].firstarc=pj;
	}
	return OK;
}//��������ͼ 

Status CreateUDN(ALGraph &G){//�ڽӱ�(G.kind=UDN) 
	int i,j,k,IncInfo;
	ArcNode *pi,*pj;
	char v1,v2;
	printf("���붥����G.vexnum:");	scanf("%d",&G.vexnum);
	printf("�������G.arcnum:");	scanf("%d",&G.arcnum);
	printf("����߰���������Ϣ���(1--������0--������):");	scanf("%d",&IncInfo);
	getchar();
	for(i=0;i<G.vexnum;++i){//�����ͷ���� 
		printf("���붥��G.vertices[%d].data:",i);
		scanf("%c",&G.vertices[i].data);//���붥��ֵ 
		getchar();
		G.vertices[i].firstarc=NULL;//��ʼ������ͷָ��Ϊ�� 
	}
	for(k=0;k<G.arcnum;++k){//������� 
		printf("�������%d���ߵ��������㣺",k+1);
		scanf("%c%c",&v1,&v2);//����һ���ߵ�ʼ����յ� 
		getchar();
		i=LocateVex(G,v1);	j=LocateVex(G,v2);//ȷ��v1v2��G��λֵ������� 
		if(!(pi=(ArcNode*)malloc(sizeof(ArcNode))))	exit(OVERFLOW);
		pi->adjvex=j;//�Ի���㸳�ڽӵ㡰λ�á���Ϣ 
		pi->nextarc=G.vertices[i].firstarc;
		G.vertices[i].firstarc=pi;//��������G.vertices[i] 
		if(!(pj=(ArcNode*)malloc(sizeof(ArcNode))))	exit(OVERFLOW);
		pj->adjvex=i;
		pj->nextarc=G.vertices[j].firstarc;
		G.vertices[j].firstarc=pj;
		if(IncInfo){
			printf("������Ȩֵ��");
			scanf("%d",pj->info);
			pi->info=pj->info; 
		} 
	}
 	return OK;
}//���������� 

Status CreateGraph(ALGraph &G){
	printf("������ͼ�����ࣺ0��ʾDG��1��ʾDN��2��ʾUDG��3��ʾUDN\n");
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
	printf("����ڽӱ�\n");
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
