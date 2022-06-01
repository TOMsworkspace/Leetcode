/**
 * @file TrieTree.cpp
 * @author TOMsworkspace (2683322180@qq.com)
 * @brief 
 * @version 1.0
 * @date 2022-05-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<iostream>
#include<cstring>
using namespace std;
const int MAXN = 26;

struct Trie{
    // 代表当前节点可以延伸出的边，数量可变
    Trie* Next[MAXN];
    // 标记当前节点是否是保存信息的结尾，也可以代表前缀个数
    int Flag;

    Trie()
    {
        // 初始化以该信息为前缀的信息个数
        Flag = 1;
        memset(Next, 0, sizeof(Next));
    }
};

class TrieTree{
    
private:
    Trie* root;
    
    void Free(Trie* root)
    {
        if (root == NULL)
            return;
        //释放trie树的每一个节点占用的内存
        for (int i = 0; i < MAXN; ++i)
        {
            if(root->Next[i])
                Free(root->Next[i]);
        }
        delete(root);
    }

public:
    TrieTree(){
        root = new Trie();
    }

    ~TrieTree(){
        free(root);
    }

    void insert(string s)
    {
        int len = s.length();
        int id;
        Trie* p = root;
        Trie* q;
        //将s的每一个字符插入trie树
        for (int i = 0; i < len; i++)
        {
            id = s[i] - 'a';
            //如果没有边，则新建一个trie节点，产生一条边，用以代表该字符。
            if (p->Next[id] == NULL)
            {
                q = new Trie();
                p->Next[id] = q;
                p = p->Next[id];
            }
            //如果存在边，则沿着该边走。
            else
            {
                p = p->Next[id];
                //累加以该信息为前缀的信息个数
                ++(p->Flag);
            }
        }
    }

    int query(const string str)
    {
        int len = str.size();
        Trie* p = root;
        //在trie树上顺序搜索str的每一个字符
        for (int i = 0; i < len; ++i)
        {
            int id = str[i] - 'a';
            p = p->Next[id];
            if (p == NULL)
                return 0;
        }
        return p->Flag;
    }
};


int main()
{
    TrieTree root = TrieTree();
    const char* word[4] = {"banana","band","bee","absolute"};
    const char* fore[4] = { "ba","b","band","abc" };
    for (int i = 0; i < 4; i++)
    {
        root.insert(word[i]);
    }

    for (int i = 0; i < 4; i++)
    {
        cout << root.query(fore[i]) << endl;
    }
}
