//组合数快速求模模板
#include<iostream>
#include<bits/stdc++.h>

using namespace std;
#define mod ((int)1e9 + 7)
//1000000007是一个质数

//阶乘

long long Fac(long long n){
    long long res = 1;
    if(n <= 1)
        return n; 
    for(int i = 2; i <= n; ++i)
        res = (res * i) % mod;
    return res;
}

//快速幂a^n mod MOD
long long pow_m(long long a, long long n){
    long long res = 1;
    long long tmp = a % mod;

    while(n){
        if(n & 1){
            res = (res * tmp) % mod;
        }

        tmp = tmp * tmp % mod;
        n >>= 1;
    }

    return res;
}


//Multiplicative inverse 乘法逆元
//1、扩展欧几里得算法
//******************************
//返回 d=gcd(a,b); 和对应于等式 ax+by=d 中的 x,y
long long extend_gcd(long long a,long long b,long long &x,long long &y){
    if(a==0&&b==0) return -1;//无最大公约数
    if(b==0){ 
        x=1;
        y=0;
        return a;
    }
    long long d=extend_gcd(b,a%b,y,x);
    y -= a/b*x;
    return d;
}

//********* 求逆元 *******************
//ax = 1(mod n)
long long mod_reverse(long long a,long long n){
    long long x,y;
    long long d=extend_gcd(a,n,x,y);
    if(d==1) return (x%n+n)%n;
    else return -1;
}

//简洁写法
//注意：这个只能求 a < m 的情况，而且必须保证 a 和 m 互质
//求 ax = 1( mod m) 的 x 值，就是逆元 (0<a<m)
long long inv(long long a,long long m){
    if(a == 1)return 1;
    return inv(m%a,m)*( m - m/a)%m;
}

//利用欧拉函数，费马小定理
//费马小定理：假如p是质数，且gcd(a,p)=1，那么 a^(p-1)≡1（mod p）
//所以a*a^(p-2)≡1（mod p）
//那a^(p-2)就是a的乘法逆元
//mod 为素数, 而且 a 和 m 互质
long long inv(long long a)//为素数mod
{
    return pow_m(a,mod - 2);
}


//用乘法逆元和快速幂求组合数

// 当我们要求（a / b） mod p的值，且 a 很大，无法直接求得a / b的值时，我们就要用到乘法逆元。
// 满足 b * k ≡ 1 (mod p) 的 k 的值就是 b 关于 p 的乘法逆元。
// 我们可以通过求 b 关于 p 的乘法逆元 k，将 a 乘上 k 再模 p，即 (a * k) mod p。其结果与(a / b) mod p等价。
// 证:
// 因为 b * k ≡ 1 (mod p)
// 则有 b * k = p* x+1
// 得到 k = (p * x + 1) / b
// 将 k 代入(a * k) mod p
// 得到：
// (a * (p * x + 1) / b) mod p
// =((a * p * x) / b + a / b) mod p
// =[((a * p * x) / b) mod p +(a / b)] mod p
// =[(p * (a * x) / b) mod p +(a / b)] mod p
// =(0 + (a / b)) mod p
// = (a/b) mod p


//组合数公式：
//约定f（a）代表a的阶乘， C(m,n) = f(m)/(f(n)*f(m-n));
//f(m)/(f(n) * f(m-n))%mod =（f(m)/f(n)）%mod * (1/f(m-n)）%mod
//=f(m) * pow_m(f(m-n),mod-2) % mod* pow_m(f(n),mod-2) % mod

//inv(f(m - n), mod) = f(m - n)^(mod - 2);
//inv(f(n), mod) = f(n)^(mod - 2);

long long C(long long n , long long k){
    return ((Fac(n) * inv(n - k, mod - 2)) % mod * inv(k,mod - 2) % mod ) % mod;
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
