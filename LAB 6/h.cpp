#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
 
#include <cstdio>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <math.h>
using namespace std;
 
int l;
 
struct node {
    int index;
    node * parent;
    set<int> children;
    int depth;
    int s = 1;
    int color;
};
 
vector<int> lastVisited;
vector<node *> tree;
int ** dp;
int depth = 0;
 
void makeParent(int x) {
    for (set<int>::iterator it = tree.at(x)->children.begin();
        it != tree.at(x)->children.end(); ++it) {
        tree.at(*it)->parent = tree.at(x);
        tree.at(*it)->children.erase(x);
        makeParent(*it);
    }
}
 
void dfs(int v) {
    tree.at(v)->depth = ++depth;
 
    dp[v][0] = tree.at(v)->parent->index;
    for (int i = 1; i < l; ++i) {
        dp[v][i] = dp[dp[v][i - 1]][i - 1];
    }
 
    for (set<int>::iterator it = tree.at(v)->children.begin();
        it != tree.at(v)->children.end(); ++it) {
        dfs(*it);
    }
 
    --depth;
}
 
int lca(int x, int y) {
    if (tree.at(x)->depth > tree.at(y)->depth) {
        swap(x, y);
    }
 
    int d;
    while (d = tree.at(y)->depth - tree.at(x)->depth) {
        d = log(d) / log(2);
        y = dp[y][d];
    }
    if (x == y) {
        return x;
    }
    for (int i = l - 1; i >= 0; --i) {
        if (dp[x][i] != dp[y][i]) {
            x = dp[x][i];
            y = dp[y][i];
        }
    }
    return dp[x][0];
}
 
void colorCount(int index) {
    for (set<int>::iterator it = tree.at(index)->children.begin();
        it != tree.at(index)->children.end(); ++it) {
        colorCount(*it);
        tree.at(index)->s += tree.at(*it)->s;
        int i = tree.at(index)->s;
    }
    int col = tree.at(index)->color;
    if (lastVisited.at(col) != -1) {
        tree.at(lca(index, lastVisited.at(col)))->s--;
    }
    lastVisited.at(col) = index;
}
 
int main() {
    int n, m, x, y;
    int parent = -1;
    char c;
    scanf("%d", &n);
 
    if (n == 1) {
        printf("1");
        return 0;
    }
    l = ceil(log(n - 1) / log(2));
    dp = new int *[n];
    for (int i = 0; i < n; ++i) {
        tree.push_back(new node{i});
        dp[i] = new int[l];
        lastVisited.push_back(-1);
    }
 
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &x, &y);
        if (x == 0) {
            parent = i;
            tree.at(i)->parent = tree.at(i);
        }
        --x;
        --y;
        if (x != -1) {
            tree.at(i)->children.insert(x);
            tree.at(x)->children.insert(i);
        }
        tree.at(i)->color = y;
    }
 
    makeParent(parent);
    dfs(parent);
    colorCount(parent);
 
    for (int i = 0; i < n; ++i) {
        printf("%i ", tree.at(i)->s);
    }
         
    return 0;
}