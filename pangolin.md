# Pangolin
## INPUT
>支持gr,txt,adj,mtx图格式输入,对于无标签图于Galois一样采用gr图格式.需要保证图对称,且不包含自环以及重边,不然需要先用tools/graph-convert的convert工具将其转换,对于有标签的图于Arabesque和RStream一样采用adj格式. adj格式讲图按照下面的方式输入:
>> \# \<num vertices> <num edges>
\<vertex id> \<vertex label> \[\<neighbour id1> \<neighbour id2> ... \<neighbour id n>]
\<vertex id> \<vertex label> \[\<neighbour id1> \<neighbour id2> ... \<neighbour id n>] 
>     
>目前<b>不支持边携带标签信息</b>,顶点id从0到定点个数-1,并在$GALOIS_HOME/lonestarmine/test_data准备了测试用图

## BUILD
### cpu部分
>1.下载Galois源码(https://github.com/IntelligentSoftwareSystems/Galois)
>>$ git clone https://github.com/IntelligentSoftwareSystems/Galois.git
>>
>2.按照Gloria的readme解决依赖(gcc,CMake,Boost,libllvm,libfmt)
>>\$ sudo pacman -S gcc
\$ sudo pacman -S boost
\$ sudo pacman -S llvm
\$ sudo pacman -S fmt
>    
>3.跳转到/Galois 下新建目录 build并跳转到目录下
>4.使用下列指令编译文件
>>\$ cmake -S $sourse_dir -B $build_dir -DCMAKE_BUILD_TYPE=Release
>>
>5.跳转到/lonestar/mining/cpu/motif-conting下在terminal中输入
>> $ make -j
>>
>6.跳转到/build/inputs目录下输入
>>$ make input
>>
>上述操作之后生成所需的input文件
>7.使用下面操作以使用相关功能
>>\$ ./triangle-counting-mining-cpu -symmetricGraph -simpleGraph \$BUILD_DIR/inputs/Mining/citeseer.csgr -t 28
\$ ./k-clique-listing-cpu -symmetricGraph -simpleGraph \$BUILD_DIR/inputs/Mining/citeseer.csg r -k=3 -t 28
\$ ./motif-counting-cpu -symmetricGraph -simpleGraph $BUILD_DIR/inputs/Mining/citeseer.csgr -k=3 -t 56
\$ ./frequent-subgraph-mining-cpu -symmetricGraph -simpleGraph \$BUILD_DIR/inputs/Mining/citeseer.sadj -ft adj -k=2 -ms=300 -t 28
### gpu部分
>前四步同上
>5.安装依赖moderngpu，以及第三方子库
>> $ yaourt -S moderngpu
>> $ git submodule init
>> $ git submodule update
>>
>6.使用下列指令编译文件
>>\$ cmake ./ -DGALOIS_CUDA_CAPABILITY="6.1" #注意这里的6.1需要根据显卡型号自己去查
>>
>7.跳转到/lonestar/mining/gpu/motif-conting下在terminal中输入
>> $ make -j
>>
>8.使用以下命令运行程序
>>$ ./motif-counting-gpu -symmetricGraph -simpleGraph -k=5 citeseer.csgr 
>>
## 依赖关系
/Galois/lonestar/mining/gpu/motif-counting/motif_gpu.cpp $(\checkmark)$
>/Galois/libgalois/include/galois/Galois.h $(\checkmark)$
/Galois/lonestar/mining/gpu/motif-counting/motif.h$(\checkmark)$
/Galois/lonestar/mining/libminingbench/include/MiningBench/Start.h$(\checkmark)$
/llvm/Support/CommandLine.h$(\checkmark)$

/Galois/libgalois/include/galois/Galois.h$(\checkmark)$
>/Galois/libgalois/include/galois/config.h$(\checkmark)$
/Galois/libgalois/include/galois/Loops.h
/Galois/libgalois/include/galois/SharedMemSys.h
/Galois/libgalois/include/galois/runtime/Mem.h

/Galois/lonestar/mining/gpu/motif-counting/motif.h $(\checkmark)$
>/Galois/libpangolin/gpu/pangolin/types.cuh$(\checkmark)$


/Galois/lonestar/mining/libminingbench/include/MiningBench/Start.h$(\checkmark)$
>llvm/Support/CommandLine.h$(\checkmark)$

/Galois/libpangolin/gpu/pangolin/types.cuh$(\checkmark)$
>null

Galois/lonestar/mining/gpu/motif.cu
>motif.h

## 编译参数详情
### motif-counting-gpu
文件目录：build/lonestar/mining/gpu/motif-counting/CMakeFiles/motif-counting-gpu.dir/link.txt
编译参数：
>/usr/bin/c++ -O3 -DNDEBUG -march=native CMakeFiles/motif-counting-gpu.dir/motif_gpu.cpp.o CMakeFiles/motif-counting-gpu.dir/motif.cu.o -o motif-counting-gpu   -L/opt/cuda-9.0/lib64/stubs  -L/opt/cuda-9.0/lib64  -L/usr/lib/gcc/x86_64-pc-linux-gnu/6.5.0  ../../libminingbench/libminingbench_gpu.a ../../../../libgpu/libgalois_gpu.a ../../../../libgalois/libgalois_shmem.a /usr/lib/libnuma.so /usr/lib/libLLVMSupport.a -lz -lrt -ldl -ltinfo -lpthread -lm /usr/lib/libLLVMDemangle.a -lcudadevrt -lcudart_static -lrt -lpthread -ldl 

解释
>/usr/bin/c++ : 编译器路径
-O3 : 开O3优化
-DNDEBUG : 关掉所有的assert宏(相关链接:https://stackoverrun.com/cn/q/6647397)
-march=native : 生成目标文件时针对编译的机器进行优化
.o : 编译所需用的.cpp.o文件
>>CMakeFiles/motif-counting-gpu.dir/motif_gpu.cpp.o # 可能需要改
CMakeFiles/motif-counting-gpu.dir/motif.cu.o    #可能需要
>>
>-o : 制定生成文件名,后面跟的第一个参数即为文件名
motif-counting-gpu : 生成文件名
-L : 链接库文件搜索路径
>>/opt/cuda-9.0/lib64/stubs # 不用改
/opt/cuda-9.0/lib64 # 不用改
/usr/lib/gcc/x86_64-pc-linux-gnu/6.5.0 # 不用改
>>
>.a : 路径所需的.a文件
>>/build/lonestar/mining/libminingbench/libminingbench_gpu.a # 依赖库
/build/libgpu/libgalois_gpu.a # 依赖库
/build/libgalois/libgalois_shmem.a #依赖库
/usr/lib/libLLVMSupport.a # 不用改
/usr/lib/libLLVMDemangle.a # 不用改
>>
>.so : 所需的.so文件
>> /usr/lib/libnuma.so #不用改
>>
>-l : 所需的指定依赖库
>>-lz -lrt -ldl -ltinfo -lpthread -lm -lcudadevrt -lcudart_static -lrt -lpthread -ldl 
### motif.cu.o
文件目录：/home/guan/桌面/test/Galois/lonestar/mining/gpu/motif-counting/Makefile:241
编译参数：
>cd /home/guan/桌面/test/Galois && $(MAKE) -s -f lonestar/mining/gpu/motif-counting/CMakeFiles/motif-counting-gpu.dir/build.make lonestar/mining/gpu/motif-counting/CMakeFiles/motif-counting-gpu.dir/motif.cu.o
## 可能也遇到问题
>驱动以及内核版本不能过高（？）,需要有nvidia_nvm该组件的支持


