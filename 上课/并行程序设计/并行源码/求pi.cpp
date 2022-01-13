#include <bits/stdc++.h>
#include <random>
#include <time.h>
#include <mpi.h>
using namespace std;
const int maxn = 1e6;
int A[100];
int main(int argc, char **argv)
{
    int rank;
    int size;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size); // assume size = x ^ 2, N % x == 0
    
    clock_t begin = clock();
    default_random_engine random(time(NULL));
    uniform_real_distribution<double> uniform(0.0,1.0);
    for(int i=0;i<maxn;i++){
        double x = uniform(random);
        double y = uniform(random);
        if(x*x+y*y<=1) A[rank]++;
    }
    if(rank==0){
        for(int i=1;i<size;i++) MPI_Recv(A+i,1,MPI_INT,i,0,MPI_COMM_WORLD,&status);
        int sum = 0;
        for(int i=0;i<size;i++)  sum += A[i];

        printf("tot:%d hit:%d pi:%lf 相对误差:%lf %%\n",maxn*size,sum,4.0*sum/maxn/size,abs(4.0*sum/maxn/size-3.1415926535)/3.1415926535*100);
        
    }else {
        MPI_Send(A+rank,1,MPI_INT,0,0,MPI_COMM_WORLD);
    }

    MPI_Finalize();
    clock_t end = clock();
    if (rank == 0){
        printf("Runtime:%lf(ms)\n",1000.0*(end-begin)/CLOCKS_PER_SEC);
    }

    return 0;
}