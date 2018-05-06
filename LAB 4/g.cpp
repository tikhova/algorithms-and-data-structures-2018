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
 
struct xBarrier {
    int x = 0;
    bool type = true;
    int yUp = 0;
    int yDown = 0;
};
 
struct node {
    int value = 0;
    int addition = 0;
};
 
void push(node * tree, int v) {
    tree[(v << 1) + 1].addition += tree[v].addition;
    tree[(v << 1) + 2].addition += tree[v].addition;
    tree[v].value = tree[v].value + tree[v].addition;
    tree[v].addition = 0;
}
 
void add(node * tree, int v, int cl, int cr, int l, int r, int value) {
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
 
int search(node * tree, int v, int cl, int cr) {
    if (cl == cr) {
        return cl;
    }
 
    push(tree, v);
    int cm = (cl + cr) / 2;
    if (tree[v].value + tree[v].addition == tree[(v << 1) + 1].value + tree[(v << 1) + 1].addition) {
        return search(tree, (v << 1) + 1, cl, cm);
    }
    else if (tree[v].value + tree[v].addition == tree[(v << 1) + 2].value + tree[(v << 1) + 2].addition) {
        return search(tree, (v << 1) + 2, cm + 1, cr);
    }
    return -1;
}
 
bool operator <(xBarrier a, xBarrier b) {
    if (a.x < b.x) {
        return true;
    }
    if (a.x == b.x && a.type == true && b.type == false) {
        return true;
    }
    return false;
}
 
 
int main() {
    int n;
    scanf("%d", &n);
    xBarrier * x = new xBarrier[n * 2];
    int y1, y2;
    int minY = INT16_MAX;
    int maxY = INT16_MIN;
    int size;
    int maxWindows = INT16_MIN, answerX = 0, answerY = 0;
     
    //create array of xBariers
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d%d", &x[i].x, &y1, &x[n + i].x, &y2);
        x[i].yDown = min(y1, y2);
        x[i].yUp = max(y1, y2);
        x[n + i].yDown = x[i].yDown;
        x[n + i].yUp = x[i].yUp;
        x[n + i].type = false;
        minY = min(minY, x[i].yDown);
        minY = min(minY, x[n + i].yDown);
        maxY = max(maxY, x[i].yUp);
        maxY = max(maxY, x[n + i].yUp);
    }
    for (int i = 0; i < n; i++) {
        x[i].yDown -= minY;
        x[i].yUp -= minY;
        x[n + i].yDown -= minY;
        x[n + i].yUp -= minY;
    }
    sort(x, x + n * 2);
 
    //build a max-tree
    size = maxY - minY;
    node * tree = new node[size * 4];
 
    //set maxWindows on this xBorder
    for (int i = 0; i < 2 * n; ++i) {
        add(tree, 0, 0, size, x[i].yDown, x[i].yUp, x[i].type ? 1 : -1);
        y1 = search(tree, 0, 0, size);
        if (y1 != -1) {
            if (tree[0].value > maxWindows) {
                maxWindows = tree[0].value;
                answerX = x[i].x;
                answerY = y1;
            }
        }
    }
    printf("%d\n%d %d", maxWindows, answerX, answerY + minY);
    return 0;
}