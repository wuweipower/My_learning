#include<mpi.h>
#include<time.h>
#include<random>
#include<iostream>

using namespace std;
//compile order mpicc mpi.cpp -o mpi
//execute order mpirun -np 4 ./mpi
//compile order mpicxx mpi.cpp -o mpi

const int mod=100;

void print_mat(int* mat,int rows,int cols)
{
    for(int i =0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            printf("%d ",mat[i*rows+j]);
        }
        printf("\n");
    }
}
void init_mat(int* mat,int rows, int cols)
{
    srand((unsigned)time(NULL));
    for(int i=0;i<rows*cols;i++)
    {
        mat[i]= rand()%mod;
    }
    //print_mat(mat,rows,cols);
}
void mat_mul_one_thread(int * mat_a,int* mat_b, int * res,int m, int p, int n)
{
    for(int i=0;i<m;i++)
    {
        for(int j =0;j<n;j++)
        {
            int temp;
            for(int k =0;k<p;k++)
            {
                temp+=mat_a[i*p+k]*mat_b[k*n+j];
            }
            res[i*n+j] = temp;
        }
    }
}
int main(int argc, char* argv[])
{

    int *mat_a;
    int *mat_b;
    int *mat_c;
    int m=2000,p=2000,n=2000; //mat_a(m*p), mat_b(p*n) mat_c(m*n)

    int *block_a,*block_c;

    double start,end;
    int myrank,procs;
    MPI_Status status;
    
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&procs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);

    if(procs==1)//serial
    {
        mat_a = new int[m*p];
        mat_b = new int[p*n];
        mat_c = new int[m*n];
        
        init_mat(mat_a,m,p);
        init_mat(mat_b,p,n);
        //init_mat(mat_c,m,n);

        start = MPI_Wtime();
        mat_mul_one_thread(mat_a,mat_b,mat_c,m,p,n);
        end = MPI_Wtime();

        cout<<"Time: "<<end-start<<endl;
        // print_mat(mat_a,m,p);
        // print_mat(mat_b,p,n);
        // cout<<"matc"<<endl;
        // print_mat(mat_c,m,n);
        delete[] mat_a;
        delete[] mat_b;
        delete[] mat_c;
    }
    else//parallel
    {
        int block_m = m/procs;//分多少块给一个进程

        block_a = new int[block_m*p];
        mat_b= new int[p*n];//共用mat_b
        block_c = new int [block_m*n];

        if(myrank==0)
        {
            mat_a = new int[m*p];
            mat_c = new int[m*n];

            init_mat(mat_a,m,p);
            init_mat(mat_b,p,n);
        }
        MPI_Barrier(MPI_COMM_WORLD);

        start = MPI_Wtime();
        /*分配数据*/
        //将矩阵mat_a 一对多分别发送对应块数
        MPI_Scatter(mat_a,block_m*p,MPI_INT,block_a,block_m*p,MPI_INT,0,MPI_COMM_WORLD);
        //共用矩阵mat_b
        MPI_Bcast(mat_b,p*n,MPI_INT,0,MPI_COMM_WORLD);

        /*并行计算mat_c的各个分块*/
        mat_mul_one_thread(block_a,mat_b,block_c,block_m,p,n);
        MPI_Barrier(MPI_COMM_WORLD);

        MPI_Gather(block_c,block_m*n,MPI_INT,mat_c,block_m*n,MPI_INT,0,MPI_COMM_WORLD);

        int remain_start = block_m*procs;

        if(myrank==0 && remain_start<m)
        {
            int remain_rows = m - remain_start;
            mat_mul_one_thread(mat_a+remain_start*p,mat_b,mat_c+remain_start*n,remain_rows,p,n);

        }
        delete[] block_a;
        delete[] mat_b;
        delete[] block_c;

        end = MPI_Wtime();
        if(myrank==0)
        {
            delete[] mat_a;
            delete[] mat_c;
            cout<<myrank<<" "<<"Time: "<<end-start<<endl;
        }
        
        //MPI_Barrier(MPI_COMM_WORLD);
        
    }


    MPI_Finalize();

}