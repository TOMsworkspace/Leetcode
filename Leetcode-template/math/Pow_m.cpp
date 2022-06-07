#include<bits/stdc++.h>
using namespace std;

#define MOD ((int)7)

//快速幂a^n mod MOD
long long pow_m(long long a, long long n){
    long long res = 1;
    long long tmp = a % MOD;

    while(n){
        if(n & 1){
            res = (res * tmp) % MOD;
        }

        tmp = tmp * tmp % MOD;
        n >>= 1;
    }

    return res;
}

int main(){
    int n;
    while(cin >> n){
        int a, b;
        cin >> a >> b;
        cout << pow_m(a,b) << endl;
    }
    return 0;
}