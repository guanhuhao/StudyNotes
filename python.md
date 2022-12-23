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

## 文件读写
使用open打开指定文件,并确定读写形式,如下:
```python
file = open("data.txt","r+")
content = file.read()
file.write("hello world")
```
|模式|说明|
|---|---|
|r	|以只读方式打开文件。文件的指针将会放在文件的开头。这是默认模式。|
|rb	|以二进制格式打开一个文件用于只读。文件指针将会放在文件的开头。这是默认模式。|
|r+	|打开一个文件用于读写。文件指针将会放在文件的开头。|
|rb+	|以二进制格式打开一个文件用于读写。文件指针将会放在文件的开头。|
|w	|打开一个文件只用于写入。如果该文件已存在则将其覆盖。如果该文件不存在，创建新文件。|
|wb|	以二进制格式打开一个文件只用于写入。如果该文件已存在则将其覆盖。如果该文件不存在，创建新文件。|
|w+	|打开一个文件用于读写。如果该文件已存在则将其覆盖。如果该文件不存在，创建新文件。
|wb+	|以二进制格式打开一个文件用于读写。如果该文件已存在则将其覆盖。如果该文件不存在，创建新文件。|
|a|	打开一个文件用于追加。如果该文件已存在，文件指针将会放在文件的结尾。也就是说，新的内容将会被写入到已有内容之后。如果该文件不存在，创建新文件进行写入。|
|ab	|以二进制格式打开一个文件用于追加。如果该文件已存在，文件指针将会放在文件的结尾。也就是说，新的内容将会被写入到已有内容之后。如果该文件不存在，创建新文件进行写入。|
|a+	|打开一个文件用于读写。如果该文件已存在，文件指针将会放在文件的结尾。文件打开时会是追加模式。如果该文件不存在，创建新文件用于读写。|
|ab+	|以二进制格式打开一个文件用于追加。如果该文件已存在，文件指针将会放在文件的结尾。如果该文件不存在，创建新文件用于读写|

## 排序
sort函数的第一个参数是一个迭代器,第二个参数为自定义比较函数这里使用lambda函数,表示输入为x,返回-x[1],然后按照返回值进行升序排列
```python
sorted(List,key = lambda x:-x[1])
```
## pyplot
使用之前需要引入下面的库
```python
import matplotlib.pyplot as plt 
```

画折线图并显示
```
x = [i for i in dic.keys()] 
y = [i for i in dic.values()]
plt.plot(x,y)
plt.show()
```

plt可选参数
|参数|含义|
|---|---|
|color|线条颜色|
|linewidth|线粗|
|linestyle|线型|

使用对数坐标
```python
plt.yscale('log')
plt.xscale('log')
```

plt图注相关链接:
https://zhuanlan.zhihu.com/p/41781440

## 计时
### 日期时间戳
```python
import datetime
datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')
```

### 计时函数
```python
import time 
time_beg = time.time()
# do something
time_end = time.time()
print("runtime:",(time_end-time_beg),"s")
```