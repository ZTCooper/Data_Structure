#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define INFINITY INT_MAX//���ֵ
#define MAX_VERTEX_NUM 20//��󶥵����
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
	VertexType vexs[MAX_VERTEX_NUM];//��������
	int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//�ڽӾ���
	int vexnum,arcnum;//������������
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
	printf("���붥����G.vexnum:");scanf("%d",&G.vexnum);
	printf("�������G.arcnum:");scanf("%d",&G.arcnum);
	getchar();
	for(i=0;i<G.vexnum;i++){
		printf("���붥��G.vexs[%d]:",i);
		scanf("%c",&G.vexs[i]);
		getchar();
	}
	for(i=0;i<G.vexnum;++i)//��ʼ���ڽӾ���
		for(j=0;j<G.vexnum;++j){
			G.arcs[i][j]=INFINITY;
		}
		for(k=0;k<G.arcnum;++k){
			printf("�����%d����vi��vj��Ȩֵw(int):\n",k+1);
			scanf("%c%c%d",&v1,&v2,&w);
			getchar();
			i=LocateVex(G,v1);	j=LocateVex(G,v2);
			G.arcs[i][j]=w;//��<v1,v2>��Ȩֵ
			G.arcs[j][i]=G.arcs[i][j];
		}
		return OK;
}//���������� 

void list(MGraph G){
	int i,j;
	printf("����ڽӾ���\n");
	for(i=0;i<G.vexnum;++i){
		printf("%c----",G.vexs[i]);
		for(j=0;j<G.vexnum;++j)
			if(G.arcs[i][j]=INFINITY)
				printf("%4s","��");
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
}//���߰�Ȩֵ�Ӵ�С����

void print_edge(Edge edge[],int arcnum){
    int i = 0;
    while(i < arcnum){
        printf("%d,%d,%d",edge[i].start,edge[i].end,edge[i].cost);
        i++;
    }
}//����ߵ���Ϣ

int findFather(int father[],int v){
    int t = v;
    while(father[t] != -1)
        t = father[t];
    return t;
}//�ҳ�ָ���ڵ����������ͨ�������������ҳ�����ڵ���father�������±�

void MiniSpanTree_Kruscal(MGraph G,Edge edge[]){
    int father[MAX_VERTEX_NUM];
    int i,count,v1,v2;
    // ��ʼ��father����
    for(i = 0;i < MAX_VERTEX_NUM;i++){
        father[i] = -1;
    }
    i = 0;
    count = 0; // ͳ�Ƽ�����С�����еı���
    // ���������������֮��ı�
    while(i < G.arcnum && count < G.arcnum){
        v1 = findFather(father,edge[i].start);
        v2 = findFather(father,edge[i].end);
        // ����������ڵ㲻����ͬһ����ͨ�����������ͬһ����ͨ����
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
