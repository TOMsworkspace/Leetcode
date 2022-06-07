#include<bits/stdc++.h>
using namespace std;

//素数
// 2.1.1 素数筛选（判断 <MAXN 的数是否素数）
/*
 * 素数筛选，判断小于 MAXN 的数是不是素数。
 * notprime 是一张表，为 false 表示是素数，true 表示不是素数
 */
const int MAXN = 1000010;
bool notprime[MAXN]; //值为 false 表示素数，值为 true 表示非素数
void init()
{
    memset(notprime, false, sizeof(notprime));
    notprime[0] = notprime[1] = true;
    for (int i = 2; i < MAXN; i++)
    {
        if (!notprime[i])
        {
            if (i > MAXN / i)
                continue; //防止后面 i*i 溢出 (或者 i,j 用 longlong)
            //直接从 i*i 开始就可以，小于 i 倍的已经筛选过了, 注意是 j+=i
            for (int j = i * i; j < MAXN; j += i)
                notprime[j] = true;
        }
    }
}

// 2.1.2 素数筛选（筛选出小于等于 MAXN 的素数）
/*
 * 素数筛选，存在小于等于 MAXN 的素数
 * prime[0] 存的是素数的个数
 */

const int MAXN = 10000;
int prime[MAXN + 1];
void getPrime()
{
    memset(prime, 0, sizeof(prime));
    for (int i = 2; i <= MAXN; i++)
    {
        if (!prime[i])
            prime[++prime[0]] = i;
        for (int j = 1; j <= prime[0] && prime[j] <= MAXN / i; j++)
        {
            prime[prime[j] * i] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
}

int main()
{
    init(); //执行程序开始的打表操作
    int n;
    while (cin >> n)
    {
        if (notprime[n])
            cout << "不是素数！" << endl; //判断是否为素数
        else
            cout << "是素数！" << endl;
    }
    return 0;
}
