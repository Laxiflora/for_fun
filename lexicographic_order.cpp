#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

string reverse(string nums , int start , int end){
    string newnums(nums);
    for(int i = start,j=end ; i <= end && j >=start; i++,j--){
        newnums[i] = nums[j];
    }
    return newnums;
}

int ctoi(char ch){
    return (int)ch-'0';
}

string perm(string nums){
    int size = nums.size();
    if(size == 0 || size == 1){
        return nums;
    }
    int p = size-1, q=size-1;
    while(p!=0 && ctoi(nums[p]) <= ctoi(nums[p-1]) ){
        p--;
    }
    if(p==0){
        nums = reverse(nums,0,size-1);
    }
    else if(p==size){     //swap(nums[p],nums[q])
        char temp = nums[p];
        nums[p] = nums[q];
        nums[q] = temp;
    }
    else{
        p--;
        while(ctoi(nums[q]) <= ctoi(nums[p]) ){
            q--;
        }
        char temp = nums[p];
        nums[p] = nums[q];
        nums[q] = temp;
        nums = reverse(nums,p+1,size-1);
    }
    return nums;
}



int main(void){
    string nums;
    cin>>nums;
    cout<<perm(nums)<<endl;
    return 0;
}