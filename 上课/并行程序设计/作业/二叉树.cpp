#include <stdio.h>
#include <string.h>
#include <bits/stdc++.h>
#include "mpi.h"
#define GHH(...) printf(__VA_ARGS__)
// #define GHH(...) 
// using namespace std;

int main(int argc, char* argv[])
{
    clock_t begin = clock();
    int numprocs, myid, source;
    MPI_Status status;
    int data[10];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    data[0] = myid;
    GHH("thread %d begin!\n",myid);
    if(myid == 0);
    else if(myid == 1 ){                 //根节点
        MPI_Recv(data+1, 1, MPI_INT, myid*2, myid*2,  //阶段1,收集来自左右子树的和
            MPI_COMM_WORLD, &status);
        GHH("root %d get sum %d from left son %d\n",myid,data[1],myid*2);
       
        MPI_Recv(data+2, 1, MPI_INT, myid*2+1, myid*2+1,
            MPI_COMM_WORLD, &status);
        GHH("root %d get sum %d from right son %d\n",myid,data[2],myid*2+1);
        
        data[0]+=data[1]+data[2];

        GHH("root %d send sum %d to left son %d\n",myid,data[0],myid*2);
        MPI_Send(data, 1, MPI_INT, myid*2, myid,    //阶段2,向下广播求和的值
            MPI_COMM_WORLD); 

        GHH("root %d send sum %d to right son %d\n",myid,data[0],myid*2+1);
        MPI_Send(data, 1, MPI_INT, myid*2+1, myid,    //阶段2,向下广播求和的值
            MPI_COMM_WORLD); 
    }else if (myid >= (numprocs+1)/2){ //叶子结点
        MPI_Send(data, 1, MPI_INT, myid/2, myid,    //阶段1,向上传递自身节点值
            MPI_COMM_WORLD); 
        GHH("leaf %d send itself to parent %d\n",myid,myid/2);
        
        MPI_Recv(data, 1, MPI_INT, myid/2, myid/2,    //阶段2,收到来自根节点的全局和
            MPI_COMM_WORLD, &status);
        GHH("leaf %d get sum %d from parent %d\n",myid,data[0],myid/2);

    }else {                         //中间节点
        MPI_Recv(data+1, 1, MPI_INT, myid*2, myid*2,  //阶段1,收集来自左右子树的和
            MPI_COMM_WORLD, &status);        
        GHH("midnode %d get sum %d from left son %d\n",myid,data[1],myid*2);

        MPI_Recv(data+2, 1, MPI_INT, myid*2+1, myid*2+1,
            MPI_COMM_WORLD, &status);
        GHH("midnode %d get sum %d from right son %d\n",myid,data[2],myid*2+1);

        data[0]+=data[1]+data[2];

        MPI_Send(data, 1, MPI_INT, myid/2, myid,    //向其父亲节点发送该节点左右子树以及自己的和
            MPI_COMM_WORLD); 
        GHH("midnode %d send itself to parent %d\n",myid,myid/2);

        MPI_Recv(data, 1, MPI_INT, myid/2, myid/2,    //阶段2,向下广播自根节点的全局和
            MPI_COMM_WORLD, &status);
        GHH("midnode %d get sum %d from parent %d\n",myid,data[0],myid/2);

        MPI_Send(data, 1, MPI_INT, myid*2, myid,
            MPI_COMM_WORLD);
        GHH("midnode %d send sum %d to left son %d\n",myid,data[0],myid*2);

        MPI_Send(data, 1, MPI_INT, myid*2+1, myid,
            MPI_COMM_WORLD);
        GHH("midnode %d send sum %d to right son %d\n",myid,data[0],myid*2+1);

    }
    MPI_Finalize();

    clock_t end = clock();
    printf("thread %d sum is %d. Runtime :%lf(ms)\n",myid,data[0],1000.0*(end-begin)/CLOCKS_PER_SEC);
} /* end main */

// mpic++ -o fun test.cpp -fopenmp > compile.log
// mpirun -n 8 -genv OMP_NUM_THREADS 1 ./fun > out.log