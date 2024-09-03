# Manjaro入门安装 

## 导入AUR源
### 方案一（新）
terminal 输入
> $ sudo pacman-mirrors -i -c China -m rank
### 方案二（旧）
在<b>/etc/pacman.conf</b> 末尾添加两行
>\$ [archlinuxcn]
>\$ Server = https://mirrors.ustc.edu.cn/archlinuxcn/$arch

### 后续操作（更新源/扩充软件库）

**扩充软件库**
安装<b>archlinuxcn-keyring</b>导入GPG eky
>$ sudo pacman -S archlinuxcn-keyring

如果出现类似什么：无法在本地签署/密钥xxx生成于未来xxx秒后（可能是因为时空扭曲或系统时钟问题）使用下面操作(以root权限)：

>+ pacman -Syu haveged
>+ systemctl start haveged
>+ systemctl enable haveged
>+ 
>+ rm -fr /etc/pacman.d/gnupg
>+ pacman-key --init
>+ pacman-key --populate archlinux
>+ pacman-key --populate archlinuxcn

参考链接：https://www.archlinuxcn.org/gnupg-2-1-and-the-pacman-keyring/
**更新源**
>$ sudo pacman -Syyu

参考链接:https://mirrors.ustc.edu.cn/help/archlinuxcn.html

## 安装搜狗输入法
### 方案一（新）
依次打开:菜单->manjaro Hello -> application ->extend language support -> manjaro Asian Input support Fcitx -> update system（右上角），安装完毕后选择中文
然后打开terminal，输入：
> yay -S fcitx-sogoupinyin

完成安装即可
### 方案二（旧）
先安装fcitx输入法框架,再安装sogou拼音
>\$ sudo pacman -S fcitx
>\$ yaourt -S fcitx-sogoupinyin 

编辑<b>~.xprofile</b>(如没有则自己创建),添加以下内容(该步骤用于解决输入法无法切换的问题)
>export GTK_IM_MODULE = fcitx
>export QT_IM_MODULE = fcitx
>export XMODIFIERS="@im=fcitx"

并执行以下命令生效
>source ~/.bashrc

如果安装过程中遇到以下错误:
>==> 错误 : Cannot find the strip binary required for object file stripping

则执行以下指令
>sudo pacman -S base-devel

## 安装代理
下载clash客户端（https://github.com/Dreamacro/clash/releases ）选择clash-linux-vxxx.gz，解压并更名为clash，解压命令如下
> $ gzip XXX.gz -d 解压位置

在对应位置打开终端输入：
> $ ./clash -d .

如果显示端口已占用可以使用下面指令查看，然后使用kill删除对应进程：
> $ lsof -i:端口号

设置系统代理：
>系统设置->网络->设置->设置系统代理服务器配置
根据代理的端口设置对应HTTP代理以及SOCK代理即可

如果需要设置yaourt走代理则再控制台输入以下命令
>$ https_proxy='127.0.0.1:7890' http_proxy='127.0.0.1:7890' yaourt arm-linux-gnueabihf

如要设置开机自启动则再同目录下创建文件<b>autoClash.sh</b>并填入以下代码
>#!/bin/bash
>./clash -d . 1>./out.log


参考链接:
>https://64mb.org/2017/05/12/%E4%B8%BAyaourt%E8%AE%BE%E7%BD%AE%E4%BB%A3%E7%90%86/

## 安装proxychains
安装proxychains
>sudo pacmans -S proxychains
编辑/etc/proxychains.conf
注释掉,防止dns污染风险
>proxy_dns
设置代理出口(最后一项根据你自己的代理端口进行设置)
>socks5 127.0.0.1 7891
参考链接:
>https://guangchuangyu.github.io/cn/2018/09/proxychains/

## 安装坚果云
> $ pacman -S nutstore

如果安装后登录界面空白，则进行下面操作：
>+ 打开文件 /opt/nutstore/conf/nutstore.properties  
>+ 将最后一行的webui.enable=true  修改成 webui.enable=false 

如果上述问题解决后窗口大小无法调整则安装下面的依赖并重启：
>+ sudo pacman -S gvfs 
>+ sudo pacman -S libappindicator-gtk3
>+ sudo pacman -S python2-gobject

参考链接：https://blog.csdn.net/Nmdzps178/article/details/117375227

## 安装chrome(没用了QAQ)
>\$ sudo pacman -S google-chrome

## 安装QQ/微信/Tim
>\$ yay -S deepin-wine-qq
>\$ yay -S deepin-wine-wechat
>\$ yay -S deepin-wine-tim

PS:之前没安装wine的话，会先装wine-helper什么的环境，需要挺长时间的，下载之后在菜单里找对应安装文件运行即可

## 安装网易云
>\$ sudo pacman -S netease-cloud-music

如果不能输入中文则先下载qcef库然后将opt/netease/netease-cloud-music下的netease-cloud-music.bash改一下
>\#!/bin/sh
>HERE="\$(dirname "\$(readlink -f "\${0}")")"
>export LD_LIBRARY_PATH="\${HERE}"/libs
>export QT_PLUGIN_PATH="\${HERE}"/plugins 
>export QT_QPA_PLATFORM_PLUGIN_PATH="\${HERE}"/plugins/platforms
>export XDG_CURRENT_DESKTOP=DDE
>exec "\${HERE}"/netease-cloud-music \$@

参考链接：
https://blog.csdn.net/Kalidaxiong123/article/details/101680715
https://github.com/HexChristmas/archlinux
## 安装vscode （没用了QAQ）
>\$ sudo pacman -S visual-studio-code-bin

## 安装.dep文件
首先先安装debtap
>$ yay -S debtap

## Manjaro系统时间与windows系统时间同步
>\$ sudo timedatectl set-local-rtc true

参考链接：https://blog.csdn.net/weixin_36349646/article/details/102597290

## tmp空间不足
编辑/etc/fstab文件
将tmpfs那行改成
>tmpfs /tmp      tmpfs defaults,size=30G          0 0

## 防止系统万一崩了
>https://luzibuye.github.io/2017/11/25/>Linux%E4%B8%8B%E7%9A%84%E7%B3%BB%E7%BB%9F%E5%A4%87%E4%BB%BD%E4%B8%8E%E6%81%A2%E5%A4%8D/
>https://bbs.archlinuxcn.org/viewtopic.php?id=5533
>https://wiki.archlinux.org/index.php/Rsync_(%E7%AE%80%E4%BD%93%E4%B8%AD%E6%96%87)

## 修复windows引导
>grub-mkconfig -o /boot/grub/grub.cfg

参考链接：https://blog.csdn.net/weixin_40293491/article/details/108091530

## 多显示器/显示器切换黑屏
删除/重命名(mv) /etc/X11/mhwd.d/nvidia.conf
PS:可以试一下
