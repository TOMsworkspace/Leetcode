/**
 * @file SegTree.cpp
 * @author TOMsworkspace (2683322180@qq.com)
 * @brief 区间最大值线段树,动态开点，leetcode-699
 * @version 1.0
 * @date 2022-05-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include<iostream>
#include<cmath>
#include<vector>

struct Node{
    Node *left, *right;
    int val, tag;

    Node(int val = 0, int tag = 0):val(val), tag(tag), left(nullptr), right(nullptr) {}
};

class SegmentTree {
private:
    Node* root;
    int l, r;

    void del(Node * node){
        if(!node) return;
        if(node->left) del(node->left);
        if(node->right) del(node->right);
        delete node;
    }

    void pushdown(Node * node){
        //if(!if) trees[node] = new Node();
        if(!node->left) node->left = new Node();
        if(!node->right) node->right = new Node();

        if(node->tag == 0) return;

        int tag = node->tag;
        node->left->tag = tag, node->left->val = tag;
        node->right->tag = tag, node->right->val = tag;
        node->tag = 0;
    }

    void pushup(Node * node){
        node->val = max(node->left->val, node->right->val);
    }

public:

    ~SegmentTree(){
        del(root);
    }

    SegmentTree(int l = 0, int r = 1e9):l(l), r(r) {
        root = new Node();
    }

    int query(int left, int right){
        return query(root, l, r, left, right);
    }

    int query(Node * node, int l, int r, int left, int right){

        if(l >= left && right >= r){
            return node->val;
        }

        pushdown(node);

        int mid = l + (r - l) / 2;
        int ans = 0;
        if(left <= mid){
            ans = query(node->left, l, mid, left, right);
        }
        
        if(right > mid){
            ans = max(ans, query(node->right, mid + 1, r, left, right));
        }

        return ans;
    }

    void update(int left, int right, int v){
        update(root, l, r, left, right, v);
    }

    void update(Node * node, int l, int r, int left, int right, int v){

        if(left <= l && right >= r){
            node->val = v;
            node->tag = v;
            return;
        }

        pushdown(node);

        int mid = l + (r - l) / 2;
        if(left <= mid){
            update(node->left, l, mid, left, right, v);
        }
        
        if(right > mid){
            update(node->right, mid + 1, r, left, right, v);
        }
        
        pushup(node);
    }
};

class Solution {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        vector<int> ans;
        SegmentTree* tree = new SegmentTree(1, 1e9);
        int mx = 0;
        for (auto& p : positions)
        {
            int l = p[0], w = p[1], r = l + w - 1;
            int h = tree->query(l, r) + w;
            mx = max(mx, h);
            ans.push_back(mx);
            tree->update(l, r, h);
        }
        return ans;
    }
};
