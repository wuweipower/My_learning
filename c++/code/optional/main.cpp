#include<iostream>
#include<fstream>
#include<string>
using std::string;
using std::cout;
#include<optional>

std::optional<string> read(const string& filepath)
{
    std::ifstream stream(filepath);
    if(stream)
    {
        stream.close();
        string res;
        return res;
    }
    return {};
}
int main()
{
    std::optional<string> data = read("data.txt");
    string val = data.value_or("NOT present");
    cout<<val<<"\n";
    if(data.has_value())
    {
        cout<<"read successfully \n";
    }
    else
    {
        cout<<"error\n";
    }
}
