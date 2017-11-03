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
typedef int DistanceMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

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

void ShortestPath_FLOYD(MGraph G,PathMatrix P[],DistanceMatrix &D){
	int i,v,w,u;
	for(v=0;v<G.vexnum;++v)
		for(w=0;w<G.vexnum;++w){
			D[v][w]=G.arcs[v][w].adj;
			for(u=0;u<G.vexnum;++u) P[v][w][u]=FALSE;
			if(D[v][w]<INFINITY&&D[v][w]!=0){
				P[v][w][v]=TRUE;P[v][w][w]=TRUE;
			}
		}
	for(u=0;u<G.vexnum;++u)
		for(v=0;v<G.vexnum;++v)
			for(w=0;w<G.vexnum;++w)
				if(D[v][u]+D[u][w]<D[v][w]){
					D[v][w]=D[v][u]+D[u][w];
					for(i=0;i<G.vexnum;++i)
						P[v][w][i]=P[v][u][i]||P[u][w][i];
				}
	printf("输出每一对顶点之间的最短路径长度如下:\n");
	for(v=0;v<G.vexnum;++v){
		printf("%c----",G.vexs[v]);
		for(w=0;w<G.vexnum;++w)
			if(D[v][w]==INFINITY)
				printf("%4s","∞");
			else
				printf("%4d",D[v][w]);
		printf("\n");
	}
	printf("输出每一对顶点之间的最短路径如下：\n");
	for(v=0;v<G.vexnum;++v){
		printf("%c----",G.vexs[v]);
		for(w=0;w<G.vexnum;++w){
			for(u=0;u<G.vexnum;++u)
				if(P[v][w][u]) printf("%c",G.vexs[u]);
				else printf("");
			printf(" ");
			}
		printf("\n"); 
		}
}

int main(){
	MGraph G;
	PathMatrix P[MAX_VERTEX_NUM];
	DistanceMatrix D;
	CreateGraph(G);
	list(G);
	ShortestPath_FLOYD(G,P,D);
	printf("\n");
}

