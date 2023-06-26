#include<iostream>

class Singleton
{
public:
    static Singleton& get()//only instance of this class
    {
        return s_instance;
    }
    void func();
private:
    Singleton(){}
    static Singleton s_instance;
};
Singleton Singleton::s_instance;

int main()
{
    Singleton& singleton = Singleton::get();
    
}