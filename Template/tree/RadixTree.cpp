/**
 * @file RadixTree.cpp
 * @author TOMsworkspace (2683322180@qq.com)
 * @brief  [ull, char *]基数树
 * @version 1.0
 * @date 2022-05-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include<bits/stdc++.h>
using namespace std;

//#define MEMPOOL

#define RADIX_INSERT_VALUE_OCCUPY -1	//该节点已被占用
#define RADIX_INSERT_VALUE_SAME -2		//插入了相同的值
#define RADIX_DELETE_ERROR -3			//删除错误

//typedef unsigned int value_ptr_t;
typedef unsigned long long value_t;

typedef unsigned long long key_t;

#define BITS 2
const int radix_tree_height = sizeof(key_t) * 8 / BITS;//树的高度
//返回key中由pos指定的位的值，位数由BITS指定
#define CHECK_BITS(key,pos) (( ((key_t)(key)) << sizeof(key_t) * 8 - (pos + 1) * BITS ) >> (sizeof(key_t) * 8 - BITS))
//基数树节点
typedef struct radix_node_t radix_node_t;
struct radix_node_t {
	radix_node_t* child[1 << BITS];
	radix_node_t* parent;
	value_t value;//节点储存的值
};


//使用内存池是为减少建立节点时重新申请内存的时间
#ifdef MEMPOOL

//内存池描述结构，放在内存池的前段
typedef struct radix_pool {
	struct radix_pool* next;//内存池是双向循环链表的一个节点
	struct radix_pool* prev;
//已分配内存中还未使用的内存首地址
	char* start;
//已分配内存中还未使用的内存长度
	size_t size;
}radix_pool, * pool_t;

#define MEMPAGE 4096
#define INIT_NODE_NUM (16*32) //初始备用节点数
#define INIT_POOL_SIZE (MEMPAGE * 32)	//初始内存池大小

#endif

class RadixTree{

private:
    //根节点
	radix_node_t* root;
	
	//储存已分配但不在树中的节点（双向链表，这里储存其中的一个节点）
	radix_node_t* freelist;

#ifdef MEMPOOL
    //内存池指针
	pool_t pool;

    //内存池扩大函数，num：新内存池的大小，=-1使用默认值,单位：页
    pool_t get_new_pool(size_t num)
    {
        if (num == -1)num = INIT_POOL_SIZE;
        pool_t pool = (pool_t)malloc(num * MEMPAGE);
        if (pool == NULL)return NULL;
        pool->start = (char*)pool + sizeof(radix_pool);
        pool->size = num * MEMPAGE - sizeof(radix_pool);
        pool->next = this->pool->next;
        pool->prev = this->pool;
        this->pool->next->prev = pool;
        this->pool->next = pool;
        this->pool = pool;
        return pool;
    }
#endif

    //创建一个节点，从内存池中取出可以使用的节点/新建一个结点
    radix_node_t* radix_node_alloc()
    {
        radix_node_t* node;
        if (this->freelist != NULL) {//从free中提取节点
            node = this->freelist;
            this->freelist = node->parent;
        }
        else {//在内存池中寻找可以使用的内存

#ifdef MEMPOOL
            if (this->pool->size < sizeof(radix_node_t)) {//如果剩余空间不够分配，则重新分配
                get_new_pool(-1);
            }
            node = (radix_node_t*)(this->pool->start);
            this->pool->start += sizeof(radix_node_t);
            this->pool->size -= sizeof(radix_node_t);
#else
            node = (radix_node_t *)malloc(sizeof(radix_node_t));
#endif

        }

        for (size_t i = 0; i < (1 << BITS); i++)
        {
            node->child[i] = NULL;
        }
        
        node->parent = NULL;
        node->value = NULL;
        return node;
    }

    //打印函数，会打印出所有叶节点储存的值
    void radix_print(radix_node_t* node)
    {
        if (node == NULL) return;
        if (node->value != NULL)
            cout << node->value << endl;

        for (size_t i = 0; i < (1 << BITS); i++)
        {
            radix_print(node->child[i]);
        }
    }

public:

    RadixTree(){

        radix_node_t* ns;

#ifdef MEMPOOL
        int i;
        char* p = (char*)malloc(INIT_POOL_SIZE);

        //为内存池结构分配空间
        ((pool_t)p)->next = (pool_t)p;
        ((pool_t)p)->prev = (pool_t)p;
        ns = (radix_node_t*)((char*)p + sizeof(radix_pool));
        //在内存中创建链表

        int nodenum = max(INIT_NODE_NUM, (int)(INIT_POOL_SIZE - sizeof(radix_pool)) / sizeof(radix_node_t));
        for ( i = 1; i < nodenum; ++i) {
            ns[i].parent = &ns[i + 1];
        }

        ns[i].parent = NULL;

        for (size_t i = 0; i < (1 << BITS); i++)
        {
            ns[0].child[i] = NULL;
        }

        ns[0].parent = NULL;
        ns[0].value = NULL;

        ((pool_t)p)->start = (char*)ns + sizeof(radix_node_t) * INIT_NODE_NUM;
        ((pool_t)p)->size = INIT_POOL_SIZE - sizeof(radix_pool) - sizeof(radix_node_t) * INIT_NODE_NUM;

        this->pool = (pool_t)p;
        this->root = ns;
        this->freelist = &ns[1];  
#else
        ns = (radix_node_t *)malloc(sizeof(radix_node_t));
        
        ns->parent = NULL;

        for (size_t i = 0; i < (1 << BITS); i++)
        {
            ns->child[i] = NULL;
        }

        ns->value = NULL;
        this->root = ns;
        this->freelist = NULL;  
#endif

    }

    ~RadixTree(){

#ifdef MEMPOOL
        pool_t p = this->pool;
        while(p->next){
            pool_t next = p->next;
            p->prev->next = NULL;
            free(p);
            p = next;
        }
#else

        if(this->root){
            vector<radix_node_t *> nodes;
            nodes.push_back(this->root);
            this->root = NULL;

            while(nodes.size()){
                radix_node_t * node = nodes.back();
                nodes.pop_back();
                for (size_t i = 0; i < (1 << BITS); i++)
                {
                    if(node->child[i]) nodes.push_back(node->child[i]);
                }

                free(node);
            }
        }
#endif
    }

    int insert(key_t key, value_t value){
        int i, temp;
        radix_node_t* node, * child;
        node = this->root;
        for (i = 0; i < radix_tree_height; i++) {
            temp = CHECK_BITS(key, i);
            if (!node->child[temp]) {
                child = radix_node_alloc();
                if (!child)return NULL;
                child->parent = node;
                node->child[temp] = child;
                node = node->child[temp];
            }
            else {
                node = node->child[temp];
            }
        }
        if (node->value == value)return RADIX_INSERT_VALUE_SAME;
        if (node->value != NULL)return RADIX_INSERT_VALUE_OCCUPY;
        node->value = value;
        return 0;
    }

    int deleteNode(key_t key){
        radix_node_t* node = this->root, * par;
        int i = 0, temp = 0;
        if (node == NULL)return RADIX_DELETE_ERROR;
        do {
            temp = CHECK_BITS(key, i++);
            node = node->child[temp];
        } while (node && i < radix_tree_height);
        //node为储存value的节点，在父节点中将此节点的链接置空，
        //然后清空value后将此节点加入free中
        if (node == NULL)return RADIX_DELETE_ERROR;
        par = node->parent;
        par->child[temp] = NULL;
        node->value = NULL;
        
        for (size_t i = 0; i < (1 << BITS); i++)
        {
            node->child[i] = NULL;
        }
        
        node->parent = this->freelist->parent;
        this->freelist->parent = node;
        return 0;
    }

    

    //节点查找函数
    //key为索引，返回叶节点被查找到的值
    value_t find(key_t key)
    {
        int i = 0, temp;
        radix_node_t* node;
        node = this->root;
        while (node && i < radix_tree_height) {
            temp = CHECK_BITS(key, i++);
            node = node->child[temp];
        }
        if (node == NULL) return NULL;
        return node->value;
    }

    void print(){
        radix_print(this->root);
    }

};







