#include<iostream>
#include<string>
using std::string;
/**
 * 1.意图：为其他对象提供一种代理以控制对这个对象的访问
 * 2.主要解决：直接访问对象时带来的问题
 * 3.实例：windows快捷方式，买火车票去代售点而不是火车站去买
 * 4.和适配器模式的区别：适配器模式主要改变所考虑对象的接口
 * 5.和装饰器模式的区别：装饰器时为了增强功能，而代理模式是为了加以控制
*/

class Image
{
public:
    void display();
};

class RealImage : public Image
{
private:
    string filename;
public:
    RealImage(string filename)
    {
        this->filename = filename;
        load(filename);
    }
    RealImage(){
        this->filename = "";
    }
    void display()
    {
        std::cout<<"Display: "<<filename<<"\n";
    }
    string getFilename()
    {
        return this->filename;
    }
    void load(string filename)
    {
        std::cout<<"loading"<<"\n";    
    }

};

class ProxyImage : public Image
{
private:
    RealImage realImage;
    string filename;
public:
    ProxyImage(string filename)
    {
        this->filename = filename;
    }

    void display()
    {
        if(this->realImage.getFilename()=="")
        {
            realImage = RealImage(filename);
        }
        realImage.display();
    }

};
int main()
{
    ProxyImage image = ProxyImage("test");
    image.display();

    image.display();

}