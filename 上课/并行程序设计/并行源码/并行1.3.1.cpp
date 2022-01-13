#include <bits/stdc++.h>
#include "mpi.h"
using namespace std;
const int n = 1000000;
int a[n+10],b[n+10],c[n+10],d[n+10];
int aa[n+10],bb[n+10],cc[n+10],dd[n+10];
double chuan(){
    clock_t begin = clock();
    for(int i =1;i<=n;i++){
        aa[i]=bb[i]+cc[i+1];
    }
    for(int i=1;i<=n;i++){
        cc[i]=aa[i]*dd[i];
    }
    clock_t end = clock();
    // printf("串行用时:%5lf(ms)\n",1000.0*(end-begin)/CLOCKS_PER_SEC);
    return 1000.0*(end-begin)/CLOCKS_PER_SEC;
}
bool check(){
    for(int i=1;i<=n;i++){
        if(aa[i]!=a[i]||cc[i]!=c[i]) {
            cout<<"error!"<<endl;
            return false;
        }
    }
    return true;
}
int main(int argc, char* argv[])
{
    
    for(int i=0;i<n+5;i++){
        a[i]=aa[i]=rand()%100;
        b[i]=bb[i]=rand()%100;
        c[i]=cc[i]=rand()%100;
        d[i]=dd[i]=rand()%100;

    }
    double time_seq = chuan();

    clock_t begin = clock();
    #pragma omp parallel for 
    for(int i =1;i<=n;i++){
        a[i]=b[i]+c[i+1];
    }
    #pragma omp parallel for 
    for(int i=1;i<=n;i++){
        c[i]=a[i]*d[i];
    }
    clock_t end = clock();
    if (check()) printf("串行程序与并行程序结果一致!\n");
    double time_pra = 1000.0*(end-begin)/CLOCKS_PER_SEC;
    printf("并行用时:%5lf(ms)\n",time_pra);
    printf("串行用时:%5lf(ms)\n",time_seq);
    printf("加速比为:%lf\n",time_seq/time_pra);

} /* end main */