#### context free grammar

G=(终结符集合，非终结符集合，productions推导式集合，开始符号)

![image-20220611215740825](C:/Users/17526/Desktop/notes/compiler/img/image-20220611215740825.png)

![image-20220611225122296](C:/Users/17526/Desktop/notes/compiler/img/image-20220611225122296.png)

上下文很敏感，所以前后有alpha和beta

derivation: 推导

S=>*β 零步或者多步推导

**sectencial** form: S=>*β, β is a sentential form of G(**S也是**)

**sentence**: it is a sentential form, and it contains only terminals

L(G) is the set of sentences derived from S

E=>*F+(i\*i+1) F=>i

i是i+(i*i+1)的**直接短语**，最左的直接短语是**句柄** 如果F=>\*i那么只是短语。

#### definition of Parser Tree

A parse tree over the grammar G is a rooted labeled tree with the following properties:

1. The root node is labeled with the start symbol S
2. Each leaf node is labeled with a terminal or with ε
3. Each nonleaf node is labeled with a nonterminal
4. If a node with label A ∈ VN has n children with labels X1,X2,..,Xn(which may be terminals or nonterminals), then A->X1X2...Xn ∈P

- leftmost derivation

  A derivation in which the leftmost nonterminal is replaced at each step in the derivation

  It corrsponds to a preorder of the parser tree

- rightmost derivation

  A derivation in which the rightmost nonterminal is replaced at each step in the derivation

  It corrsponds to a reverse of postorder of the parser tree

leftmost and rightmost are unique for strings they construct

they both give rise to a parser tree

#### abstract syntax tree

只包含特别重要的信息

中间结点是操作符，叶节点是操作数

#### ambiguity

1.定义规则，如优先级，越往后优先级越高

2.改文法，遇到同优先级，确定结合顺序（左结合还是右结合）

E->E+E | E×E | (E) | i

改为

E -> E+T | T 

T -> T×F | F 

F -> (E) | i

