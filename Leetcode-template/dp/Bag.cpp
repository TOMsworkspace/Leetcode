//背包
#include<bits/stdc++.h>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXLEN 10000
int dp[MAXLEN];
int nValue, nKind;

// 0-1 背包，代价为 cost, 获得的价值为 weight
void ZeroOnePack(int cost, int weight)
{
    for (int i = nValue; i >= cost; i--)
        dp[i] = max(dp[i], dp[i - cost] + weight);
}

//完全背包，代价为 cost, 获得的价值为 weight
void CompletePack(int cost, int weight)
{
    for (int i = cost; i <= nValue; i++)
        dp[i] = max(dp[i], dp[i - cost] + weight);
}

//多重背包
void MultiplePack(int cost, int weight, int amount)
{
    if (cost * amount >= nValue)
        CompletePack(cost, weight);
    else
    {
        int k = 1;
        while (k < amount)
        {
            ZeroOnePack(k * cost, k * weight);
            amount -= k;
            k <<= 1;
        }
        ZeroOnePack(amount * cost, amount * weight); //这个不要忘记了，经常掉了
    }
}

//分组背包：

/*
for k = 1 to K
    for v = V to 0
        for item i in group k
            F[v] = maxF[v],F[v-Ci]+Wi
*/

int main(){

    vector<int> weights = {1, 3, 2, 5, 2, 4};
    vector<int> costs = {2, 1, 3, 4, 1, 1};

    nValue = 10, nKind = 6;

    for(int i = 0; i < 6; i++){
        //ZeroOnePack(costs[i], weights[i]);
        CompletePack(costs[i], weights[i]);
    }

    for(int i = 1; i <= 10; i++){
        cout << dp[i] << " ";
    }

    cout << endl;

    return 0;
}   
