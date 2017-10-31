#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define INFINITY INT_MAX//最大值
#define MAX_VERTEX_NUM 20//最大顶点个数
typedef int Status;
typedef int VRType;
typedef int InfoType;
typedef enum{DG,DN,UDG,UDN}GraphKind;

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

typedef struct PNode{
	VertexType adjvex;
	VRType lowcost;
}PNode,closedge[MAX_VERTEX_NUM];

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
			printf("输入第%d条边vi、vj和权值w(int):\n",k+1);
			scanf("%c%c%d",&v1,&v2,&w);
			getchar();
			i=LocateVex(G,v1);	j=LocateVex(G,v2);
			G.arcs[i][j].adj=w;//弧<v1,v2>的权值
			G.arcs[j][i].adj=G.arcs[i][j].adj;
		}
		return OK;
}//构造无向网

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

int Minimum(MGraph G,closedge closedge) //求closedge中权值最小的边，并返回其顶点在vexs中的位置 
{
	
    int i,j; 
    double k = 1000; 
    for(i=0; i<G.vexnum; i++)
	{
        if(closedge[i].lowcost != 0 && closedge[i].lowcost < k) 
        {
            k = closedge[i].lowcost;
            j = i;
        }
    }
    return j;
}


void MiniSpanTree_PRIM(MGraph G,VertexType u){//最小生成树prim
	int i,j,k;
	closedge closedge;
	k=LocateVex(G,u);
	for(j=0;j<G.vexnum;j++){
		if(j!=k){
			closedge[j].adjvex=u;
			closedge[j].lowcost=G.arcs[k][j].adj;
		}
	}
	closedge[k].lowcost=0;
	for(i=1;i<G.vexnum;i++){
		k=Minimum(G,closedge);
		printf("<%c %c> ",closedge[k].adjvex,G.vexs[k]);
		closedge[k].lowcost=0;
		for(j=0;j<G.vexnum;j++){
			if(G.arcs[k][j].adj<closedge[j].lowcost){
				closedge[j].adjvex=G.vexs[k];
				closedge[j].lowcost=G.arcs[k][j].adj;
			}//if
		}//for
	}//for
}

int main() {
	MGraph G;
	CreateGraph(G);
    list(G);
	MiniSpanTree_PRIM(G,'A');
	printf("\n");
}
