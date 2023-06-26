## List(线性表)

## Array based list(顺序表)

code

```c++
#include<bits/stdc++.h>
using namespace std;
template<class elem> class List
{
  public:

  virtual bool insert(const elem& e ) = 0;

  virtual bool append(const elem& e) = 0;

};
template<class elem>
class AList : public List<elem>
{
  private:
  int maxSize;
  int fence;
  int listSize;
  elem* elemList;

  public:
  AList(int size = 300)
  {
    maxSize = size;
    listSize = fence = 0;
    elemList = new elem[maxSize];
  }

  ~AList()
  {
    delete[] elemList;
  }

  bool insert(const elem& e)//当前位置插入，从当前位置一直往后移动复杂度为O(n)
  {
    if(listSize==maxSize)
    {
      return false;
    }
    for(int i= listSize; i>fence;i--)
    {
      elemList[i] =  elemList[i-1];
    }
    elemList[fence] = e;
    listSize++;
    return true;
  }

  bool append(const elem& e)
  {
    if(listSize==maxSize)
    {
      return false;
    }
    elemList[listSize] = e;
    listSize++;
    return true;
  }
  bool remove(elem& e)//后面往前面移动复杂度为O(n)
  {
    if(listSize==0)
    return false;
    e = elemList[fence];
    for(int i=fence;i<listSize-1;i++)
    {
      elemList[i]= elemList[i+1];
    }
    return true;
  }

  elem operator [](int index)
  {
    return elemList[index];
  }
};
int main()
{
  AList<int> a;
  int c;
  a.append(47);
  a.insert(89);
  a.remove(c);
  cout<<a[0]<<"  "<<a[1]<<endl;  
  cout<<c<<endl;
  cout<<"hello"<<endl;
}
```

## Like list(链表)

code

```c++
#include<iostream>
#include<cmath>
using namespace std;
#include<stack>
template<class elem> class List
{
  public:

  virtual bool insert() = 0;

};

template<class elem>
class Link
{
    public:
    elem element;
    Link* next;
    
    Link(const elem& e,Link* nextVal = NULL )
    {
        element = e;
        next = nextVal;
    }
    Link(Link* nextVal=NULL)
    {
        next = nextVal;
    }
};

template<class elem>
class LList : public List<elem>
{
    public:
    Link<elem>* fence;
    Link<elem>* head;
    Link<elem>* tail;
    int size;
    void init()
    {
        fence = head = tail = new Link<elem>;
        size = 0;
    }
    void clear()
    {
        while(head->next!=NULL)
        {
            Link<elem> * temp = head->next;
            head->next = temp->next;
            delete temp;
        }
        delete head;
    }

    bool insert()
    {
        int total;
        cin>>total;
        for(int i =0;i<total;i++)
        {
            int num;
            cin>>num;
            fence->next = new Link<elem>(num);
            fence = fence->next;
            size++;
        }
        return true;
    }

    void show() const
    {
        Link<elem>* temp = head;
        while(temp->next!=NULL)
        {
            cout<<temp->next->element;
            temp = temp->next;
            if(temp->next!=NULL)
            {
                cout<<" ";
            }
        }
        cout<<endl;
    }
    void rshow()//反序输出
    {
        stack<elem>s;
        Link<elem>* temp =head;
        while(temp->next!=NULL)
        {
            s.push(temp->next->element);
            temp = temp->next;
        }
        while(!s.empty())
        {
            cout<<s.top()<<" ";
            s.pop();
        }
        cout<<endl;
    }
    
    bool remove(elem  it)
    {
        Link<elem>* temp = head;
        while(temp->next!=NULL)
        {
            if(temp->next->element==it)
            {
                Link<elem>* d = temp->next;
                temp->next = d->next;
                delete d;
                size--;
            }
            else
            temp = temp->next;
        }

        return 1;

    }

};
int main()
{
    LList<int> L;
    L.init();
    //string order;
    for(int i =0;i<30;i++)
    {
        cout<<pow(2,i)<<",";
    }
    return 0;
}
```

```c++
void prev()
{
    if(curr==head) return;
    Link<elem>* temp = head;
    while(temp->next!=curr) temp = temp->next;//找到curr的前一个
    curr = temp;//将curr移动到前一个
}
```

```c++
elem remove()
{
    //删除的是当前的下一个
	elem it = curr->next->val;
    Link<elem>* ltemp = curr->next;//把这个被删的node先拿出来
    if(tail==curr->next) tail = curr;
    curr->next = curr->next->next;
    delete ltemp;
    cnt--;
    return it;
}
```

```c++
//insert的写法
void insert(const elem&e)
{
    curr->next = new Link<elem>(e,curr->next);//新插入的是在curr和curr->next之间
    											//在创建的同时这个新建的指向curr->next，然后更新curr->next
    if(tail==curr) tail = curr->next;//更新tail
    cnt++;
}
```

==删除的时候要用delete把内存返回给储存器==

## Freelist

可利用空间表存放当前那些不用的线性表结点。

- 从一个链表中删除的结点就可以放在可利用空间表的首端。
- 当插入的时候，先检查是否有可以用的线性表结点，如无，则new

**new**

```c++
void* operator new(size_t)
{
    if(freelist==null) return ::new Link;//c++标准版new
    Link<elem>* temp = freelist;
    freelist = freelist->next;
    return temp;
}
```

**delete**

```c++
void operator delete(void* ptr)
{
    ((Link<elem>*)ptr)->next = freelist;
    freelist = (link<elem>*)ptr;
}
```

freelist是个static变量，被所有对象利用

## Double list

code

```c++
#include<bits/stdc++.h>
using namespace std;

template<class elem>class Link
{
    public:
    elem element;
    Link<elem>* prev;
    Link<elem>* next;

    Link(const elem& e, Link<elem>* prev=NULL,Link<elem>* next = NULL)
    {
        element = e;
        this->next = next;
        this->prev= prev;
    }

    Link(Link<elem>* prev=NULL,Link<elem>* next = NULL)
    {
        this->next = next;
        this->prev= prev;
    }
};

template<class elem>
class LList 
{
    
    Link<elem>* fence;
    Link<elem>* head;
    Link<elem>* tail;

    int rightCount;
    int leftCount;

    public:
    void init()
    {
        fence = tail = head = new Link<elem>;
        rightCount = leftCount = 0;
    }

    bool insert(const elem& e)
    {
        fence->next = new Link<elem>(e,fence,fence->next);
        if(fence->next->next!=NULL)//已经有两个节点及以上的情况
        {
            fence->next->next->prev = fence->next;
        }
        if(fence == tail)
        {
            tail = fence->next;
        }
        rightCount++;
        return true;
    }
	
    void print()const
    {
        Link<elem>*temp = head;
        while(temp->next!=NULL)
        {
            cout<<temp->next->element<<" ";
            temp = temp->next;
        }
    }
};
int main()
{
    LList<int> a;
    a.init();
    a.insert(12);
    a.insert(24);
    a.insert(44);
    a.print();
}
```

```c++
elem remove()
{
    if(curr->next==tail)
    {
        return null;
    }
    elem it = curr->next->element;
    Link<elem>* ltemp = curr->next;
    curr->next->next->prev = curr;
    curr->next = curr->next->next;
    delete ltmep;
    cnt--;
    return it;
}//这是书上给的模板
```

## Stack

code

array based

```c++
void push(const elem& e)
{
    listArray[top++] = e;
}
elem pop()
{
    return listArray[--top];
}
elem topVal()
{
    return listArray[top-1];
}
```

list based

```c++
void push(const elem& e)
{
	top = new Link<elem>(e,top);
    size++;
}

elem pop()
{
	elem it = top->element;
    Link<elem>* ltemp = top->next;
    delete top;
    top = ltemp;
    return it;
}
```





## Queue队列

problem：当enqueue和dequeue操作多了以后，前面的空间会浪费

|      |      | 1(front) | 12   | 2(rear) |      |      |
| ---- | ---- | -------- | ---- | ------- | ---- | ---- |

solution: 环形列表使用**取模运算**



## 字典
