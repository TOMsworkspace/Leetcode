#include<iostream>
using namespace std;

/*
void makeNext(const char P[], int next[])
{
	int q, k;//q是当前要计算第q个字符的next值，k是对应的next值
	int m = strlen(P);
	next[0] = 0;
	for (q = 1, k = 0; q < m; q++)
	{
		while (k > 0 && P[k] != P[q])
		{
			k = next[k - 1];
		}
		if (P[q] == P[k])
		{
			k++;
		}
		next[q] = k;
	}
}

int  kmp(const char T[], const char P[], int next[])
{
	int n, m;
	n = strlen(T);
	m = strlen(P);
	makeNext(P, next);
	int i = 0;
	int j = 0;
	while (i < n && j < m)
	{
		if ( j==0||T[i] == P[j])
		{
			i++;
			j++;
		}
		else
		{
			j = next[j-1];
		}
	}
	if (j == m)
		return  i - m + 1;
	else
		return -1;
	
}
*/


//kuangbing
//1.1 KMP
/*
    * next[] 的含义：x[i-next[i]...i-1]=x[0...next[i]-1]    
    * next[i] 为满足 x[i-z...i-1]=x[0...z-1] 的最大 z 值（就是 x 的自身匹配）
*/

void kmp_pre(char x[],int m,int next[]){
    int i,j;
    j=next[0] = -1;
    i=0;
    while(i<m){
        while(-1 != j && x[i]!=x[j])
            j=next[j];
        next[++i]=++j;
    }
}

/*
    * kmpNext[i] 的意思:next'[i]=next[next[...[next[i]]]](直到next'[i]<0 或者 x[next'[i]]!=x[i])
    * 这样的预处理可以快一些
*/

void preKMP(char x[],int m,int kmpNext[]){
    int i,j;
    j=kmpNext[0] = -1;
    i=0;
    while(i<m){
        while(-1 != j && x[i] != x[j])
            j=kmpNext[j];
        if(x[++i]==x[++j])kmpNext[i]=kmpNext[j];
        else kmpNext[i]=j;
    }
}

/*
* 返回 x 在 y 中出现的次数，可以重叠
*/
//int next[10010];
int KMP_Count(char x[],int m,char y[],int n, int next[]){//x 是模式串，y 是主串
    int i,j;
    int ans=0;
    //preKMP(x,m,next);
    kmp_pre(x,m,next);
    i=j=0;
    while(i<n){
        while(-1 != j && y[i] != x[j])
            j = next[j];
        i++;
        j++;
        if(j >= m){
            ans++;
            j = next[j];
        }
    }
    return ans;
}

int main()
{
	int next[100] = { 0 };
	char T[] = "abababababc";
	char P[] = "abab";
    cout << KMP_Count(P,3, T,11,next);
    return 0;
}