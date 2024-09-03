## 常用指令
> 1.sudo docker ps # 列表显示容器  
> 2.sudo docker images # 列表显示镜像  
> 3.sudo docker run -it --name $name$ xxx:yyy /bin/bash # 创建xxx镜像:yyytag的实例,命名为$name$
> 4.sudo docker container exec -it \[containerID]  /bin/bash #进入对应ID的容器  
> 5.sudo systemctl start docker # 启动docker服务  
> 6.docker start name # 启动name的容器  
> 7.docker rm \[containerID] # 删除容器  
> 8.docker stop name/ID$ # 关闭指定名字/ID的容器  
> 9.docker pull name:tag # 获取开源镜像  

docker run 指令备选参数  
```
    --name=$NAME # 指定docker实例名字
    --privileged=true #  用来开启特权模式,否则无法在docker里使用systemctl等指令
    --cap-add=SYS_NICE # SYS_NICE来避免mbind error
    --net $DEV$ # 指定虚拟网桥
    --ip $ADDRESS$ # 指定IP
    --restart=always # 自动启动docker
    -p $host_port$:$tar_port$ # 端口映射
    -v $/localpath$:$/dockerpath$ # $/dockerpath$挂载到$/localpath$下
    -h $Hostname$ # 指定主机名称
    #在/bin/bash 命令后添加可执行文件,则容器启动后都会运行该脚本
```

## 给docker换源
使用下面编辑/etc/docker/daemon.json,覆盖为下面内容  
```
"registry-mirrors": [
    "http://hub-mirror.c.163.com",
    "https://docker.mirrors.ustc.edu.cn",
    "https://registry.docker-cn.com"
]

```
重启docker服务  
> sudo systemctl daemon-reload  
> sudo systemctl restart docker  

## 创建新docker后可能需要操作
### 换源
执行下面命令,对sources文件进行修改,如果源换挂了参考下面链接恢复  
https://blog.csdn.net/lizongti/article/details/108823299  
``` 
mv -f /etc/apt/sources.list /etc/apt/sources.list.bak
cat > /etc/apt/sources.list<< EOF
deb http://mirrors.163.com/ubuntu/ bionic main restricted universe multiverse
deb http://mirrors.163.com/ubuntu/ bionic-security main restricted universe multiverse
deb http://mirrors.163.com/ubuntu/ bionic-updates main restricted universe multiverse
deb http://mirrors.163.com/ubuntu/ bionic-proposed main restricted universe multiverse
deb http://mirrors.163.com/ubuntu/ bionic-backports main restricted universe multiverse
deb-src http://mirrors.163.com/ubuntu/ bionic main restricted universe multiverse
deb-src http://mirrors.163.com/ubuntu/ bionic-security main restricted universe multiverse
deb-src http://mirrors.163.com/ubuntu/ bionic-updates main restricted universe multiverse
deb-src http://mirrors.163.com/ubuntu/ bionic-proposed main restricted universe multiverse
deb-src http://mirrors.163.com/ubuntu/ bionic-backports main restricted universe multiverse
EOF

```
然后更新update一下  
> sudo apt-get update  

升级一下  
> apt-get upgrade  

### 安装常用软件
> sudo apt-get install unzip wget make g++ vim   

PS:
libssl-dev:用来给openssl用的(?),不然有的时候找不到openssl  


boost依赖  
> apt-get install libicu-dev   

#### 安装指定版本cmake:
参考链接:https://askubuntu.com/questions/355565/how-do-i-install-the-latest-version-of-cmake-from-the-command-line  
推荐方案B

#### 安装boost库
参考链接:https://blog.csdn.net/qq_41854911/article/details/119454212  


## 启动docker若发生问题
若使用docker相关指令显示  
> Cannot connect to the Docker daemon at unix:///var/run/docker.sock. Is the docker daemon running?  

则可以使用  
> sudo systemctl start docker  

来启动docker-daemon进程,若启动daemon显示  
> Failed to start docker.service: Unit docker.service not found.   

则可能是因为/usr/lib/systemd/system/docker.service,文件丢失或错误,可以通过重载daemon-reload,来重新生成相关文件   
> cd /usr/lib/systemd/system/ && touch docker.socket
> systemctl daemon-reload  
> systemctl start docker.service  

## 启动并进入对应容器
启动  
>docker start name # 启动name的容器  

进入
> sudo docker container exec -it \[containerID]  /bin/bash #进入对应ID的容器  

## 制作镜像
制作image  
> docker commit -m "xx" -a "test" container-id test/image:tag  
>> -a：提交的镜像作者。  
>> container-id：步骤2中的容器id。可以使用docker ps -a查询得到容器id。  
>> -m：提交时的说明文字。  
>> test/image:tag：仓库名/镜像名:TAG名。  

打包为tar文件用于传输  
> docker save -o mysql.tar mysql:v1

新设备导入image  
> docker load < xxx.tar  


参考链接:https://www.jianshu.com/p/0692043b6d7f
