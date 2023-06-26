CXX = g++
TAR = a
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))#路径替换
FLAGS = -c -Wall

$(TAR): $(OBJ)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(FLAGS) $< -o $@
	

.PHONY: clean #防止当前目录下有一个clean文件 伪目标
clean:
	rm *.o