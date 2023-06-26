推导用=>

规约用<= 或者|-

最右推导，最左规约

## Main Idea

### Definition

### Implementation

#### general format

| parsing stack | Input        | Action |
| :------------ | :----------- | :----- |
| $             | InputString$ |        |
| ...           | ...          | ...    |
| @StartSymbol  | $            | accept |

**Bottom-up parsing stack** :tokens, nonterminals, status. store s the symbols having been matched.

### steps

1. Base on the stack content and use the next token in the input as a lookahead to determine the next action to be performed

2. two possible actions

   **Shift: shift a terminal from the front of the input to the top of the stack**(将输入的字符中的第一个压栈)

   **Reduce: reduce a string α at the top of the stack to a nonterminal A, given the production A->α**(production 的逆操作)

   

### example

![image-20220410001823856](C:\Users\17526\AppData\Roaming\Typora\typora-user-images\image-20220410001823856.png)

这里就是一位一位地读取input，然后根据state匹配一个表中的行为和状态

## Characters

### right sentential form

Each of the intermediate strings in rightmost derivation is called a right sentential form

### viable prefix（可行前缀）

不超过句柄的前缀，这里d是句柄，不能超过

aA, aAc, aAcd are all viable prefix of aAcde

### handle

- The string matches the right-hand side of the production that is used in the next reduction

- Together with the position in the right sentential form where it occurs 

- And the production used to reduce it is called the handle of the right sentential form

  For example
  In the right sentential form “abbcde”, the handle is the string consisting of the leftmost “b”, together with the production A->b

**能够reduce的production的右边**就是handle

![image-20220410003345030](C:\Users\17526\AppData\Roaming\Typora\typora-user-images\image-20220410003345030.png)

==S=>*αAw, A->β is a production==

==so we say that β is the handle of αβw==

==beta是语法树的最左叶子==



自底向上的语法分析比自顶向下一般更强大

## method

### LR(K)

Basing on the string on top of the parsing stack (represented as state) and using the next K(K≥0) tokens in the input as lookahead to determine handle for reduction

- L表示输入是从左到右处理
- R表示最右推导
- K表示需要K个向前看的symbol



<img src="C:\Users\17526\AppData\Roaming\Typora\typora-user-images\image-20220410003944642.png" alt="image-20220410003944642" style="zoom: 70%;" />**假设已知这个表**



<img  src="C:\Users\17526\AppData\Roaming\Typora\typora-user-images\image-20220410004105639.png" alt="image-20220410004105639" style="zoom:67%;" /> 

​		这个栈是包括了字符和状态

​		**每次的action是根据当前栈顶的状态和input的第一个字符决定，然后去查表**

#### 	  Attention 

- s2 表示shift一个字符并且将状态2压入栈
- r2表示执行第二个reduce 比如这里就是(2)A->b  并且这里还会**pop**相应的字符栈和状态栈中的对应数量的元素，并且分别压入**A**和	goto中的**3**状态 ==这里的3状态是先把**A**push进来后和状态栈顶的2决定的==



## Items

### LR(0) Item

 A LR(0) item of a grammar G is a production of G with a distinguished position in its right-hand side
For example, production U→XYZ has four items
[0] U→ • XYZ [1] U→X • YZ
[2] U→XY • Z [3] U→XYZ •
**production A→εhas only one item A→•**
These are called LR(0) items because they contain no explicit reference to lookahead

### meaning of items

An item records an intermediate step in the recognition of the right-hand side of a production
**A→ • α means that we may be about to recognize an A by using production A→ α**
**A→β • γ means that β has already been seen (β must appear at the top of stack)**
**and that it may be possible to derive the next input token from γ**
**A→α • means that α now resides on the top of the stack and may be the handle, if A->α is to be used for the next reduction**

- #### Initial Item

  **form like A->• α**

- #### Complete Item

  **form like A→α •**





<img src="C:\Users\17526\AppData\Roaming\Typora\typora-user-images\image-20220410010511780.png" alt="image-20220410010511780" style="zoom:50%;float:left" />



| Action                                                       | GOTO                                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| Terminals + $                                                | Nonterminals                                                 |
| I~0~表示状态0 上面的图的箭头上是terminal的时候就是shift操作然后箭头指向的状态就是要转移的状态 | 当箭头上是非终结符时，就是GOTO操作，转移的状态就是箭头指向的状态 |

在上面的action中

- 只有I~1~状态的时候输入$就会accept其他都不是accept
- 像I~4~ I~6~这种没有箭头指向其他的状态的，**在LR(0)中都是reduce，不管输入什么**



#### Shift-Reduce Conflict

If a set contains shift item A→α•aβ and complete item B→r•, an ambiguity arises as to whether shift ‘a’ or reduce ‘r’ to B

#### Reduce-Reduce Conflict

If a set contains complete item A→β• and B→r•, an ambiguity arises as to which production to use for the reduction

==A grammar is LR(0) if and only if non of the set of items has shift-reduce conflict or reduce-reduce conflict.==

### SO we need SLR(1)(simple LR(1))

==**for item A→r•, reduction only takes place when the next token a∈FOLLOW(A)**==



I={X→α•bβ‚Α→r•‚Β→δ•}, where b∈VT，
if FOLLOW(A) ∩FOLLOW(B)=φ and not
includes b, the action of I is based on the
next input token ‘a’

-  a=b, then shift

- If a∈FOLLOW(A), then reduce with A→r

- If a∈FOLLOW(B), then reduce with B→δ 

- Otherwise, an error occurs

  

如果上面输入的a会无法决定是否改shift还是reduce那么这个grammar就不是SLR(1)

### so we need LR(1)

1. LR(1) item
   A LR(1) item is a pair consisting of a
   LR(0) item and a lookahead token
   [A-> a•b,c] where A->a•b is a LR(0)
   item and c is a lookahead token

2. The Construction of automation of
   LR(1) items
   These are similar to LR(0)
   transactions except that they keep
   track of lookaheads.

3. The transactions between LR(1) items

   <img src="C:\Users\17526\AppData\Roaming\Typora\typora-user-images\image-20220416204326805.png" alt="image-20220416204326805" style="zoom:50%;float:left" />

   

   **I`的任何项目都属于`CLOSURE(I)**
   
   **若item[A->α•Bβ,a]属于`CLOSURE(I)`，B->r是文法中的一项规则，b∈FIRST(βa)，则[B->•r,b]也属于`CLOSURE(I)`**
   
   **重复直到闭包不在增大**
   
   
   
   要lookahead
   
   <img src="C:\Users\17526\AppData\Roaming\Typora\typora-user-images\image-20220416210514239.png" alt="image-20220416210514239" style="zoom:50%;float:left" />

### LALR(1)(lookahead LR(1))

两个状态有相同的item，除了lookahead不一样。可以合并为一个状态，将lookahead扩充eff

<img src="C:\Users\17526\AppData\Roaming\Typora\typora-user-images\image-20220416205135976.png" alt="image-20220416205135976" style="zoom:70%;float:left" />



