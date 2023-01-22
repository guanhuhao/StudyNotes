# 表格
```latex
\begin{figure*} % 双栏跨栏
\begin{center}  % 居中
    \setlength{\tabcolsep}{6mm}{
    \renewcommand\arraystretch{1.5} % 设置行距,表示1.5倍行距,注需导入array包
    \begin{tabular}{c|c|c|c|c|ccc } % l,r,c 表示居左/右/中对齐方式,个数表示表格的列数, | 表示是否存在分割线
    Hypergraph & |V| & |E| & $\sum_{e\in E} deg(E)$& max deg(v) & max deg(e)\\
    \hline % 行分割线
    Web trackers  & 27,665,730 & 5,624,219 & 140,613,762 & 1,100,065  & 11,571,952  \\ 
    dblp-author & 1,953,085 & 12,282,059 & 12,282,059  & 1,386 & 287  \\ 
    dbpedia-location & 172,091 & 53,407 & 293,697 & 12,189 & 28 \\ 
    actor-movie & 127,823 & 383,640 & 1,470,404  & 294 & 646  \\ 
    orkut-group & 2,783,196 & 8,730,857 & 327,037,487 & 40,425 & 318,240 \\ 
    github & 56,519 & 120,867 & 	440,237 & 884 & 3,675 \\ 
    \end{tabular}
    }
    \textbf{Table 2} Data Set. % 标题,可以放到上面
\end{center}
\end{figure*}
``` 