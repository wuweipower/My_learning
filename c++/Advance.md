# Exception

```c++

#include <iostream>
using namespace std;
 
double division(int a, int b)
{
   if( b == 0 )
   {
      throw "Division by zero condition!";
   }
   return (a/b);
}
 
int main ()
{
   int x = 50;
   int y = 0;
   double z = 0;
 
   try {
     z = division(x, y);
     cout << z << endl;
   }catch (const char* msg) {
     cerr << msg << endl;
   }
 
   return 0;
}

```



```c++

#include <iostream>
#include <exception>
using namespace std;
 
struct MyException : public exception
{
  const char * what () const throw ()
  {
    return "C++ Exception";
  }
};
 
int main()
{
  try
  {
    throw MyException();
  }
  catch(MyException& e)
  {
    std::cout << "MyException caught" << std::endl;
    std::cout << e.what() << std::endl;
  }
  catch(std::exception& e)
  {
    //其他的错误
  }
}

```







# 动态内存

**malloc()** 函数在 C 语言中就出现了，在 C++ 中仍然存在，但建议尽量不要使用 malloc() 函数。new 与 malloc() 函数相比，其主要的优点是，new 不只是分配了内存，它还创建了对象。其实new里面也有malloc()

二维数组

```c++

#include <iostream>
using namespace std;
 
int main()
{
    int **p;   
    int i,j;   //p[4][8] 
    //开始分配4行8列的二维数据   
    p = new int *[4];
    for(i=0;i<4;i++){
        p[i]=new int [8];
    }
 
    for(i=0; i<4; i++){
        for(j=0; j<8; j++){
            p[i][j] = j*i;
        }
    }   
    //打印数据   
    for(i=0; i<4; i++){
        for(j=0; j<8; j++)     
        {   
            if(j==0) cout<<endl;   
            cout<<p[i][j]<<"\t";   
        }
    }   
    //开始释放申请的堆   
    for(i=0; i<4; i++){
        delete [] p[i];   
    }
    delete [] p;   
    return 0;
}

```



构造与析构

```
int main( )
{
   Box* myBoxArray = new Box[4];
 
   delete [] myBoxArray; // 删除数组
   return 0;
}

结果：
调用构造函数！
调用构造函数！
调用构造函数！
调用构造函数！
调用析构函数！
调用析构函数！
调用析构函数！
调用析构函数！
```



# 命名空间

```c++

#include <iostream>
using namespace std;
 
// 第一个命名空间
namespace first_space{
   void func(){
      cout << "Inside first_space" << endl;
   }
}
// 第二个命名空间
namespace second_space{
   void func(){
      cout << "Inside second_space" << endl;
   }
}
int main ()
{
 
   // 调用第一个命名空间中的函数
   first_space::func();
   
   // 调用第二个命名空间中的函数
   second_space::func(); 
 
   return 0;
}

```

嵌套

```c++

namespace namespace_name1 {
   // 代码声明
   namespace namespace_name2 {
      // 代码声明
   }
}

```

如何使用嵌套

```

// 访问 namespace_name2 中的成员
using namespace namespace_name1::namespace_name2;
 
// 访问 namespace_name1 中的成员
using namespace namespace_name1;
```



# 模板

函数模板

```
template <typename T>
inline T const& Max (T const& a, T const& b) 
{ 
    return a < b ? b:a; 
}
```

类模板

```c++
template <class T>
class Stack { 
  private: 
    vector<T> elems;     // 元素 
 
  public: 
    void push(T const&);  // 入栈
    void pop();               // 出栈
    T top() const;            // 返回栈顶元素
    bool empty() const{       // 如果为空则返回真。
        return elems.empty(); 
    } 
}; 
 
template <class T>
void Stack<T>::push (T const& elem) 
{ 
    // 追加传入元素的副本
    elems.push_back(elem);    
} 
 
template <class T>
void Stack<T>::pop () 
{ 
    if (elems.empty()) { 
        throw out_of_range("Stack<>::pop(): empty stack"); 
    }
    // 删除最后一个元素
    elems.pop_back();         
} 
 
template <class T>
T Stack<T>::top () const 
{ 
    if (elems.empty()) { 
        throw out_of_range("Stack<>::top(): empty stack"); 
    }
    // 返回最后一个元素的副本 
    return elems.back();      
} 
```

```
 Stack<int>         intStack;  // int 类型的栈 
```



# 预处理器

 **#include** 指令。这个宏用于把头文件包含到源文件中。

\#define 预处理指令用于创建符号常量

```
#define MIN(a,b) (a<b ? a : b)
```

您可以只在调试时进行编译，调试开关可以使用一个宏来实现，如下所示：

```c++
#ifdef DEBUG
   cerr <<"Variable x = " << x << endl;
#endif
```

\# 和 ## 预处理运算符在 C++ 和 ANSI/ISO C 中都是可用的

```c++

#include <iostream>
using namespace std;
 
#define MKSTR( x ) #x
 
int main ()
{
    cout << MKSTR(HELLO C++) << endl;//输出字符串
 
    return 0;
}

#include <iostream>
using namespace std;
 
#define concat(a, b) a ## b
int main()
{
   int xy = 100;
   
   cout << concat(x, y);
   return 0;
}

```



# 信号处理

signal

```c++
signal(registered signal, signal handler)
```

signal有SIGINT、SIGABRT、SIGFPE、SIGILL、SIGSEGV、SIGTERM、SIGHUP

raise

```
int raise (signal sig);
```



```c++

#include <iostream>
#include <csignal>
#include <unistd.h>
 
using namespace std;
 
void signalHandler( int signum )
{
    cout << "Interrupt signal (" << signum << ") received.\n";
 
    // 清理并关闭
    // 终止程序 
 
   exit(signum);  
 
}
 
int main ()
{
    int i = 0;
    // 注册信号 SIGINT 和信号处理程序
    signal(SIGINT, signalHandler);  
 
    while(++i){
       cout << "Going to sleep...." << endl;
       if( i == 3 ){
          raise( SIGINT);
       }
       sleep(1);
    }
 
    return 0;
}
```



# 多线程

一下是linux环境

```shell
$ g++ test.cpp -lpthread -o test.o
```



```c++

#include <iostream>
// 必须的头文件
#include <pthread.h>
 
using namespace std;
 
#define NUM_THREADS 5
 
// 线程的运行函数
void* say_hello(void* args)
{
    cout << "Hello Runoob！" << endl;
    return 0;
}
 
int main()
{
    // 定义线程的 id 变量，多个变量使用数组
    pthread_t tids[NUM_THREADS];
    for(int i = 0; i < NUM_THREADS; ++i)
    {
        //参数依次是：创建的线程id，线程参数，调用的函数，传入的函数参数
        int ret = pthread_create(&tids[i], NULL, say_hello, NULL);
        if (ret != 0)
        {
           cout << "pthread_create error: error_code=" << ret << endl;
        }
    }
    //等各个线程退出后，进程才结束，否则进程强制结束了，线程可能还没反应过来；
    pthread_exit(NULL);
}

```

传递参数

最好参数封装成一个struct然后转化指针

```c++

#include <iostream>
#include <cstdlib>
#include <pthread.h>
 
using namespace std;
 
#define NUM_THREADS     5
 
struct thread_data{
   int  thread_id;
   char *message;
};
 
void *PrintHello(void *threadarg)
{
   struct thread_data *my_data;
 
   my_data = (struct thread_data *) threadarg;
 
   cout << "Thread ID : " << my_data->thread_id ;
   cout << " Message : " << my_data->message << endl;
 
   pthread_exit(NULL);
}
 
int main ()
{
   pthread_t threads[NUM_THREADS];
   struct thread_data td[NUM_THREADS];
   int rc;
   int i;
 
   for( i=0; i < NUM_THREADS; i++ ){
      cout <<"main() : creating thread, " << i << endl;
      td[i].thread_id = i;
      td[i].message = (char*)"This is message";
      rc = pthread_create(&threads[i], NULL,
                          PrintHello, (void *)&td[i]);
      if (rc){
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }
   }
   pthread_exit(NULL);
}
```



连接与分离线程

```c++

#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
 
using namespace std;
 
#define NUM_THREADS     5
 
void *wait(void *t)
{
   int i;
   long tid;
 
   tid = (long)t;
 
   sleep(1);
   cout << "Sleeping in thread " << endl;
   cout << "Thread with id : " << tid << "  ...exiting " << endl;
   pthread_exit(NULL);
}
 
int main ()
{
   int rc;
   int i;
   pthread_t threads[NUM_THREADS];
   pthread_attr_t attr;
   void *status;
 
   // 初始化并设置线程为可连接的（joinable）
   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
 
   for( i=0; i < NUM_THREADS; i++ ){
      cout << "main() : creating thread, " << i << endl;
      rc = pthread_create(&threads[i], NULL, wait, (void *)&i );
      if (rc){
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }
   }
 
   // 删除属性，并等待其他线程
   pthread_attr_destroy(&attr);
   for( i=0; i < NUM_THREADS; i++ ){
      rc = pthread_join(threads[i], &status);
      if (rc){
         cout << "Error:unable to join," << rc << endl;
         exit(-1);
      }
      cout << "Main: completed thread id :" << i ;
      cout << "  exiting with status :" << status << endl;
   }
 
   cout << "Main: program exiting." << endl;
   pthread_exit(NULL);
}
```

使用标准库thread

```c++
// 演示多线程的CPP程序
// 使用三个不同的可调用对象
#include <iostream>
#include <thread>
using namespace std;
 
// 一个虚拟函数
void foo(int Z)
{
    for (int i = 0; i < Z; i++) {
        cout << "线程使用函数指针作为可调用参数\n";
    }
}
 
// 可调用对象
class thread_obj {
public:
    void operator()(int x)
    {
        for (int i = 0; i < x; i++)
            cout << "线程使用函数对象作为可调用参数\n";
    }
};
 
int main()
{
    cout << "线程 1 、2 、3 "
         "独立运行" << endl;
 
    // 函数指针
    thread th1(foo, 3);
 
    // 函数对象
    thread th2(thread_obj(), 3);
 
    // 定义 Lambda 表达式
    auto f = [](int x) {
        for (int i = 0; i < x; i++)
            cout << "线程使用 lambda 表达式作为可调用参数\n";
    };
 
    // 线程通过使用 lambda 表达式作为可调用的参数
    thread th3(f, 3);
 
    // 等待线程完成
    // 等待线程 t1 完成
    th1.join();
 
    // 等待线程 t2 完成
    th2.join();
 
    // 等待线程 t3 完成
    th3.join();
 
    return 0;
}
```

