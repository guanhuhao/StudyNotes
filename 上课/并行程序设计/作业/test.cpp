#include <iostream>
#include <mpi.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <iomanip>

#define A(x, y) A[x * K + y]
#define B(x, y) B[x * N + y]
#define C(x, y) C[x * N + y]
#define subA(x, y) subA[x * b_Acol + y]
#define subB(x, y) subB[x * b_Bcol + y]
#define subC(x, y) subC[x * b_Bcol + y]
using namespace std;

int main(int argc, char **argv)
{

    if (argc != 5)
    {
        return 111;
    }
    int rank, size;
    int Pc, Pr;
    int b_Bcol, b_Arow, b_Acol, b_Brow;
    int self_col, self_row;
    int M, N, K;
    double start, end;
    double t[4] = {0.0}, sumt[4];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size); // assume size = x ^ 2, N % x == 0

    float *A, *B, *C, *subA, *subB, *subC, *subA_buf, *subB_buf;
    M = atoi(argv[1]);
    N = atoi(argv[2]);
    K = atoi(argv[3]);
    Pr = atoi(argv[4]);
    if(size % Pr != 0 && rank == 0){
        cout << "size cannot be divided by Pr. ERROR!" << endl;
    }
    Pc = size / Pr;

    if (rank == 0)
    {

        A = (float *)malloc(M * K * sizeof(float));
        B = (float *)malloc(N * K * sizeof(float));
        C = (float *)malloc(M * N * sizeof(float));
        for (int i = 0; i < M * K; ++i)
        {
            A[i] = 1.0;
        }
        for (int i = 0; i < K * N; ++i)
        {
            B[i] = 1.0;
        }
    }

    b_Arow = M / Pr;
    b_Bcol = N / Pc;
    b_Acol = K / Pc;
    b_Brow = K / Pr;

    start = MPI_Wtime();
    MPI_Comm topo_comm, row_comm, col_comm;
    int topo_dims[2] = {Pr, Pc};
    int periods[2] = {1, 1};
    int local_rank;
    int coord[2];
    MPI_Cart_create(MPI_COMM_WORLD, 2, topo_dims, periods, 1, &topo_comm);
    MPI_Comm_rank(topo_comm, &local_rank);
    MPI_Cart_coords(topo_comm, local_rank, 2, coord);
    int masks[4] = {0, 1, 1, 0};
    MPI_Cart_sub(topo_comm, masks, &row_comm);
    MPI_Cart_sub(topo_comm, masks + 2, &col_comm);

    subA = (float *)malloc(b_Arow * b_Acol * sizeof(float));
    subB = (float *)malloc(b_Brow * b_Bcol * sizeof(float));
    subC = (float *)malloc(b_Arow * b_Bcol * sizeof(float));

    subA_buf = (float *)malloc(b_Arow * sizeof(float));
    subB_buf = (float *)malloc(b_Bcol * sizeof(float));

    if (rank == 0)
    {
        for (int i = 0; i < b_Arow; ++i)
        {
            for (int j = 0; j < b_Acol; ++j)
            {
                subA(i, j) = A((i + coord[0] * b_Arow), (j + coord[1] * b_Acol));
            }
        }

        for (int i = 1; i < size; ++i)
        {
            int other_coord[2];
            MPI_Cart_coords(topo_comm, i, 2, other_coord);
            for (int j = 0; j < b_Arow; ++j)
            {
                MPI_Send(&A((other_coord[0] * b_Arow + j), (other_coord[1] * b_Acol)), b_Acol, MPI_FLOAT, i, j, topo_comm);
            }
        }
    }
    else
    {
        for (int j = 0; j < b_Arow; ++j)
        {
            MPI_Recv(subA + j * b_Acol, b_Acol, MPI_FLOAT, 0, j, topo_comm, MPI_STATUS_IGNORE);
        }
    }
    end = MPI_Wtime();
    t[0] = end - start;

    start = MPI_Wtime();
    if (rank == 0)
    {
        for (int i = 0; i < b_Brow; ++i)
        {
            for (int j = 0; j < b_Bcol; ++j)
            {
                subB(i, j) = B((i + coord[0] * b_Brow), (j + coord[1] * b_Bcol));
            }
        }

        for (int i = 1; i < size; ++i)
        {
            int other_coord[2];
            MPI_Cart_coords(topo_comm, i, 2, other_coord);
            for (int j = 0; j < b_Brow; ++j)
            {
                MPI_Send(&B((other_coord[0] * b_Brow + j), (other_coord[1] * b_Bcol)), b_Bcol, MPI_FLOAT, i, j, topo_comm);
            }
        }
    }
    else
    {
        for (int j = 0; j < b_Brow; ++j)
        {
            MPI_Recv(subB + j * b_Bcol, b_Bcol, MPI_FLOAT, 0, j, topo_comm, MPI_STATUS_IGNORE);
        }
    }
    memset(subC, 0, b_Arow * b_Bcol * sizeof(float));
    MPI_Barrier(MPI_COMM_WORLD);
    end = MPI_Wtime();
    t[1] = end - start;

    start = MPI_Wtime();
    for (int k = 0; k < K; ++k)
    {
        int root = k / b_Acol;
        int j = k % b_Acol;
        if (coord[1] == root)
        {
            for (int i = 0; i < b_Arow; ++i)
            {
                subA_buf[i] = subA(i, j);
            }
            MPI_Bcast(subA_buf, b_Arow, MPI_FLOAT, root, row_comm);
        }
        else
        {
            MPI_Bcast(subA_buf, b_Arow, MPI_FLOAT, root, row_comm);
        }

        root = k / b_Brow;
        j = k % b_Brow;
        if (coord[0] == root)
        {
            for (int i = 0; i < b_Bcol; ++i)
            {
                subB_buf[i] = subB(j, i);
            }
            MPI_Bcast(subB_buf, b_Bcol, MPI_FLOAT, root, col_comm);
        }
        else
        {
            MPI_Bcast(subB_buf, b_Bcol, MPI_FLOAT, root, col_comm);
        }

        for (int ii = 0; ii < b_Arow; ++ii)
        {
            for (int jj = 0; jj < b_Bcol; ++jj)
            {
                subC(ii, jj) += subA_buf[ii] * subB_buf[jj];
            }
        }
    }
    end = MPI_Wtime();
    t[2] = end - start;

    start = MPI_Wtime();
    if (rank == 0)
    {
        for (int i = 0; i < b_Arow; ++i)
        {
            for (int j = 0; j < b_Bcol; ++j)
            {
                C((i + coord[0] * b_Arow), (j + coord[1] * b_Bcol)) = subC(i, j);
            }
        }
        for (int i = 1; i < size; ++i)
        {
            int other_coord[2];
            MPI_Cart_coords(topo_comm, i, 2, other_coord);
            for (int j = 0; j < b_Arow; ++j)
            {
                MPI_Recv(&C((other_coord[0] * b_Arow + j), (other_coord[1] * b_Bcol)), b_Bcol, MPI_FLOAT, i, j, topo_comm, MPI_STATUS_IGNORE);
            }
        }
    }
    else
    {
        for (int j = 0; j < b_Arow; ++j)
        {
            MPI_Send(subC + j * b_Bcol, b_Bcol, MPI_FLOAT, 0, j, topo_comm);
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
    end = MPI_Wtime();
    t[3] = end - start;

    // cout << "rank: " << rank << ", sendA time:" << t[0] * 1e3 << ", sendB time:" << t[1] * 1e3 << ", calC time:" << t[2] * 1e3 << ", recvC time:" << t[3] * 1e3 <<  " ms" << endl
    MPI_Reduce(t, sumt, 4, MPI_DOUBLE, MPI_SUM, 0, topo_comm);

    if (rank == 0)
    {
        cout << sumt[2] * 1e3 / size << endl;
        for (int i = 0; i < M; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                if(abs(C(i, j) - K) > 1e-3){
                    cout << setprecision(20) << "Not close at (" << i << ", " << j << "), get " << C(i, j) << endl;
                    if (i != 0)
                        break;
                }
            }
        }
    }

    if (rank == 0)
    {
        free(A);
        free(B);
        free(C);
    }
    free(subA);
    free(subB);
    free(subC);
    free(subA_buf);
    free(subB_buf);
    MPI_Finalize();
    return 0;
}