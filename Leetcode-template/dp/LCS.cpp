#include<iostream>
#include<algorithm>
using namespace std;

//LIS O(N ^ 2) 
/*
    最长递增子序列
*/
constexpr int M = 1000, N = 1000; 
/*
int dp[N];
int LIS_1(char a[], int n){
    int res = 0;
    for(int i = 1; i <= n;i++)
    {
        dp[i] = 1;
        for(int j=1;j<=i;j++)
        {
            if(a[j] < a[i]) dp[i] = max(dp[i],dp[j] + 1);
            res = max(res,dp[i]);
        }
    }

    return res;
}
*/
//LIS O(NlogN) 
/*
    最长递增子序列
*/

/*
int LIS_2(char a[], int n){    
    int len = 0;
    for(int i = 1;i < n;i++)
    {
        int pos=lower_bound(dp, dp + len, a[i]) - dp;
        len=max(len,pos + 1);
        dp[pos] = a[i];
    }
    return len;
}

int LDS_2(char a[], int n){    
    int len = 0;
    for(int i = 1;i < n;i++)
    {
        int pos=upper_bound(dp, dp+len, a[i], greater<int>()) - dp;//更新序列结尾第一个小于a[i]的序列
        len = max(len,pos + 1);
        dp[pos] = a[i];
    }
    return len;
}

*/

//LCS O(N*M) 
/*
    最长公共子序列
*/

int dp[M][N];

int LCS(char a[], int m, char b[], int n){    
    
    for(int i = 1;i <= m;i++)
    {
        for(int j = 1;j <= n;j++)
        {
            dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
            if(a[i - 1] == b[j - 1]) dp[i][j]=max(dp[i][j],dp[i-1][j-1]+1);
        }
    }

    return dp[m][n];
}


//LCIS O(N*M) 
/*
    最长公共上升子序列
*/


int LCIS(char a[],int m, char b[], int n){    
    //f[i][j]表示所有在[0...i],b[0....j]中出现过，以b[j]结尾的序列的集合
 
    int ans = 0;
    for(int i = 1;i <= m;i++)
    {
        int temp = 1;
        for(int j = 1;j <= n;j++)
        {
            dp[i][j] = max(dp[i-1][j],dp[i][j]);
            if(a[i - 1] == b[j - 1]) dp[i][j] = max(temp,dp[i][j]);
            if(a[i - 1] > b[j - 1]) temp = max(temp,dp[i-1][j]+1);
        }
    }
    for(int i = 1;i <= n;i++) ans = max(ans,dp[m][i]);

    return ans;
}



int main()
{   
    char a[] = "ababcbadabe";
    char b[] = "abacde";

   // cout << LCS(a,11,b,4);
    cout << LCIS(a,10,b,6);
    return 0;
}

