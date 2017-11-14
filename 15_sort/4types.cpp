#include <stdio.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define MAXSIZE 20          //һ������ʾ����С˳������󳤶�
#define LT(a, b) (a<b)
#define EQ(a, b) (a==b)
int pivotkey,pivotloc;
typedef int Status;
typedef int KeyType;
typedef int InfoType;
typedef struct {	
	KeyType key;            //�ؼ�����
	InfoType otherinfo;      //����������
}RedType;
typedef struct {	
	RedType r[MAXSIZE+1];   //r[0]���û������ڱ���Ԫ
	int length;             //˳�����
}SqList;                    //˳�������

//��ʼ��˳���
Status InitList(SqList &L) { 
  // ����һ���յ�˳���L��
  L.length = 0;            //�ձ���Ϊ0
  return OK;
} // InitList

//����n��Ԫ�ص�˳���
Status CreateList(SqList &L, int n) {
	int i;
	printf("����%d��Ԫ�أ�\n",n);
	for(i=1; i<=n; i++) {
		scanf("%d", &L.r[i].key);
		++L.length;
	}
	if (L.length==0) return ERROR;     // ����ʧ��
	return OK;
}

//���˳���
Status DispList(SqList &L) {  //���������
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
	printf("��ʼ��˳���");
	InitList(L);
	if (L.length==0)
		printf("˳���Ϊ�գ�\n");
	printf("����˳����Ԫ�ظ�����");
	scanf("%d", &n);
	CreateList(L, n);
	printf("���%d��Ԫ�ص�˳������£�\n", n);
	DispList(L);
	InsertSort(L);
	printf("ֱ�Ӳ������������£�\n");
	DispList(L);

	printf("��ʼ��˳���");
	InitList(L);
	if (L.length==0)
		printf("˳���Ϊ�գ�\n");
	printf("����˳����Ԫ�ظ�����");
	scanf("%d", &n);
	CreateList(L, n);
	printf("���%d��Ԫ�ص�˳������£�\n", n);
	DispList(L);
	QuickSort(L);
	printf("�������������£�\n");
	DispList(L);

	printf("��ʼ��˳���");
	InitList(L);
	if (L.length==0)
		printf("˳���Ϊ�գ�\n");
	printf("����˳����Ԫ�ظ�����");
	scanf("%d", &n);
	CreateList(L, n);
	printf("���%d��Ԫ�ص�˳������£�\n", n);
	DispList(L);
	SelectSort(L);
	printf("ѡ�����������£�\n");
	DispList(L);

	printf("��ʼ��˳���");
	InitList(L);
	if (L.length==0)
		printf("˳���Ϊ�գ�\n");
	printf("����˳����Ԫ�ظ�����");
	scanf("%d", &n);
	CreateList(L, n);
	printf("���%d��Ԫ�ص�˳������£�\n", n);
	DispList(L);
	HeapSort(L);
	printf("�����������£�\n");
	DispList(L);
}