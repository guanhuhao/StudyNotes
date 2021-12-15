#include <stdio.h>
#include <string.h>
#include <bits/stdc++.h>
#include "mpi.h"
int main(int argc, char* argv[])
{
    clock_t begin = clock();
    int numprocs, myid, source;
    MPI_Status status;
    int data[10];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    data[0]=myid+1;
    for(int i = 1; i < numprocs ; i<<=1){
        MPI_Send(data,1,MPI_INT,myid^i,myid^i,MPI_COMM_WORLD);
        MPI_Recv(data+1,1,MPI_INT,myid^i,myid,MPI_COMM_WORLD,&status);
        data[0] += data[1];
    }
    MPI_Finalize();
    clock_t end = clock();
    printf("thread %d sum is %d. Runrime:%lf(ms)\n",myid,data[0],1000.0*(end-begin)/CLOCKS_PER_SEC);
} /* end main */

// mpic++ -o fun test.cpp -fopenmp > compile.log
// mpirun -n 8 -genv OMP_NUM_THREADS 1 ./fun > out.log