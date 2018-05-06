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
 
void set(int * tree, int cur, int tl, int tr, int pos, int x) {
    if (tl == tr) {
        tree[cur] = x;
        return;
    }
    int tm = (tl + tr) / 2;
    if (pos <= tm) {
        set(tree, cur * 2 + 1, tl, tm, pos, x);
    }
    else {
        set(tree, cur * 2 + 2, tm + 1, tr, pos, x);
    }
    tree[cur] = min(tree[(cur << 1) + 2], tree[(cur << 1) + 1]);
}
 
void build(int * t, int cur, int tl, int tr) {
    if (tl > tr) {
        t[cur] = INT_MAX;
    }
    if (tl == tr) {
        t[cur] = tl;
        return;
    }
    int tm = (tl + tr) / 2;
    build(t, cur * 2 + 1, tl, tm);
    build(t, cur * 2 + 2, tm + 1, tr);
    t[cur] = min(t[(cur << 1) + 2], t[(cur << 1) + 1]);
}
 
int treeMin(int * tree, int v, int cl, int cr, int l, int r) {
    if (l > r)
        return INT_MAX;
 
    if (l == cl && r == cr)
        return tree[v];
 
    int cm = (cl + cr) / 2;
    return min(
        treeMin(tree, (v << 1) + 1, cl, cm, l, min(r, cm)),
        treeMin(tree, (v << 1) + 2, cm + 1, cr, max(l, cm + 1), r)
    );
}
 
int main() {
    freopen("parking.in", "r", stdin);
    freopen("parking.out", "w", stdout);
    int n, m, x, y;
    string command;
    scanf("%d%d\n", &n, &m);
    int * tree = new int[n * 4];
    build(tree, 0, 0, n - 1);
 
    for (int i = 0; i < m; ++i) {
        cin >> command >> x;
        if (command.compare("enter") == 0) {
            y = treeMin(tree, 0, 0, n - 1, x - 1, n - 1);
            if (y == INT_MAX) {
                y = treeMin(tree, 0, 0, n - 1, 0, x - 1);
            }
            set(tree, 0, 0, n - 1, y, INT_MAX);
            printf("%d\n", y + 1);
        }
        else if (command.compare("exit") == 0) {
            set(tree, 0, 0, n - 1, x - 1, x - 1);
        }
    }
    return 0;
}