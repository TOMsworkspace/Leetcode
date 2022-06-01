#include<bits/stdc++.h>
using namespace std;

constexpr int maxx = 205;
int n, m;
int vis[maxx][maxx];
int dis[maxx][maxx];
int loc[4][4] = { {-1,0},{1,0},{0,1},{0,-1} };
char s[maxx][maxx];
int ans;
void bfs(int ss,int sd)
{
	//pair<int,int> p;
	//p.first 第一个元素 p.second 第二个元素
	queue<pair<int, int>> q;
	q.push(make_pair(ss, sd));
	vis[ss][sd] = 1;
	while (!q.empty())
	{
		int l = q.front().first;
		int r = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			int u = l + loc[i][0];
			int v = r + loc[i][1];
			if (s[u][v] != '#' && u <= n && u > 0 && v <= m && v > 0&&vis[u][v]==0)
			{
				dis[u][v] = dis[l][r] + 1;
				if (s[u][v] == 'x')
					dis[u][v]++;
				vis[u][v] = 1;
				q.push(make_pair(u, v));
				if (s[u][v] == 'r'&&dis[u][v]<ans)
					ans=dis[u][v];
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	int ss, sd;
	while (cin >> n >> m)
	{
		memset(vis, 0, sizeof vis);
		memset(dis, 0, sizeof dis);
		ans = 99999;
		for (int i = 1; i <= n; i++)
		{
			cin >> (s[i] + 1);
			for (int j = 1; j <= m; j++)
			{
				if (s[i][j] == 'a')
				{
					ss = i;
					sd = j;
				}
			}	
		}
		bfs(ss, sd);	
		if (ans==99999)
		{
			cout << "Poor ANGEL has to stay in the prison all his life.\n";
     	}
		else
			cout <<ans << endl;
	}
}
