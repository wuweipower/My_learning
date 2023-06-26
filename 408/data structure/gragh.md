# 图的表示

## 相邻矩阵

用一个二维数组来表示。





## 邻接表(adjacency list)

邻接表是一个以链表为元素的数组，这个数组中包含|V|个元素，其中第*i*个元素储存的是一个指针，它指向顶点v~i~边构成的链表，这个链表通过储存顶点v~i~的邻接点来表示对应的边

**邻接表可以说是树结构的“子节点表”表示法的推光**



# 图的实现

## 邻接矩阵

```c++
const int UNVISITED=0;
const int VISITED=1;
class Graghm
{
    private:
    int numVertex,numEdge;
    int **matrix;
    int *mark;

    public:
    Graghm(int numVert)
    {
        init(numVert);
    }
    ~Graghm()
    {
        delete[] mark;
        for(int i=0;i<numVertex;i++)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    void init(int n)
    {
        int i;
        numVertex =n;
        numEdge=0;
        mark = new int[n];
        for(i=0;i<numVertex;i++)//初始化每一个结点的访问状态
        {
            mark[i]=UNVISITED;
        }
        matrix = (int**) new int*[numVertex];//创建二维数组
        for(i=0;i<numVertex;i++)
        {
            matrix[i] = new int[numVertex];
        }
        for(i=0;i<numVertex;i++)
        {
            for(int j=0;j<numVertex;j++)
            {
                matrix[i][j]=0;
            }
        }
    }

    int n(){return numVertex;}
    int e(){return numEdge;}

    int first(int v)
    {
        for(int i=0;i<numVertex;i++)
        {
            if(matrix[v][i]!=0) return i;
        }
        return numVertex;//不存在就返回这个
    }

    int next(int v, int w)
    {
        for(int i=w+1;i<numVertex;i++)
        {
            if(matrix[v][i] !=0) return i;
        }
        return numVertex;
    }

    void setEdge(int v1,int v2, int weight)
    {
        if(matrix[v1][v2]==0)
        {
            numEdge++;
            matrix[v1][v2]=weight;
        }

    }

    void deleteEdge(int v1, int v2)
    {
        if(matrix[v1][v2]!=0)
        {
            numEdge--;
            matrix[v1][v2]=0;
        }
    }
    
    bool isEdge(int v1, int v2)
    {
        return matrix[v1][v2] !=0;
    }

    int weight(int v1, int v2)
    {
        return matrix[v1][v2];
    }
    int getMark(int v) {
        return mark[v];
    }
    void setMark(int v, int val)
    {
        mark[v] = val;
    }

};
```

上面代码为教材所给。

## 邻接表

```c++
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
```

上面代码为笔者自写的。



# 图的遍历

## DFS

```c++
void DFS(Gragh* G, int v)
{
    PreVisit(G,v);//在访问前的一些action
    G->setMark(v,VISITED);//标记为访问
    for(int w->G->first(v);w<G->n();w = G->next(v,w))//扩展所有的子节点
    {
        if(G->getMark==UNVISITED)
            DFS(G,w);//得到一个子节点后就继续深入下去
    }
    postVisted(G,v);
}
```

以上为伪代码。

对于上面的for循环，在二叉树中为

```c++
DFS(root->left);
DFS(root->right);
```

因为二叉树就两个子节点，所以可以一个一个递归，但是图的子节点是不确定的，所以需要循环来递归下去。

若要具体问题的代码或者模板代码可以参考algorithm里面的



## BFS

```c++
void BFS(Gragh* G, int start,queue<int>* Q)
{
    int v,w;
    Q->enqueue(start);//事先压入一个进去，用来初始化
    G->setMark(start,VISITED);//设置已经访问
    while(Q->length()!=0)
    {
        v->Q->dequeue();
        Previsit(G,v);
        for(w = G->first(v);w<G->n();w = G->next(v,w))//访问所有子结点
        {
            if(G->getMark(w)==UNVISITED)
            {
                G->setMark(w,VISITED);//设置已经访问  
                Q->enqueue(w);
            }

        }
    }
}
```

思想就是将未访问的结点进入队列，然后不断拓展子节点。就像一圈一圈地扩展一样。

上述为伪代码。主要是思想的体现，核心为队列，扩展结点，访问设置



## 拓扑排序

```c++
void topsort(Gragh* G)
{
    for(int i=0;i<G->n();i++)//初始化
    {
        G->setMark(i,UNVISITED);
    }
    for(int i=0;i<G->n();i++)
        if(G->getMark(i)==UNVISITED)
            tophelp(G,i);
}

void tophelp(Gragh* G, int v)
{
    G->setMark(v,VISITED);
    for(int w = G->first(v);w<G->n();w = G->next(v,w))
        if(G->getMark(w)==UNVISITED)
            tophelp(G,w);
    print(v);
}
```



```c++
void topsort(Gragh*G, queue<int>*Q)
{
    int count[G->n()]={0};//现在c++支持内置数组初始化可以是一个变量
    for(int v = 0;v<G->n();v++)
        for(int w = G->first(v); w<G->n();w = G->next(v,w))
        {
            count[w]++;//prerequisites的数量
        }
    for(int v = 0;v<G->n();v++)
        if(count[v]==0)
            Q->enqueue(v);//将没有先前条件的结点加入队列
    while(Q->length()!=0)
    {
        int v=Q->dequeue();
        print(v);
        for(int w = G->first(v); w<G->n();w = G->next(v,w))
        {
            count[w]--;
            if(count[w]==0)
                Q->enqueue(w);
        }
    }
}
```



# 单源最短路径

## Dijkstra(贪心)

- 从起点开始，将邻接点的距离临时设置为边的权重
- 选择权重最短的点继续处理，处理这个点的邻接点，如果从这点到它的邻接点的距离比原本设置的距离要短，则更新这个点距离
- 再次选择从第二步的那个点开始权重最短的点，从这个点开始，重复第二步的步骤
- 直到处理完所有的点

利用优先队列或者堆来实现





## 动态规划

定义状态d(A,B):

- A到B的最短距离

状态转移:

- d(S,T) = min{d(S,X)+d(X,T)} X∈{S的邻接点}

forward approach (backward reasoning)

- d(S,T) = min{1+d(A,T),2+d(B,T)}
- 往下求d(A,T),d(B,T)之类的，一直到全部求出

这个用到递归的思想

backward approach (forward reasoning)

- 先求d(S,A),d(S,B)  S的邻接点
- 再求d(S,C),d(S,D) 邻接点的邻接点
- 类似BFS，向外扩展

这个可以用滑动窗口来解





# 最小生成树

## Prim

两个点的集合，一个集合是已经选择的点，一个集合是没有选择的点

- 从任意一点开始，选择离这个点最近的点，将这两个点加入`已选择集合`
- 在剩下的点中分别找出与已经选择的点的边，选择最短的边并且满足不形成环，将这个点加入集合
- 重复第二步，直到点全被选完

**可以使用优先队列实现**

```c++
#include<iostream>
#include<time.h>
#include<vector>
#include<algorithm>
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
    bool operator<(const edge& other)
    {
        return this->weight < other.weight;
    }
};
struct node
{
    char value;//顶点 
    vector<edge> point_to;
};


const int total=6;
int sum=0;
bool visited[total] = {false};
void prim(vector<node>& nodes)
{
    vector<char> result;
    visited[0] = true;
    result.push_back(nodes[0].value);
    for(int i =0;i<total;i++)
    {
        vector<edge>temp;
        for(int k=0;k<result.size();k++)
        {
            int size = nodes[result[k]-'A'].point_to.size();
            for(int j=0;j<size;j++)
            {
                temp.push_back(nodes[result[k]-'A'].point_to[j]);
            }

        }
        sort(temp.begin(),temp.end());//这一步可以使用优先队列

        for(int j = 0;j<temp.size();j++)
        {
            if(visited[temp[j].value-'A']==false)
            {
                //cout<<visited[temp[j].value-'A']<<endl;
                result.push_back(temp[j].value);
                sum+=temp[j].weight;
                visited[temp[j].value-'A'] = true;
                break;
            }
        }
    }

    for(int i=0;i<result.size();i++)
    {
        cout<<result[i]<<" ";
    }
    cout<<endl;
    cout<<sum<<endl;
}
int main()
{
    vector<node> nodes(total);
    for(int i =0;i<nodes.size();i++)
    {
        nodes[i].value='A'+i;
        int n=0;
        cin>>n;
        for(int j=0;j<n;j++)
        {
            char val;
            int weight;
            cin>>val>>weight;
            nodes[i].point_to.push_back(edge(val,weight));
        }
        //cout<<nodes[i].value<<endl;
    }
    clock_t start=clock();
    prim(nodes);
    clock_t end=clock();
    cout<<end-start<<endl;

}
```



## Kruskal

个人理解：每次都是选择权重最小的两个边来形成树，过程中不断检查是否形成环。

标准：

- 把顶点分成|V|个等价类。

- 然后按照权重的大小顺序处理每一条边。

- 如果一条边连接属于**两个不同等价类**的顶点，那么就把这个边加入到MST中，并把这两类合并成一个等价类。（如果一条边连接属于**两个同等价类**的顶点，跳过）

- 反复执行这个过程，直到最后只有一个等价类。

等价类和合并参考**并查集**

