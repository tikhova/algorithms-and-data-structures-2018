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
    long long value = LLONG_MIN;
};
 
void push(node * tree, int v) {
    tree[(v << 1) + 1].value = max(tree[(v << 1) + 1].value, tree[v].value);
    tree[(v << 1) + 2].value = max(tree[(v << 1) + 2].value, tree[v].value);
}
 
void set(node * tree, int v, int l, int r, int cl, int cr, long long value) {
    if (l > r)
        return;
 
    if (l == cl && cr == r) {
        tree[v].value = max(value, tree[v].value);
        return;
    }
 
    push(tree, v);
    int cm = (cl + cr) / 2;
    set(tree, (v << 1) + 1, l, min(r, cm), cl, cm, value);
    set(tree, (v << 1) + 2, max(l, cm + 1), r, cm + 1, cr, value);
    tree[v].value = min(tree[(v << 1) + 1].value, tree[(v << 1) + 2].value);
}
 
long long treeMin(node * tree, int v, int l, int r, int cl, int cr) {
    if (l > r)
        return LLONG_MAX;
 
    if (l == cl && r == cr)
        return tree[v].value;
 
    int cm = (cl + cr) / 2;
    push(tree, v);
    return min(
        treeMin(tree, (v << 1) + 1, l, min(r, cm), cl, cm),
        treeMin(tree, (v << 1) + 2, max(l, cm + 1), r, cm + 1, cr)
    );
}
 
long long get(node * tree, int v, int cl, int cr, int x) {
    if (cl == cr)
        return tree[v].value;
 
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
    freopen("rmq.in", "r", stdin);
    freopen("rmq.out", "w", stdout);
    int n, m;
    scanf("%d%d", &n, &m);
    int * a = new int[m];
    int * b = new int[m];
    long long * v = new long long[m];
 
    node * tree = new node[n * 4];
 
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%lld", &a[i], &b[i], &v[i]);
        set(tree, 0, a[i] - 1, b[i] - 1, 0, n - 1, v[i]);
    }
     
    long long f;
    bool consistent = true;
    for (int i = 0; i < m && consistent; ++i) {
        f = treeMin(tree, 0, a[i] - 1, b[i] - 1, 0, n - 1);
        consistent = f == v[i];
    }
 
    long long k;
    if (consistent) {
        printf("consistent\n");
        for (int i = 0; i < n; ++i) {
            k = get(tree, 0, 0, n - 1, i);
            if (k == LLONG_MIN) {
                k = INT_MAX;
            }
            printf("%lld ", k);
        }
    }
    else {
        printf("inconsistent");
    }
    return 0;
}