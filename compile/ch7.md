# Runtime Environment

is the structure of the target computer's register and memory that serves to manage memory and maintain the information needed to guide execution process

- register and memory allocation is performed during execution
- designing the runtime environment during compilation can maintain an environment only indirectly
- it must generate code to perform the necessary maintennance operations during program execution

RAM can be divided into Code area(固定住了在程序执行前)，Data area

**Data area：**

**global/static area** 

- 这里的数据是在内存中固定了的并且优先于执行，包含了程序的全局和静态数据
- 在一个area单独申请一部分内存

**stack area 动态的**

- 用于last in first out的数据

**heap area 动态的**

- 动态申请内存 如c++ new delete;c malloc free

| code area                                                  |
| ---------------------------------------------------------- |
| global/static area                                         |
| stack                                                      |
| free space  (栈区会向这个地方扩展，堆区也会向这个地方扩展) |
| heap                                                       |



## fully static environment

所有data都是静态的，内存在执行的时候是固定的

- 没有pointer 或者动态申请
- 程序不能递归
- 例子：FORTRAN77

## stack-based environment

data space is allocated at the top of the stack as(当) a new procedure call is made and deallocated again when the call exits

非常常见

- 可以递归
- 局部变量会申请内存在每一次调用
- C, pascal



## fully dynamic environment

data space is allocated and deallocated 在执行期间的任意时间，data space is dynamically freed only when all references to it have disappeared(garbage collection)

堆管理和全动态环境：程序员手动申请和销毁内存来堆管理，若是全动态环境，堆会被自动管理

## parameter pass

- 在调用procedure的时候要申请内存

- an activation record(活动记录) must contain the following sections in minimum

  | space for parameters                                         |
  | ------------------------------------------------------------ |
  | space for bookkeeping(记账) information, including return address |
  | space for local data                                         |
  | space for local temporaries                                  |

In a procedure call, parameters correspond to locations in the activation record, which are filled in with the arguments by the caller, prior to jumping to the code for the called procedure.

### pass by value

- arguments are evaluated at the time of the call, and their values are stored in locations corresponding to parameters in the activation record
- during the execution of the called procedure, code will access these eventual(最后的) value directly

参数会被看作初始化的局部变量，对它们的改变不会改变其他非局部变量的改变

### pass by reference 

传location of the variable(参数的地址)

- during the execution of the called procedure, the compiler must turn local access to a reference parameter into indirect access, 因为传的值实际是实参的**地址**。示意图中表示值的部分填上地址

对参数的改变会影响原本的。

形参会为实参的alias（没有拷贝）

### pass by value-result

和传引用差不多，但是不会有alias

会拷贝一份实参的值，然后又将改变的值返回原来的实参，因此实参也是会被改变的



### pass by name

delayed evaluation, inline function(内联函数)

将函数的内容拷贝到主函数里面，将形参替换成实参