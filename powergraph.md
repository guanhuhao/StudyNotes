# Power Graph
对于PowerGraph中涉及的计算抽象为一个无状态的节点程序GASVertexProgram,该程序严格按照以下方式定义函数接口:

<pre class="pseudocode">
\begin{algorithm}
\caption{GASVertexProgram}
\begin{algorithmic}
\PROCEDURE{GASVertexProgram}{$u$}
    \STATE $gather(D_u,D_{(u,v)},D_v) \to Accum$
    \STATE $sum(Accum left, Accum right) \to Accum$
    \STATE $scatter(D_u^{new},D_{(u,v)},D_v) \to (D_{(u,v)}^{new},Accum)$
\ENDPROCEDURE
\end{algorithmic}
\end{algorithm}
</pre>

其中$D_u,D_v$表示节点数据,$D_{u,v}$表示边数据
在gather以及sum阶段使用map reduce来获取周围顶点数据,
对于gather函数被节点u的临边并行的调用,传递邻居节点数据或者边数据,并返回一个用户自定义的累加器.
对于sum函数,将gather得到的结果进行汇总,进行sum操作(**要求sum操作可交换且可关联的操作**),其最终结果计为$a_u$传递给apply阶段.