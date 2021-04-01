<script type="text/javascript" src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML"></script>
<script type="text/x-mathjax-config">
    MathJax.Hub.Config({ tex2jax: {inlineMath: [['$', '$']]}, messageStyle: "none" });
</script> 
# CUDA-MEME 
## 技术介绍
>CUDA-MEME（version 3.0）是基于MEME（version 4.4.0）的motif发现工具，使用混合CUDA，OpenMP，MPI混合编程实现
目前CUDA-MEME之支持OOPS'以及ZOOPS模式，在Tesla C1060 GPU Computing card，GeForce GTX 280 graphics card，以及GPU集群上经过测试。同时该软件也被加入到NVIDIA Tesla Bio Workbench (http://www.nvidia.com/object/meme_on_tesla.html 查了没找到，网页跳转到其他地方了).
## Introduction
>该软件允许使用单/多GPU加速motif查，对于多GPU采用基于MPI的架构进行设计。
分别采用两个Makefile文件对程序进行编译：
1.Makefile.gpu编译并生成单GPu的二进制文件<b>（不依赖MPI库）</b>
2.Makefile.mgpu编译并生成GPU集群的二进制文件<b>（需要MPI库的支持，据软件作者说在 MPICH/MPICH2 MPI library的支持下工作良好）</b>

## 安装步骤
>1. 安装 CUDA 2.0或更好版本的SDK以及Toolkits$(\checkmark)$
>2. 安装 MPICH/MPICH2,安装这个巨慢，安了一下午了都还没安好，同时需要注意需要python2的支持，还需要手动导入一次公钥$（\times）$
A328C3A2C3C45C06


>3. 安装convert$(\checkmark)$
>4. 下载cuda-meme-vxxx.tar.gz，并解压$(\checkmark)$
>5. 根据实际支持CUDA的图形计算硬件调整Makefile的参数（如果GPU是Fermi将设置改成-arch sm_20，如果容量为1.3则改成-arch sm_13，1.2以及1.1同理，<b>此处设置对CUDA程序的正确性有很大的影响</b>）
>6. 在命令行使用以下操作运行程序：
>>1. "$ make -f Makefile.gpu" 该操作将生成release 版本的 “cuda-meme程序”
>>2. “$ make -f Makefile.gpu clean”删除所有生成的二进制文件
>>3. “$ make -f Makefile.mgpu”生成多GPu版本的执行程序
>>4. "$ make -f Makefile.mgpu clean" 同2

>7. 如果MEME_ETC_DIR被定义，则程序将会从指定目录寻找所需资源，否则将会使用当前工作目录的etc目录
