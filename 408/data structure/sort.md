# 插入排序

```c++
template<typename E, typename Comp>
void sort(E A[], int n)
{
    for(int i =1;i<n;i++)
    {
        for(int j=i;j>0 && Comp::prior(A[j], A[j-1]);j--)
            swap(A,j,j-1);
	}
}
```

具体实现版

```c++
void sort(int num[],int n)
{
    for(int i=1;i<n;i++)
    {
        for(int j=i; j>0 && num[j]<num[j-1];j--)//后面一个小于当前这个
            swap(num[j],num[j-1]);
    }
}
```

算法讲解：

- 本质就是不断扩展数组的排序长度，将下一个元素根据比较插入到合适的位置。
- 因为插入前的部分数组已经排好序了，所以只需要比较和交换。



# 冒泡排序

```c++
void sort(int num[],int n)
{
    for(int i=0;i<n-1;i++)
    {
        for(int j=i;j<n-i-1;j++)//冒出最大值，然后缩小排序范围
        {
            if(num[j]>num[j+1])//把大的，放在后面
                swap(num[j],num[j+1]);
        }
    }
}
```

算法讲解：

- 不断两个两个比较，将最值放在某一边（最左或最右）
- 不断缩小数组排序的范围



# 选择排序

```c++
void sort(int num[],int n)
{
    for(int i=0;i<n-1;i++)
    {
        int lowindex = i;
        for(int j=i+1;j<n;j++)
        {
            if(num[j]<num[lowindex])
            {
                lowindex = j;
			}
		}
        swap(num[i],num[lowindex]);
    }
}
```

算法讲解：

- 每次都选最值来交换



# shell排序

```c++
template<typename E, typename Comp>
void inssort(E A[],int n,int incr)//插入排序 incr是步长
{
    for(int i=incr;i<n;i++)
    {
        for(int j=i;j>=incr && Comp::prior(A[j],A[j-incr]);j-=incr)
            swap(A,j,j-incr);
	}
}
template<typename E, typename Comp>
void shellSort(E A[],int n)
{
    for(int i=n/2;i>2;i/=2)
    {
        for(int j=0;j<i;j++)
        {
            inssort<E,Comp>(&A[j],n-j,i)
        }
    }
    inssort<E,Comp>(A,n,1);
}
```

算法讲解：

- 排序子序列
- 最后选择排序整个数组

这样处理其实就是优化选择排序，减少swap的次数，也就是减少逆序的出现

这个算法很难分析，复杂度为O(n^1.5^)



# 归并排序

分治法

```c++
template<typename E,typename Comp>
void mergeSort(E A[],E temp[],int left,int right)
{
    if(right-left<= THRESHOLD)//长度很小直接插入排序
    {
        inssort<E,Comp>(&A[left],right-left);
        return;
    }
    int i,j,k,mid=(left+right)/2;
    mergeSort<E,Comp>(A,temp,left,mid);
    mergeSort<E,Comp>(A,temp,mid+1,right);
    //下面的两个for循环时复制操作
    for(i=mid;i>=left;i--)
        temp[i]=A[i];
    for(j=1;j<=right-mid;j++)
        temp[right-j+1]=A[j+mid];
    //Merge
    for(i=left;j=right,k=left;)
}
```

算法讲解

- 把整个数组不断分解，分解为简单的情况，然后排序
- 将两个排好序的字数组合并



# 快速排序



```c++
int data[1000];

int partition(int left, int right)
{
    int i=left;
    int temp = data[right];//把尾部的元素作为基准
    for(int j=left;j<right;j++)
    {
        if(data[j]<temp)
        {
            swap[data[j],data[i]];
            i++;
        }
    }
    swap(data[i],data[right]);
    return i;//返回基准数的位置
}

void qsort(int left,int right)
{
    if(left<right)
    {
        int i=partition(left,right);
        qsort(left,i-1);
        qsort(i+1,right);
    }
}
```

算法解析：

- 分治法

partition的步骤

- 尾部t作为基准数，i指向比 t 小的左部分，j指向比 t 的右部分
- 若data[j]<data[t]，交换data[j] 和 data[i] 然后i++，j++
- 若data[j]>=data[t],j++
- 最后交换data[i], data[t]。i指向基准数的当前位置



# 堆排序

利用最大堆或者最小堆来排序，就是不断的remove最值



# 分配排序和基数排序

