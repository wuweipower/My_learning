# **GNU的GCC/G++**

首先我们可以将GCC/G++看成一个整体，不存在GCC专门编译C语言，G++专门编译C++语言这种分别，因为编程语言发展至今是非常复杂的，编译器同样也是。我们将两者都看成GCC，GCC支持C、C++和Fortran语言。

而GCC(GNU Compiler Collection，GNU编译器集合)，就是GNU运动的代表性成果，它的初衷是为GNU的自由系统开发完整的编译器。

**所以，在Linux甚至Windows上各种涉及开发环境配置，源码编译的地方，都离不开gcc和g++。**



# **Windows的Mingw/MSVC**

MinGW(Minimalist GNUfor Windows)，它是一个可自由使用和自由发布的Windows特定头文件和使用GNU工具集导入库的集合，允许你在Windows平台生成本地的Windows程序而不需要第三方C运行时(C Runtime)库。

运行时库：支持程序运行的基本函数的集合，一般是静态库lib或动态库dll。

而MSVC，就是上文所说的第三方C运行时库：由微软开发的VC运行时库，被Visual Studio IDE所集成。所以我们使用VS时会附带MSVC编译器。

所以可以看到啦，MinGW和MSVC都是Windows C/C++语言编译支持，配置环境时遇到两者择其一即可。

# **LLVM的clang/clang++**

有了前文，对LLVM与clang不用解释应该也知道了。

LLVM是构架编译器(compiler)的框架系统，以C++编写而成，用于优化以任意程序语言编写的程序的编译时间(compile-time)、链接时间(link-time)、运行时间(run-time)以及空闲时间(idle-time)，对开发者保持开放，并兼容已有脚本。

LLVM计划启动于2000年，最初由美国UIUC大学的Chris Lattner博士主持开展。2006年Chris Lattner加盟Apple Inc.并致力于LLVM在Apple开发体系中的应用。Apple也是LLVM计划的主要资助者。

目前LLVM已经被苹果IOS开发工具、Xilinx Vivado、Facebook、Google等各大公司采用。

# **Make/CMake**

但make依然有很多不足，比如

1. make对于类unix系统是通用的，但对windows系统并不友好(不能跨平台)
2. make语法简单，也就导致了它功能的限制
3. 不同编译器的语法规则不同，编写的makefile语法如果适合GCC则不适合MSVC

所以，CMake就应运而生啦。

**CMake是比Make更高一层的工具**，Make是编写对应编译器的makefile从而实现编译，而CMake是写一份独立的CmakeList.txt文件，然后该文件会根据当前系统环境选择适合的构建生成器（如VS或者make），然后将CmakeList.txt翻译为适合的文件，再进一步调用系统编译器进行项目构建。



# Make

make就是一个命令管理工具

比如我写一个批处理文件 windows环境下是bat

a.bat

里面就是一些可以在cmd敲的命令

```bash
echo hello
pip install numpy
```

在cmd窗口就可以执行



也就是在命令前加上一个@，这个符号就是告诉make，在运行的时候这一行命令不显示出来。

```
@echo hello#命令就不会显示
```

时间戳来看文件是否改变





```makefile
Cxx = g++ #就是简单的变量及赋值
FLAGS = -Wall

.PHONY: clean
clean:
	rm *.o
```

```
make -f 文件名 如果你的文件不是Makefile
```

version 1

```makefile
hello: a.cpp b.cpp#依赖
	g++ -o hello a.cpp b.cpp #注意用tab
```

version 2

```makefile
CXX = g++
TAR = hello
OBJ = a.o b.o
$(TAR): $(OBJ)
	$(CXX) -o $(TAR) $(OBJ)

a.o: a.cpp
	$(CXX) -c a.cpp
b.o: b.cpp
	$(CXX) -c b.cpp
```



version 3

```makefile
CXX = g++
TAR = hello
OBJ = a.o b.o
Flags = -c -Wall
$(TAR): $(OBJ)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(Flags) $< -o $@
	
.PHONY: clean #防止当前目录下有一个clean文件
clean:
	rm *.o
```



version 4

```makefile
CXX = g++
TAR = hello
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))#路径替换
FLAGS = -c -Wall

$(TAR): $(OBJ)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(Flags) $< -o $@
	
.PHONY: clean #防止当前目录下有一个clean文件 伪目标
clean:
	rm *.o
```

grammar

```
$@ 表示规则中的目标
$< 表示规则中第一个依赖条件
$^ 表示规则中所有的依赖条件
如果想采⽤ echo 输出‘$’，则必需⽤两个连着的‘$’。还有就是，$@对于 Shell 也有特殊的意思，我们需要在“$$@”之前再加⼀个脱字符‘\’。
 ifdef、ifeq、ifndef 和 ifneq 四种语句形式
```









# CMake

