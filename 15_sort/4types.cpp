#include <stdio.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define MAXSIZE 20          //一个用作示例的小顺序表的最大长度
#define LT(a, b) (a<b)
#define EQ(a, b) (a==b)
int pivotkey,pivotloc;
typedef int Status;
typedef int KeyType;
typedef int InfoType;
typedef struct {	
	KeyType key;            //关键字项
	InfoType otherinfo;      //其他数据项
}RedType;
typedef struct {	
	RedType r[MAXSIZE+1];   //r[0]闲置或用作哨兵单元
	int length;             //顺序表长度
}SqList;                    //顺序表类型

//初始化顺序表
Status InitList(SqList &L) { 
  // 构造一个空的顺序表L。
  L.length = 0;            //空表长度为0
  return OK;
} // InitList

//创建n个元素的顺序表
Status CreateList(SqList &L, int n) {
	int i;
	printf("输入%d个元素：\n",n);
	for(i=1; i<=n; i++) {
		scanf("%d", &L.r[i].key);
		++L.length;
	}
	if (L.length==0) return ERROR;     // 创建失败
	return OK;
}

//输出顺序表
Status DispList(SqList &L) {  //输出排序结果
	int i;
	if (L.length==0) return ERROR;
	for(i=1; i<=L.length; i++)
		printf("%d ", L.r[i].key);
	printf("\n");
	return OK;
}

void InsertSort(SqList &L){
	for(int i=2;i<=L.length;++i)
		if(LT(L.r[i].key,L.r[i-1].key)){
			L.r[0]=L.r[i];
			L.r[i]=L.r[i-1];
			for(int j=i-2;LT(L.r[0].key,L.r[j].key);--j)
				L.r[j+1]=L.r[j];
			L.r[j+1]=L.r[0];
		}
}

int Partition(SqList &L,int low,int high){
	L.r[0]=L.r[low];
	pivotkey=L.r[low].key;
	while(low<high){
		while(low<high&&L.r[high].key>=pivotkey) --high;
		L.r[low]=L.r[high];
		while(low<high&&L.r[low].key<=pivotkey) ++low;
		L.r[high]=L.r[low];
	}
	L.r[low]=L.r[0];
	return low;
}

void QSort(SqList &L,int low,int high){
	if(low<high){
		pivotloc=Partition(L,low,high);
		QSort(L,low,pivotloc-1);
		QSort(L,pivotloc+1,high);
	}
}

void QuickSort(SqList &L){
	QSort(L,1,L.length);
}

int SelectMinKey(SqList &L,int i){
	int min;
	for(i=1;i<n;i++){
		min=i;
		for(int j=i;j<n;j++)
			if(L.r[j].key<L.r[min].key)
				min=j;
	}
	return min;
}

void SelectSort(SqList &L){
	for(int i=1;i<L.length;++i){
		int j=SelectMinKey(L,i);
		if(i!=j){
			int temp=L.r[i].key;
			L.r[i].key=L.r[j].key;
			L.r[j].key=temp;
		}
	}
}

void HeapAdjust(SqList &L,int s,int m){
	int rc=L.r[s].key;
	for(int j=2*s;j<=m;j*=2){
		if(j<m&&LT(L.r[j].key,L.r[j+1].key)) ++j;
		if(!LT(rc,L.r[j].key)) break;
		L.r[s]=L.r[j];	s=j;
	}
	L.r[s].key=rc;
}

void HeapSort(SqList &L){
	for(int i=L.length/2;i>0;--i)
		HeapAdjust(L,i,L.length);
	for(i=L.length;i>1;--i){
		int temp=L.r[1].key;
		L.r[1].key=L.r[i].key;
		L.r[i].key=temp;
		HeapAdjust(L,1,i-1);
	}
}

void main()
{
	SqList L;
	int n;
	printf("初始化顺序表，");
	InitList(L);
	if (L.length==0)
		printf("顺序表为空！\n");
	printf("输入顺序表的元素个数：");
	scanf("%d", &n);
	CreateList(L, n);
	printf("输出%d个元素的顺序表如下：\n", n);
	DispList(L);
	InsertSort(L);
	printf("直接插入排序结果如下：\n");
	DispList(L);

	printf("初始化顺序表，");
	InitList(L);
	if (L.length==0)
		printf("顺序表为空！\n");
	printf("输入顺序表的元素个数：");
	scanf("%d", &n);
	CreateList(L, n);
	printf("输出%d个元素的顺序表如下：\n", n);
	DispList(L);
	QuickSort(L);
	printf("快速排序结果如下：\n");
	DispList(L);

	printf("初始化顺序表，");
	InitList(L);
	if (L.length==0)
		printf("顺序表为空！\n");
	printf("输入顺序表的元素个数：");
	scanf("%d", &n);
	CreateList(L, n);
	printf("输出%d个元素的顺序表如下：\n", n);
	DispList(L);
	SelectSort(L);
	printf("选择排序结果如下：\n");
	DispList(L);

	printf("初始化顺序表，");
	InitList(L);
	if (L.length==0)
		printf("顺序表为空！\n");
	printf("输入顺序表的元素个数：");
	scanf("%d", &n);
	CreateList(L, n);
	printf("输出%d个元素的顺序表如下：\n", n);
	DispList(L);
	HeapSort(L);
	printf("堆排序结果如下：\n");
	DispList(L);
}