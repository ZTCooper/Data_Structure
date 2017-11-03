#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define INFINITY 32767//最大值
#define MAX_VERTEX_NUM 20//最大顶点个数
typedef int Status;
typedef int VRType;
typedef int InfoType;
typedef enum{DG,DN,UDG,UDN}GraphKind;
typedef int Boolean;
typedef Boolean PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef int ShortPathTable[MAX_VERTEX_NUM];

typedef struct ArcCell{
	VRType adj;
	InfoType *info;
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef char VertexType;
typedef struct{
	VertexType vexs[MAX_VERTEX_NUM];//顶点向量
	AdjMatrix arcs;//邻接矩阵
	int vexnum,arcnum;//顶点数，弧数
	GraphKind kind;
}MGraph;

int LocateVex(MGraph G,char v){
	int i;
	for(i=0;i<G.vexnum;++i)
		if(G.vexs[i]==v) return i;
		return -1;
}

Status CreateGraph(MGraph &G){
	int i,j,k,w;
	VertexType v1,v2;
	printf("输入顶点数G.vexnum:");scanf("%d",&G.vexnum);
	printf("输入边数G.arcnum:");scanf("%d",&G.arcnum);
	getchar();
	for(i=0;i<G.vexnum;i++){
		printf("输入顶点G.vexs[%d]:",i);
		scanf("%c",&G.vexs[i]);
		getchar();
	}
	for(i=0;i<G.vexnum;++i)//初始化邻接矩阵
		for(j=0;j<G.vexnum;++j){
			G.arcs[i][j].adj=INFINITY;
			G.arcs[i][j].info=NULL;
		}
		for(k=0;k<G.arcnum;++k){
			printf("输入第%d条边起点vi、终点vj和权值w(int):\n",k+1);
			scanf("%c%c%d",&v1,&v2,&w);
			getchar();
			i=LocateVex(G,v1);	j=LocateVex(G,v2);
			G.arcs[i][j].adj=w;//弧<v1,v2>的权值
		}
		return OK;
}//构造有向网

void list(MGraph G){
	int i,j;
	printf("输出邻接矩阵：\n");
	for(i=0;i<G.vexnum;++i){
		printf("%c----",G.vexs[i]);
		for(j=0;j<G.vexnum;++j)
			if(G.arcs[i][j].adj==INFINITY)
				printf("%4s","∞");
			else
				printf("%4d",G.arcs[i][j].adj);
			printf("\n");
	}
}

void ShortestPath_DIJ(MGraph G,int v0,PathMatrix &P,ShortPathTable &D){
	bool final[MAX_VERTEX_NUM];
	int i,j,v,w,min;
	for(v=0;v<G.vexnum;++v){
		final[v]=FALSE;	D[v]=G.arcs[v0][v].adj;
		for(w=0;w<G.vexnum;++w)	P[v][w]=FALSE;
		if(D[v]<INFINITY){P[v][v0]=TRUE;	P[v][v]=TRUE;}
	}
	D[v0]=0;	final[v0]=TRUE;
	for(i=1;i<G.vexnum;++i)
	{
		min=INFINITY;
		for(w=0;w<G.vexnum;++w)
			if(!final[w])
				if(D[w]<min)
					{v=w;	min=D[w];}
		final[v]=TRUE;
		for(w=0;w<G.vexnum;++w)
			if(!final[w]&&(min+G.arcs[v][w].adj<D[w])){
				D[w]=min+G.arcs[v][w].adj;
				for(j=0;j<G.vexnum;++j)	P[w][j]=P[v][j];
				P[w][w]=TRUE;
			}
	}
	for(i=0;i<G.vexnum;++i){
		if(i!=0){
			printf("%3c %3c ",G.vexs[v0],G.vexs[i]);
			if(D[i]!=INFINITY) printf("%5d ",D[i]);
			else printf("%5s ","无");
			printf("(");
			for(j=0;j<G.vexnum;++j)
				if(P[i][j]) printf("%c",G.vexs[j]);
			printf(")");
			printf("\n");
		}
	}
}

void main(){
	MGraph G;
	int v0;
	PathMatrix P;
	ShortPathTable D;
	CreateGraph(G);
	list(G);
	printf("输入源点序号v0:");
	scanf("%d",&v0);
	printf("输入源点序号%d到其余顶点的最短路径如下：\n",v0);
	printf("始点 终点 路径长度 最短路径\n");
	ShortestPath_DIJ(G,v0,P,D);
	printf("\n");
}



					