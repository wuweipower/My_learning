#include<iostream>
#include<vector>
#include<array>
#include<algorithm>
using namespace std;

struct zl
{
    uint16_t size:2;
    uint32_t a:4;

};

int main()
{
    cout<<sizeof(zl);
}