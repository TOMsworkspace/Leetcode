#include <bits/stdc++.h>
using namespace std;

//最短路
// 4.1.1 Dijkstra 单源最短路
/*
 * 权值必须是非负
 * 单源最短路径，Dijkstra 算法，邻接矩阵形式，复杂度为O(n^2)
 * 求出源 beg 到所有点的最短路径，传入图的顶点数，和邻接矩阵 cost[][]
 * 返回各点的最短路径 lowcost[], 路径 pre[].
 * pre[i] 记录 beg 到 i 路径上的父结点，pre[beg]=-1
 * 可更改路径权类型，但是权值必须为非负
 */
const int MAXN = 1010;
#define typec int
const typec INF = 0x3f3f3f3f; //防止后面溢出，这个不能太大
bool vis[MAXN];
int pre[MAXN];

void Dijkstra(typec cost[][MAXN], typec lowcost[], int n, int beg)
{
    for (int i = 0; i < n; i++)
    {
        lowcost[i] = INF;
        vis[i] = false;
        pre[i] = -1;
    }
    lowcost[beg] = 0;
    for (int j = 0; j < n; j++)
    {
        int k = -1;
        int Min = INF;
        for (int i = 0; i < n; i++)
        {
            if (!vis[i] && lowcost[i] < Min)
            {
                Min = lowcost[i];
                k = i;
            }
            if (k == -1)
                break;
            vis[k] = true;
            for (int i = 0; i < n; i++)
            {
                if (!vis[i] && lowcost[k] + cost[k][i] < lowcost[i])
                {
                    lowcost[i] = lowcost[k] + cost[k][i];
                    pre[i] = k;
                }
            }
        }
    }
}

// 4.1.2 Dijkstra 算法 + 堆优化
/*
 * 使用优先队列优化，复杂度 O (E log E)
 * 使用优先队列优化 Dijkstra 算法
 * 复杂度 O(ElogE)
 * 注意对 vector<Edge>E[MAXN] 进行初始化后加边
 */
const int INF = 0x3f3f3f3f;
const int MAXN = 1000010;

struct qnode
{
    int v;
    int c;
    qnode(int _v = 0, int _c = 0) : v(_v), c(_c) {}
    bool operator<(const qnode &r) const
    {
        return c > r.c;
    }
};

struct Edge
{
    int v, cost;
    Edge(int _v = 0, int _cost = 0) : v(_v), cost(_cost) {}
};

vector<Edge> E[MAXN];
bool vis[MAXN];
int dist[MAXN];
//点的编号从 1 开始

void Dijkstra(int n, int start)
{
    memset(vis, false, sizeof(vis));
    for (int i = 1; i <= n; i++)
        dist[i] = INF;
    priority_queue<qnode> que;
    while (!que.empty())
        que.pop();
    dist[start] = 0;
    que.push(qnode(start, 0));
    qnode tmp;
    while (!que.empty())
    {
        tmp = que.top();
        que.pop();
        int u = tmp.v;
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = 0; i < E[u].size(); i++)
        {
            int v = E[tmp.v][i].v;
            int cost = E[u][i].cost;
            if (!vis[v] && dist[v] > dist[u] + cost)
            {
                dist[v] = dist[u] + cost;
                que.push(qnode(v, dist[v]));
            }
        }
    }
}

void addedge(int u, int v, int w)
{
    E[u].push_back(Edge(v, w));
}

// 4.1.3 单源最短路 bellman_ford 算法
/*
 * 单源最短路 bellman_ford 算法，复杂度 O(VE)
 * 可以处理负边权图。
 * 可以判断是否存在负环回路。返回 true, 当且仅当图中不包含从源点可达的负权回路
 * vector<Edge>E; 先 E.clear() 初始化，然后加入所有边
 * 点的编号从 1 开始 (从 0 开始简单修改就可以了)
 */
const int INF = 0x3f3f3f3f;
const int MAXN = 550;
int dist[MAXN];
struct Edge
{
    int u, v;
    int cost;
    Edge(int _u = 0, int _v = 0, int _cost = 0) : u(_u), v(_v), cost(_cost) {}
};

vector<Edge> E;
//点的编号从 1 开始
bool bellman_ford(int start, int n)
{
    for (int i = 1; i <= n; i++)
        dist[i] = INF;
    dist[start] = 0;
    //最多做 n-1 次
    for (int i = 1; i < n; i++)
    {
        bool flag = false;
        for (int j = 0; j < E.size(); j++)
        {
            int u = E[j].u;
            int v = E[j].v;
            int cost = E[j].cost;
            if (dist[v] > dist[u] + cost)
            {
                dist[v] = dist[u] + cost;
                flag = true;
            }
        }
        if (!flag)
            return true; //没有负环回路
    }
    for (int j = 0; j < E.size(); j++)
        if (dist[E[j].v] > dist[E[j].u] + E[j].cost)
            return false; //有负环回路
    return true;          //没有负环回路
}

// 4.1.4 单源最短路 SPFA
/*
 * 单源最短路 SPFA
 * 时间复杂度 0(kE)
 * 这个是队列实现，有时候改成栈实现会更加快，很容易修改
 * 这个复杂度是不定的
 */

const int MAXN = 1010;
const int INF = 0x3f3f3f3f;
struct Edge
{
    int v;
    int cost;
    Edge(int _v = 0, int _cost = 0) : v(_v), cost(_cost) {}
};

vector<struct Edge> E[MAXN];
void addedge(int u, int v, int w)
{
    E[u] push_back(Edge(v, w));
}

bool vis[MAXN]; //在队列标志
int cnt[MAXN];  //每个点的入队列次数
int dist[MAXN];

bool SPFA(int start, int n)
{
    memset(vis, false, sizeof(vis));
    for (int i = 1; i <= n; i++)
        dist[i] = INF;
    vis[start] = true;
    dist[start] = 0;
    queue<int> que;
    while (!que.empty())
        que.pop();
    que.push(start);
    memset(cnt, 0, sizeof(cnt));
    cnt[start] = 1;
    while (!que.empty())
    {
        int u = que.front();
        que.pop();
        vis[u] = false;
        for (int i = 0; i < E[u].size(); i++)
        {
            int v = E[u][i].v;
            if (dist[v] > dist[u] + E[u][i].cost)
            {
                dist[v] = dist[u] + E[u][i].cost;
                if (!vis[v])
                {
                    vis[v] = true;
                    que.push(v);
                    if (++cnt[v] > n)
                        return false;
                    // cnt[i] 为入队列次数，用来判定是否存在负环回路
                }
            }
        }
    }
    return true;
}

***************************************************

/**
 * @brief 例题： leetcode: 1334
 * 有 n 个城市，按从 0 到 n-1 编号。给你一个边数组 edges，其中 edges[i] = [fromi, toi, weighti] 代表 fromi 和 toi 两个城市之间的双向加权边，
 * 距离阈值是一个整数 distanceThreshold。返回能通过某些路径到达其他城市数目最少、且路径距离 最大 为 distanceThreshold 的城市。
 * 如果有多个这样的城市，则返回编号最大的城市。
 *
 * 注意，连接城市 i 和 j 的路径的距离等于沿该路径的所有边的权重之和。
 *
 */

class Solution
{
public:
    int findTheCity(int n, vector<vector<int>> &edges, int distanceThreshold)
    {

        vector<vector<int>> dis(n, vector<int>(n, INT_MAX / 2));

        unordered_map<int, vector<int>> g;

        for (auto &edge : edges)
        {
            dis[edge[0]][edge[1]] = edge[2];
            dis[edge[1]][edge[0]] = edge[2];
            g[edge[0]].push_back(edge[1]);
            g[edge[1]].push_back(edge[0]);
        }

        // floyd algothrim: 枚举点
        for (int i = 0; i < n; i++)
            dis[i][i] = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == j || dis[j][i] == INT_MAX / 2)
                    continue;
                for (int k = j + 1; k < n; k++)
                {
                    if (j != k && dis[i][k] + dis[j][i] < dis[j][k])
                    {
                        dis[k][j] = dis[j][k] = dis[j][i] + dis[i][k];
                    }
                }
            }
        }

        // dijkstra algothrim： 枚举点
        //  for(int i = 0; i < n; i++) dis[i][i] = 0;
        //  for(int i = 0; i < n; i++){
        //      priority_queue<pair<int,int>> q;
        //      for(int j = 0; j < n; j++){
        //          if(j != i && dis[i][j] != INT_MAX / 2)
        //              q.emplace(-dis[i][j], j);
        //      }

        //     while(q.size()){
        //         auto [d, node] = q.top();
        //         q.pop();

        //         if(-d <= dis[i][node]){
        //             for(auto nd : g[node]){
        //                 if(dis[i][nd] > dis[i][node] + dis[node][nd]){
        //                     dis[i][nd] = dis[i][node]+ dis[node][nd];
        //                     q.emplace(-dis[i][nd], nd);
        //                 }
        //             }
        //         }
        //     }
        // }

        // bellman ford： 枚举边
        //  for(int i = 0; i < n; i++) dis[i][i] = 0;
        //  for(int i = 0; i < n; i++){
        //      for(int j = 0; j < n - 1; j++){
        //          for(auto & edge : edges){
        //              int u = edge[0], v = edge[1], w = edge[2];
        //              if(dis[i][u] + w < dis[i][v]){
        //                  dis[i][v] = dis[i][u] + w;
        //              }

        //             if(dis[i][v] + w < dis[i][u]){
        //                 dis[i][u] = dis[i][v] + w;
        //             }
        //         }
        //     }
        // }

        // SPFA：枚举边
        //  for(int i = 0; i < n; i++) dis[i][i] = 0;
        //  for(int i = 0; i < n; i++){
        //      vector<bool> inq(n, false);
        //      list<int> q;

        //     for(int j = 0; j < n; j++){
        //         if(j != i && dis[i][j] != INT_MAX / 2){
        //             if(q.size() && dis[i][j] < dis[i][q.front()])
        //                 q.push_front(j);
        //             else
        //                 q.push_back(j);
        //             inq[j] = true;
        //         }
        //     }

        //     while(q.size()){
        //         int node = q.front();
        //         q.pop_front();

        //         inq[node] = false;

        //         for(auto nd : g[node]){
        //             if(dis[i][node] + dis[node][nd] < dis[i][nd]){
        //                 dis[i][nd] = dis[i][node] + dis[node][nd];
        //                 if(!inq[nd]){
        //                     if(q.size() && dis[i][nd] < dis[i][q.front()])
        //                         q.push_front(nd);
        //                     else
        //                         q.push_back(nd);
        //                 }
        //             }
        //         }
        //     }
        // }

        int ans = -1;
        int maxcity = n;

        for (int i = 0; i < n; i++)
        {
            int cnt = 0;
            for (int j = 0; j < n; j++)
                cnt += (dis[i][j] <= distanceThreshold && i != j);
            if (cnt <= maxcity)
            {
                maxcity = cnt;
                ans = i;
            }
        }

        return ans;
    }
};
