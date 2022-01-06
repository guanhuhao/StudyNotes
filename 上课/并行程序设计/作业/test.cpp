#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define A(x, y) A[x * N + y]
#define Q(x, y) Q[x * N + y]

int N;
float *A, *Q;

void  wait(int line, int base, int *condition)
{
    while (1)
    {
        if (condition[line] >= base)
        {
            break;
        }
    }
}
void transform(int j, int start, int end)
{
    for (int i = start; i < end; ++i)
    {
        float sq = sqrt(A(j, j) * A(j, j) + A(i, j) * A(i, j));
        float c = A(j, j) / sq;
        float s = A(i, j) / sq;
        float ajk, aik, qjk, qik;
        for (int k = 0; k < N; ++k)
        {
            ajk = c * A(j, k) + s * A(i, k);
            qjk = c * Q(j, k) + s * Q(i, k);
            aik = -s * A(j, k) + c * A(i, k);
            qik = -s * Q(j, k) + c * Q(i, k);
            A(j, k) = ajk;
            Q(j, k) = qjk;
            A(i, k) = aik;
            Q(i, k) = qik;
        }
    }
}

void randData(){
    freopen("data.txt","w",stdout);
    int n=1000;
    printf("%d\n",n);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            printf("%d ",rand()%100);

    fclose(stdout);
}

int main(int argc, char **argv)
{
    double start, end;
    int threads_num = 16;
    FILE *fp = fopen("data.txt", "r");
    fscanf(fp, "%d", &N);
    A = (float *)malloc(N * N * sizeof(float));
    for (int i = 0; i < N * N; ++i)
    {
        fscanf(fp, "%f", A + i);
    }
    fclose(fp);
    Q = (float *)malloc(N * N * sizeof(float));
    for (int i = 0; i < N * N; ++i)
    {
        if (i / N == i % N)
        {
            Q[i] = 1;
        }
        else
        {
            Q[i] = 0;
        }
    }
    int *condition = (int *)malloc(N * sizeof(int));
    int total_thread, my_thread, block, base;
    for (int i = 0; i < N; i++)
    {
        condition[i] = 0;
    }
    start = omp_get_wtime();
    omp_set_num_threads(threads_num);
#pragma omp parallel shared(Q, A, condition) private(my_thread, total_thread, base, block)
    {
        my_thread = omp_get_thread_num();
        total_thread = omp_get_num_threads();
        block = N / total_thread;
        base = my_thread * block;
        for (int j = 0; j < base + block; ++j)
        {
            if (j < base)
            {
                 wait(j, base, condition);
                transform(j, base, base + block);
            }
            else
            {
                transform(j, j + 1, base + block);
            }
            condition[j] = base + block;
        }
    }
    end = omp_get_wtime();
    printf("%.3f\n", (double)(end - start) * 1e3);
    free(A);
    free(Q);
    free(condition);
    return 0;
}
