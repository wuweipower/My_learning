# 树

## 树的遍历

实现遍历的方式就是广度和深度的结合。

与我写的一个图的遍历相似，for循环是相似的

```c++
void print(Node<elem>* root)
{
    if(root->isLeaf()) cout<<"leaf"<<endl;
    else cout<<"internal"<<endl;
    for(Node<elem>* temp = root->leftmostChild();temp!=null;temp = temp->rightSibling())
    {
        print(temp);
    }
}
```

```c++
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<time.h>
#include<climits>
using namespace std;

struct edge
{
    char value;//被指的顶点
    int weight;//边长
    edge(char value, int weight)
    {
        this->value = value;
        this->weight = weight;
    }
};
struct node
{
    char value;//顶点 
    vector<edge> next;
};

int ans = INT_MAX;
char start='0';
char nex;
const char e='6';
vector<char>path;
void dfs(char s,int sum,vector<node>& nodes)
{
    path.push_back(s); 
    if(sum>ans) return;

    if(s==e)
    {
        for(int i=0;i<path.size();i++)
        {
            cout<<path[i]<<" ";
        }
        cout<<endl;
        cout<<"cost: "<<sum<<endl;
        if(sum<ans) ans=sum;
        
    }
    for(int i=0;i<nodes[s-'0'].next.size();i++)
    {
        //sum+=nodes[start-'0'].next[i].weight;
        nex = nodes[s-'0'].next[i].value;
        //path.push_back(nex);
        dfs(nex,sum+nodes[s-'0'].next[i].weight,nodes);
        path.pop_back();
    }

}
```



## 父指针表示法

实现树的最简单的方法就是每一个结点只保存一个指针域，指向父结点。

缺点：无法找到最左子节点和右兄弟结点

这种方法主要是为了并查集

并查集。找根节点。

```c++
int find(int curr)
{
    while(array[curr]!=ROOT) curr = array[curr];//向父节点移动，本质就是更新指针
    return curr;
}
```

| **父结点的下标** | **-** | **0** | **0** | **1** | **1** | **2** |
| ---------------- | ----- | ----- | ----- | ----- | ----- | ----- |
| **标号**         | R     | A     | B     | C     | D     | E     |
| **结点的下标**   | 1     | 2     | 3     | 4     | 5     | 6     |

加权合并规则

- 把结点较少的树的根节点指向结点较多树的跟结点。

## 路径压缩

当查找一个结点X的根节点的时候，设根节点为R，把由X到R的路径上的每一个结点的父指针都指向R。

```c++
int find(int curr)
{
    if(array[curr]==root) return curr;
    array[curr]  = find(array[curr]);//这一步和下一步将路径上的每一个结点的父节点指向了根节点
    return array[curr];//上面的递归找到了根节点
}
```

如果只是简单find的递归版本，应该是这样

```c++
int find(int curr)
{
    if(array[curr]==root) return curr;
    else return find(array[curr]);
}
```



## 树的实现

### 子节点表示法

```c++
class node
{
    int val;//结点的值
    int parent;//node* parent
    vector<int> child;//vector<node*>child
};
```

缺点：找一个子节点中的值，复杂度是O(n)

### 左子节点/右兄弟结点表示法

```c++
class node
{
    int val;//结点的值
    int parent;//node* parent
    int child;//node* child
    int rightSibling;//node* rightSibling
};
```



### 动态结点法

```c++
class node
{
    int val;
    int size;
    node* child = new node[size];//这里其实不一定是指针数组，说实话，这样写显得我不懂指针，主要是课本的思想是这样的
    //当child增加时
    //下面为伪代码
    void addChild(const node* add)
    {
        //进行深拷贝
        node* temp = new node[++size];
		for(int i=0;i<size-1;i++)
        {
            temp[i] = child[i];
        }
        temp[size] = add;
        child = temp;//
	}
};
```

其实上面的代码可以简略为下面这个

```c++
class node
{
    int val;
    node* child;
};
```

# K-tree

没啥好说的

# 树顺序表示



<img src="..\pic\image-20220420212518879.png" alt="image-20220420212518879" style="zoom:67%;float:left" />

