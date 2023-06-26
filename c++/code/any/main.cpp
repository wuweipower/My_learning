#include<iostream>
#include<any>

//c++17
int main()
{
    std::any data;
    data = 1;
    data = "a";
    
    auto val = std::any_cast<std::string>(data);
}