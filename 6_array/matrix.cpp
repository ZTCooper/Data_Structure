#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 12500
typedef int Status;
typedef int ElemType;
#define MU 5
#define NU 6
typedef struct{
	int i,j;
	ElemType e;
}Triple;
typedef struct{
	Triple data[MAXSIZE+1];
	int mu,nu,tu;
}TSMatrix;

Status CreatMatrix(TSMatrix &M)
{
	int e,i,j,k=1;
	M.mu=MU; M.nu=NU;
	srand((unsigned)time(NULL));
	M.tu=rand()%15;
	for(i=1;i<M.mu;i++)
	{
		for(j=1;j<M.nu;j++)
		{
			e=rand()%30;
			if(e!=0){
				M.data[k].i=i;
				M.data[k].j=j;
				M.data[k].e=e;
				k++;				
			}
		}if(k==M.tu) break;
	}
		return OK;
}

void print(TSMatrix M){
	int k;
	printf("mu=%-2d,nu=%-2d,tu=%-2d",M.mu,M.nu,M.tu);
	printf("\n");
	for(k=1;k<=M.tu;k++){
		printf("i=%-2d,j=%-2d,e=%-2d",M.data[k].i,M.data[k].j,M.data[k].e);
		printf("\n");
	}
}

Status TransposeSMatrix(TSMatrix M,TSMatrix &T){
	T.mu=M.nu;T.nu=M.mu;T.tu=M.tu;
	if(T.tu){
		int q=1;
		for(int col=1;col<=M.nu;++col)
			for(int p=1;p<=M.tu;++p)
				if(M.data[p].j==col){
					T.data[q].i=M.data[p].j;
					T.data[q].j=M.data[p].i;
					T.data[q].e=M.data[p].e;
					++q;}
				}
	return OK;
}

Status FastTransposeSMatrix(TSMatrix M,TSMatrix &T){
	int num[MAXSIZE],cpot[MAXSIZE];
	T.mu=M.nu;T.nu=M.mu;T.tu=M.tu;
	if(T.tu){
		for(int col=1;col<=M.nu;++col) num[col]=0;
		for(int t=1;t<=M.tu;++t) ++num[M.data[t].j];
		cpot[1]=1;
		for(col=2;col<=M.nu;++col) cpot[col]=cpot[col-1]+num[col-1];
		for(int p=1;p<=M.tu;++p){
			col=M.data[p].j;
			int q=cpot[col];
			T.data[q].i=M.data[p].j;
			T.data[q].j=M.data[p].i;
			T.data[q].e=M.data[p].e;
			++cpot[col];
		}
	}
	return OK;
}

void main()
{
	TSMatrix M,T;
	CreatMatrix(M);
    FastTransposeSMatrix(M,T);
	printf("Êä³öÏ¡Êè¾ØÕóM£º\n");
	print(M);
	printf("Êä³ö×ªÖÃ¾ØÕóT£º\n");
	print(T);
}



