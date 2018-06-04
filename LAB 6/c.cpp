#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
 
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <math.h>
using namespace std;
 
 
struct node {
    int index;
    int height = 0;
    node * parent = nullptr;
    set<int> children;
    int s = 1;
    int chain;
    int id;
    int depth;
};
 
struct STnode {
    long long value = 0;
    long long addition = 0;
};
 
vector<node *> tree;
vector<vector<int> *> chains;
vector<STnode *> chainsST;
 
void makeParent(int x) {
    for (set<int>::iterator it = tree.at(x)->children.begin();
        it != tree.at(x)->children.end(); ++it) {
        tree.at(*it)->parent = tree.at(x);
        tree.at(*it)->children.erase(x);
        makeParent(*it);
        tree.at(x)->s += tree.at(*it)->s;
    }
}
 
void dfs(node * x, int d) {
    x->depth = d;
    for (set<int>::iterator it = x->children.begin(); it != x->children.end(); ++it) {
        dfs(tree.at(*it), d + 1);
    }
}
 
void hld(node * curr_node, int ch_id) {
    chains.at(ch_id)->push_back(curr_node->index);
    curr_node->chain = ch_id;
    curr_node->id = chains.at(ch_id)->size() - 1;
 
    int max_id = -1, m = INT_MIN;
    for (set<int>::iterator it = curr_node->children.begin();
        it != curr_node->children.end(); ++it) {
        if (tree.at(*it)->s > m) {
            m = tree.at(*it)->s;
            max_id = *it;
        }
    }
    if (max_id != -1) {
        hld(tree.at(max_id), ch_id);
    }
 
    for (set<int>::iterator it = curr_node->children.begin();
        it != curr_node->children.end(); ++it) {
        if (*it != max_id) {
            chains.push_back(new vector<int>);
            hld(tree.at(*it), chains.size() - 1);
        }
    }
}
 
int lca(int x, int y) {
    int chain_x = tree.at(x)->chain;
    int chain_y = tree.at(y)->chain;
    if (chain_x == chain_y) {
        return tree.at(x)->depth < tree.at(y)->depth ? x : y;
    }
    int root_x = chains.at(chain_x)->front() == 0 ?
        0 : tree.at(chains.at(chain_x)->front())->parent->index;
    int root_y = chains.at(chain_y)->front() == 0 ?
        0 : tree.at(chains.at(chain_y)->front())->parent->index;
    if (tree.at(root_x)->depth > tree.at(root_y)->depth) {
        return lca(root_x, y);
    }
    if (root_x == root_y) {
        return root_x;
    }
    return lca(x, root_y);
}
 
void build(STnode * STtree, vector<int> * a, int v, int cl, int cr) {
    if (cl == cr)
        STtree[v].value = tree.at(a->at(cl))->height;
    else {
        int cm = (cl + cr) / 2;
        build(STtree, a, (v << 1) + 1, cl, cm);
        build(STtree, a, (v << 1) + 2, cm + 1, cr);
        STtree[v].value = max(STtree[(v << 1) + 1].value, STtree[(v << 1) + 2].value);
    }
}
 
void buildST(vector<vector<int> *> chains) {
    for (int i = 0; i < chains.size(); ++i) {
        chainsST.push_back(new STnode[chains.at(i)->size() * 4]);
        build(chainsST.at(i), chains.at(i), 0, 0, chains.at(i)->size() - 1);
    }
}
 
void push(STnode * tree, int v) {
    tree[(v << 1) + 1].addition += tree[v].addition;
    tree[(v << 1) + 2].addition += tree[v].addition;
    tree[v].value = tree[v].value + tree[v].addition;
    tree[v].addition = 0;
}
 
void add(STnode * tree, int v, int cl, int cr, int l, int r, int value) {
    if (l > r)
        return;
    if (l == cl && cr == r) {
        tree[v].addition += value;
        return;
    }
 
    push(tree, v);
    int cm = (cl + cr) / 2;
    add(tree, (v << 1) + 1, cl, cm, l, min(r, cm), value);
    add(tree, (v << 1) + 2, cm + 1, cr, max(l, cm + 1), r, value);
    tree[v].value = max(
        tree[(v << 1) + 1].value + tree[(v << 1) + 1].addition,
        tree[(v << 1) + 2].value + tree[(v << 1) + 2].addition);
    tree[v].addition = 0;
}
 
void crawl(int u, int v, int value) {
    int chain_v = tree.at(v)->chain;
    int chain_u = tree.at(u)->chain;
 
    while (chain_u != chain_v) {
        add(chainsST.at(chain_u), 0, 0, chains.at(chain_u)->size() - 1,
            0, tree.at(u)->id, value);
        u = tree.at(chains.at(chain_u)->front())->parent->index;
        chain_u = tree.at(u)->chain;
    }
    add(chainsST.at(chain_v), 0, 0, chains.at(chain_v)->size() - 1,
        tree.at(v)->id, tree.at(u)->id, value);
}
 
void add(int x, int y, int value) {
    int curr_lca = lca(x, y);
    crawl(x, curr_lca, value);
    crawl(y, curr_lca, value);
    add(chainsST.at(tree.at(curr_lca)->chain),
        0, 0, chains.at(tree.at(curr_lca)->chain)->size() - 1,
        tree.at(curr_lca)->id, tree.at(curr_lca)->id, -value);
}
 
long long get(STnode * tree, int v, int cl, int cr, int x) {
    if (cl == cr)
        return tree[v].value + tree[v].addition;
 
    push(tree, v);
    int cm = (cl + cr) / 2;
    if (x <= cm) {
        get(tree, (v << 1) + 1, cl, cm, x);
    }
    else {
        get(tree, (v << 1) + 2, cm + 1, cr, x);
    }
}
 
int main() {
    int n;
    scanf("%d", &n);
 
    for (int i = 0; i < n; ++i) {
        tree.push_back(new node{ i });
    }
 
    int x, y;
    for (int i = 1; i < n; ++i) {
        scanf("%d %d", &x, &y);
        tree.at(x - 1)->children.insert(y - 1);
        tree.at(y - 1)->children.insert(x - 1);
    }
 
    makeParent(0);
    chains.push_back(new vector<int>);
    hld(tree.at(0), 0);
    dfs(tree.at(0), 0);
    buildST(chains);
 
    int h;
    scanf("%d\n", &h);
    char command;
    long long d;
    for (int i = 0; i < h; ++i) {
        scanf("%c", &command);
        switch (command) {
        case '+':
            scanf("%d %d %lld\n", &x, &y, &d);
            add(x - 1, y - 1, d);
            break;
        case '?':
            scanf("%d\n", &x);
            x--;
            printf("%lld\n", get(chainsST.at(tree.at(x)->chain),
                0, 0, chains.at(tree.at(x)->chain)->size() - 1, tree.at(x)->id));
            break;
        }
    }
 
    return 0;
}