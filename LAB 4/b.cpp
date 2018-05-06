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
 
void build(long long* a, long long * t, int cur, int tl, int tr) {
    if (tl == tr) {
        t[cur] = a[tl];
        return;
    }
    int tm = (tl + tr) / 2;
    build(a, t, cur * 2 + 1, tl, tm);
    build(a, t, cur * 2 + 2, tm + 1, tr);
    t[cur] = t[cur * 2 + 2] + t[cur * 2 + 1];
}
 
long long sum(long long* tree, int cur, int tl, int tr, int l, int r) {
    if (l > r) 
        return 0;
    if (l == tl && r == tr) 
        return tree[cur];
    int tm = (tl + tr) / 2;
    return sum(tree, cur * 2 + 1, tl, tm, l, min(r, tm)) +
           sum(tree, cur * 2 + 2, tm + 1, tr, max(l, tm + 1), r);
}
 
void set(long long* tree, int cur, int tl, int tr, int pos, int x) {
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
    tree[cur] = tree[cur * 2 + 1] + tree[cur * 2 + 2];  
}
 
 
int main() {
    freopen("rsq.in", "r", stdin);
    freopen("rsq.out", "w", stdout);
 
    int n, i, j;
    string command;
    scanf("%d", &n);
    long long b;
    long long * a = new long long[n];
    long long * tree = new long long[4 * n];
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }
    build(a, tree, 0, 0, n - 1);
 
    while (cin >> command >> i >> j) {
        if (command.compare("sum") == 0) {
            printf("%lld\n", sum(tree, 0, 0, n - 1, i - 1, j - 1));
        }
        else if (command.compare("set") == 0) {
            set(tree, 0, 0, n - 1, i - 1, j);
        }
    }
    return 0;
}