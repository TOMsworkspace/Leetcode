#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
// 4.2.1 Prim 算法
/*
 * Prim 求 MST
 * 耗费矩阵 cost[][]，标号从 0 开始，0∼n-1
 * 返回最小生成树的权值，返回 -1 表示原图不连通
 */

const int INF = 0x3f3f3f3f;
const int MAXN = 110;
bool vis[MAXN];
int lowc[MAXN];
//点是 0 n-1
int Prim(int cost[][MAXN], int n)
{
    int ans = 0;
    memset(vis, false, sizeof(vis));
    vis[0] = true;
    for (int i = 1; i < n; i++)
        lowc[i] = cost[0][i];
    for (int i = 1; i < n; i++)
    {
        int minc = INF;
        int p = -1;
        for (int j = 0; j < n; j++)
        {
            if (!vis[j] && minc > lowc[j])
            {
                minc = lowc[j];
                p = j;
            }
        }
        if (minc == INF)
            return -1; //原图不连通
        ans += minc;
        vis[p] = true;
        for (int j = 0; j < n; j++)
        {
            if (!vis[j] && lowc[j] > cost[p][j])
            {
                lowc[j] = cost[p][j];
            }
        }
    }
    return ans;
}

// 4.2.2 Kruskal 算法
/*
 * Kruskal 算法求 MST
 */
const int MAXN = 110;   //最大点数
const int MAXM = 10000; //最大边数
int F[MAXN];            //并查集使用
struct Edge
{
    int u, v, w;
} edge[MAXM]; //存储边的信息，包括起点/终点/权值

int tol; //边数，加边前赋值为 0
void addedge(int u, int v, int w)
{
    edge[tol].u = u;
    edge[tol].v = v;
    edge[tol++].w = w;
}

//排序函数，讲边按照权值从小到大排序
bool cmp(Edge a, Edge b)
{
    return a.w < b.w;
}
int find(int x)
{
    if (F[x] == -1)
        return x;
    else
        return F[x] = find(F[x]);
}
//传入点数，返回最小生成树的权值，如果不连通返回 -1
int Kruskal(int n)
{
    memset(F, -1, sizeof(F));
    sort(edge, edge + tol, cmp);
    int cnt = 0; //计算加入的边数
    int ans = 0;
    for (int i = 0; i < tol; i++)
    {
        int u = edge[i].u;
        int v = edge[i].v;
        int w = edge[i].w;
        int t1 = find(u);
        int t2 = find(v);
        if (t1 != t2)
        {
            ans += w;
            F[t1] = t2;
            cnt++;
        }
        if (cnt == n - 1)
            break;
    }
    if (cnt < n - 1)
        return -1; //不连通
    else
        return ans;
}

//****************************

//例题

/**
 * @brief leetcode: 1584
 * 给你一个points 数组，表示 2D 平面上的一些点，其中 points[i] = [xi, yi] 。
 * 连接点 [xi, yi] 和点 [xj, yj] 的费用为它们之间的 曼哈顿距离 ：|xi - xj| + |yi - yj| ，其中 |val| 表示 val 的绝对值。
 * 请你返回将所有点连接的最小总费用。只有任意两点之间 有且仅有 一条简单路径时，才认为所有点都已连接。
 *
 */

// prim算法，从点出发
class Solution
{
public:
    int minCostConnectPoints(vector<vector<int>> &points)
    {
        int n = points.size();

        vector<vector<int>> g(n, vector<int>(n));

        for (int i = 0; i < n; i++)
        {
            int x1 = points[i][0], y1 = points[i][1];
            for (int j = i + 1; j < n; j++)
            {
                int x2 = points[j][0], y2 = points[j][1];
                int dis = abs(x1 - x2) + abs(y1 - y2);
                g[i][j] = dis;
                g[j][i] = dis;
            }
        }

        unordered_set<int> st;
        vector<int> dis(n, INT_MAX / 2);

        priority_queue<pair<int, int>> q;
        q.emplace(0, 0);

        int ans = 0;

        while (q.size())
        {
            auto [d, node] = q.top();
            q.pop();

            if (st.count(node))
                continue;

            st.insert(node);
            ans -= d;

            for (int i = 0; i < n; i++)
            {
                if (i != node && !st.count(i) && g[node][i] < dis[i])
                {
                    dis[i] = g[node][i];
                    q.emplace(-dis[i], i);
                }
            }
        }

        return ans;
    }
};

// Kruskal 算法： 从最短边出发

class Solution
{
private:
    vector<int> parents, rank;

public:
    int find(int x)
    {
        if (x != parents[x])
        {
            parents[x] = find(parents[x]);
        }
        return parents[x];
    }

    void Union(int x, int y)
    {
        int px = find(x), py = find(y);
        if (px != py)
        {
            if (rank[px] >= rank[py])
            {
                parents[py] = px;
                rank[py] += rank[px];
            }
            else
            {
                parents[px] = py;
                rank[px] += rank[py];
            }
        }
    }

    bool isconnect(int x, int y)
    {
        return find(x) == find(y);
    }

    int minCostConnectPoints(vector<vector<int>> &points)
    {
        priority_queue<pair<int, int>> q;

        int n = points.size();
        for (int i = 0; i < n; ++i)
        {
            int x1 = points[i][0], y1 = points[i][1];
            for (int j = i + 1; j < n; ++j)
            {
                int x2 = points[j][0], y2 = points[j][1];
                q.emplace(-abs(x1 - x2) - abs(y1 - y2), i * 1000 + j);
            }
        }

        parents.resize(n);
        rank.resize(n, 1);
        for (int i = 0; i < n; i++)
        {
            parents[i] = i;
        }

        int ans = 0;
        for (int i = 0; i < n - 1; i++)
        {

            auto [len, edge] = q.top();
            q.pop();
            int a = edge / 1000, b = edge % 1000;

            Union(a, b);
            ans -= len;

            while (q.size() && isconnect(q.top().second / 1000, q.top().second % 1000))
                q.pop();
        }

        return ans;
    }
};