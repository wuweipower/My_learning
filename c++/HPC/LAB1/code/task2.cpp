#include<iostream>
#include<omp.h>
#include<random>
#include<time.h>
#include<cmath>
#include<vector>
using namespace std;

int f(int x)
{
	int sum = 0;
	int b = x, e = b + x;
	for (int i = b; i <= e; ++i)
		sum += int(sin(double(i)) * 2); // include <cmath> first
	return sum;
}

int serial()
{
    int sum=0;
    for(int i=0;i<=32767;i++)
    {
        sum+=f(i);
    }
    return sum;
}
int parralle()
{
    int sum=0;
    #pragma omp parrallel for
    for(int i=0;i<=32767;i++)
    {
        #pragma omp critical
        sum+=f(i);
    }
    return sum;
}
int parrallel_1()
{
    omp_set_num_threads(10);
    int total=0;
    int sum[10]={0};
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        for(int i =id;i<32760;i+=10)
        {
            sum[id]+=f(i);
        }
    }
    for(int i=0;i<10;i++)
    {
        total+=sum[i];
    }
    for(int i=32760;i<32767;i++)
    {
        total+=f(i);
    }
    return total;
}
int main()
{
    //serial 
    double start,end;
    start = omp_get_wtime();
    cout<<serial()<<endl;
    end = omp_get_wtime();
    cout<<"time for serial is "<<end-start<<endl;

    //parallel
    start = omp_get_wtime();
    cout<<parralle()<<endl;
    end = omp_get_wtime();
    cout<<"time for critical is "<<end-start<<endl;

    start = omp_get_wtime();
    cout<<parrallel_1()<<endl;
    end = omp_get_wtime();
    cout<<"time for parallel is "<<end-start<<endl;
}

