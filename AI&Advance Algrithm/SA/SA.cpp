#include<iostream>
#include<cmath>
#include<random>
#include<time.h>
using namespace std;

const int N = 8;
const int GOAL = N*(N-1)/2;
string x="";
void init()
{
    string temp="";
    for(int j=0;j<N;j++)
    {
        temp+=to_string(rand()%N+1);
    }
    x = temp;
}

string getNew()
{
    string temp="";
    for(int j=0;j<N;j++)
    {
        temp+=to_string(rand()%N+1);
    }
    return temp;
}
int evaluate(string x)
{
    int fitness=0;
    for(int j=0;j<N;j++)
    {
        for(int k=j+1;k<N;k++)
        {
            if(x[j]!=x[k] && abs(j-k)!=abs(x[k]-x[j]))
            fitness++;
        }
    }
    return fitness;
}

int main()
{
    double T = INT32_MAX;//initial temperature
    int T_min = 1e-12;//the lowest temperature
    double alpha = 0.02;//the ratio of descence
    int iterations = 100;//the number of iterations
    srand(unsigned(time(0)));
    
    init();

    while(T>T_min)
    {
        for(int i = 0;i<iterations;i++)
        {
            string newX = getNew();
            int delta = evaluate(newX)-evaluate(x);
            if(delta>=0)
            {
                x = newX;
            }
            else
            {
                if((rand()%10000)/10000.0<exp(double(delta/T)))
                x = newX;
            }
        }
        T*=alpha;
       // cout<<T<<endl;
    }
    cout<<x<<endl;
    cout<<evaluate(x)<<endl;

}