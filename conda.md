## 配置镜像源
``` 
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/main/ 
conda config --set show_channel_urls yes
```

## 创建新环境
```
conda create -n 环境名
```

## 查看当前conda环境
```
conda info --envs
```

## 激活环境
```
conda activate 环境名
```

## 删除环境
```
conda remove -n 环境名 --all
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