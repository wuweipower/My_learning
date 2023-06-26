#include<iostream>
#include<map>
#include<vector>
#include<random>
#include<time.h>
using namespace std;

void bubbleSort(vector<int>& nums)
{
    for(int i =0;i<nums.size();i++)
    {
        for(int j=i+1;j<nums.size();j++)
        {
            if(nums[j]<nums[i])
            {
                int temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
            }
        }
    }
}

// template<typename T>
// void swap(T& a,T& b)
// {
//     T temp = a;
//     a = b;
//     b = temp;
// }

void selectionSort(vector<int>&nums)
{
    for(int i=0;i<nums.size();i++)
    {
        int minIndex = i;
        for(int j=i+1;j<nums.size();j++)
        {
            if(nums[j]<nums[minIndex])
            {
                minIndex=j;
            }
        }
        if(minIndex!=i)
        {
            swap(nums[minIndex],nums[i]);
        }
    }
}

void quickSort(vector<int>& arr,int begin,int end)
{
    if(begin>end)return;
    int temp = arr[begin];
    int i =begin;
    int j = end;
    while (i != j)
    {
        while(arr[j]>=temp && j>i)
        {
            j--;
        }
        while(arr[i]<temp && j>i)
        {
            i++;
        }
        if(j>i)
        {
            int t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
        }
    }
    arr[begin] = arr[i];
    arr[i] = temp;
    quickSort(arr,begin,i-1);
    quickSort(arr,i+1,end);
}

int main()
{
    int n;
    srand((unsigned int)time(0));
    clock_t start,end;
    cin>>n;
    vector<int>nums;
    for(int i=0;i<n;i++)
    {
        nums.push_back((int)(rand()));
    }
    start = clock();
    quickSort(nums,0,nums.size()-1);
    end = clock();
    cout<<"quick sort: "<<(double)(end-start)<<endl;

    nums.clear();
    for(int i=0;i<n;i++)
    {
        nums.push_back((int)(rand()));
    }
    start = clock();
    bubbleSort(nums);
    end = clock();
    cout<<"bubble Sort: "<<(double)(end-start)<<endl;

    nums.clear();
    for(int i=0;i<n;i++)
    {
        nums.push_back((int)(rand()));
    }
    start = clock();
    selectionSort(nums);
    end = clock();
    cout<<"selection Sort: "<<(double)(end-start)<<endl;
}


