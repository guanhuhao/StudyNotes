#include <stdio.h>
#include <string.h>
#include "mpi.h"
int main(int argc, char* argv[])
{
    int numprocs, myid, source;
    MPI_Status status;
    int data[10];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    for(int i = 1; i < numprocs ; i<<=1){
        MPI_Send(data,1,MPI_INT,myid^i,myid^i,MPI_COMM_WORLD);
        MPI_Recv(data+1,1,MPI_INT,myid^i,myid,MPI_COMM_WORLD,&status);
        data[0] += data[1];
    }
    MPI_Finalize();
    printf("thread %d sum is %d\n",myid,data[0]);
} /* end main */