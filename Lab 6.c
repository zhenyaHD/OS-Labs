#include <stdio.h>
#include <malloc.h>

#define ONEGB 1024*1024*1024

int main()
{
    int count = 5;
    long long* buf[count];

    printf("Запрашиваю выделить 5 GB по 1GB\n");
    for (int i = 0; i < count; i++)
    {
        buf[i] = malloc(ONEGB);
        if (buf[i] == NULL)
        {
            printf("Ошибка");
            return -1;
        }
    }
    printf("Успешно выделено %d GB\n", count);
    getchar();
    printf("Пробуем записать данные в первые 2 GB\n");
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < ONEGB / sizeof(long long); i++)
        {
            buf[j][i] = 7;
        }
    }
    printf("Успешно записаны данные в 2 GB\n Нажмите кнопочку любую\n");
    getchar();
    printf("Теперь пробуем записать данные в оставшиеся 3 GB\n"); //Записать не получится
    for (int j = 2; j < count; j++)
    {
        for (int i = 0; i < ONEGB / sizeof(long long); i++)
        {
            buf[j][i] = 8;
        }
    }
    printf("Успешно записаны данные");
    return 0;
}