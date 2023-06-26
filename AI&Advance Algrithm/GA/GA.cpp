#include<iostream>
#include<vector>
#include<string>
#include<random>
#include<time.h>
using namespace std;

/*
    initial populatin
    fitness function
    selection
    crossover
    mutation
*/
struct Individual
{
    string geneticCode;//基因码
    int fitness;//适应度
    double end;//概率的右边边界
    Individual(string gc)
    {
        this->geneticCode = gc;
    }
    Individual(string gc, int fit)
    {
        this->geneticCode = gc;
        this->fitness = fit;
    }
};
const int N = 8;//N-queens problem
const int NUM = 20;//the number of individuals
const int GOAL = (N-1)*N/2;
vector<Individual> indivs;
vector<Individual> offsprings;
void init()
{
    for(int i = 0;i<NUM;i++)
    {
        string temp="";
        for(int j=0;j<N;j++)
        {
            temp+=to_string(rand()%N+1);
        }
        indivs.push_back(Individual(temp));
    }
}

void fit()
{
    int sum = 0;
    for(int i=0;i<indivs.size();i++)
    {
        string temp = indivs[i].geneticCode;
        int fitness=0;
        for(int j=0;j<N;j++)
        {
            for(int k=j+1;k<N;k++)
            {
                if(temp[j]!=temp[k] && abs(j-k)!=abs(temp[k]-temp[j]))
                fitness++;
            }
        }
        indivs[i].fitness = fitness;
        sum+=fitness;
    }
    int count=0;
    for(int i=0;i<indivs.size();i++)
    {
        indivs[i].end = double(indivs[i].fitness+count)/sum;
        count+=indivs[i].fitness;
        //cout<<indivs[i].end<<endl;
    }
}
void check()
{
    fit();
    for(int i = 0;i<indivs.size();i++)
    {
        //cout<<indivs[i].fitness<<endl;
        if(indivs[i].fitness==GOAL)
        {
            cout<<indivs[i].geneticCode<<endl;
            exit(1);
        }
    }
}
void crossover(Individual& a, Individual& b)
{
    int random = rand()%N+1;

    string t1 = a.geneticCode;
    string t2 = b.geneticCode;
    string temp = t1.substr(0,random);
    
    string newA = t2.substr(0,random)+t1.erase(0,random);
    string newB = temp + t2.erase(0,random);

    offsprings.push_back(Individual(newA));
    offsprings.push_back(Individual(newB));
}
void select()
{
    for(int i=0;i<NUM/2;i++)
    {
        double random = (rand()%1000)/1000.0;
        int father = 0;
        for(int j=0;j<NUM;j++)
        {
            if(random<indivs[j].end)
            {
                father=j;
                break;
            }
        }

        random = (rand()%1000)/1000.0;
        int mother = 0;
        for(int j=0;j<NUM;j++)
        {
            if(random<indivs[j].end)
            {
                mother=j;
                break;
            }
        }

        if(father!=mother)
        {
            crossover(indivs[father],indivs[mother]);
        }

        else
        i--;
    }
}


void mutate()
{
    for(int i = 0;i<offsprings.size();i++)
    {
        int random = rand()%1000;
        if(random<10)//百分之一的突变率
        {
            random = rand()%N;//选择突变的位置
            offsprings[i].geneticCode[random] = (rand()%N+1)+'0';//随机突变
        }
    }

    indivs = offsprings;
    offsprings.clear();
}
int main()
{
    srand(unsigned(time(0)));
    init();
    while(1)
    {
        fit();
        select();
        mutate();
        check();
    }
}