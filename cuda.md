# CUDA
## CUDA程序执行流程
注:host代指CPU以及内存,device代指GPU
>1.分配host内存，并进行数据初始化；
2.分配device内存，并从host将数据拷贝到device上；
3.调用CUDA的核函数在device上完成指定的运算；
4.将device上的运算结果拷贝到host上；
5.释放device和host上分配的内存。
## kernel
>kernel是CUDA中一个重要的概念，kernel是在device上线程中并行执行的函数，**核函数用__global__符号声明**，在调用时需要用<<<grid, block>>>来指定kernel要执行的线程数量，在CUDA中，每一个线程都要执行核函数，并且每个线程会分配一个唯一的线程号thread ID，这个ID值可以通过核函数的内置变量threadIdx来获得。
## 限定词作用
>\_\_global__：在device上执行，从host中调用（一些特定的GPU也可以从device上调用），返回类型必须是void，不支持可变参数参数，不能成为类成员函数。注意用__global__定义的kernel是**异步**的，这意味着host不会等待kernel执行完就执行下一步。
\_\_device__：在device上执行，单仅可以从device中调用，不可以和__global__同时用。
\_\_host__：在host上执行，仅可以从host上调用，**一般省略不写**，不可以和__global__同时用，但可和__device__，此时函数会在device和host都编译

## 分析工具
nvprof

## 踩过的坑
安装好cuda之后进入/cuda目录先跑一下sample
>make -C sample
然后跳转目录到/cuda/sample/bin/x86_64/linux/release
>./deviceQuery
看最后一行是fail（失败）还是pass（成功）
![](/pic/cuda-nvidia对照表.png)
nvcc架构显卡型号对照表https://arnon.dk/matching-sm-architectures-arch-and-gencode-for-various-nvidia-cards/
## 参考链接
https://zhuanlan.zhihu.com/p/34587739

