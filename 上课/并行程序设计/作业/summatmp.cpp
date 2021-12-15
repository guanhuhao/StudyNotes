// 本实验通信域大小为4,其中所有myid%4=0的构成通信域H
// root节点为id最大的,因此要求numprocs应该为4k+1
#include <stdio.h>
#include <string.h>
#include <bits/stdc++.h>
#include "mpi.h"
using namespace std;
const int maxn = 4;
/*summa算法 */
int mesh_c=maxn;
int mesh_r=maxn;
int n=maxn;
int m=maxn;
int l=maxn;
int num_procs = 0;
int C[maxn][maxn];
int A[maxn][maxn];
int A_line[maxn*maxn];
int B[maxn][maxn];
int B_line[maxn*maxn];
void My_summa(const int my_rank, int *a, int *b)
{
    int *c;
    int len_c;
    int dest, tag;
    int my_rank_row, my_rank_col;
    int *a_col_send, *b_row_send, *a_col_recv, *b_row_recv;
    MPI_Status status_a, status_b;
    my_rank_row = my_rank / mesh_c;
    my_rank_col = my_rank % mesh_c;
    a_col_send = (int *)malloc((m / mesh_r) * sizeof(int));    
    b_row_send = (int *)malloc((n / mesh_c) * sizeof(int));    
    a_col_recv = (int *)malloc((m / mesh_r) * sizeof(int));
    b_row_recv = (int *)malloc((n / mesh_c) * sizeof(int));

    /*各处理器将自己所拥有的A矩阵分块的列发送给跟自己同一行的其他处理器*/
    printf("check1\n");
    for (int k = 0; k < l / mesh_c; ++k)
    {
        for (int i = 0; i < m / mesh_r; ++i)
        {
            a_col_send[i] = a[i * (l / mesh_c) + k];
        }
        printf("check 1.1\n");
        for (int i = 0; i < mesh_c; ++i)
        {
            dest = my_rank_row * mesh_c + i;
            tag = my_rank_col * (l / mesh_c) + k;
            printf("dest:%d tag:%d\n",dest,tag);
            MPI_Send(a_col_send, m / mesh_r, MPI_INT, dest, tag, MPI_COMM_WORLD);
        }
    }
    printf("check2\n");
    /*各处理器将自己所拥有的B矩阵分块的行发送给跟自己同一列的其他处理器*/
    for (int k = 0; k < l / mesh_r; ++k)
    {                        
        for (int i = 0; i < n / mesh_c; ++i)
        {
            b_row_send[i] = b[k * (n / mesh_c) + i];
        }
        for (int i = 0; i < mesh_r; ++i)
        {
            dest = my_rank_col + i * mesh_c;
            tag = my_rank_row * (l / mesh_r) + k;
            MPI_Send(b_row_send, n / mesh_c, MPI_INT, dest, tag, MPI_COMM_WORLD);
        }
    }
    printf("check3\n");
    /*初始化C分块 */
    len_c = (m / mesh_r) * (n / mesh_c);
    c = (int *)malloc(len_c * sizeof(int));
    for (int i = 0; i < len_c; ++i)
    {
        c[i] = 0;
    }
       
    for (int k = 0; k < l; ++k)
    {      /*各个处理器接收来自同一行处理器中的所有A分块的列和同一列处理器中的所有B分块的行*/
        MPI_Recv(a_col_recv, m / mesh_r, MPI_INT, my_rank_row * mesh_c + k / (l / mesh_c), k,
                MPI_COMM_WORLD, &status_a);
        MPI_Recv(b_row_recv, n / mesh_c, MPI_INT, k / (l / mesh_r) * mesh_c + my_rank_col, k,
                MPI_COMM_WORLD, &status_b);
               /*各个处理器已经拥有了计算对应C子块的所有信息，相乘累加后即可得到对应C子块*/
        for (int x = 0; x < m / mesh_r; ++x)
        { 
            for (int y = 0; y < n / mesh_c; ++y)
            {
                c[x * (n / mesh_c) + y] += a_col_recv[x] * b_row_recv[y]; 
            }
        }
    }
        /*各处理器将C子块发送给0号进程*/
    MPI_Send(c, len_c, MPI_INT, 0, 99, MPI_COMM_WORLD);
    free(c);
    free(a_col_send), free(b_row_send), free(a_col_recv), free(b_row_recv);
}

 /*0号进程接收所有C子块信息*/
void Collect_C()
{
    int k, i, j;
    int len_c, id_recv;
    int *c_recv;
    int c_imin, c_imax, c_jmin, c_jmax;
    MPI_Status status;

    len_c = (m / mesh_r) * (n / mesh_c);
    c_recv = (int *)malloc(len_c * sizeof(int));
        /*将C子块填到相应的C矩阵坐标下 */
    for (k = 0; k < num_procs; ++k)
    {
        MPI_Recv(c_recv, len_c, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        id_recv = status.MPI_SOURCE;
        c_imin = (id_recv / mesh_c) * (m / mesh_r);
        c_imax = c_imin + m / mesh_r - 1;
        c_jmin = (id_recv % mesh_c) * (n / mesh_c);
        c_jmax = c_jmin + n / mesh_c - 1;
        for (i = c_imin; i <= c_imax; ++i)
        {
            for (j = c_jmin; j <= c_jmax; ++j)
            {
                C[i][j] = c_recv[(i - c_imin) * (n / mesh_c) + (j - c_jmin)];
            }
        }    
    }

    free(c_recv);
}

 /*打印矩阵 */
void Print(char *str, int matrix[maxn][maxn], int m, int n)
{
    int i, j;
    printf("%s", str);
    for (i = 0; i < m; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            printf("%-6d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void RandData(){
    for(int i = 0; i < maxn; i++){
        for(int j = 0 ; j < maxn; j++){
            A[i][j] = rand()%100;
            B[i][j] = rand()%100;
            A_line[i*maxn+j] = A[i][j];
            B_line[i*maxn+j] = B[i][j];
        }
    }
}
int main(int argc,char* argv[]){

    RandData();

    int myid, source;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    My_summa(myid, A_line, B_line);
    Collect_C();
    Print("Summa 计算结果",C,maxn,maxn);
    return 0;
}