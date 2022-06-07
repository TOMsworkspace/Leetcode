/**
 * @file UnionFindSet.cpp
 * @author TOMsworkspace (2683322180@qq.com)
 * @brief 
 * @version 1.0
 * @date 2022-05-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include<bits/stdc++.h>

using namespace std;

/**
 * @brief 并查集
 * 
 */
class UnionFindSet{
private:
    vector<int> parents, rank;
    int count;

public:
    UnionFindSet(int len):count(len){
        parents.resize(len);
        rank.resize(len, 1);

        for(int i = 0; i < len; i++){
            parents[i] = i;
        }
    }
    int find(int x){
        if(x != parents[x]){
            parents[x] = find(parents[x]);
        }
        return parents[x];
    }
    
    void Union(int x, int y){
        int px = find(x), py = find(y);
        if(px != py){
            if(rank[px] >= rank[py]){
                parents[py] = px; 
                rank[py] += rank[px];
            }
            else{
                parents[px] = py;
                rank[px] += rank[py];
            }
            --count;
        }
    }
    
    bool isconnect(int x, int y){
        return find(x) == find(y);
    }

    int getCount() const {
        return count;
    }
};


/**
 * @brief 例题： leetcode： 200
 * 
 */

class Solution
{
public:
    int numIslands(vector<vector<char>> &grid)
    {

        int row = grid.size();
        if (!row)
            return 0;
        int col = grid[0].size();

        UnionFindSet uf(row * col);

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (grid[i][j] == '1')
                {
                    grid[i][j] = '0';
                    if (i - 1 >= 0 && grid[i - 1][j] == '1')
                        uf.Union(i * col + j, (i - 1) * col + j);
                    if (i + 1 < row && grid[i + 1][j] == '1')
                        uf.Union(i * col + j, (i + 1) * col + j);
                    if (j - 1 >= 0 && grid[i][j - 1] == '1')
                        uf.Union(i * col + j, i * col + j - 1);
                    if (j + 1 < col && grid[i][j + 1] == '1')
                        uf.Union(i * col + j, i * col + j + 1);
                }
            }
        }

        return uf.getCount();
    }
};