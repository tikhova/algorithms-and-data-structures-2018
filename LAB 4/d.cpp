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
 
int lineLength;
 
struct node {
    long long length = 0;
    long long count = 0;
    int color = 0; // 0 for white, 1 for black, -1 for mixed
};
 
void build(node * tree, long long * a, int v, int cl, int cr) {
    if (cl == cr)
        tree[v].length = a[cl];
    else {
        int cm = (cl + cr) / 2;
        build(tree, a, (v << 1) + 1, cl, cm);
        build(tree, a, (v << 1) + 2, cm + 1, cr);
    }
}
 
void push(node * tree, int v) {
    if (tree[v].color != -1) {
        tree[(v << 1) + 1].color = tree[v].color;
        tree[(v << 1) + 2].color = tree[v].color;
        tree[(v << 1) + 1].length = (tree[v].length + 1) / 2;
        tree[(v << 1) + 2].length = tree[v].length - tree[(v << 1) + 1].length;
        tree[(v << 1) + 1].count = tree[v].color;
        tree[(v << 1) + 2].count = tree[v].color;
    }
}
 
long long get(node * tree, int v, int cl, int cr, int x) {
    if (cl == cr)
        return tree[v].color;
    push(tree, v);
    int cm = (cl + cr) / 2;
    if (x <= cm) {
        get(tree, (v << 1) + 1, cl, cm, x);
    }
    else {
        get(tree, (v << 1) + 2, cm + 1, cr, x);
    }
}
 
void set(node * tree, int v, int l, int r, int cl, int cr, int value) {
    if (l > r)
        return;
 
    if (l == cl && cr == r) {
        tree[v].color = value;
        tree[v].length = value * (r - l + 1);
        tree[v].count = value;
        return;
    }
 
    push(tree, v);
    int cm = (cl + cr) / 2;
    set(tree, (v << 1) + 1, l, min(r, cm), cl, cm, value);
    set(tree, (v << 1) + 2, max(l, cm + 1), r, cm + 1, cr, value);
 
    tree[v].color = (tree[(v << 1) + 1].color == tree[(v << 1) + 2].color) ? tree[(v << 1) + 1].color : -1;
    tree[v].length = tree[(v << 1) + 1].length + tree[(v << 1) + 2].length;
    tree[v].count = tree[(v << 1) + 1].count + tree[(v << 1) + 2].count;
    if (get(tree, v, cl, cr, cm) == 1 && get(tree, v, cl, cr, cm + 1) == 1) {
        tree[v].count--;
    }
}
 
long long sum(node * tree, int v, int cl, int cr, int l, int r) {
    if (l > r)
        return 0;
    if (l == cl && r == cr)
        return tree[v].length;
 
    push(tree, v);
    int cm = (cl + cr) / 2;
    return sum(tree, (v << 1) + 1, cl, cm, l, min(r, cm)) +
        sum(tree, (v << 1) + 2, cm + 1, cr, max(l, cm + 1), r);
}
 
int main() {
    freopen("painter.in", "r", stdin);
    freopen("painter.out", "w", stdout);
 
    int n;
    scanf("%d", &n);
    char * color = new char[n];
    int * leftBorder = new int[n];
    int * rightBorder = new int[n];
    int minBorder = INT16_MAX;
    int maxBorder = INT16_MIN;
    for (int i = 0; i < n; i++) {
        scanf("%c", &color[i]);
        scanf("%c%d%d", &color[i], &leftBorder[i], &rightBorder[i]);
        rightBorder[i] += leftBorder[i];
        minBorder = min(minBorder, leftBorder[i]);
        maxBorder = max(maxBorder, rightBorder[i]);
    }
    lineLength = maxBorder - minBorder;
    node * tree = new node[lineLength * 4];
 
    for (int i = 0; i < n; i++) {
        leftBorder[i] -= minBorder;
        rightBorder[i] -= minBorder;
    }
     
    for (int i = 0; i < n; i++) {
        if (color[i] == 'W') {
            set(tree, 0, leftBorder[i], rightBorder[i] - 1, 0, lineLength - 1, 0);
        }
        else {
            set(tree, 0, leftBorder[i], rightBorder[i] - 1, 0, lineLength - 1, 1);
        }
        printf("%lld %lld\n", tree[0].count, sum(tree, 0, 0, lineLength - 1, 0, lineLength - 1));
    }
    return 0;
}