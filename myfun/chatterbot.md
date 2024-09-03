# ChatterBot踩坑笔记
## 基础教程
这里找到了一篇很好的教程（要不是装环境坑太多了，这篇文章就基本上能满足大多数需求了QAQ，建议先跟着下面的教程走，遇到了问题再看看本篇文章是否有帮助
https://zhuanlan.zhihu.com/p/78714067
官方文档：https://chatterbot.readthedocs.io/en/stable/
## 装环境遇到的坑
### 1.python版本
注意截至该片文章写的时候，chattebot只支持python版本>=3.4且<3.8(最新的3.9以及3.8都不支持),故建议使用python3.6的版本（如果要接nonebot则选用3.7）
顺便一提，本人使用的是windows环境，不确定linux是否会有其他玄学问题
### 2.安装chatterbot
直接使用下面方式安装chatterbot时可能会出现依赖关系解决不了导致出现疯狂报错
>$ pip install chatterbot

除了上述方法,chatterbot文档中还提供了其他几种方法(包括git上先下载安装包,再pip ./xxx等,本人就是使用这种方式安装成功的),具体的方法再下面的链接中自行找到适合自己的方案
https://chatterbot.readthedocs.io/en/stable/setup.html#installation
### 3.安装scapy
用以上方法安装好chatterbot之后还需要解决部分依赖关系，正常按照提示，其中最难解决的就是scapy的依赖，首先是版本问题，能下spacy2最好，因为目测chatter使用的是scapy2.x的版本，而最新版本为scapy3，其中scapy3对于部分语句相较scapy2有更严谨的限制，导致scapy2写的的部分语句会报错，虽然也能通过对chatter的代码略加修改也能正常运行，但是一定要记住安装的大版本是1.x，2.x还是3.x这会影响下面安装en的操作
此处安装scapy的方式有很多种，如果一种不行建议换另外的方法多试试
#### 方案一、pypi直接下载
>$ pip install "scapy>=2.0,<3" #此处>=2.0,<3是版本控制，例如本句表示下载大于2.0小于3的spacy版本
#### 方案二、先下载安装包再本地安装
到下列链接中找到自己需要的版本
>https://pypi.org/project/spacy/#history

然后下载对应的.whl文件或者.gz.tar然后使用类似的命令本地安装
>$ pip install ./xxxx.whl 

### 4.安装scapy的依赖en模块
首先安装完scapy之后也不是直接能用通常情况下运行程序会有以下类似的报错信息
>OSError: [E050] Can't find model 'en'. It doesn't seem to be a shortcut link...

此时就需要使用下面命令下载en模块
>$ python -m scapy download en

**如果这一步完成后能成功import en_core_web_md包的跳过下面的内容**
如果到这一步那么你跟我一样不幸，本人使用上面的方式行不通，会报如下SSLHttps错误
>requests.exceptions.SSLError: HTTPSConnectionPool...

所以曲线救国，采用类似上面2的方式先下载压缩包然后在本地安装
下面链接是在知乎上找到的对该问题的解决方案
https://www.zhihu.com/question/56095738

然后en包可以在谷歌中搜索"en_core_web_md 1/2/3"的方式自己找一下，一般情况下包名大致上是这样的：en_core_web_md-3.0.0.tar.gz

同上安装好之后检测以下能不能正常import en_core_web_md，不行的话建议推翻重来(╯‵□′)╯︵┻━┻

**注：使用知乎上的方法时必须得注意下载的en大版本号需要跟之前下载的scapy大版本号匹配，比如scapy选择3.x的那么en就需要选择3.0.0的版本，不然会因为这两个包公用的模块（如thinc，cymem等等）版本冲突导致无法正常安装**
### 5. 关联en模块
#### 使用spacy2或者spacy1
用上述方法安装之后仍然可能会出现以下报错信息
>  Warning: no model found for 'en'
    Only loading the 'en' tokenizer.

这是因为下载后的en_core_web_md还没跟spacy关联，所以spacy找不到
首先检查以下是否能正常导入en_core_web_md的包确认已经安装完成
>import en_core_web_md

然后使用下面命令关联文件（注意此处可能需要使用管理员权限）
>python -m spacy link en_core_web_md en
#### 使用spacy3
忘了报错提醒是啥了，不过跟上面的不太一样，大致意思是spacy3使用了其他的方式导入en包，这个时候需要跳转到最底层的文件里面有个函数的第一个参数name改成name+"_core_web_md"，原因是因为3之前允许使用en这样的缩写，3之后需要使用单词全拼

到此为止，chatterbot的环境大致上已经配完了
