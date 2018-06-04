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
    int height;
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
    bool resetFlag = false;
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
    if (tree[v].resetFlag) {
        tree[(v << 1) + 1].value = tree[v].value;
        tree[(v << 1) + 2].value = tree[v].value;
        tree[v].resetFlag = false;
        tree[(v << 1) + 1].resetFlag = true;
        tree[(v << 1) + 2].resetFlag = true;
        tree[(v << 1) + 1].addition = 0;
        tree[(v << 1) + 2].addition = 0;
    }
    tree[(v << 1) + 1].addition += tree[v].addition;
    tree[(v << 1) + 2].addition += tree[v].addition;
    tree[v].value = tree[v].value + tree[v].addition;
    tree[v].addition = 0;
}
 
void change(STnode * tree, int v, int l, int r, int cl, int cr, int value) {
    if (l > r)
        return;
 
    if (l == cl && cr == r) {
        tree[v].value = value;
        tree[v].addition = 0;
        return;
    }
 
    int cm = (cl + cr) / 2;
    change(tree, (v << 1) + 1, l, min(r, cm), cl, cm, value);
    change(tree, (v << 1) + 2, max(l, cm + 1), r, cm + 1, cr, value);
    tree[v].value = max(
        tree[(v << 1) + 1].value + tree[(v << 1) + 1].addition,
        tree[(v << 1) + 2].value + tree[(v << 1) + 2].addition);
    tree[v].addition = 0;
}
 
void change(STnode * tree, int v, int x, int cl, int cr, int value) {
    change(tree, v, x, x, cl, cr, value);
}
 
long long treeMax(STnode * tree, int v, int cl, int cr, int l, int r) {
    if (l > r) {
        return LLONG_MIN;
    }
 
    if (l == cl && r == cr) {
        return tree[v].value + tree[v].addition;
    }
 
    int cm = (cl + cr) / 2;
    push(tree, v);
    return max(
        treeMax(tree, (v << 1) + 1, cl, cm, l, min(r, cm)),
        treeMax(tree, (v << 1) + 2, cm + 1, cr, max(l, cm + 1), r)
    );
}
 
long long crawl(int u, int v) {
    int chain_v = tree.at(v)->chain;
    int chain_u = tree.at(u)->chain;
    long long ans = LLONG_MIN;
 
    while (chain_u != chain_v) {
        ans = max(ans, treeMax(chainsST.at(chain_u), 0, 0,
            chains.at(chain_u)->size() - 1, 0, tree.at(u)->id));
        u = tree.at(chains.at(chain_u)->front())->parent->index;
        chain_u = tree.at(u)->chain;
    }
    return max(treeMax(chainsST.at(chain_v), 0, 0, chains.at(chain_v)->size() - 1,
        tree.at(v)->id,  tree.at(u)->id), ans);
}
 
long long findMax(int x, int y) {
    int curr_lca = lca(x, y);
    return max(crawl(x, curr_lca), crawl(y, curr_lca));
}
 
int main() {
    freopen("mail.in", "r", stdin);
    freopen("mail.out", "w", stdout);
 
    int n;
    scanf("%d", &n);
 
    int h;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &h);
        tree.push_back(new node{ i, h });
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
 
    scanf("%d\n", &h);
    char command;
    for (int i = 0; i < h; ++i) {
        scanf("%c %d %d\n", &command, &x, &y);
        switch (command) {
        case '!':
            change(chainsST.at(tree.at(x - 1)->chain), 0, tree.at(x - 1)->id,
                0, chains.at(tree.at(x - 1)->chain)->size() - 1, y);
            break;
        case '?':
            printf("%lld\n", findMax(x - 1, y - 1));
            break;
        }
    }
 
    return 0;
}