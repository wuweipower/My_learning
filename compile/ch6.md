静态语义：在执行前，编译器所做的

动态语义：在执行时

属性文法是用来描述语义

语法指导语义分析

## 属性文法

属性文法包含属性和属性等式

属性是需要计算的特性

属性等式表示了这种计算与语法的关系

定义：An attribute is any property of a programming language construct

属性一般有：变量的数据类型，一个表达式的值，变量在内存中的地址，程序的目标代码

![image-20220613211906907](C:/Users/17526/Desktop/notes/compiler/img/image-20220613211906907.png)

#### Synthesized Attribute

综合属性：child to parent，这个结点的属性依赖于子节点的属性。如算术表达式

A->X1X2X3..Xn

A.a = f(X1X2X3..Xn)

如果属性文法中的属性都是综合属性，那么这个就叫S-attributed grammar

适合自底向上分析和后序遍历一个树

#### Inherited Attribute

Inherited attributes have dependencies that flow either from parent to children in the parse tree or from sibling to sibling

这个结点的属性依赖于父节点和左兄弟结点

preorder或者preorder&inorder

属性值储存在node的field里面

属性的计算可以在语法分析的阶段完成

compilers that perform one-pass translation compute all attributes during the pass

由于分析的时候，分许输入是从左到右的，所以有可能依赖图可以从右到左 L-attributed

L grammar:一个结点的某个值依赖于这条语法规则的中这个结点的左边如：

X0->X1X2...Xn

the value of aj at Xi can only depend on attributes of the symbols X0,...,Xi-1 that occur to the left of Xi in the grammar rule

这种情况下an S-attributed grammar is L-attributed

递归下降中，计算属性可以通过把继承属性作为参数，综合属性作为返回值

LR语法分析时，适合 handling primarily synthesized attributes.加一个语义值的栈

symbol table用来储存与已声明的常量，变量和函数的属性支持

- 插入
- 查找
- 删除

声明：插入符号表

语句：主要是类型检查

