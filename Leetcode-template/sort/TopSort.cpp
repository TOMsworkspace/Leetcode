#include<iostream>
#include<cstdio>
#include<queue>
#include<vector>
using namespace std;
const int MX = 500 + 10;
int N, M;
vector<int>G[MX];//可约当做声明了一个二维数组
int indegree[MX];//记录各定点入度的数组
queue<int>q;

//初始化，将AOV网存储到数据结构中
void init()
{
	for (int i = 1; i <= M; i++)//M是关系数
	{
		int node1, node2;
		cin >> node1 >> node2;
		G[node1].push_back(node2);
		//在G[node1]的尾部加入数据node2，表示node2是node1的直接后继
		indegree[node2]++;//node2的入度加一
	}
}

int topo_sort()
{
	for (int i = 1; i <= N; i++)
		if (indegree[i] == 0)
			q.push(i);//若i的入度为0，则将i入队
	int cnt = 0;
	while (!q.empty())
	{
		cnt++;
		int tmp = q.front();//记录当前队头元素
		q.pop();
		for (int i = 0; i < G[tmp].size(); i++)//遍历当前队头元素tmp的所有直接后继
		{
			int node = G[tmp][i];//node记录tmp的第i个直接后继（i从0开始）
			indegree[node]--;
			if (indegree[node] == 0)
				q.push(node);//入度为0，则入队
		}
		if (!q.empty())
			cout << tmp << " ";
		else
			cout << tmp;//使最后一个输出数据后面无空格
	}
	if (cnt < N)
		return -1;//说明存在点没有入队，即成环。
}
