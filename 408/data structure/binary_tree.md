## 预备单词

ancestor 祖先

descendant 子孙

## 定义

结点**M**的深度就是从根节点到M的路径长度。

树的高度等于最深结点+1。任何深度为d的结点的层数都是d。根节点为0，深度为0.

满二叉树的每一个结点或者是一个分支结点，恰好有两个非空子节点；或者是叶节点。

完全二叉树从根节点起每一层从左到右填充。一颗高度为d的完全二叉树除了d-1层以外，每一层都是满的



## 遍历

==三种遍历只是visit的位置不同==

```c++
void preorder(BinNode<elem>* root)
{
    if(root==null) return;
    visit(root);//输出信息
    preorder(root->left);
    preorder(root->right);
}
void preorder(BinNode<elem>* root)
{
    if(root==null) return;
    visit(root);//输出信息
    preorder(root->left);
    preorder(root->right);
}
void preorder(BinNode<elem>* root)
{
    if(root==null) return;
    visit(root);//输出信息
    preorder(root->left);
    preorder(root->right);
}
```



二叉树的数据结构

```c++
class node
{
    Key k;
    Val v;
    node* left;
    node* right;
}
```



## 使用数组实现完全二叉树（堆）

- parent(r) = (r-1)/2向下取整
- leftChild(r)=2r+1
- rightChild(r)=2r+2
- leftSibling(r)=r-1 r为偶数
- rightSibing(r)=r+1 r为奇数



## 二叉搜索树

**左边小于，右边大于等于**

```c++
#include<iostream>
using namespace std;

template<class elem>
class BinNode
{
    //get function
    virtual elem& val()=0;

    //set function
    virtual void setVal(const elem&)=0;
    virtual void setLeft(BinNode*)=0;
    virtual void setRight(BinNode*)=0;
    virtual bool isLeaf()=0;
};

template<class elem>
class BinNodePtr : public BinNode<elem>
{
    elem it;
    BinNodePtr* lc;
    BinNodePtr* rc;
    public:
    BinNodePtr()
    {
        lc=rc=NULL;
    }
    BinNodePtr(elem& e,BinNodePtr l = NULL,BinNodePtr r = NULL)
    {
        it=e;
        lc=l;
        rc=r;
    }
    elem& val()
    {
        return it;
    }

    inline BinNodePtr<elem>* left()
    {
        return lc;
    }
    inline BinNodePtr<elem>* right()
    {
        return rc;
    }
    void setVal(const elem& e)
    {
        it =e;
    }
    void setLeft(BinNode<elem>*l)
    {
        lc = (BinNodePtr<elem>*)l;
    }
    void setRight(BinNode<elem>*r)
    {
        rc = (BinNodePtr<elem>*)r;
    }

    bool isLeaf()
    {
        return (lc==NULL&&rc==NULL);
    }
    void visit(BinNodePtr<elem>* subroot)
    {
        cout<<subroot->val()<<endl;
    }

    void preorder(BinNodePtr<elem>* subroot)
    {
        if(subroot==NULL) return;
        visit(subroot);
        preorder(subroot->left())
        preorder(subroot->right())
    }

    void postorder(BinNodePtr<elem>* subroot)
    {
        if(subroot==NULL) return;
        postorder(subroot->left());
        postorder(subroot->right());
        visit(subroot);
    }
    void inorder(BinNodePtr<elem>* subroot)
    {
        if(subroot==NULL) return;
        inorder(subroot->left());
        vist(subroot);
        inorder(subroot->right());
    }

    int findHeight(BinNodePtr<elem>* subroot)
    {
        if(subroot==NULL) return 0;
        return 1+max(findHeight(subroot->left()),findHeight(sub->right()));
    }

    bool find(BinNodePtr<elem>*subroot,elem key)
    {
        if(subroot==NULL) return false;
        if(subroot->val()==key) return true;
        return find(subroot->left(),key)||find(subroot->right(),key);
    }
};

template<class elem>
class BST
{
    BinNodePtr<elem>* root;
    int nodecount;
    BinNodePtr<elem>* removeHelp(BinNodePtr<elem>*subroot,const elem&e, BinNodePtr<elem>*t)
    {
        if(subroot==NULL) return NULL;
        else if(subroot->val()>e)
        {
            subroot->setLeft(removeHelp(subroot->left(),e,t));
        }
        else if(subroot->val()<e)
        {
            subroot->setRight(removeHelp(subroot->right(),e,t));
        }
        else
        {   
            BinNodePtr<elem>* temp;
            t = subroot;
            if(subroot->left()==NULL)
            {
                subroot = subroot->right();
            }else if(subroot->right==NULL)
            {
                subroot = subroot->left();
            }
            else{
                subroot->setRight(deletemin(subroot->right(),temp));
                elem te = subroot->val();
                subroot->setVal(temp->val());
                temp->setVal(te);
                t = temp;
            }
        }
        return subroot;
    }
    BinNodePtr<elem>* insertHelp(BinNodePtr<elem>*node,const elem&e)
    {
        //类似从头开始
        if(node==NULL)
        return new BinNodePtr<elem>(e,NULL,NULL);
        if(node->val()>e)
        {
            node->setLeft(insertHelp(node->left(),e));
        }
        else
        {
            node->setRight(insertHelp(node->right(),e));
        }
        return node;
    }
    bool insert(const elem&e)
    {
        root = insertHelp(root,e);
        nodecount++;
        return true;
    }
    bool findHelp(BinNodePtr<elem>*subroot,const elem&e)
    {
        if(subroot==NULL) return false;
        if(subroot->val()==e) return true;
        if(e<subroot->val())
        {
            return findHelp(subroot,e);
        }
        if(e>subroot->val())
        {
            return findHelp(subroot,e);
        }
        
    }
    BinNodePtr<elem>* deletemin(BinNodePtr<elem>*subroot,BinNodePtr<elem>*& min)
    {
        if(subroot->left()==NULL)
        {
            min = subroot;
            return subroot->right();
        }
        else{
            subroot->setLeft(deletemin(subroot->left(),min));
            return subroot;
        }
    }
    public:
    BST()
    {
        root=NULL;
        nodecount=0;
    }


};

//heap
template<typename E>
class heap
{
    E* Heap;
    int maxSize;
    int n;

    //Help function to put elements in its correct position
    void shiftdowm(int pos)
    {
        while(!isLeaf(pos))
        {
            //记录左右child的pos
            int j = leftchild(pos);
            int rc = rightchild(pos);
            //保证j是最大的
            //找到child中最大的那个
            if(rc<n&&Heap[rc]>Heap[j])
            {
                j=rc;
            }
            if(Heap[pos]>Heap[j]) return;//符合maxheap
            //不符合maxheap交换自己和child的值
            swap(Heap,pos,j);
            pos = j;//往下移
        }
    }

    public:
    heap(E* h, int num.int max)
    {
        Heap=h;
        n=num;
        maxSize = max;
        buildHeap();
    }
    int size()const
    {
        return n;
    }
    bool isLeaf(int pos)
    {
        return (pos>=n/2)&&(pos<n);
    }
    int leftchild(int pos) const
    {
        return 2*pos+1;
    }
    int rightchild(int pos)const
    {
        return 2*pos+2;
    }
    int parent(int pos)const
    {   
        return (pos-1)/2;
    }
    void buildHeap()
    {
        for(int i =n/2-1;i>=0;i--)
        {
            shiftdowm(i);
        }
    }
    bool insert(const E& val)
    {
        if(n>=maxSize) return false;
        int curr = n++;
        Heap[curr] = val;
        while((curr!=0)&&Heap[curr]>Heap[parent(curr)])
        {
            swap(Heap,curr,parent(curr));
            curr = parent(curr);
        }
        return true;
    }
    bool removemax(E& e)
    {   
        if(n==0) return false;//empty
        swap(Heap,0,--n);
        if(n!=0)
        shiftdowm(0);
        e = Heap[n];
        return true;
    }
    bool remove(int pos, E& e)
    {
        bool flag = false;
        if(pos<0||pos>n) return false;
        swap(Heap,pos,--n);
        //可能交换过后该节点比上一个节点的值大
        while((pos!=0)&&Heap[pos]>Heap[parent(pos)])
        {
            swap(Heap,pos,parent(pos));
            pos = parent(pos);
            flag = true;
        }
        //因为进入循环后就可以保证堆的结构（因为原来就是稳定的结构）
        //未进入循环可能会出现child比自己大的情况
        if(!flag) shiftdowm(pos);
        e = Heap[n];
        return true;
    }
};
template<typename elem>
void swap(elem* e,int a,int b)
{
    elem temp = e[a];
    e[b] = e[a];
    e[a] = temp;
}

//优先队列就是根节点的操作，我们只关心根节点的值，因为最大或者最小
template<class elem>
class FreqPair
{
    elem it;
    int freq;
    public:
    FreqPair(const elem& e, int f)
    {
        it =e;
        freq = f;
    }
    int weight()
    {
        return freq;
    }
    elem& val()
    {
        return it;
    }
    
};


```

find的伪代码

```c++
elem findhelp(node* root,const elem&e)
{
    if(root==null) return null;//can not find
    if(root->val==e) return root->val;
    if(root->val>e)
    {
        findhelp(root->left,e);
	}
    else
    {
        findhelp(root->right,e);
    }
}
```

删除首先要找到目标的位置，然后进行删除

删除不是直接delete而是改变指针的指向

删除最小值

- 一直往左找，找到后记为S，把S的父节点指向S的指针指向S的右节点

删除任意一个

- 无子节点，将R的父节点指向它的指针指向NULL
- 有一个，将R的父节点指向R的子节点
- 有两个，用右子树最小值替换R的值

# heap

## max heap

任意一个结点储存的值都大于或者等于任意一个子节点储存的值

## min heap

任意一个结点储存的值都小于或者等于任意一个子节点储存的值

插入：

```c++
    bool insert(const E& val)
    {
        if(n>=maxSize) return false;
        int curr = n++;
        Heap[curr] = val;
        while((curr!=0)&&Heap[curr]>Heap[parent(curr)])
        {
            swap(Heap,curr,parent(curr));
            curr = parent(curr);
        }
        return true;
    }
```



删除：

- 删除最值，将最值与最后一个值相交换，并且减少n，使用户访问不到最后一个元素，同时还要保持堆的结构
- 删除任意一个值，删除原理都是交换，主要是要保持堆的结构

```c++
    bool removemax(E& e)
    {   
        if(n==0) return false;//empty
        swap(Heap,0,--n);
        if(n!=0)
        shiftdowm(0);
        e = Heap[n];
        return true;
    }
    bool remove(int pos, E& e)
    {
        bool flag = false;
        if(pos<0||pos>n) return false;
        swap(Heap,pos,--n);
        //可能交换过后该节点比上一个节点的值大
        while((pos!=0)&&Heap[pos]>Heap[parent(pos)])
        {
            swap(Heap,pos,parent(pos));
            pos = parent(pos);
            flag = true;
        }
        //因为进入循环后就可以保证堆的结构（因为原来就是稳定的结构）
        //未进入循环可能会出现child比自己大的情况
        if(!flag) shiftdowm(pos);
        e = Heap[n];
        return true;
    }
```

# Huffman code

贪心：每次都是选择最小的两个。