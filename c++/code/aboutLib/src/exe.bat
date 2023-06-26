g++ -c Engine.cpp
ar crv e.lib Engine.o
g++ main.cpp e.lib -o a
a.exe