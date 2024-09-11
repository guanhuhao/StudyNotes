# 概率论与数理统计
## 概率论基本概念
**实验(Expriment):** 一种理想的过程，可以无限重复，具有明确定义的结果或成果。
**样本空间(Sample Space) $\Omega$:** 实验所有可能的结果
**事件(Event):**  样本空间的一个子集
### 概率测度
**概率测度(probability measure) $\mathbb{P}$:** 将事件映射到[0,1]的空间中,表示事件发生的概率.
> 事件 A 的概率使用符号 $\mathbb{P}(A)$表示
对于极大概率发生的事件可以认为 $\mathbb{P} = 1$
概率测度(Probability measure)需要满足以下性质,其中$\mathcal{F}$是由被测量对象 $\mathbb{P}$定义的事件空间:
>+ 1. 空事件集概率为0, 全样本空间概率1,即: $ \phi \in \mathcal{F}, \omega \in \mathcal{F} \text{, and } \mathbb{P}(\phi) = 0, \mathbb{P}(\Omega) = 1$, 
>+ 2. 可数可加性(Countable additivity) 对于概率空间中事件 $A_i \subset \mathcal{F}, i = 1,2,...$,若$A_i$是可数的且互斥(即对于任意i,j$A_i \cap A_j = \phi$),则满足下式:
$\mathbb{P}(\cup A_i) = \sum_i \mathbb{P}(A_i)$
> 
> PS: 
  测度(measure)是给被测量目标分配一个值,用来解释被测量对象之间的差异
  可数可加性可以理解为,多个互斥概率事件并的概率等于各自概率的和

基于上述定义$\mathcal{F}$是一个 $\sigma-\text{algebra}$ 代数空间,此时我们可以使用三元组 $(\Omega,\mathcal{F},\mathbb{P})$代表一个**概率空间** (Probability Space),由**样本空间** $\Omega
$(所有可能结果),**被测量对象** (事件)$\mathcal{F}$以及**对应测度** ($\mathbb{P}$)

### 补充资料(什么是 $\sigma-\text{algebra}$ 代数空间):
 $\sigma-\text{algebra}$ 代数空间:一种特殊的集合,集合的元素为若干集合要求满足下面条件
> 1. 包含空集: $\phi \in \mathcal{A}$
> 2. 补操作封闭: $\text{if} A\in \mathcal{A}, \text{then } A^c \in \mathcal{A}$
> 3. 对可数并集封闭: $For \mathcal{A} = \{A_n\} \text{, } \cup^{\infty}_{n=1} A_n \in \mathcal{A}$

## 随机变量
对于概率空间$(\Omega,\mathcal{F},\mathbb{P})$,随机变量$X$可以认为从样本空间(自然语言)到实数空间(代数语言)的映射 $\Omega \to \mathbb{R}$,因为可以将自然语言表述的事件规范化为数学语言后可以更好的方便后续公理化.数学上可以表示为:
$$X^{-1}(I) = \{w\in \Omega: X(w) \in I \} \in F$$
$X^{-1}(I)$表示对于代数空间的特定值 $I$对应的某个事件
由于 $\{w\in \Omega: X(w) \in I \}$ 过于繁琐,可以使用 $\{X\in I\}$来直接进行表示.
由于根据映射关系$X$使得原样本空间$\Omega$中多个结果$\omega$可能对应同个$I$因此说:
$X$是$\mathcal{F}-\text{measurable}$,因为无法区分其他粒度的事件.
> 举个例子:定义投骰子事件的样本空间集合$\Omega
$为$\{投出1,投出2,...\}$,映射关系X可以定义0为投出小点数,1为投出大点数,因此可以得到类似的$\{事件:投出1\}\to 0$,...,$\{事件:投出4\} \to 1$,因此可以得到一个由$\{\phi,0,1,\Omega\}$构成的$\sigma-$代数空间$\mathcal{F}$(事件空间),该事件空间可以测量投出大点数与小点数的概率,但无法测量投出点数1或者其他点数的概率

### 期望
随机变量 $X$的期望 $\mathbb{E}(X)$表示随机变量$X$的均值,计算方式如下:
随机变量的线性可加性例如:
$$ E[aX + bY + c] = a\mathbb{E}[X] + b\mathbb{E}[Y] + c $$
期望与概率的联系:
从概率到期望: 令$X(\omega)$表示随机变量$X
$在事件$\omega$发生时的值
<center>
  
离散形式:  $\mathbb{E}(X) = \sum X(\omega)P(\omega)$  

连续形式: $\mathbb{E}(X) = \int_\Omega X(\omega) d \omega$
</center>


需要注意的是:连续性期望的存在性依赖于积分的收敛性

从期望到概率:定义特殊**指示函数**$1_A(\omega)$, 当事件$\omega \in A$时取值为1,否则为0.此时有:
$$\mathbb{E}(1_A) = 1\cdot \mathbb{P}(A) + 0 \cdot \mathbb{P}(\Omega / A) = \mathbb{P}(A)$$

### 方差&标准差
随机变量的方差表示随机变量分布与均值的偏离程度,可以表示为:
$$Var(X) = \mathbb{E}[(X-\mu)^2]$$
标准差:将方差开方后可以获得标准差$\sqrt{Var(X)}$,标准差可以使用 **切比雪夫不等式** 用来估计随机变量取值的偏离概率
切比雪夫不等式:
$$\mathbb{P}(|X-\mu|\geq k\sigma) < \frac{1}{k^2}$$
举个例子:当k=2时表示随机变量偏离均值2倍标准差的概率小于1/4
证明方式如下:
令事件A:$|X-\mu| > k\sigma$
$$\sigma^2 = \mathbb{E}[(X-\mu)^2] > \mathbb{E}[k^2\sigma^2] = k^2\sigma^2 > k^2\sigma^2\mathbb{P}(A)$$
然后两边同时除$\sigma^2$ 即可证明

### 条件期望
条件意味着降低的不确定性,可以用下面的方式进行定义,若随机变量$V$满足下面条件则可以说随机变量$V$是随机变量$X$在$\mathcal{G}$下的条件期望:
对于整个概率空间 $(\Omega,\mathcal{F},\mathbb{P})$的一个子空间$\mathcal{G}$(要求$\mathcal{G}$也满足$\sigma-$代数)
1. V是$\mathcal{G}$可测量的,即$\mathcal{G}-\text{measure}$
2. 对于任何事件$A\in \mathcal{G}$,满足$\mathbb{E}(V\cdot 1_A) = \mathbb{E}(E\cdot 1_A)$

关于条件概率的计算形式化的表达为:
$$V = \mathbb{E}[X|\mathcal{G}] = \frac{\mathbb{E}(X\cdot 1_A)}{\mathbb{P} (A)}$$

P19页推导(w)

--- 

条件概率
条件概率定义为:
$$\mathbb{P}(A|B) = \mathbb{E}[1_A|B] = \frac{\mathbb{E}(1_A \cdot 1_B)}{\mathbb{P}(B)} = \frac{\mathbb{P}(A \cap B)}{\mathbb{P}(B)} $$
表示事件A得结果在条件$$1_B(w)$$为1时的结果
全概率公式
贝叶斯定理
$$\mathbb{P}(A_j|B) = \frac{\mathbb{P}(A_j\cap B)}{\mathbb{P}(B)}$$
先验概率(priori probability): $$\mathbb{P}(A)$$表示事件A发生(或不发生)的概率
后验概率(posterior probability):,$$\mathbb P(A_j|B)$$ 表示事件 $$B$$发生情况下事件A发生的概率
独立事件

概率分布
概率分布(Probability Distribution): 定量描述随机变量行为的函数 
累积分布函数(CDF): 对概率分布进行积分或累加,计作$$F_X(\cdot)$$为:
$$F_X(x) = \mathbb{P} (X<x) $$
  CDF满足下面性质:
1. 累计分布函数非递减(non-decrease)
2. CDF的极值: $$\lim x\to -\infty, F_X(x) = 0; \lim x \to \infty, F_X(x) = 1$$
概率密度函数(PDF):对累积分布函数(CDF)求导可以获得单点处的概率记为$$f_X(y)$$,因此可以得出概率密度函数有与累积密度函数的关系:
$$F_X(x) = \int_{-\infty}^x f_X(y) dy$$
要求$$f_X(y) > 0$$
CDF 与 PDF 满足下面性质:
1. 区间概率等于累积分布的差:$$\mathbb{P}(a < X < b) = F_X(b) - F_X(a)$$
2. 若左极限存在则: $$\mathbb{P}(X<b) = \lim _{a\to b^-}\mathbb{P}(X\leq b) = \lim_{a\to b^-} F_X(a)$$
3. 若$$\mathbb{P}(X < b) = \mathbb{P}(X \leq b)$$,则有$$\mathbb{P}(X = b) = 0$$
4. 随机变量X的期望可以表示为 $$\mathbb{E}[X] = \int_\mathbb{R}x f_X(x) dx$$
  1. 进一步的有关于随机变量X的函数$$g(X)$$的期望可以计算为$$\mathbb{E}(g(X)) = \int_{\mathbb{R}}g(X)f_X(x)dx$$
 概率质量函数(PMF):

独立同分布(i.i.d)
要求随机变量满足两点:1. 随机变量满足同一分布 2.随机变量之间保证独立

常见分布
均匀分布: