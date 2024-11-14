#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    int arr[] = {
         5, 12, 16, 20, 0,
         9, 8, 7, 6, 0,
         0, 0, 5, 2, 5,
         0, 7, 10, 15, 0,
         3, 2, 5, 7, 0 };
    int my_file;
    int* my_map;
    struct stat s;
    my_file = open("file.bin", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU | S_IRGRP | S_IROTH);
    lseek(my_file, sizeof(arr) - 1, SEEK_SET);//на нулевой байт переходим
    write(my_file, "", 1);//делаем запись 0, что означает конец строки, т.е. и записываем туда 1 байт(нулевой)
    my_map = mmap(0, sizeof(arr), PROT_WRITE | PROT_READ, MAP_SHARED, my_file, 0);
    close(my_file);

    memcpy(my_map, arr, sizeof(arr));
    munmap(my_map, sizeof(arr));

    my_file = open("file.bin", O_RDONLY, 0);
    fstat(my_file, &s);
    my_map = mmap(0, s.st_size, PROT_READ, MAP_SHARED, my_file, 0);
    close(my_file);
    int count = 0;
    while (my_map[count] != 0)
    {
        printf("Массив номер %d начинается с %d\n ячейки", count + 1, my_map[count]);
        count++;
    }
    printf("Всего arry: %d\n", count);

    munmap(my_map, sizeof(my_map));

    int i;
    printf("Индекс массива: ");
    scanf("%d", &i);

    my_file = open("file.bin", O_RDONLY);
    fstat(my_file, &s);
    my_map = mmap(0, s.st_size, PROT_READ, MAP_SHARED, my_file, 0);
    close(my_file);
    int j = 0;
    for (j = my_map[i - 1]; my_map[j] != 0; j++)
    {
        printf("%d ", my_map[j]);
    }

    munmap(my_map, sizeof(my_map));
    return 0;
}
