#include<bits/stdc++.h>

using namespace std;

//i左边值小于等于value，右边值比value大
int two_patition(vector<int> & nums, int begin, int end, int value){
    int i = begin - 1, j = begin;

    while(j <= end){
        if(nums[j] <= value){
            swap(nums[j++], nums[++i]);
        }
        else{
            j++;
        }
    }

    return i; 
}

//i左边值比value小，k右边值比value大
int three_patition(vector<int> & nums, int begin, int end, int value){
    int i = begin - 1, j = begin, k = end;

    while(j < k){
        if(nums[j] > value){
            swap(nums[j], nums[--k]);
        }
        else if(nums[j] < value){
            swap(nums[j++], nums[++i]);
        }
        else{
            j++;
        }
    }

    return k;
}

//寻找第k个数
int quickSelect(vector<int> & nums, int begin, int end, int k){
    if(k > end - begin + 1) return -1;
    if(begin == end || k <= 0) return begin;

    int pi = rand() % (end - begin + 1) + begin;
    int pivot = nums[pi];

    swap(nums[pi], nums[end]);
    int i = two_patition(nums, begin, end - 1, pivot);
    swap(nums[end], nums[++i]);

    int len = i - begin + 1;
    if(len == k){
        return i;
    }
    else if(len > k){
        return quickSelect(nums, begin, i - 1, k);
    }
    else{
        return quickSelect(nums, i + 1, end, k - len);
    }
}


int main(int argc, char const *argv[])
{
    /* code */
    vector<int> nums = {1, 5, 1, 1, 6, 4};

    //cout << three_patition(nums, 0, 5, 1) << endl;
    //cout << two_patition(nums, 0, 5, 1) << endl;
    cout << nums[quickSelect(nums, 0, 5, 6)] << endl;

    return 0;
}
