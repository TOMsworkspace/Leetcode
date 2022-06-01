#include<bits/stdc++.h>
using namespace std;

long long gcd_r(long long a,long long b){
    if(b == 0) return a; 
    return gcd_r(b,a%b);
}

long long gcd_i(long long a,long long b){
    if(b == 0) return a;
    while (b != 0)
    {
        int c = b;
        b  = a % b;
        a = c;
        /* code */
    }

    return a;
}

long long lcm(long long a,long long b){
    return a/gcd_r(a,b)*b;
}

int main(){

    int n ;
    cin >> n;
    while(n--){
        int a , b;
        cin >> a >> b;

       // cout << gcd_r(a, b) << " " << gcd_i(a,b) << " " << gcd(a, b) << endl;
    }
    return 0;
}