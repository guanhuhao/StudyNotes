// 本实验通信域大小为4,其中所有myid%4=0的构成通信域H
// root节点为id最大的,因此要求numprocs应该为4k+1
#include <stdio.h>
#include <string.h>
#include <bits/stdc++.h>
#include "mpi.h"
using namespace std;
int data[1050];
int recv[1050];
void my_alltoall(const void *sendbuf, const int sendcount, MPI_Datatype sendtype, 
    void *recvbuf,const int recvcount, MPI_Datatype recvtype, MPI_Comm comm,int numprocs,int myid){
        int offset = 0;
        MPI_Status status;
        // printf("numprocs: %d\n",numprocs);
        for(int i=0;i<numprocs;i++) {
            if(i==myid) continue;
            MPI_Send((int*)(sendbuf)+i*sendcount, sendcount, sendtype, i, 1, comm);
            // printf("thread %d send msg to thread %d\n",myid,i);
        }
        for(int i=0;i<numprocs;i++) {
            if(i==myid) continue;
            MPI_Recv((int*)(recvbuf)+i*recvcount, recvcount, recvtype, i, 1, comm, &status);
        }

        // printf("thread %d recived data :\n",myid);
        // for(int i=0;i<numprocs*recvcount;i++){
        //     printf("%d ",*((int*)(recvbuf)+i*recvcount));
        // }
        // printf("\n");
}
void my_allgather(const void *sendbuf, const int sendcount, MPI_Datatype sendtype, 
    void *recvbuf,const int recvcount, MPI_Datatype recvtype, MPI_Comm comm,int numprocs,int myid){
        int offset = 0;
        MPI_Status status;
        for(int i=0;i<numprocs;i++) {
            if(i==myid) continue;
            MPI_Send((int*)sendbuf, sendcount, sendtype, i, 1, comm);
        }
        for(int i=0;i<numprocs;i++) {
            if(i==myid) continue;
            MPI_Recv((int*)(recvbuf)+i*recvcount, recvcount, recvtype, i, 1, comm, &status);
        }

        // printf("thread %d recived data :\n",myid);
        // for(int i=0;i<numprocs*recvcount;i++){
        //     printf("%d ",*((int*)(recvbuf)+i*recvcount));
        // }
        // printf("\n");
}
int main(int argc, char* argv[])
{
    int numprocs, myid, source;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    for(int i=0;i<10;i++) data[i]=myid*10+i;

    clock_t begin = clock();
    MPI_Alltoall(data,1,MPI_INT,recv,1,MPI_INT,MPI_COMM_WORLD);
    clock_t end = clock();
    if(myid == 0) printf("MPI_Alltoall 用时%.3lf(ms)\n",1000.0*(end-begin)/CLOCKS_PER_SEC);

    begin = clock();
    my_alltoall(data,1,MPI_INT,recv,1,MPI_INT,MPI_COMM_WORLD,numprocs,myid);
    end = clock();
    if(myid == 0) printf("my_alltoall 用时%.3lf(ms)\n",1000.0*(end-begin)/CLOCKS_PER_SEC);

    begin = clock();
    MPI_Allgather(data,1,MPI_INT,recv,1,MPI_INT,MPI_COMM_WORLD);
    end = clock();
    if(myid == 0) printf("MPI_AllGather 用时%.3lf(ms)\n",1000.0*(end-begin)/CLOCKS_PER_SEC);

    begin = clock();
    my_allgather(data,1,MPI_INT,recv,1,MPI_INT,MPI_COMM_WORLD,numprocs,myid);
    end = clock();
    if(myid == 0) printf("my_allgather 用时%.3lf(ms)\n",1000.0*(end-begin)/CLOCKS_PER_SEC);

    MPI_Finalize();
} /* end main */