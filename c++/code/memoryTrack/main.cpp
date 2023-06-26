#include<iostream>

void* operator new(size_t size)
{
    std::cout<<"allocating "<<size<<"\n";
    return malloc(size);
}

struct Object
{
    int x,y,z;
};

int main()
{
    Object* obj = new Object();
}