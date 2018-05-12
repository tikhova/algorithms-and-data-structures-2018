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
using namespace std;
 
struct node {
    int y;
    int c;
    int value;
    bool hasZero;
    node * left = nullptr;
    node * right = nullptr;
};
 
int getC(node * t) {
    if (t) {
        return t->c;
    }
    return 0;
}
 
void fix(node * t) {
    if (!t) {
        return;
    }
    t->c = getC(t->left) + getC(t->right) + 1;
}
 
void split(node * t, int x, node *&t1, node *&t2) {
    if (!t) {
        t1 = t2 = nullptr;
        return;
    }
    int k = getC(t->left) + 1;
    if (k <= x) {
        split(t->right, x - k, t->right, t2);
        t1 = t;
    }
    else {
        split(t->left, x, t1, t->left);
        t2 = t;
    }
    fix(t);
}
 
node * merge(node * t1, node * t2) {
    if (t1 == nullptr) {
        return t2;
    }
    if (t2 == nullptr) {
        return t1;
    }
    if (t1->y > t2->y) {
        t1->right = merge(t1->right, t2);
        fix(t1);
        return t1;
    }
    else {
        t2->left = merge(t1, t2->left);
        fix(t2);
        return t2;
    }
}
 
node * newTreap(vector<int> a) {
    node * res = nullptr;
    for (int i = 0; i < a.size(); ++i) {
        res = merge(res, new node{ rand(), 1, a.at(i), true });
    }
    return res;
}
 
node * moveToFront(node * t, int l, int r) {
    node * t1, *t2, *t3;
    split(t, l, t1, t2);
    split(t2, r + 1 - l, t2, t3);
    return merge(merge(t2, t1), t3);
}
 
void getArray(node * t) {
    if (!t) {
        return;
    }
    getArray(t->left);
    printf("%d ", t->value);
    getArray(t->right);
}
 
int main() {
    int n, m, x, y;
    vector<int> a;
 
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        a.push_back(i);
    }
    node * root = newTreap(a);
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &x, &y);
        root = moveToFront(root, x - 1, y - 1);
    }
    getArray(root);
    return 0;
}