#include<iostream>
using namespace std;

void QuickSort(int *nums,int start,int end)
{
    if(start!=end)
    {
        int i=start,j=end,exchange;
        int stand=nums[i];
        for(i,j;i!=j;)
        {
            if(nums[j]<stand)
            {
                exchange=nums[i];
                nums[i]=nums[j];
                 nums[j]=exchange;
                --j;
            }
            if(nums[i]>stand)
            {
                exchange=nums[j];
                nums[j]=nums[i];
                nums[i]=exchange;
                ++i;
            }
        }
        int k=i;
        QuickSort(nums,start,k);
        QuickSort(nums,k+1,end);
    }
}

int main()
{
    int nums[5];
    for(int i=0;i<5;++i)
    {
        cin>>nums[i];
    }
    QuickSort(nums,0,4);
}