

token (Kind, Value)

lexeme is the string value represented by a token

- reserved words and special symbol have only one lexeme
- number and identifier have infinitely many lexemes

## Interface of scanner 

scanning is  a single pass

scanning is a sub function of the parser: when called by the parser it returns the single next token from the input

## Regular Expression

represent patterns of strings and characters

### Alphabet

- definition: Any finite set of symbols
- example: A={a,b,c}

### String

- definition: A string over some alphabet is a finite sequence of symbols drawn from that alphabet.
- example: a, ab, aaca are strings of Α={a‚b,c}
- length of string: |abc|=3
- empty string denoted by ε, |ε|=0 and {ε} != Φ

### Operations on String

- Concatenation
  - If x and y are strings,then the concatenation of x and
    y,written as xy,is the string formed by appending y to x
  - example: x=ST，y=abu ,xy=STabu εx = xε=x

- Exponentiation 
  - a^1^=a a^2^=aa a^0^=ε

### Language

- definition: Any set of strings over some fixed alphabet
- example: **{ε}is a language,Φ, the empty set is also a language**

### Operations on language 

- Concatenation of L and M is written as LM LM ={st|s∈L,t∈M}

  - L={ab,cde} M = {0,1}LM ={ab0,ab1,cde0,cde1} 参考笛卡尔积

  - {ε}A = A{ε}=A

- Exponentiation 类似地

- Closure

  - L * = L 0∪ L1∪ L 2∪ L 3∪...
  - L += L 1∪ L 2∪ L 3∪...

ε and Φ are regular expression

任何一个在字母表里面的字符都是正则表达式

**优先级：闭包>串联>或**



### Some RE

d=0|1|..|9

unsigned integer dd^*^

### Issues

- ambiguity: 一**些字符串会匹配多个RE**
- 一个字符串可以是关键词或者标识符时，**优先关键词**
- 若一个字符串可以被识别为单个或者多个时，**多个优先**
- **分隔符。**Scanner discards them after checking for any token delimiting effects
- **lookahead**

## Finite Automata

==Finite== Automata are mathematical ways of describing particular kinds of algorithms.

Deterministic Finite Automata(DFA)
Nondeterministic Finite Automata(NFA)

states

transitions

start state

accepting state 

### DFA

A DFA M=（S，Σ，T，S0，A）

1. S is a set of states
2. Σ is an alphabet
3. T is a transition function T: S X ∑->S, T(Si,a)=Sj
   represents when the current state is Si and the current
   input character is a，DFA will transit to state Sj
4. S~0~∈S is a start state
5. A is a set of accepting states

Error transitions are not drawn in the diagram

### NFA

similar to DFA except ==ε-transition== and ==more than one transitions from a state for a particular character==

![image-20220611172601067](C:/Users/17526/Desktop/notes/compiler/img/image-20220611172601067.png)

![image-20220611172634139](C:/Users/17526/Desktop/notes/compiler/img/image-20220611172634139.png)



### NFA->DFA

有ε-transition就把后面那个状态和前一个状态合并为一个

![image-20220611173253958](C:/Users/17526/Desktop/notes/compiler/img/image-20220611173253958.png)

![image-20220611174140072](C:/Users/17526/Desktop/notes/compiler/img/image-20220611174140072.png)

![image-20220611174613452](C:/Users/17526/Desktop/notes/compiler/img/image-20220611174613452.png)

![image-20220611174647038](C:/Users/17526/Desktop/notes/compiler/img/image-20220611174647038.png)

==ε-closure要包括自己==

rename的时候 每一行后面要写0或者1表示是否accept

Equivalent States
If s and t are two states, they are equivalent if and
only if:
• s and t are both accepting states or both non-accepting states.
• For each character a∈Σ, s and t have transitions on a to the **equivalent states**

Minimizing Algorithm
**Split the set of states into some un-intersected sets, so**
**states in one set are equivalent to each other, while any two**
**states of different sets are distinguishable.**

这里A选项不是NFA是DFA

![image-20220611191032227](C:/Users/17526/Desktop/notes/compiler/img/image-20220611191032227.png)

BC

| 表达式 | 匹配                              |
| ------ | --------------------------------- |
| c      | 单个非运算符字符c                 |
| \c     | 字符c的字面值                     |
| "s"    | 串s的字面值                       |
| .      | 除换行符以外                      |
| ^      | 一行的开始                        |
| $      | 行的末尾                          |
| [s]    | 字符串s中任何一个字符             |
| [^s]   | 不在串s中的任何一个字符           |
| r*     | 和r匹配的零个或者多个串连接成的串 |
| r+     | 和r匹配的一个或者多个串连接成的串 |
| r?     | 零个或者一个r                     |
| r{m,n} | 最少m，最多n个r的重复出现         |
| ab     | a后面加上b                        |
| a\|b   | a或者b                            |
| (r)    | 与r相同                           |
| a/b    | 后面跟有b时的a                    |



![image-20220611205457328](C:/Users/17526/Desktop/notes/compiler/img/image-20220611205457328.png)

