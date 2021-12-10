# Pyecharts 
该教程主要面向1.x版本(面向新时代)
首先pyecharts 1.x**仅支持python3.6+**
## 一、安装
在命令行中直接敲:
> pip install pyecharts 

其他安装方式可以参考官方文档:
https://pyecharts.org/#/zh-cn/quickstart?id=%e5%a6%82%e4%bd%95%e5%ae%89%e8%a3%85

## 二、代码形式
对于pyechart提供了两种书写形式:1.链式调用 2.单独调用
### 链式调用
目前个人的理解时将方法以及相关参数以类似类的方式封装到一个对象里,即如下:
```python
bar = (
    Bar()
    .add_xaxis(["衬衫", "羊毛衫", "雪纺衫", "裤子", "高跟鞋", "袜子"])
    .add_yaxis("商家A", [5, 20, 36, 10, 75, 90])
    .set_global_opts(title_opts={"text": "主标题", "subtext": "副标题"})
)
bar.render()
```
上述完成一个柱状图Bar的一个实例bar的创建,其x轴y轴对应数据填充以及一些基本图标参数的设置,后续可以直接实用bar来进行对应操作

### 单独调用
单独调用比较符合传统代码风格,先创建一个对象,再逐步往里面填充所需元素,不过考虑到对于复杂图标,可能链式调用的可供参考的代码会更多,因此可能后续会更多的使用链式调用的方式来调用
```python
bar = Bar()
bar.add_xaxis(["衬衫", "羊毛衫", "雪纺衫", "裤子", "高跟鞋", "袜子"])
bar.add_yaxis("商家A", [5, 20, 36, 10, 75, 90])
bar.set_global_opts(title_opts=opts.TitleOpts(title="主标题", subtitle="副标题"))
bar.render()
```

## 三、设置主题
pyecharts内置了10+种主题,可以根据实际需求以及个人偏好进行调整,主题存放在pyecharts.globals该包内,调用方法如下:
```python
from pyecharts.charts import Bar
from pyecharts import options as opts
# 内置主题类型可查看 pyecharts.globals.ThemeType
from pyecharts.globals import ThemeType

bar = (
    Bar(init_opts=opts.InitOpts(theme=ThemeType.LIGHT))
    .add_xaxis(["衬衫", "羊毛衫", "雪纺衫", "裤子", "高跟鞋", "袜子"])
    .add_yaxis("商家A", [5, 20, 36, 10, 75, 90])
    .add_yaxis("商家B", [15, 6, 45, 20, 35, 66])
    .set_global_opts(title_opts=opts.TitleOpts(title="主标题", subtitle="副标题"))
)
bar.render()
```
可供选择的参数以及对应的效果预览图可以参考下面的连接:
https://pyecharts.org/#/zh-cn/themes?id=%e4%b8%bb%e9%a2%98%e9%a3%8e%e6%a0%bc

## 具体图表绘制
### 柱状图

### 热点图
对于参数设置以及解释,可以参考官方文档:
https://pyecharts.org/#/zh-cn/rectangular_charts?id=heatmap%ef%bc%9a%e7%83%ad%e5%8a%9b%e5%9b%be

下面给出一个简单热力图的实例:
```python
import random

from pyecharts import options as opts
from pyecharts.charts import HeatMap
from pyecharts.faker import Faker

value = [[i, j, random.randint(0, 50)] for i in range(24) for j in range(7)]
c = (
    HeatMap()
    .add_xaxis(Faker.clock)
    .add_yaxis(
        "series0",
        Faker.week,
        value,
        label_opts=opts.LabelOpts(is_show=True, position="inside"),
    )
    .set_global_opts(
        title_opts=opts.TitleOpts(title="HeatMap-Label 显示"),
        visualmap_opts=opts.VisualMapOpts(),
    )
    .render("heatmap_with_label_show.html")
)
```