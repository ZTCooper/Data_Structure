#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;
typedef struct{
	char *ch;
	int length;
}HString;

Status StrAssign(HString &T,char *chars){
	int i=0,j;
	if(T.ch) free(T.ch);
	while(chars[i]) i++;
	if(!i){T.ch=NULL;	T.length=0;}
	else{
		if(!(T.ch=(char*)malloc(i*sizeof(char))))
			exit(OVERFLOW);
		for(j=0;j<i;j++)
			T.ch[j]=chars[j];
		T.length=j;
	}
	return OK;
}

Status StrLength(HString &S){
	return S.length;
}

int StrCompare(HString S,HString T){
	int i;
	for(i=0;i<S.length&&i<T.length;++i)
		if(S.ch[i]!=T.ch[i]) return S.ch[i]-T.ch[i];
		return S.length-T.length;
}

int ClearStr(HString &S){
	if(S.ch) {free(S.ch); S.ch=NULL;}
	S.length=0;
	return OK;
}

int StrDelete(HString &S,int pos,int len){
	int i;
	for(i=pos+len-1;i<=S.length-1;i++)
		S.ch[i-len]=S.ch[i];
	S.length=S.length-len;
	return OK;
}

Status Concat(HString &T,HString S1,HString S2){
	int i,j;
	if(T.ch) free(T.ch);
	if(!(T.ch=(char*)malloc((S1.length+S2.length)*sizeof(char))))
		exit(OVERFLOW);
	for(i=0;i<S1.length;i++)
		T.ch[i]=S1.ch[i];
	T.length=S1.length+S2.length;
	for(i=S1.length,j=0;i<T.length,j<S2.length;i++,j++)
		T.ch[i]=S2.ch[j];
	return OK;
}

Status StrCopy(HString &T,HString S){
	int i;
	if(T.ch) free(T.ch);
	if(!(T.ch=(char*)malloc((S.length)*sizeof(char))))
		exit(OVERFLOW);
	for(i=0;i<S.length;i++)
		T.ch[i]=S.ch[i];
	T.length=S.length;
	return OK;
}

Status SubString(HString &Sub,HString S,int pos,int len){
	int i,j;
	if(pos<1||pos>S.length||len<0||len>S.length-pos+1)
		return ERROR;
	if(Sub.ch) free(Sub.ch);
	if(!len){Sub.ch=NULL;	Sub.length=0;}
	else{
		Sub.ch=(char*)malloc(len*sizeof(char));
		for(i=0,j=pos-1;i<len,j<pos+len-1;i++,j++)
			Sub.ch[i]=S.ch[j];
		Sub.length=len;
	}
	return OK;
}

Status StrInsert(HString &S,int pos,HString T){
	int i,j;
	if(pos<1||pos>S.length+1) return ERROR;
	if(T.length){
		if(!(S.ch=(char*)realloc(S.ch,(S.length+T.length)*sizeof(char))))
			exit(OVERFLOW);
		for(i=S.length-1;i>=pos-1;--i)
			S.ch[i+T.length]=S.ch[i];
		for(i=pos-1,j=0;i<pos+T.length-1,j<T.length;i++,j++)
			S.ch[i]=T.ch[j];
		S.length+=T.length;
	}
	return OK;
}

int DispStr(HString &S){
	int i;
	for(i=0;i<S.length;i++)
		printf("%c",S.ch[i]);
	printf("\n");
	return OK;
}

void main()
{
	HString T,S,S1,S2,Sub;
	int pos,len;
	char *a,str[100],*chars="House";
	T.ch=NULL;
	S.ch=NULL;
	S1.ch=NULL;
	S2.ch=NULL;
	Sub.ch=NULL;
	printf("����ַ�������chars:%s\n",chars);
	StrAssign(T,chars);
	printf("����һ����ֵ���ڴ�����chars�Ĵ�T:");
	DispStr(T);
	StrCopy(S,T);
	printf("����T��ֵ���Ƶ���S��ȥ����S��ֵΪ��");
	DispStr(S);
	printf("��S�ĳ���Ϊ��%d\n",StrLength(S));
	printf("�Ƚϴ�S�ʹ�T�Ĵ�С��%d\n",StrCompare(S,T));
	printf("��S��Ϊ�մ���\n");
	ClearStr(S);
	printf("��S��ֵΪ��");
	DispStr(S);
	printf("��T��ֵΪ��");
	DispStr(T);
	a=str;
	printf("���봮S1��");
	scanf("%s",a);
	StrAssign(S1,a);
	printf("��S1��ֵΪ��");
	DispStr(S1);
	printf("���봮S2��");
	scanf("%s",a);
	StrAssign(S2,a);
	printf("��S2��ֵΪ��");
	DispStr(S2);
	printf("������S1��S2���Ӷ��ɵ��´�S��");
	Concat(S,S1,S2);
	DispStr(S);
	printf("����S���Ӵ�����ʼ�ַ�λ�ã�");
	scanf("%d",&pos);
	printf("����S���Ӵ��ĳ��ȣ�");
	scanf("%d",&len);
	printf("��Sub���ش�S�ĵ�%d���ַ��𳤶�Ϊ%d���Ӵ���",pos,len);
	SubString(Sub,S,pos,len);
	DispStr(Sub);
	printf("���봮S�Ĳ���λ�ã�");
	scanf("%d",&pos);
	printf("�ڴ�S��%d��λ�ò��봮T�������S��ֵΪ��",pos);
	StrInsert(S,pos,T);
	DispStr(S);
	printf("���봮Sɾ�����Ӵ�����ʼ�ַ�λ�ã�");
	scanf("%d",&pos);
	printf("���봮Sɾ�����Ӵ��ĳ��ȣ�");
	scanf("%d",&len);
	printf("��S��ɾ����%d���ַ��𳤶�Ϊ%d���Ӵ���ɾ����S��ֵΪ��",pos,len);
	StrDelete(S,pos,len);
	DispStr(S);
}
