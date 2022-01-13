// 本实验通信域大小为4,其中所有myid%4=0的构成通信域H
// root节点为id最大的,因此要求numprocs应该为4k+1
#include <stdio.h>
#include <string.h>
#include "mpi.h"
int data[10];
int main(int argc, char* argv[])
{
    int numprocs, myid, source;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);


    if(myid == numprocs-1){
        data[0]=100;
        printf("root node send msg to h0\n");
        MPI_Send(data, 1, MPI_INT, 0, 0,MPI_COMM_WORLD); 
    }else if(myid%4 == 0){
        if(myid==0){
            MPI_Recv(data, 1, MPI_INT, numprocs-1, myid,
                MPI_COMM_WORLD, &status);
            printf("h0 node received msg %d\n",data[0]);
            for(int i = myid+4; i <= numprocs-1 ; i+=4){
                printf("h0 node send msg to h%d\n",i/4);
                MPI_Send(data, 1, MPI_INT, i, i,MPI_COMM_WORLD);
            }
        }else{
            MPI_Recv(data, 1, MPI_INT, 0, myid,
                MPI_COMM_WORLD, &status);
            printf("h%d node received msg %d\n",myid/4,data[0]);
        }
        for(int i = 1; i <= 3; i++){
            printf("h%d node send msg to n%d%d\n",myid/4,myid/4,i);
            MPI_Send(data, 1, MPI_INT, myid+i, myid+i,
                MPI_COMM_WORLD);
        }
    }else {
        MPI_Recv(data, 1, MPI_INT, myid-myid%4, myid,
                MPI_COMM_WORLD, &status);
        printf("n%d%d node received msg %d\n",myid/4,myid%4,data[0]);
    }
    MPI_Finalize();
} /* end main */