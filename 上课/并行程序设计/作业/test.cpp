#include <bits/stdc++.h>
#include "mpi.h"
using namespace std;
const int n = 100;
const int mod = 1e4;
int a[5*n+10][5*n+10],c[5*n+10][5*n+10],d[5*n+10][5*n+10];
int aa[n*5+10][n*5+10],cc[5*n+10][5*n+10],dd[5*n+10][5*n+10];
void chuan(){
    clock_t begin = clock();
    for(int i=1;i<=n;i++){
        for(int j =1;j<=n;j++){
            aa[3*i+2*j][2*j]=cc[i][j]*2;
            if(i-j+6>0) dd[i][j]=aa[i-j+6][i+j];
        }
    }
    clock_t end = clock();
    printf("串行用时:%5lf(ms)\n",1000.0*(end-begin)/CLOCKS_PER_SEC);
}
void check(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(a[i][j]!=aa[i][j]||c[i][j]!=cc[i][j]||d[i][j]!=dd[i][j]) cout<<i<<" error"<<endl;
        }
    }
}
int main(int argc, char* argv[])
{
    
    for(int i=0;i<n+5;i++){
        for(int j=0;j<n+5;j++){
            a[i][j]=aa[i][j]=rand()%100;
            c[i][j]=cc[i][j]=rand()%100;
            d[i][j]=dd[i][j]=rand()%100;
        }

    }
    chuan();

    clock_t begin = clock();
    #pragma omp parallel for 
    for(int i =1;i<=n;i++){
        #pragma omp parallel for 
        for(int j=1;j<=n;j++){
            a[3*i+2*j][2*j]=c[i][j]*2;
        }
    }
    #pragma omp parallel for 
    for(int i =1;i<=n;i++){
        #pragma omp parallel for 
        for(int j=1;j<=n;j++){
            if(i-j+6>0)
                d[i][j]=a[i-j+6][i+j];
        }
    }
    clock_t end = clock();
    printf("并行用时:%5lf(ms)\n",1000.0*(end-begin)/CLOCKS_PER_SEC);

    check();
} /* end main */