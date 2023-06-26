```c++
int i ;
void f(int x)
{
    cout<<x<<i;
}
int main()
{
    i=3;
    f(i++);//输出34
}
```



```
int a=11
int a={11}
int a{11}
```



```c++
int a[5]={1};//a[0]=1,其他为0
double number[10];
sizeof(number);//10*8

int* ptr = &v[0];//假设为3000
ptr+=2;//结果为3000+2*4
```

任何类型除void*可以赋值给void\* 反之不行

```
b[3]==*(bptr+3)==*(b+3)

int b[5];
int *bptr = b;
b+=3;//error 它试图用指针修改数组名的值
```

```
int n[]={1,2};

//下面两个等价
int a(const int *v);
int a(const int v[]);
```



```
for(int a : items);
for(int &a : items);
```



```
char color[]="blue";
char color[]={'b','l','u','e','\0'};
```



&不能作用于常量或者产生临时值的表达式

如果提供的初始化值的数目少于元素个数，剩下的元素会被初始化为0.如果多于则报错



```
int j=10,i;
i=(j++,j+100,j+888);
cout<<i;//输出899
先计算j++,在j+100,计算完后 j只是加了1，即j=11.最后j+888 = 899赋值给i
```



```
enum e{a,b};
默认'a'==1
可以指定
enum e{a=2,b};
a和b不需要声明，随便写
```



# class

```c++
#ifndef TIME_H
#define TIME_H
//这些预处理指令防止重include


#endif


```

成员函数不管定义在哪，作用域都是类。

如果成员函数在类内定义，则编译器会尝试将其设置为inline函数，提高性能。inline可以认为是直接将函数的内容写进主函数，这样就可以减少函数栈的调用，从而减小开销。

对象只包含数据成员

编译器会制造一个类的成员函数的copy，所有对象共享这个copy

file scope：在所有函数或者类之外的。比如全局变量，函数定义，原型。

block scope：从声明开始到}。比如局部变量，参数，静态局部变量

访问同名的全局变量使用 ::var

重载的返回类型一样，参数列表不一样

```
int a();
int a(int b)
```

函数签名=函数名加参数列表

析构函数只能为 ~className() 必须为public

析构函数本身不会真正释放对象内存，只是做termination house keeping。内存也行会被新对象使用

external:在全局变量中，引用声明使用extern关键字且不进行初始化，否则声明为定义，导致分配空间：

```
int x; // definition x is 0
extern int y; //y defined in elsewhere
extern char c = ‘g’; // definition ,c is initialized
```

C++提供了两种变量声明。一种是定义声明（defining declaration）简称定义，它给变量分配内存空间；另外一种是引用声明（referencing declaration）简称为声明，它不给变量分配空间，因为它引用已有变量。

全局对象构造最先，构造最后

static对象构造发生的时间在执行到他那里的时候，析构函数与全局一样，在程序结束的时候调用。

```c++
class A{
    char ch;
    public:
    A(char ch)
    {
        this->ch = ch;
        cout<<ch<<" constructor"<<endl;
    }
    ~A()
    {
        cout<<ch <<" destructor"<<endl;
    }
};

A a('a');
void func()
{
    static A b('b');
}
int main()
{
    func();
}
```

结果

```
a constructor
b constructor
b destructor
a destructor
```



const对象只能调用const方法

不能把构造和析构声明为const



成员初始化器的顺序不重要，按照成员对象在类中声明的顺序执行

若一个成员对象未在成员初始化中初始化，会自动其默认构造函数，若该成员对象没有默认构造函数则会报错

在初始化列表中初始化可以避免双重初始化

```c++
    char ch;
    B b;
    public:
    A(char ch):b(B('a'))
    {       
        this->ch = ch;     
    }
```

若为

```
A(char ch)
    {       
        b=B('a');
        this->ch = ch;     
    }
```

结果为

```
default
B
```

friend function是授予关系，不是索取。

```c++
类里面 friend void f(A a);
类外面
void f(A a)
{

    cout<<a.ch<<endl;//ch 为私有
}
```

friend function 可以放在任意位置，可重载。

static成员函数不能用this指针，只能访问static member function 和 static data member

static 可以节省空间，只会被初始化一次

static的基本类型变量默认为0.

static类内声明，类外初始化。

在类外初始化的时候不要加static

可以使用::访问static



this指针不是对象的一部分。

this指针会作用默认隐式参数在对象的非静态函数。

long的大小由机器和编译器决定。

```c++
A a;
sizeof(a);//会输出a的成员数据对象的大小 
		  //注意不是简单的加起来，因为要内存对齐，会以最大字节数的变量为基准
```

如果是下面这样

```c++
class B{
    int a;//4个字节
    long long n;//8个字节
};
class A{
    private:
        B c;
        char b;//一个字节
};

sizeof(A)等于24 相当于把B的成员数据拿过来了
```



```c++
class C{};
sizeof(C) 等于1
```



static const可以在类内初始化

数组定义时可以用{}初始化

```
int a[10]={1,2};
```



for循环里面不断创建对象，会不断构造 析构

```c++
    for(int i =0;i<5;i++)
    {
        A a('a');
    }

```

this 指针的类型取决于对象的类型



若以成员函数的方式重载运算符，那么这个必须是非static，因为他们必须由该类的对象调用并作用在这个对象上。

重载运算符

- 优先级不能改
- 操作数个数不变
- 不能创造新的运算符
- 作用的基本类型方式不能改变 比如 + 不能重载为减号的意义
- 关系运算符如+ +=必须单独重载
- 重载[], (), ->, +=, -=, *=, /=时重载函数必须为类成员
- 二元运算符可以重载为一个非static成员函数或者两个函数的非成员函数，一般为友元。 
- 重载一元运算符：不带参的非static成员函数，或者带一个参数的非成员函数

```c++
//类内
bool operator <(const string & other)
{
}

//类外
bool operator < (const string a, const string b)
{
    
}
```

前置++和后置++的重载

返回类型为引用是为了链式

```
前置
Date & operator ++()
{
	add;
	return *this;
}
后置
Date & operator ++(int)
{
	temp = this->val;
	add;
	return temp;
}
```



delete ptr: 先调用析构函数，然后回收内存

不能delete不是new的内存

不是重复delete同一处，解决方法就是设置为nullptr

动态数组

```c++
int *p = new int[10];
delete[] p;

//二维
int *m = new int *[rows];
for(int i =0;i<rows;i++)
{
    m[i] = new int[cols]
}
```



解决浅拷贝中会出现重复delete同一处的问题，使用深拷贝

重写拷贝构造函数，重新new，把东西复制过来

```
A(A a)
{
	for 
}
```

可以delete不要的函数

```
void func() = delete;
```

为了支持初始化列表使用initializer_list<>



编译器可以区别

```
int& operator[](int);//可修改
int operator[](int)const;//只是返回
```



转换运算符

```
MyClass::operator char*()const;
使用的时候static_cast<char*>(s);
MyClass::operator othertype()const;
使用的时候static_cast<othertype>(s);
```



任何单参构造器都可以用来执行隐式转换，即构造安徽念书接受的类型会转换为定义了该构造函数的类的对象。

当左操作不是对象的类型时，可能需要由一个非成员函数来重载。

a+b,b+a a和b不同类型，需要重载两次

new会调用构造函数



防止对象被copy可以：重载=运算和重载拷贝构造函数设置为private。或者delete这两个函数



```
    Complex cl(1, 2);
    //下面两个等价
    Complex c2(c1);
    Complex c2 = c1;
```

```
    Complex(const Complex & c){//copy constructor
        real = c.real; imag = c.imag;
        cout<<"Copy Constructor called"<<endl ;
    }
```



```
    #include<iostream>
    using namespace std;
    class A{
    public:
        A(){};
        A(A & a){
            cout<<"Copy constructor called"<<endl;
        }
    };
    void Func(A a){ }
    int main(){
        A a;
        Func(a);
        return 0;
    }
    Copy constructor called
```

拷贝构造函数必须是按引用传递，否则会无限递归，原因是按值传递的时候会执行拷贝函数。

当类对象包含new时，若不为其提供重载=和拷贝构造函数，会造成逻辑错误

构造和析构的顺序

- 最顶层的构造到最底层的构造
- 然后析构反过来

private和protected继承不满足‘是一个’的关系

基类=delete，派生类也会=delete

派生类实例化的时候，会自动调用父类的构造

protected只被派生类使用，其他人不能使用，



父类的构造器和赋值操作不会被继承



多态实现时通过虚函数和动态绑定实现的（在执行期间绑定，迟绑定）

派生类地址给基类指针才能对

downcasting 使基类指针转为派生指针。

虚函数virtual

一旦一个函数是虚函数，那么整个继承链中保持virtual

c++11中在派生类的每一个覆盖函数上使用override会使编译器检查基类是否由一个同名集通参数列表的函数，若无则报错类似java@overrvide



```
//父类中
virtual void func() const ;

//子类中
void func() override;
```



可以通过指向派生类对象的基类指针，指向派生类对象的基类引用



若引用特定对象名和原点成员选择运算符则静态绑定。

这个函数不能再派生类中覆盖。

```
virtual void func() final;
```

防止这个类作为基类

```
class Myclass final{};
```

类有一个或多个虚函数，这个类是抽象类，不能被实例化

```
virtual void func() const=0;这个函数不会有实现
```

```
//如果Bptr是指向A对象的基类指针则会设为A的指针，否则设置为nullptr
dynamic_cast<A*>(Bptr)
```



```
typeid运算符返回一个 type_info类对象的引用，其name()方法返回基于指针的字符串
```

cin标准输入流

cout标准输出流

cerr无缓冲标准错误流

clog无缓冲标准

wchar_t存储unicode

char16_t char32_t unicode



```c++
const char* const word = "agian";
cout<<static_cast<const void*>(word);//输出第一个字符的地址
```

```c++
cout.put('A').put('\n');
cout.put(65);
```

```c++
while((ch=cin.get())!=EOF)
{
    cout.put(ch);
}
```

```
while(cin>>a)
//cin>>a调用流重载void*强制转换运算符函数，操作成功返回非空指针，否则返回空指针
```

插入空字符结束字符数组中输入的字符串

分隔符没有放在字符数组中，而保留再流中

```
char buff[size];//可读size-1个字符
cin.get(buff,size);//默认遇到\n终止
getline()将\n从流中移除
cin.ignore读取并丢弃一定数量的字符，默认为1或遇到指定分隔符时停止。默认EOF
putback将先前用get从输入流中获的字符在放回流中
peek返回输入流中下一个字符，但并不能将它从流中去除
cout.write("ABC",2)//输出AB
gcount返回最近一次输入操作所读取的字符数
fixed:用一般的方式输出浮点数，而不是科学计数法
cout.width
```



```
std::ostream & tab()
{
    
}
```

| 模式标志   | 描述                                                         |
| ---------- | ------------------------------------------------------------ |
| ios::app   | 追加模式。所有写入都追加到文件末尾。                         |
| ios::ate   | 文件打开后定位到文件末尾                                     |
| ios::in    | 打开文件用于读取                                             |
| ios::out   | 打开文件用于写入。                                           |
| ios::trunc | 如果该文件已经存在，其内容将在打开文件之前被截断，即把文件长度设为 0。 |



```c++

#include <fstream>
#include <iostream>
using namespace std;
 
int main ()
{
    
   char data[100];
 
   // 以写模式打开文件
   ofstream outfile;
   outfile.open("afile.dat");
 
   cout << "Writing to the file" << endl;
   cout << "Enter your name: "; 
   cin.getline(data, 100);
 
   // 向文件写入用户输入的数据
   outfile << data << endl;
 
   cout << "Enter your age: "; 
   cin >> data;
   cin.ignore();
   
   // 再次向文件写入用户输入的数据
   outfile << data << endl;
 
   // 关闭打开的文件
   outfile.close();
 
   // 以读模式打开文件
   ifstream infile; 
   infile.open("afile.dat"); 
 
   cout << "Reading from the file" << endl; 
   infile >> data; 
 
   // 在屏幕上写入数据
   cout << data << endl;
   
   // 再次从文件读取数据，并显示它
   infile >> data; 
   cout << data << endl; 
 
   // 关闭打开的文件
   infile.close();
 
   return 0;
}

```



```

// 定位到 fileObject 的第 n 个字节（假设是 ios::beg）
fileObject.seekg( n );
 
// 把文件的读指针从 fileObject 当前位置向后移 n 个字节
fileObject.seekg( n, ios::cur );
 
// 把文件的读指针从 fileObject 末尾往回移 n 个字节
fileObject.seekg( n, ios::end );
 
// 定位到 fileObject 的末尾
fileObject.seekg( 0, ios::end );
```



```
long location = file.tellg()
long location = file.tellp()
```



```
file.write(reinterpret_cast<const char*>(&obj),sizeof(class))
```

string对象没有统一的大小

```c++

#include <iostream>
#include <string>
 
using namespace std;
 
template <typename T>
inline T const& Max (T const& a, T const& b) 
{ 
    return a < b ? b:a; 
} 
int main ()
{
 
    int i = 39;
    int j = 20;
    cout << "Max(i, j): " << Max(i, j) << endl; 
 
    double f1 = 13.5; 
    double f2 = 20.7; 
    cout << "Max(f1, f2): " << Max(f1, f2) << endl; 
 
    string s1 = "Hello"; 
    string s2 = "World"; 
    cout << "Max(s1, s2): " << Max(s1, s2) << endl; 
 
    return 0;
}

```

```c++

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <stdexcept>
 
using namespace std;
 
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
 
int main() 
{ 
    try { 
        Stack<int>         intStack;  // int 类型的栈 
        Stack<string> stringStack;    // string 类型的栈 
 
        // 操作 int 类型的栈 
        intStack.push(7); 
        cout << intStack.top() <<endl; 
 
        // 操作 string 类型的栈 
        stringStack.push("hello"); 
        cout << stringStack.top() << std::endl; 
        stringStack.pop(); 
        stringStack.pop(); 
    } 
    catch (exception const& ex) { 
        cerr << "Exception: " << ex.what() <<endl; 
        return -1;
    } 
}

```



枚举

如果枚举没有初始化, 即省掉"=整型常数"时, 则从第一个标识符开始。

例如，下面的代码定义了一个颜色枚举，变量 c 的类型为 color。最后，c 被赋值为 "blue"。

```
enum color { red, green, blue } c;
c = blue;
```

默认情况下，第一个名称的值为 0，第二个名称的值为 1，第三个名称的值为 2，以此类推。但是，您也可以给名称赋予一个特殊的值，只需要添加一个初始值即可。例如，在下面的枚举中，**green** 的值为 5。

```
enum color { red, green=5, blue };
```

在这里，**blue** 的值为 6，因为默认情况下，每个名称都会比它前面一个名称大 1，但 red 的值依然为 0。



常量转换只能用于转换掉 const 属性，不能改变对象的类型。

```
const int i = 10;
int& r = const_cast<int&>(i); // 常量转换，将const int转换为int
```

重新解释转换将一个数据类型的值重新解释为另一个数据类型的值，通常用于在不同的数据类型之间进行转换。

重新解释转换不进行任何类型检查，因此可能会导致未定义的行为。

```
int i = 10;
float f = reinterpret_cast<float&>(i); // 重新解释将int类型转换为float类型
```





作用域

- **局部作用域**：在函数内部声明的变量具有局部作用域，它们只能在函数内部访问。局部变量在函数每次被调用时被创建，在函数执行完后被销毁。
- **全局作用域**：在所有函数和代码块之外声明的变量具有全局作用域，它们可以被程序中的任何函数访问。全局变量在程序开始时被创建，在程序结束时被销毁。
- **块作用域**：在代码块内部声明的变量具有块作用域，它们只能在代码块内部访问。块作用域变量在代码块每次被执行时被创建，在代码块执行完后被销毁。
- **类作用域**：在类内部声明的变量具有类作用域，它们可以被类的所有成员函数访问。类作用域变量的生命周期与类的生命周期相同。







| 限定符   | 含义                                                         |
| -------- | ------------------------------------------------------------ |
| const    | **const** 定义常量，表示该变量的值不能被修改。。             |
| volatile | 修饰符 **volatile** 告诉该变量的值可能会被程序以外的因素改变，如硬件或其他线程。。 |
| restrict | 由 **restrict** 修饰的指针是唯一一种访问它所指向的对象的方式。只有 C99 增加了新的类型限定符 restrict。 |
| mutable  | 由 **restrict** 表示类中的成员变量可以在 const 成员函数中被修改。 |
| static   | 由 **restrict** 表示变量的存储区域在程序生命周期内都存在，即使超出了变量作用域。 |
| register | 由 **restrict** 建议编译器将变量存储在寄存器中，以提高程序执行速度。 |

## thread_local 存储类

使用 thread_local 说明符声明的变量仅可在它在其上创建的线程上访问。 变量在创建线程时创建，并在销毁线程时销毁。 每个线程都有其自己的变量副本。

thread_local 说明符可以与 static 或 extern 合并。

可以将 thread_local 仅应用于数据声明和定义，thread_local 不能用于函数声明或定义。

以下演示了可以被声明为 thread_local 的变量：

```c++

thread_local int x;  // 命名空间下的全局变量
class X
{
    static thread_local std::string s; // 类的static成员变量
};
static thread_local std::string X::s;  // X::s 是需要定义的
 
void foo()
{
    thread_local std::vector<int> v;  // 本地变量
}

```

**extern** 存储类用于提供一个全局变量的引用，全局变量对所有的程序文件都是可见的。当您使用 'extern' 时，对于无法初始化的变量，会把变量名指向一个之前定义过的存储位置。

当您有多个文件且定义了一个可以在其他文件中使用的全局变量或函数时，可以在其他文件中使用 *extern* 来得到已定义的变量或函数的引用。可以这么理解，*extern* 是用来在另一个文件中声明一个全局变量或函数。

extern 修饰符通常用于当有两个或多个文件共享相同的全局变量或函数的时候
