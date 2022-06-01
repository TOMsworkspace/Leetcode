/**
 * @file DFS.cpp
 * @author TOMsworkspace (2683322180@qq.com)
 * @brief 
 * @version 1.0
 * @date 2022-05-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//深度优先搜索
#include<bits/stdc++.h>
using namespace std;

/*
void dfs()
{
	if (到达终点状态)
	{
		...
			return;
	}
	if (越界或者是不合法状态)
		return;
	if (特殊状态)
		return;
	for (扩展方式)
	{
		if (扩展方式所到达状态合法)
		{
			修改操作;//根据题意来添加标记
			dfs();
			还原标记;
			//是否还原标记根据题意
			//如果加上(还原标记)就是回溯法
		}
	}
}
*/

/**
 * @brief leetcode: 200
 * 给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
 * 岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。
 * 此外，你可以假设该网格的四条边均被水包围。
 *
 */

class Solution
{
public:
	int numIslands(vector<vector<char>> & grid)
	{
		int res = 0;
		for (int i = 0; i < grid.size(); i++)
		{
			for (int j = 0; j < grid[0].size(); j++)
			{
				if (grid[i][j] == '1')
				{
					dfs(i, j, grid);
					res++;
				}
			}
		}
		return res;
	}

	void dfs(int i, int j, vector<vector<char>> &grid)
	{
		if (i >= 0 && j >= 0 && i < grid.size() && j < grid[0].size())
		{
			if (grid[i][j] == '1')
				grid[i][j] = '0';
			else
				return;
			dfs(i + 1, j, grid);
			dfs(i - 1, j, grid);
			dfs(i, j + 1, grid);
			dfs(i, j - 1, grid);
		}
	}
};
