#include<iostream>
#include<fstream>
#include <csignal>
#include<cmath>
using std::cout;
using std::endl;
int val =  10;
#define ccc
class A{
    public:
    A()
    {
        cout<<"A"<<endl;
    }
    virtual void func() {}
};
class B : public A{
    public:
    B()
    {
        cout<<"B"<<endl;
    }
    void func() 
    {

    }
};
namespace ll ccc
{

};
class Ber
{
private:
    const int a = 11;
    int arrr[a];
};
int main()
{
    int j=10,i;
    i=(j++,j+100,j+888);
    cout<<i;
    enum e{a,b};
    cout<<a;
    
}