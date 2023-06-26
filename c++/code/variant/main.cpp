#include<iostream>
#include<variant>
#include<string>
int main()
{
    std::variant<std::string, int> data;
    data = "a";
    std::cout<<std::get<std::string>(data)<<"\n";
    auto* value = std::get_if<std::string>(&data);
    if(value)
    {
        auto v= *value;
    }
    data = 2;
    std::cout<<std::get<int>(data)<<"\n";
    data.index();
}