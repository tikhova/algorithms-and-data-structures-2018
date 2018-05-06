#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
 
#include <cstdio>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
 
struct node {
    int value = 0;
    bool resetFlag = false;
    int left;
    int right;
};
 
void build(node * t, int cur, int tl, int tr) {
    t[cur].left = tl;
    t[cur].right = tr;
    if (tl == tr) {
        return;
    }
    int tm = (tl + tr) / 2;
    build(t, cur * 2 + 1, tl, tm);
    build(t, cur * 2 + 2, tm + 1, tr);
}
 
void push(node * tree, int v) {
    if (tree[v].resetFlag) {
        tree[(v << 1) + 1].value = max(tree[v].value, tree[(v << 1) + 1].value);
        tree[(v << 1) + 2].value = max(tree[v].value, tree[(v << 1) + 2].value);
        tree[v].resetFlag = false;
        tree[(v << 1) + 1].resetFlag = true;
        tree[(v << 1) + 2].resetFlag = true;
    }
}
 
void set(node * tree, int v, int cl, int cr, int l, int r, int value) {
    if (l > r)
        return;
 
    if (l == cl && cr == r) {
        tree[v].value = max(tree[v].value, value);
        tree[v].resetFlag = true;
        return;
    }
 
    push(tree, v);
    int cm = (cl + cr) / 2;
    set(tree, (v << 1) + 1, cl, cm, l, min(r, cm), value);
    set(tree, (v << 1) + 2, cm + 1, cr, max(l, cm + 1), r, value);
    tree[v].value = min(tree[(v << 1) + 1].value, tree[(v << 1) + 2].value);
}
 
int get(node * tree, int v, int cl, int cr) {
    if (cl == cr) {
        return cl;
    }
 
    int cm = (cl + cr) / 2;
    push(tree, v);
    if (tree[(v << 1) + 1].value == tree[v].value) {
        return get(tree, (v << 1) + 1, cl, cm);
    }
    else {
        return get(tree, (v << 1) + 2, cm + 1, cr);
    }
}
 
int treeMin(node * tree, int v, int cl, int cr, int l, int r) {
    if (l > r)
        return -1;
 
    if (l == cl && r == cr) {
        return v;
    }
 
    int cm = (cl + cr) / 2;
    push(tree, v);
    int a = treeMin(tree, (v << 1) + 1, cl, cm, l, min(r, cm));
    int b = treeMin(tree, (v << 1) + 2, cm + 1, cr, max(l, cm + 1), r);
    if ((a == -1 ? INT_MAX : tree[a].value) < (b == -1 ? INT_MAX : tree[b].value)) {
        return a;
    }
    return b;
}
 
int main() {
    //freopen("rmq.in", "r", stdin);
    int n, m;
    int a, b, c;
    string command;
    scanf("%d%d\n", &n, &m);
    node * tree = new node[n * 4];
    build(tree, 0, 0, n - 1);
    for (int i = 0; i < m; ++i) {
        cin >> command;
        if (command.compare("defend") == 0) {
            scanf("%d%d%d", &a, &b, &c);
            set(tree, 0, 0, n - 1, a - 1, b - 1, c);
        }
        else if (command.compare("attack") == 0) {
            scanf("%d%d", &a, &b);
            c = treeMin(tree, 0, 0, n - 1, a - 1, b - 1);
            printf("%d %d\n", tree[c].value, get(tree, c, tree[c].left, tree[c].right) + 1);
        }
    }
    return 0;
}