#include <stdio.h>
#include <malloc.h>

#define ONEGB 1024*1024*1024

int main()
{
    int count = 5;
    long long* buf[count];

    printf("���������� �������� 5 GB �� 1GB\n");
    for (int i = 0; i < count; i++)
    {
        buf[i] = malloc(ONEGB);
        if (buf[i] == NULL)
        {
            printf("������");
            return -1;
        }
    }
    printf("������� �������� %d GB\n", count);
    getchar();
    printf("������� �������� ������ � ������ 2 GB\n");
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < ONEGB / sizeof(long long); i++)
        {
            buf[j][i] = 7;
        }
    }
    printf("������� �������� ������ � 2 GB\n ������� �������� �����\n");
    getchar();
    printf("������ ������� �������� ������ � ���������� 3 GB\n"); //�������� �� ���������
    for (int j = 2; j < count; j++)
    {
        for (int i = 0; i < ONEGB / sizeof(long long); i++)
        {
            buf[j][i] = 8;
        }
    }
    printf("������� �������� ������");
    return 0;
}