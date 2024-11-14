#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <__msvc_filebuf.hpp>
#include <xlocmes>
typedef struct { char name[100]; int age; int skill; } mystruct;
int main()
{
    int my_file;
    mystruct form;
    struct flock fl;
    char filename[100];
    int index;

    printf("Введите название нового или старого файла с анкетами(.bin): ");
    scanf("%100s", &filename);
    char ac;
    printf("Долбавить новую анкуету: A\nРаботать с существующими: C\n");
    scanf("%c", &ac);
    if (ac == 'A' || ac == 'a') 
    {
        my_file = open(filename, O_RDWR | O_CREAT, S_IRWXU | S_IRGRP | S_IROTH);
        if (my_file == -1) {
            printf("--- Ошибка: %s ---\n", strerror(errno));
            return 0;
        }
        printf("Ввести Ф_И_О(вместо пробелов используйте _ ): ");
        scanf("%100s", &form.name);
        printf("Ввести возраст: ");
        scanf("%3d", &form.age);
        printf("Ввести стаж: ");
        scanf("%3d", &form.skill);
        lseek(my_file, 0, SEEK_END);
        write(my_file, &form, sizeof(mystruct));
        close(my_file);
    }
    else if (ac == 'C' || ac == 'c')
    {
        printf("Введите номер анкеты(число): ");
        scanf("%4d", &index);
        char rw;
        printf("Читать: R\nПисать: W\n");
        scanf("%c", &rw);
        if (rw == 'W' || rw == 'w')
        {
            my_file = open(filename, O_RDWR | O_CREAT, S_IRWXU | S_IRGRP | S_IROTH);
            if (my_file == -1) {
                printf("--- Ошибка: %s ---\n", strerror(errno));
                return 0;
            }
            memset(&fl, 0, sizeof(fl));
            fl.l_type = F_WRLCK;
            fl.l_whence = SEEK_SET;
            fl.l_start = sizeof(mystruct) * (index - 1);
            fl.l_len = sizeof(mystruct);
            fcntl(my_file, F_SETLKW, &fl);
            lseek(my_file, sizeof(mystruct) * (index - 1), SEEK_SET);
            read(my_file, &form, sizeof(mystruct));
            printf("\n%s\n%d\n%d\n", form.name, form.age, form.skill);
            memset(&fl, 0, sizeof(fl));
            printf("Изменить Ф_И_О(вместо пробелов используйте _ ): ");
            scanf("%100s", &form.name);
            printf("Изменить возраст: ");
            scanf("%3d", &form.age);
            printf("Изменить стаж: ");
            scanf("%3d", &form.skill);
            lseek(my_file, sizeof(mystruct) * (index - 1), SEEK_SET);
            write(my_file, &form, sizeof(mystruct));
            close(my_file);
        }
        else if (rw == 'R' || rw == 'r')
        {
            my_file = open(filename, O_RDONLY, 0);
            if (my_file == -1) 
            { 
                printf("--- Ошибка: %s ---\n", strerror(errno));
                return 0; 
            }
            lseek(my_file, sizeof(mystruct) * (index - 1), SEEK_SET);
            read(my_file, &form, sizeof(mystruct));
            printf("\nФИО: %s\nВозраст: %d\nСтаж: %d\n", form.name, form.age, form.skill);
            printf("Закрытие чтения");
            close(my_file);
        }
        else
        {
            printf("Error");
        }
    }
    else 
    {
        printf("Error");
    }
    return 0;
}




