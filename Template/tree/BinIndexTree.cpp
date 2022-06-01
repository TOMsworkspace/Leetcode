/**
 * @file BinIndexTree.cpp
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

class BinIndexTree
{
private:
    vector<int> c;
    int len;

public:
    BinIndexTree(int len):len(len), c(len, 0) {}

    ~BinIndexTree() {}

    int lowbit(int x) {
        return x & (-x);
    }

    void add(int p, int v) {
        while (p < len) {
            c[p] += v;
            p += lowbit(p);
        }
    }

    int get(int p) {
        int r = 0;
        while (p > 0) {
            r += c[p];
            p -= lowbit(p);
        }
        return r;
    }

    void clear(){
        for(int i = 0; i < len; i++){
            c[i] = 0;
        }
    }

};


/**
 * @brief Leetcode: 1395
 * 
 */

static constexpr int MAX_N = 1000;

class Solution {
public:
    
    vector <int> disc;
    vector <int> iLess, iMore, kLess, kMore;

    int numTeams(vector<int>& rating) {
        disc = rating;
        disc.push_back(-1);
        sort(disc.begin(), disc.end());
        auto getId = [&] (int target) {
            return lower_bound(disc.begin(), disc.end(), target) - disc.begin();
        };

        int n = rating.size();

        BinIndexTree tree(MAX_N + 1);

        iLess.resize(rating.size());
        iMore.resize(rating.size());
        kLess.resize(rating.size());
        kMore.resize(rating.size());

        for (int i = 0; i < rating.size(); ++i) {
            auto id = getId(rating[i]);
            iLess[i] = tree.get(id);
            iMore[i] = tree.get(MAX_N) - tree.get(id); 
            tree.add(id, 1);
        }


        tree.clear();

        for (int i = rating.size() - 1; i >= 0; --i) {
            auto id = getId(rating[i]);
            kLess[i] = tree.get(id);
            kMore[i] = tree.get(MAX_N) - tree.get(id); 
            tree.add(id, 1);
        }
        
        int ans = 0;
        for (unsigned i = 0; i < rating.size(); ++i) {
            ans += iLess[i] * kMore[i] + iMore[i] * kLess[i];
        }

        return ans;
    }
};




