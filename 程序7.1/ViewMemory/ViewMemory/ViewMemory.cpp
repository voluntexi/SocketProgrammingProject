//����7.1 ��ӡ�������ڴ��ַ
#include <stdio.h>
int g1=0, g2=0, g3=0;
int main()
{
static int s1=0, s2=0, s3=0;
int v1=0, v2=0, v3=0;
//��ӡ�������������ڴ��ַ
printf("0x%x\n",&v1); //��ӡ�����ر������ڴ��ַ
printf("0x%x\n",&v2);
printf("0x%x\n\n",&v3);
printf("0x%x\n",&g1); //��ӡ��ȫ�ֱ������ڴ��ַ
printf("0x%x\n",&g2);
printf("0x%x\n\n",&g3);
printf("0x%x\n",&s1); //��ӡ����̬�������ڴ��ַ
printf("0x%x\n",&s2);
printf("0x%x\n\n",&s3);
return 0;
}