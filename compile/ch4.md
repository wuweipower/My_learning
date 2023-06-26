

# Top-down Parsing

==main problem is the choice of a production==

### method 1: backtrack递归回溯

暴力尝试所有可能性

### method 2: predictive parsing可预测的

- recursive-descent parsing 

- LL(1) parsing

  ==condition==, the grammar must be LL(1)

### First set

FIRST(A)就是能从A推导的式子中以终结符开头的终结符，最终推出只有空串，那么空串也在first set

<img src="C:\Users\17526\AppData\Roaming\Typora\typora-user-images\image-20220414113308127.png" alt="image-20220414113308127" style="zoom:50%;float:left" />

**Intuitively,**直觉地

如果一个产生式的右边的first set 交集为空集，则可以预测

### Follow set

FOLLOW(A)就是从==开始符号==开始推导的在A后面的终结符

<img src="C:\Users\17526\AppData\Roaming\Typora\typora-user-images\image-20220414113655771.png" alt="image-20220414113655771" style="zoom:50%;float:left" />

**如果A的first set里面含有空串，那么当它的first set和follow set交集为空，那么就可以预测**

**如果输入字符在first set里面就选择相应的推导式进行推导，如果在follow set里面则，则选择空串那个推导式进行推导**

==关于如何计算first和follow看平板的笔记==



## LL(1)

For each production A->α1|α2|...|αn First(αi) ∩First(αj) = Φ for all i and j,1≤i,j ≤ n,i≠j

For each nonterminal A such that First(A) contains ε, First(A) ∩Follow(A) = Φ

如何识别LL(1)的步骤

1.找出nullable非终结符（可零步或者多步推导出空串的非终结符）For each production p: Ap →X1 ....Xn , if X1....Xn∈S, then S:= SU{Ap }

2.计算产生式右边的所有式子的first

3.计算所有非终结符的follow

#### **计算first**

对于ABCDE... first(ABCDE...) = first(A)-{ε} 并上 first(B)-{ε}一直并到后面第一个不能推导出空串的==前面的注意要减去空串==

#### **计算follow**

开始符号的follow一定有ε，因为S=>S

FOR B→αAγ,

**Follow(A)=Follow(A)U(First(γ) -{ε})**

**若ε ∈ First(γ) then add Follow(B) to Follow(A)**

## 转为LL(1)

#### **left recursive removal**

<img src="C:\Users\17526\AppData\Roaming\Typora\typora-user-images\image-20220414114633741.png" alt="image-20220414114633741" style="zoom:50%;float:left" />

#### left factoring

<img src="C:\Users\17526\AppData\Roaming\Typora\typora-user-images\image-20220414114757441.png" alt="image-20220414114757441" style="zoom:50%;float:left" />





<img src="C:\Users\17526\AppData\Roaming\Typora\typora-user-images\image-20220410101519885.png" alt="image-20220410101519885" style="zoom:50%;float:left" />

反序入栈

| $startSymbol | inputString$ | action of parser |
| ------------ | ------------ | ---------------- |
| ...          | ...          | ...              |
| $            | $            | acc              |

根据input和符号栈的栈顶确定action后，

- 如果是derivation，就pop掉左侧的式子，将右侧的反向压入栈，就像这里第一行，将S pop出，然后将(S)S反向压入栈，空窗就直接删除左边的式子

- 如果是match就pop掉input的一个和stack里面的

## 如何创建parsing table,也就是查询action的表

==**根据first set 和 follow set**==

==**In other words, SELECT(V~N~**)==



### Recursive-descent parsing

对于有空串的推导，要进行follow set的判断如果不在follow里面就报错

### EBNF(extend BNF)

- {}is used to express repetition ==loop==
- [] is used to surround options ==if else==



## 构建语法表

不是nullable的非终结符，不根据follow来推导，因为没有空串推导

![image-20220612155738134](C:/Users/17526/Desktop/notes/compiler/img/image-20220612155738134.png)

当输入和栈都会空就accept

Error Recovery: after an error has occurred, the parser picks a likely place to resume the parsing

Error Repair: the parser attempts to infer a correct program from the incorrect one given

==恐慌模式==



