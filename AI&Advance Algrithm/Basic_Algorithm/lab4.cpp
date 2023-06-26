#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<time.h>
#include<climits>
using namespace std;

struct edge
{
    char value;//被指的顶点
    int weight;//边长
    edge(char value, int weight)
    {
        this->value = value;
        this->weight = weight;
    }
};
struct node
{
    char value;//顶点 
    vector<edge> next;
};

int ans = INT_MAX;
char start='0';
char nex;
const char e='6';
vector<char>path;
void dfs(char s,int sum,vector<node>& nodes)
{
    path.push_back(s); 
    if(sum>ans) return;

    if(s==e)
    {
        for(int i=0;i<path.size();i++)
        {
            cout<<path[i]<<" ";
        }
        cout<<endl;
        cout<<"cost: "<<sum<<endl;
        if(sum<ans) ans=sum;
        
    }
    for(int i=0;i<nodes[s-'0'].next.size();i++)
    {
        //sum+=nodes[start-'0'].next[i].weight;
        nex = nodes[s-'0'].next[i].value;
        //path.push_back(nex);
        dfs(nex,sum+nodes[s-'0'].next[i].weight,nodes);
        path.pop_back();
    }

}

int main()
{
    int total=7;
    vector<node>nodes(total);
    for(int i=0;i<total;i++)
    {
        nodes[i].value='0'+i;
        int n;
        cin>>n;
        for(int j=0;j<n;j++)
        {
            char val;
            int weight;
            cin>>val>>weight;
            nodes[i].next.push_back(edge(val,weight));
        }
    }
    //cout<<"finish"<<endl;
    clock_t start=clock();
    dfs('0',0,nodes);
    clock_t end = clock();

    cout<<"time: "<<end - start<<endl;
    cout<<"min cost: "<<ans;
}
/**
 * 3
1 2
2 3
3 4
2
2 3
4 2
2
4 2
5 2
1
5 2
2
6 3
5 1
1
6 5
0
*/