#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define TRUE 1 
#define FALSE 0 
#define OK 1 
#define ERROR 0 
#define OVERFLOW -2 
#define LIST_INIT_SIZE 100 
#define LISTINCREMENT 10 
typedef int Status; 
typedef int ElemType; 
typedef struct{ ElemType *elem; 	
	int length; 	
	int listsize; 
}SqList; 

Status InitList(SqList &L) {
	L.elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!L.elem) exit(OVERFLOW); 	L.length=0;
	L.listsize=LIST_INIT_SIZE; 	return OK;
 }

 void MergeList(SqList La,SqList Lb,SqList &Lc) {
	 int *pa;int *pb;int *pc;
	 int *pa_last;int *pb_last;
	 pa=La.elem;pb=Lb.elem;
	 Lc.listsize=Lc.length=La.length+Lb.length;
	 pc=Lc.elem=(ElemType*)malloc(Lc.listsize*sizeof(ElemType));
	 if(!Lc.elem) exit(OVERFLOW);
	 pa_last=La.elem+La.length-1;
	 pb_last=Lb.elem+Lb.length-1;
	 while(pa<=pa_last&&pb<=pb_last){
		 if(*pa<=*pb) *pc++=*pa++;
		 else *pc++=*pb++;
	}
	 while(pa<=pa_last) *pc++=*pa++;
	 while(pb<=pb_last) *pc++=*pb++;
 }
 
 void CreateList(SqList &L,int n){
	 int i;
	 printf("输入%d个元素:\n",n);
	 for(i=0;i<n;i++)
		 scanf("%d",&L.elem[i]);
	 printf("\n");
	 L.length=n; L.listsize=LIST_INIT_SIZE;
 }
 
 void DispList(SqList L) {
	 int i;
	 if(L.length==0) return;
	 for(i=0;i<L.length;i++)
		 printf("%d",L.elem[i]);
	 printf("\n");
 }
 
 int main() {
	 SqList La;SqList Lb;SqList Lc;
	 InitList(La);InitList(Lb);InitList(Lc);
	 printf("创建顺序表！");
	 CreateList(La,5);CreateList(Lb,5);
	 MergeList(La,Lb,Lc);
	 printf("输出顺序表所有元素！");
	 DispList(Lc);
	 return 0; 
 } 