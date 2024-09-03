该教程主要面向1.x版本(面向新时代)  
首先pyecharts 1.x **仅支持python3.6+**  
## 一、安装
在命令行中直接敲:
```
pip install pyecharts
``` 

其他安装方式可以参考[官方文档](https://pyecharts.org/#/zh-cn/quickstart?id=%e5%a6%82%e4%bd%95%e5%ae%89%e8%a3%85)

## 二、代码形式
对于pyechart提供了两种书写形式:  
1.链式调用 2.单独调用
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
可供选择的参数以及对应的效果预览图可以参考链接[主题设置](https://pyecharts.org/#/zh-cn/themes?id=%e4%b8%bb%e9%a2%98%e9%a3%8e%e6%a0%bc)

## 具体图表绘制
### 柱状图
对于参数设置以及解释,可以参考[官方文档](https://pyecharts.org/#/zh-cn/rectangular_charts?id=bar%ef%bc%9a%e6%9f%b1%e7%8a%b6%e5%9b%be%e6%9d%a1%e5%bd%a2%e5%9b%be ) 
下面给出一个简单柱状图实例:  
```python
from pyecharts import options as opts
from pyecharts.charts import Bar
from pyecharts.commons.utils import JsCode
from pyecharts.globals import ThemeType

list2 = [
    {"value": 12, "percent": 12 / (12 + 3)},
    {"value": 23, "percent": 23 / (23 + 21)},
    {"value": 33, "percent": 33 / (33 + 5)},
    {"value": 3, "percent": 3 / (3 + 52)},
    {"value": 33, "percent": 33 / (33 + 43)},
]

list3 = [
    {"value": 3, "percent": 3 / (12 + 3)},
    {"value": 21, "percent": 21 / (23 + 21)},
    {"value": 5, "percent": 5 / (33 + 5)},
    {"value": 52, "percent": 52 / (3 + 52)},
    {"value": 43, "percent": 43 / (33 + 43)},
]

c = (
    Bar(init_opts=opts.InitOpts(theme=ThemeType.LIGHT))
    .add_xaxis([1, 2, 3, 4, 5])
    .add_yaxis("product1", list2, stack="stack1", category_gap="50%")
    .add_yaxis("product2", list3, stack="stack1", category_gap="50%")
    .set_series_opts(
        label_opts=opts.LabelOpts(
            position="right",
            formatter=JsCode(
                "function(x){return Number(x.data.percent * 100).toFixed() + '%';}"
            ),
        )
    )
    .render("stack_bar_percent.html")
)
```
### 饼图
对于参数设置以及解释,可以参考 [官方文档-饼图](https://pyecharts.org/#/zh-cn/basic_charts?id=pie%ef%bc%9a%e9%a5%bc%e5%9b%be)
下面给出一个简单饼图实例:
```python
from pyecharts import options as opts
from pyecharts.charts import Pie
from pyecharts.faker import Faker

c = (
    Pie()
    .add(
        "",
        [list(z) for z in zip(Faker.choose(), Faker.values())],
        radius=["40%", "55%"],
        label_opts=opts.LabelOpts(
            position="outside",
            formatter="{a|{a}}{abg|}\n{hr|}\n {b|{b}: }{c}  {per|{d}%}  ",
            background_color="#eee",
            border_color="#aaa",
            border_width=1,
            border_radius=4,
            rich={
                "a": {"color": "#999", "lineHeight": 22, "align": "center"},
               "abg": {
                    "backgroundColor": "#e3e3e3",
                    "width": "100%",
                    "align": "right",
                    "height": 22,
                    "borderRadius": [4, 4, 0, 0],
                },
                "hr": {
                    "borderColor": "#aaa",
                    "width": "100%",
                    "borderWidth": 0.5,
                    "height": 0,
                },
                "b": {"fontSize": 16, "lineHeight": 33},
                "per": {
                    "color": "#eee",
                    "backgroundColor": "#334455",
                    "padding": [2, 4],
                    "borderRadius": 2,
                },
               
            },
        ),
    )
    .set_global_opts(title_opts=opts.TitleOpts(title="Pie-富文本示例"))
    .render("pie_rich_label.html")
)
```
其中rich中主要用于设置标签的样式,即上面formatter中设置的格式化标签  
### 热点图
对于参数设置以及解释,可以参考![官方文档-热点图](https://pyecharts.org/#/zh-cn/rectangular_charts?id=heatmap%ef%bc%9a%e7%83%ad%e5%8a%9b%e5%9b%be)  

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
        title_opts=opts.TitleOpts(title="HeatMap-Label 显示",pos_left="center"),
        visualmap_opts=opts.VisualMapOpts(
            min_=0, max_=10, is_calculable=True, orient="horizontal", pos_left="center"
        )
    )
    .render("heatmap_with_label_show.html")
)
```
通过修改.set_global_opts中visualmap_opts的min_以及max_可以修改热力图中对应的颜色  
数据填充时主要修改value的值进行,value为一个三元组的list,三元组的组成可以表示为(x,y,val),即在坐标(x,y)其数据值为val,上述代码中Faker.clock,Faker.week均为1维列表表示坐标轴标号  


## 其他
如果想在jupyter中输出图片,只需要进行少量修改即可实现  
```python
.render("heatmap_with_label_show.html") #该行代码实现输出到文件
.render_notebook()                      #该行代码实现输出到jupyter
```