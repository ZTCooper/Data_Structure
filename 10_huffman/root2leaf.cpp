#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;
typedef char TElemType;
typedef struct{
	unsigned int weight;
	unsigned int parent,lchild,rchild;
}HTNode,*HuffmanTree;
typedef char **HuffmanCode;
int s1,s2;

void Select(HuffmanTree HT,int u,int &s1,int &s2){
	int j;
	j=1;
	while(j<=u&&HT[j].parent!=0) j++;
	s1=j;
	while(j<=u){
		if(HT[j].parent==0&&HT[j].weight<HT[s1].weight) s1=j;
		j++;
	}
	HT[s1].parent=u+1;
	j=1;
	while(j<=u&&HT[j].parent!=0) j++;
	s2=j;
	while(j<=u){
		if(HT[j].parent==0&&HT[j].weight<HT[s2].weight) s2=j;
		j++;
	}
	if(s1>s2){
		j=s1;s1=s2;s2=j;
	}
}

void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int *w,int n){
	int m,i,j;
	if(n<=1) return;
	m=2*n-1;
	HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));
	//for(p=HT+1,i=1;i<=n;++i,++p,++w) *p={*w,0,0,0};
	for(i=1;i<=n;i++){
		HT[i].weight=w[i-1];
		HT[i].parent=0;
		HT[i].lchild=0;
		HT[i].rchild=0;
	}
	//for(;i<=m;++i,++p) *p={0,0,0,0};
	for(i=n+1;i<=m;i++){
		HT[i].weight=0;
		HT[i].parent=0;
		HT[i].lchild=0;
		HT[i].rchild=0;
	}
	printf("结点	weight	parent	lchild	rchild\n");
	for(i=1;i<=m;i++)
		printf("%4d%8d%8d%8d%8d\n",i,HT[i].weight,HT[i].parent,HT[i].lchild,HT[i].rchild);
	for(i=n+1;i<=m;++i){//建赫夫曼树
		Select(HT,i-1,s1,s2);
		HT[s1].parent=i;HT[s2].parent=i;
		HT[i].lchild=s1;HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;
	printf("\nselect:s1=%d s2=%d\n\n",s1,s2);
	printf("结点	weight	parent	lchild	rchild\n");
	for(j=1;j<=i;j++)
		printf("%4d%8d%8d%8d%8d\n",j,HT[j].weight,HT[j].parent,HT[j].lchild,HT[j].rchild);
	}
	//从根到叶子
	char *cd;
	HC=(HuffmanCode)malloc((n+1)*sizeof(char *));
	cd=(char *)malloc(n*sizeof(char));
	int p=m,cdlen=0;
	for(i=1;i<=m;++i)	HT[i].weight=0;
	while(p){
		if(HT[p].weight==0){
			HT[p].weight=1;
			if(HT[p].lchild!=0){p=HT[p].lchild;cd[cdlen++]='0';}
			else if(HT[p].rchild==0){
				HC[p]=(char *)malloc((cdlen+1)*sizeof(char));
				cd[cdlen]='\0',strcpy(HC[p],cd);
			}
		}
		else if(HT[p].weight==1){
			HT[p].weight=2;
			if(HT[p].rchild!=0)
			{
				p=HT[p].rchild;
				cd[cdlen++]='1';
			}
			else
			{
				HT[p].weight=0;
				p=HT[p].parent;
				--cdlen;
			}
		}
	}
}

bool visited[MAX];
Status(*VisitFunc)(int v);

void DFSTraverse(Graph G,Status(*Visit)(int v)){
	VisitFunc=Visit;
	for(v=0;v<G.vexnum;++v) visited[v]=FALSE;
	for(v=0;v<G.vexnum;++v)
	if(!visited[v]) DFS(G,v);
}

void DFS(Graph G,int v){
	visited[v]=TRUE; VisitFunc(v);
	ArcNode *p;
	for(p=G.vertices[v].firstarc; p!=NULL; p=p->nextarc)
	if(!visited[p->adjvex]) DFS(G,w)
}

int main(){
	int w[]={5,29,7,8,14,23,3,11},n=8;
	HuffmanTree HT;
	HuffmanCode HC;
	HuffmanCoding(HT,HC,w,n);
}
