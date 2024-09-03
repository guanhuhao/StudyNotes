原理:通过给远程服务器.ssh文件添加本地设备rsa公钥,实现本地设备免密登录目标服务器  
### 步骤
1.生成本地公钥:对于linux系统ssh相关信息储存在**对应用户**的~/.ssh文件夹内,如果该目录存在id_rsa.pub则可以不用重新生成,否则可以使用下面方式生成新的ssh key.  
> ls ~/.ssh # 跳转到用户对应ssh文件夹   
> ssh-keygen -t rsa -C "your_email@example.com" # 生成对应ssh key,引号内容可以自己填写

若为Windows用户,可以使用git bash的命令行操作工具完成上面步骤  
  
然后一直回车即可,或者需要手动设置rsa文件名称/位置,或根据私钥生成公钥时可以根据选择自己配置对应的filepath/passphase

2.复制公钥文件id_rsa.pub内容追加到远程服务器**对应用户**的~/.ssh/authorized_keys中(如果不存在该文件可以自行新建),操作完毕即可实现本地设备免密登录目标远程服务器的**对应用户**    

3.完成上述步骤后,使用指定设备远程登录服务器,可以实现不使用密码验证,直接登录 ,比较方便,且由于绑定固定设备登录,安全性上也有一定提升    

### 参考链接:
怎么生成公钥:https://blog.csdn.net/winycg/article/details/103130700   
怎么免密登录:https://blog.csdn.net/qq_40156289/article/details/120342781  