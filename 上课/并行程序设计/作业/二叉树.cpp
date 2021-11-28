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

    data[0] = myid;
    if(myid == 0 ){ //根节点
        MPI_Recv(data+1, 1, MPI_INT, myid*2, myid,
            MPI_COMM_WORLD, &status);
        MPI_Recv(data+2, 1, MPI_INT, myid*2+1, myid,
            MPI_COMM_WORLD, &status);
        data[0]+=data[1]+data[2];

        MPI_Send(data, 1, MPI_INT, myid/2, myid,
            MPI_COMM_WORLD); 
    }else if (myid >= numprocs/2){ //叶子结点
        MPI_Send(data, 1, MPI_INT, myid/2, myid,
            MPI_COMM_WORLD); 
        
        MPI_Recv(data, 1, MPI_INT, myid/2, myid,
            MPI_COMM_WORLD, &status);

    }else { //中间节点
        MPI_Recv(data+1, 1, MPI_INT, myid*2, myid,
            MPI_COMM_WORLD, &status);
        MPI_Recv(data+2, 1, MPI_INT, myid*2+1, myid,
            MPI_COMM_WORLD, &status);
        data[0]+=data[1]+data[2];

        MPI_Send(data, 1, MPI_INT, myid/2, myid,
            MPI_COMM_WORLD); 
        
        MPI_Recv(data, 1, MPI_INT, myid/2, myid,
            MPI_COMM_WORLD, &status);

        MPI_Send(data, 1, MPI_INT, myid*2, myid,
            MPI_COMM_WORLD);
        MPI_Send(data, 1, MPI_INT, myid*2+1, myid,
            MPI_COMM_WORLD);
    }
    MPI_Finalize();

    printf("thread %d sum is %d\n",myid,data[0]);
} /* end main */