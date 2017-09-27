#include <stdio.h>
int Count=0;

void move(char x, int n, char z)
{
	printf("%2d. Move disk %d: %c-->%c\n", ++Count, n, x, z);
}

void hanoi (int n, char x, char y, char z) {  // �㷨3.5
  // ������x�ϰ�ֱ����С���������϶��±��Ϊ1��n��n��Բ�̰�����ᵽ
  // ����z�ϣ�y����������������
  // �ᶯ���� move (x, n, z) �ɶ���Ϊ��
  //   (c�ǳ�ֵΪ0��ȫ�ֱ������԰ᶯ����)
  //   printf("%i. Move disk %i from  %c  to  %c\n", ++c, n, x, z);
  if (n==1)
    move(x, 1, z);        //�����Ϊ����Բ�̴�x�Ƶ�z
  else {
    hanoi(n-1,x,z,y);
    move(x, n, z);        //�����Ϊn��Բ�̴�x�Ƶ�z
    hanoi(n-1, y, x, z);  //��y�ϱ��Ϊ����n-1��Բ���Ƶ�z,x��������
  }
}

void main()
{
	int m;
	printf("input the number of disks: ");
	scanf("%d", &m);
	printf("The step to move %d disks:\n",m);
	hanoi(m, 'a', 'b', 'c');
}