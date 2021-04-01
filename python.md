# Python 常用trick
## 1.获取文件当前/上级/上上级目录
```python 
import os

cur_path = os.getcwd() #获取当前文件绝对路径
father_path = os.path.abspath(os.path.join(cur_path,"..")) #获取上级目录
gradfather_path = os.path.abspath(os.path.join(cur_path,"../.."))
```
参考链接:https://blog.csdn.net/leorx01/article/details/71141643

## 2.遍历指定目录
```python 
import os

#最简单的版本，不支持递归
for file in os.listdir(path): #path为目录路径，可使用本文中1的方式获取 
    print(file) # do something

# 递归版
def get_file(path):
    for file in os.listdir(path):
        if(os.path.isdir(file)) : 
            print("enter folder:"+file) #进入目录xxx
            get_file(os.path.join(path,file))
            print("exit folder:"+file) #退出目录xxx
        else :
            print(file) # do something

get_file(os.getcwd()) #调用递归函数
```
注：也可使用os.walk()实现，具体可自行搜索
参考链接：https://blog.csdn.net/sinat_29957455/article/details/82778306

