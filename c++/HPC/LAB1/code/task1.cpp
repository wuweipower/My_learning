#include<iostream>
#include<omp.h>
#include<random>
#include<time.h>
#include<vector>
using namespace std;

void print_mat(const vector<vector<int>>& mat)
{
    for(int i =0;i<mat.size();i++)
    {
        for(int j=0;j<mat[0].size();j++)
        {
            cout<<mat[i][j]<<" ";
        }
        cout<<endl;
    }
}

void init_mat(vector<vector<int>>& mat,int mod)
{
    for(int i =0;i<mat.size();i++)
    {
        for (int j=0;j<mat[0].size();j++)
        {
            mat[i][j] = rand()%mod;
        }
    }
}

void sequence_mul(vector<vector<int>>& mat_a,vector<vector<int>>& mat_b,vector<vector<int>>& mat_c)
{
    for(int i=0;i<mat_a.size();i++)
    {
        for(int j=0;j<mat_b[0].size();j++)
        {
            int temp=0;
            for(int k=0;k<mat_a[0].size();k++)
            {
                temp+=mat_a[i][k]*mat_b[k][j];
            }
            mat_c[i][j] = temp;
        }
    }
}

void parallel_mul(vector<vector<int>>& mat_a,vector<vector<int>>& mat_b,vector<vector<int>>& mat_c,int t)
{
    #pragma omp parallel for num_threads(t)
    for(int i=0;i<mat_a.size();i++)
    {
        for(int j=0;j<mat_b[0].size();j++)
        {
            int temp = 0;
            for(int k=0;k<mat_a[0].size();k++)
            {
                temp+=mat_a[i][k]*mat_b[k][j];
            }
            mat_c[i][j] = temp;
        }
    }
}

int main()
{
    srand((unsigned int)time(0));
    // double p[100];
    // for(int k=1;k<=100;k++)
    // {
    //     int row_a=10*k,col_a=10*k;
    //     int row_b=10*k,col_b=10*k;
    //     int row_c = row_a,col_c = col_b;

    //     vector<vector<int>>mat_a(row_a,vector<int>(col_a));
    //     vector<vector<int>>mat_b(row_b,vector<int>(col_b));
    //     vector<vector<int>>mat_c(row_c,vector<int>(col_b));

    //     //init
    //     srand((unsigned int)time(0));

    //     init_mat(mat_a);
    //     init_mat(mat_b);
    //     for(int i =0;i<row_c;i++)
    //     {
    //         for(int j =0;j<col_c;j++)
    //         {
    //             mat_c[i][j] = 0;
    //         }
    //     }

    //     //sequence
    //     double start,end;
    //     // start = omp_get_wtime();
    //     // sequence_mul(mat_a,mat_b,mat_c);
    //     // end = omp_get_wtime();
    //     // cout<<"sequential time is "<<end-start<<endl;
    //     // p[k-1] = end-start;
    //     //print_mat(mat_c);

    //     // double time[12];
    //     // for(int i =1;i<=12;i++)
    //     // {
    //     //     start = omp_get_wtime();
    //     //     parallel_mul(mat_a,mat_b,mat_c,i);
    //     //     end = omp_get_wtime();
    //     //     cout<<"parallel: "<<end-start<<endl;
    //     //     time[i-1]=end-start;
    //     //     //print_mat(mat_c);  
    //     // }
    //     // for(int i =0;i<12;i++)
    //     // {
    //     //     cout<<time[i]<<" ";
    //     // }

    //     //parallel
    //     start = omp_get_wtime();
    //     parallel_mul(mat_a,mat_b,mat_c,12);
    //     end = omp_get_wtime();
    //     cout<<"parallel: "<<end-start<<endl;
    //     p[k-1] =end-start; 
    //     //print_mat(mat_c);
    // }

    // for(int i =0;i<100;i++)
    // {
    //     cout<<p[i]<<",";
    // }

    int row_a=100,col_a=100;
    int row_b=100,col_b=100;
    int row_c = row_a,col_c = col_b;

    vector<vector<int>>mat_a(row_a,vector<int>(col_a));
    vector<vector<int>>mat_b(row_b,vector<int>(col_b));
    vector<vector<int>>mat_c(row_c,vector<int>(col_b));

    for(int i =1;i<=100;i++)
    {
        init_mat(mat_a,i*10);
        init_mat(mat_b,i*10);
        double start,end;
        start = omp_get_wtime();
        parallel_mul(mat_a,mat_b,mat_c,12);
        end = omp_get_wtime();
        cout<<end -start<<",";
    }
    cout<<endl;
}