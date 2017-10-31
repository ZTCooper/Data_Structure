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
#define MAX_ARC_NUM 100
typedef int Status;
typedef int VRType;
typedef int InfoType;
typedef enum{DG,DN,UDG,UDN}GraphKind;

/*typedef struct ArcCell{
	VRType adj;
	InfoType *info;
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];*/

typedef char VertexType;
typedef struct{
	VertexType vexs[MAX_VERTEX_NUM];//顶点向量
	int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//邻接矩阵
	int vexnum,arcnum;//顶点数，弧数
	GraphKind kind;
}MGraph;

typedef struct{
    int start;
    int end;
    int cost;
}Edge;

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
			G.arcs[i][j]=INFINITY;
		}
		for(k=0;k<G.arcnum;++k){
			printf("输入第%d条边vi、vj和权值w(int):\n",k+1);
			scanf("%c%c%d",&v1,&v2,&w);
			getchar();
			i=LocateVex(G,v1);	j=LocateVex(G,v2);
			G.arcs[i][j]=w;//弧<v1,v2>的权值
			G.arcs[j][i]=G.arcs[i][j];
		}
		return OK;
}//构造无向网 

void list(MGraph G){
	int i,j;
	printf("输出邻接矩阵：\n");
	for(i=0;i<G.vexnum;++i){
		printf("%c----",G.vexs[i]);
		for(j=0;j<G.vexnum;++j)
			if(G.arcs[i][j]=INFINITY)
				printf("%4s","∞");
			else
				printf("%4d",G.arcs[i][j]);
			printf("\n");
	}
}

void Init_edge(MGraph G,Edge edge[]){
    int i,j;
    int count = 0;
    for(i = 1; i <= G.vexnum;i++){
        for (j = i;j <= G.vexnum;j++){
                edge[count].start = i;
				edge[count].end = j;
                edge[count].cost = G.arcs[i][j];
                count++;
        }
    }
}   

void sort_edge(Edge edge[],int arcnum){
    int i,j;
    Edge temp;
    for(i = 0; i < arcnum - 1;i++){
        for (j = i+1;j < arcnum;j++){
            if(edge[i].cost > edge[j].cost){
                temp = edge[i];
                edge[i] = edge[j];
                edge[j] = temp;
            }
        }
    }
}//将边按权值从大到小排序

void print_edge(Edge edge[],int arcnum){
    int i = 0;
    while(i < arcnum){
        printf("%d,%d,%d",edge[i].start,edge[i].end,edge[i].cost);
        i++;
    }
}//输出边的信息

int findFather(int father[],int v){
    int t = v;
    while(father[t] != -1)
        t = father[t];
    return t;
}//找出指定节点的所属的连通分量，这里是找出其根节点在father数组中下标

void MiniSpanTree_Kruscal(MGraph G,Edge edge[]){
    int father[MAX_VERTEX_NUM];
    int i,count,v1,v2;
    // 初始化father数组
    for(i = 0;i < MAX_VERTEX_NUM;i++){
        father[i] = -1;
    }
    i = 0;
    count = 0; // 统计加入最小生树中的边数
    // 遍历任意两个结点之间的边
    while(i < G.arcnum && count < G.arcnum){
        v1 = findFather(father,edge[i].start);
        v2 = findFather(father,edge[i].end);
        // 如果这两个节点不属于同一个连通分量，则加入同一个连通分量
        if (v1 != v2){
            father[v2] = v1;
            count++;
            printf("%c,%c,%d",G.vexs[edge[i].start],G.vexs[edge[i].end],edge[i].cost);
        }
        i++;
    }
}


int main() {
	MGraph G;
	Edge edge[MAX_ARC_NUM];
	CreateGraph(G);
    list(G);
    Init_edge(G,edge);
    sort_edge(edge,G.arcnum);
	MiniSpanTree_Kruscal(G,edge);
	printf("\n");
}
