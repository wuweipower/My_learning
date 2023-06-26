#include<iostream>
#include<time.h>
#include<vector>
#include<algorithm>
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
    bool operator<(const edge& other)
    {
        return this->weight < other.weight;
    }
};
struct node
{
    char value;//顶点 
    vector<edge> point_to;
};


const int total=6;
int sum=0;
bool visited[total] = {false};
void prim(vector<node>& nodes)
{
    vector<char> result;
    visited[0] = true;
    result.push_back(nodes[0].value);
    for(int i =0;i<total;i++)
    {
        vector<edge>temp;
        for(int k=0;k<result.size();k++)
        {
            int size = nodes[result[k]-'A'].point_to.size();
            for(int j=0;j<size;j++)
            {
                temp.push_back(nodes[result[k]-'A'].point_to[j]);
            }

        }
        sort(temp.begin(),temp.end());

        for(int j = 0;j<temp.size();j++)
        {
            if(visited[temp[j].value-'A']==false)
            {
                //cout<<visited[temp[j].value-'A']<<endl;
                result.push_back(temp[j].value);
                sum+=temp[j].weight;
                visited[temp[j].value-'A'] = true;
                break;
            }
        }
    }

    for(int i=0;i<result.size();i++)
    {
        cout<<result[i]<<" ";
    }
    cout<<endl;
    cout<<sum<<endl;
}
int main()
{
    vector<node> nodes(total);
    for(int i =0;i<nodes.size();i++)
    {
        nodes[i].value='A'+i;
        int n=0;
        cin>>n;
        for(int j=0;j<n;j++)
        {
            char val;
            int weight;
            cin>>val>>weight;
            nodes[i].point_to.push_back(edge(val,weight));
        }
        //cout<<nodes[i].value<<endl;
    }
    clock_t start=clock();
    prim(nodes);
    clock_t end=clock();
    cout<<end-start<<endl;

}