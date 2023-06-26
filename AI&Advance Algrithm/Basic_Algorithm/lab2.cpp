#include<iostream>
#include<vector>
#include<map>
#include<random>
#include<time.h>
#include<algorithm>
#include<cstring>
using namespace std;

//部分背包问题

struct good
{
    float id;
    float weight;
    float profit;
    float ratio;
    float proportion;
};
bool cmp(const good & a, const good &b)
{
    return a.ratio>b.ratio;
}
bool cmp1(const good & a, const good &b)
{
    return a.id<b.id;
}
void greedy(vector<good>&Good,double M )
{
    sort(Good.begin(),Good.end(),cmp);

    for(int i=0;i<Good.size();i++)
    {
        double p = M/Good[i].profit;
        //cout<<p<<endl;
        if(p<=1)
        {
            Good[i].proportion = p;
            M=0;
        }
        else
        {
            Good[i].proportion = 1;
            M -= Good[i].profit;
        }
        //cout<<M<<endl;
    }

}
    int dp[6][51];
//0/1背包问题
void dpTest(vector<good>&g)
{

    memset(dp,0,sizeof(dp));
    for(int i=1;i<5;i++)
    {
        for(int j=0;j<50;j++)
        {
            if(g[i].weight>j)
            {
                dp[i][j] = dp[i-1][j];
            }
            else
            {
                dp[i][j] = max(dp[i-1][j] , dp[i-1][j-(int)g[i].weight]+(int)g[i].profit);
            }
        }
    }
    //cout<<dp[4][49];
}

//Tree Search
//sumV total value; sumC total Capacity
int n=5;
int W = 50;
vector<good> g;
int maxV=0;
void dfs(int index,int sumV,int sumW)
{
    if(index==n)return;
    dfs(index+1,sumV,sumW);
    if(sumW+g[index].weight<=W)
    {
        if(sumV+g[index].profit>maxV)
        maxV = sumV+g[index].profit;
        dfs(index+1,sumV+g[index].profit,sumW+g[index].weight);
    }
}
int main()
{
    int total = 10000;
    clock_t start = clock();
    for(int i=0;i<total;i++)
    {
        srand((unsigned int)time(0));
        for(int i=0;i<n;i++)
        {
            good temp;
            temp.id = i;
            temp.profit = int(rand())%40;
            temp.weight = int(rand())%40;
            temp.ratio = temp.profit/temp.weight;
            g.push_back(temp);
        }
        greedy(g,50);
        // for(int i=0;i<n;i++)
        // {
        //     cout<<g[i].id<<"profit: "<<g[i].profit<<"weight: "<<g[i].weight<<"proportion: "<<g[i].proportion<<endl;
        // }
        g.clear();
    }
    clock_t end = clock();
    cout<<"greedy: "<<end-start<<endl;

     start = clock();
    for(int i=0;i<total;i++)
    {
        srand((unsigned int)time(0));
        for(int i=0;i<n;i++)
        {
            good temp;
            temp.id = i;
            temp.profit = int(rand())%40;
            temp.weight = int(rand())%40;
            temp.ratio = temp.profit/temp.weight;
            g.push_back(temp);
        }
        dfs(0,0,0);
        //cout<<maxV<<endl;
        g.clear();
    }
     end = clock();
    cout<<"dfs: "<<end-start<<endl;

     start = clock();
    for(int i=0;i<total;i++)
    {
        srand((unsigned int)time(0));
        for(int i=0;i<n;i++)
        {
            good temp;
            temp.id = i;
            temp.profit = int(rand())%40;
            temp.weight = int(rand())%40;
            temp.ratio = temp.profit/temp.weight;
            g.push_back(temp);
        }
        dpTest(g);//若要结果，请将注释掉的cout清除注释
        g.clear();
    }
     end = clock();
    cout<<"dp: "<<end-start<<endl;
  
}