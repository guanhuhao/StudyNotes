#include <bits/stdc++.h>
#include "mpi.h"
using namespace std;
const int n = 100;
int a[n+10][n+10],b[n+10],c[n+10][n+10],d[n+10];
int aa[n+10][n+10],bb[n+10],cc[n+10][n+10],dd[n+10];
int y[n*2+10],x[n*2+10];
int yy[n*2+10],xx[n*2+10];
double chuan(){         //串行程序计算
    clock_t begin = clock();
    for(int i =1;i<=n;i++){
        xx[i]=yy[i]+10;
        for(int j =1;j<=n;j++){
            bb[j]=aa[j][n];
            for(int k=1;k<=n;k++){
                aa[j+1][k]=bb[j]+cc[j][k];
            }
            yy[i+j]=aa[j+1][n];
        }
    }
    clock_t end = clock();
    // printf("串行用时:%5lf(ms)\n",1000.0*(end-begin)/CLOCKS_PER_SEC);
    return 1000.0*(end-begin)/CLOCKS_PER_SEC;
}
bool check(){           //检查是否与串行程序相同
    for(int i=1;i<=n;i++){
        for(int j =1;j<=n;j++)
            if(aa[i][j]!=a[i][j]||cc[i][j]!=c[i][j]) {
                cout<<"error!"<<endl;
                return false;
            }
        if(b[i]!=bb[i]||d[i]!=dd[i]||x[i]!=xx[i]||y[i]!=yy[i]) {
            cout<<"error"<<endl;
            return false;
        }
    }
    return true;
}
void randData(){        //生成随机数据
    for(int i=0;i<n+5;i++){
        for(int j =0;j<n+5;j++) {
            a[i][j]=aa[i][j]=rand()%100;
            c[i][j]=cc[i][j]=rand()%100;
        }
        b[i]=bb[i]=rand()%100;
        d[i]=dd[i]=rand()%100;
        x[i]=xx[i]=rand()%100;
        y[i]=yy[i]=rand()%100;
    }
}
int main(int argc, char* argv[])
{
    randData();      //生成随机数据

    double time_seq = chuan();

    clock_t begin = clock();
    for(int i =1;i<=n;i++){
        for(int j = 1;j<=n;j++){
            b[j]=a[j][n];
            // #pragma omp parallel for 
            for(int k =1;k<=n;k++){
                a[j+1][k]=b[j]+c[j][k];
            }
            y[i+j] = a[j+1][n];
        }
    }
    
    #pragma omp parallel for 
    for(int i=1;i<=n;i++){
        x[i]=y[i]+10;
    }
    clock_t end = clock();

    if(check()) printf("串行程序与并行程序结果一致!\n");
    double time_pra = 1000.0*(end-begin)/CLOCKS_PER_SEC;
    printf("并行用时:%5lf(ms)\n",time_pra);
    printf("串行用时:%5lf(ms)\n",time_seq);
    printf("加速比为:%lf\n",time_seq/time_pra);

} /* end main */