## 新终端初始化操作
去用户根目录下面找.ssh文件中有没有id_rsa/id_rsa.pub文件，没有的话使用下面方式生成(注引号内填你自己的邮箱)  
```
$ ssh-keygen -t rsa -C "youremail@example.com"
```
然后将生成的id_rsa.pub里的所有内容复制，并打开git的 账号在Setting->SSH and GPG keys->New SSH key中将复制的内容粘贴至Key中，然后Title随便取个名字好区分就行  
```
$ git config --global user.name "Your Name"  
$ git config --global user.email "email@example.com"
```
上述操作实现绑定提交的 账号以及名称  

参考链接：https://www.liaoxuefeng.com/wiki/896043488029600/896954117292416  

## 建立新本地仓库
```
$ git clone git@github.com:xxx/xxx.git
$ cd xxx
$ git init
$ git add .*
$ git commit -m "something to do"
$ git push 
```

## 忽略文件、文件夹
在.git文件夹中创建.gitignore文件，并在编辑忽略规则,允许通配符*  
> target //忽略target 目录  
> target.json //忽略 target.json文件  
> log/* //忽略log下所有文件  
> *.css //忽略所有 .css文件  

## 常用命令
1. 清除缓存  
> git rm -r --cached .  

2. 放弃本地修改，强制更新远程文件  
> git fetch --all1  

3. 保存当前工作目录代码,回退到可以pull的代码  
> git stash  

当之后pull之后想继续合并代码的可以使用:
> git stash pop  

然后就需要自己进行冲突合并了  


4. 回退git版本到指定版本,版本号可以从git仓库中查,之后如果要将master分支更新的话,需要git push -f  
> git reset --hard "目标版本号"  

5. 代理相关指令
> 设置代理:  
>+ git config --global http.proxy 'socks5://127.0.0.1:1080'    
>+ git config --global https.proxy 'socks5://127.0.0.1:1080'   
>  
> 查看代理:  
>+ git config --global --get http.proxy  
>+ git config --global --get https.proxy  
>  
>取消代理:  
>+ git config --global --unset http.proxy   
>+ git config --global --unset https.proxy    

6. 中文乱码解决方案  
如果中文文件名出现类似\212\210之类的乱码,可以使用下面的方式让中文字符正常显示  
>+ git config --global core.quotepath false   


