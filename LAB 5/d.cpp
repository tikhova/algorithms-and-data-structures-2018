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
vector<int> a;
 
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
 
bool getHasZero(node * t) {
    if (t) {
        return t->hasZero;
    }
    return false;
}
 
void fix(node * t) {
    if (!t) {
        return;
    }
    t->c = getC(t->left) + getC(t->right) + 1;
    t->hasZero = t->value == 0 || getHasZero(t->left) || getHasZero(t->right);
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
 
node * newTreap(int n) {
    node * res = nullptr;
    for (int i = 0; i < n; ++i) {
        res = merge(res, new node{ rand(), 1, 0, true });
    }
    return res;
}
 
node * del(node * t, int x) {
    node *t1, *t2, *t3, *t4;
    split(t, x, t1, t2);
    split(t2, 1, t3, t4);
    t = merge(t1, t4);
    fix(t);
    return t;
}
 
int findZero(node * t) {
    if (!t || !getHasZero(t)) {
        return -1;
    }
    if (getHasZero(t->left)) {
        return findZero(t->left);
    }
    if (t->value == 0) {
        return getC(t->left);
    }
    if (findZero(t->right) == -1) {
        return -1;
    }
    return getC(t->left) + 1 + findZero(t->right);
}
 
node * insert(node * t, int l, int k) {
    node * t1 = nullptr;
    node * t2 = nullptr;
    int size = getC(t);
    if (size < l) {
        t = merge(t, newTreap(l - size));
    }
    split(t, l, t1, t2);
    int x = findZero(t2);
    if (x != -1) {
        t2 = del(t2, x);
    }
    node * root = new node{ rand(), 1, k };
    return merge(merge(t1, root), t2);
}
 
void getArray(node * t) {
    if (!t) {
        return;
    }
    getArray(t->left);
    printf("%d ", t->value);
    getArray(t->right);
}
 
int main() {int n, m, x;
    scanf("%d%d", &n, &m);
    node * root = nullptr;
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        root = insert(root, x - 1, i + 1);
    }
    printf("%d\n", root->c);
    getArray(root);
    return 0;
}