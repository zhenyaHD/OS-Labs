##include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>
int Loto[] = { 65,88,36,21,88,92 };
#define N 10
int main()
{
    printf("\nWelcome to Albanska Loto\n\n      ---Loto---\n");
    pid_t pids[N];
    for (int i = 0; i < N; i++)
    {
        if ((pids[i] = fork()) < 0)
        {
            printf("Ошибка процесса потомка");
            abort();
        }
        else if (pids[i] == 0)
        {
            srand(time(0) + getpid());
            printf("          %d\n", Loto[rand() % 6]);
            exit(0);
        }
    }
    int n = N;
    while (n > 0)
    {
        wait(NULL);
        n--;
    }
    printf("      ---End---\n");
}