## 配置镜像源
``` 
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/  
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/main/   
conda config --set show_channel_urls yes  
```

## 基础指令
```
conda create -n 环境名 python=x.x  # 创建环境,可选参数python=x.x指定python版本  
conda info --envs       # 查看当前conda环境
conda activate 环境名   # 激活环境
conda remove -n 环境名 --all  # 删除环境
conda deactivate        # 退出环境
conda deactivate        # conda4之前的版本是：source deactivate
```

## jupyter调用conda环境
1. 在conda(base)中安装nb_conda_kernels  
```
conda install nb_conda_kernels
```
2. 在conda创建的环境中安装ipykernel  
```
conda install ipykernel
```
或者在conda创建的环境中手动添加配置
```
python -m ipykernel install --user --name=xxx
```
PS:可以使用“jupyter kernelspec list” 查看当前可使用内核，使用“jupyter kernelspec remove xxx”移除对应内核