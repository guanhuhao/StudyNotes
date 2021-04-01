# Manjaro入门安装 

## 导入AUR源
在<b>/etc/pacman.conf</b> 末尾添加两行
>\$ [archlinuxcn]
\$ Server = https://mirrors.ustc.edu.cn/archlinuxcn/$arch

安装<b>archlinuxcn-keyring</b>导入GPG eky
>$ sudo pacman -S archlinuxcn-keyring

顺带更新以下国内源
> $ sudo pacman-mirrors -i -c China -m rank

更新源
>$ sudo pacman -Syyu

参考链接:https://mirrors.ustc.edu.cn/help/archlinuxcn.html

## 安装搜狗输入法
先安装fcitx输入法框架,再安装sogou拼音
>\$ sudo pacman -S fcitx
\$ yaourt -S fcitx-sogoupinyin 

编辑<b>~.xprofile</b>(如没有则自己创建),添加以下内容(该步骤用于解决输入法无法切换的问题)
>export GTK_IM_MODULE = fcitx
export QT_IM_MODULE = fcitx
export XMODIFIERS=@im = fcitx

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

设置系统代理：
>系统设置->网络->设置->设置系统代理服务器配置
根据代理的端口设置对应HTTP代理以及SOCK代理即可

如果需要设置yaourt走代理则再控制台输入以下命令
>$ https_proxy='127.0.0.1:7890' http_proxy='127.0.0.1:7890' yaourt arm-linux-gnueabihf

如要设置开机自启动则再同目录下创建文件<b>autoClash.sh</b>并填入以下代码
>#!/bin/bash
./clash -d . 1>./out.log


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

## 安装chrome
>\$ sudo pacman -S google-chrome

## 安装QQ/微信/Tim
>\$ yaourt -S deepin-wine-qq
\$ yaourt -S deepin-wine-wechat
\$ yaourt -S deepin-wine-tim

## 安装网易云
>\$ sudo pacman -S netease-cloud-music

如果不能输入中文则先下载qcef库然后将opt/netease/netease-cloud-music下的netease-cloud-music.bash改一下
>\#!/bin/sh
HERE="\$(dirname "\$(readlink -f "\${0}")")"
export LD_LIBRARY_PATH="\${HERE}"/libs
export QT_PLUGIN_PATH="\${HERE}"/plugins 
export QT_QPA_PLATFORM_PLUGIN_PATH="\${HERE}"/plugins/platforms
export XDG_CURRENT_DESKTOP=DDE
exec "\${HERE}"/netease-cloud-music \$@

参考链接：
https://blog.csdn.net/Kalidaxiong123/article/details/101680715
https://github.com/HexChristmas/archlinux
## 安装vscode 
>\$ sudo pacman -S visual-studio-code-bin

## Manjaro系统时间与windows系统时间同步
>\$ sudo timedatectl set-local-rtc true

参考链接：https://blog.csdn.net/weixin_36349646/article/details/102597290

## tmp空间不足
编辑/etc/fstab文件
将tmpfs那行改成
>tmpfs /tmp      tmpfs defaults,size=30G          0 0

## 防止系统万一崩了
>https://luzibuye.github.io/2017/11/25/Linux%E4%B8%8B%E7%9A%84%E7%B3%BB%E7%BB%9F%E5%A4%87%E4%BB%BD%E4%B8%8E%E6%81%A2%E5%A4%8D/
https://bbs.archlinuxcn.org/viewtopic.php?id=5533
https://wiki.archlinux.org/index.php/Rsync_(%E7%AE%80%E4%BD%93%E4%B8%AD%E6%96%87)