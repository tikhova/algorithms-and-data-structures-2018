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
    long long value = 0;
    bool resetFlag = false;
    long long addition = 0;
};
 
void build(node * tree, long long * a, int v, int cl, int cr) {
    if (cl == cr)
        tree[v].value = a[cl];
    else {
        int cm = (cl + cr) / 2;
        build(tree, a, (v << 1) + 1, cl, cm);
        build(tree, a, (v << 1) + 2, cm + 1, cr);
        tree[v].value = min(tree[(v << 1) + 1].value, tree[(v << 1) + 2].value);
    }
}
 
void push(node * tree, int v) {
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
 
void set(node * tree, int v, int l, int r, int cl, int cr, int value) {
    if (l > r)
        return;
    if (l == cl && cr == r) {
        tree[v].value = value;
        tree[v].resetFlag = true;
        tree[v].addition = 0;
        return;
    }
 
    push(tree, v);
    int cm = (cl + cr) / 2;
    set(tree, (v << 1) + 1, l, min(r, cm), cl, cm, value);
    set(tree, (v << 1) + 2, max(l, cm + 1), r, cm + 1, cr, value);
    tree[v].value = min(
        tree[(v << 1) + 1].value + tree[(v << 1) + 1].addition,
        tree[(v << 1) + 2].value + tree[(v << 1) + 2].addition);
    tree[v].addition = 0;
}
 
void add(node * tree, int v, int l, int r, int cl, int cr, int value) {
    if (l > r)
        return;
    if (l == cl && cr == r) {
        tree[v].addition += value;
        return;
    }
 
    push(tree, v);
    int cm = (cl + cr) / 2;
    add(tree, (v << 1) + 1, l, min(r, cm), cl, cm, value);
    add(tree, (v << 1) + 2, max(l, cm + 1), r, cm + 1, cr, value);
    tree[v].value = min(
        tree[(v << 1) + 1].value + tree[(v << 1) + 1].addition,
        tree[(v << 1) + 2].value + tree[(v << 1) + 2].addition);
    tree[v].addition = 0;
}
 
long long treeMin(node * tree, int v, int l, int r, int cl, int cr) {
    if (l > r) 
        return LLONG_MAX;
 
    if (l == cl && r == cr)
        return tree[v].value + tree[v].addition;
 
    int cm = (cl + cr) / 2;
    push(tree, v);
    return min(
        treeMin(tree, (v << 1) + 1, l, min(r, cm), cl, cm),
        treeMin(tree, (v << 1) + 2, max(l, cm + 1), r, cm + 1, cr)
    );
}
 
int main() {
    freopen("rmq2.in", "r", stdin);
    freopen("rmq2.out", "w", stdout);
 
    int n, i, j;
    long long x;
    string command;
    scanf("%d", &n);
    long long * a = new long long[n];
    node * tree = new node[4 * n];
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }
    build(tree, a, 0, 0, n - 1);
 
    while (cin >> command >> i >> j) {
        if (command.compare("min") == 0) {
            printf("%lld\n", treeMin(tree, 0, --i, --j, 0, n - 1));
        }
        else if (command.compare("set") == 0) {
            scanf("%lld", &x);
            set(tree, 0, --i, --j, 0, n - 1, x);
        }
        else if (command.compare("add") == 0) {
            scanf("%lld", &x);
            add(tree, 0, --i, --j, 0, n - 1, x);
        }
    }
    return 0;
}