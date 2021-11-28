#include <bits/stdc++.h>
#include "mpi.h"
using namespace std;
const int n = 999;
const int mod = 1e4;
int a[n+10],b[n+10],c[n+10],d[n+10];
int aa[n+10],bb[n+10],cc[n+10],dd[n+10];
void chuan(){
    clock_t begin = clock();
    for(int i=1;i<=n;i++){
        aa[i]=bb[i]+cc[i];
        dd[i]=(aa[i]+aa[n-i+1])/2;
    }
    clock_t end = clock();
    printf("串行用时:%5lf(ms)\n",1000.0*(end-begin)/CLOCKS_PER_SEC);
}
void check(){
    for(int i=1;i<=n;i++){
        if(aa[i]!=a[i]||cc[i]!=c[i]||bb[i]!=b[i]||dd[i]!=d[i]) cout<<i<<" "<<"error!"<<endl;
    }
}
int main(int argc, char* argv[])
{
    
    for(int i=0;i<n+5;i++){
        a[i]=aa[i]=rand()%100;
        b[i]=bb[i]=rand()%100;
        c[i]=cc[i]=rand()%100;
        d[i]=dd[i]=rand()%100;

    }
    chuan();

    clock_t begin = clock();
    #pragma omp parallel for 
    for(int i =1;i<=(n+1)/2;i++){
        a[i]=b[i]+c[i];
        // d[i]=(a[i]+a[n-i+1])/2;
    }
    #pragma omp parallel for 
    for(int i =1;i<=500;i++){
        d[i]=(a[i]+a[n-i+1])/2;
    }
    #pragma omp parallel for 
    for(int i=(n+1)/2;i<=n;i++){
        a[i]=b[i]+c[i];
        // d[i]=(a[i]+a[n-i+1])/2;
    }
    #pragma omp parallel for 
    for(int i=501;i<=n;i++){
        d[i]=(a[i]+a[n-i+1])/2;
    }
    clock_t end = clock();
    printf("并行用时:%5lf(ms)\n",1000.0*(end-begin)/CLOCKS_PER_SEC);

    check();
} /* end main */