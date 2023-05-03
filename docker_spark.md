# 使用Docker配置hadoop/spark环境
## Docker获取镜像
## 给Docker配置固定IP
参考链接:https://cloud.tencent.com/developer/article/1084166
1.使用bridge-utils配置linux环境下的网桥
2.使用pipework配置dockerIP

### bridge-utils配置网桥
下载bridge-utils
```
yum -y install bridge-utils # centos
sudo pacman -S  bridge-utils # manjaro
```
创建网络
```
brctl addbr br1     # 创建名叫 br1 的网桥
ip link set dev br1 up  # 启用 br1 网桥:ip link set [DEVICE] [UP/DOWN]
ip addr add 192.168.3.1/24 dev br1  # 分配网桥ip段: ip addr add [ADDRESS] [DEVICE] [IFNAME]
```

### 配置hadoop集群环境
教程1:https://cloud.tencent.com/developer/article/1084157?from=10680
教程2:https://github.com/Wanghui-Huang/CQU_bigdata/blob/master/Experiment/Ex1_SettingUpEnvironment/ex1.md

使用docker 配置教程:https://www.cnblogs.com/upupfeng/p/13616125.html

spark-submit --class umn.dcsg.examples.ShortestPathRunner ./examples/target/examples-1.0-SNAPSHOT-jar-with-dependencies.jar ./examples/data/spdata.csv -1 "2D" 1 100 1 1 1 