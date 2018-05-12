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
    int x;
    int y;
    long long sum;
    node * left = nullptr;
    node * right = nullptr;
};
 
long long getSum(node * t) {
    if (t) {
        return t->sum;
    }
    return 0;
}
 
void fix(node * t) {
    if (!t) {
        return;
    }
    t->sum = getSum(t->left) + getSum(t->right) + t->x;
}
 
void split(node * t, int x, node *&t1, node *&t2) {
    if (!t) {
        t1 = t2 = nullptr;
        return;
    }
    if (t->x < x) {
        split(t->right, x, t->right, t2);
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
 
int getValue(node * t, int x) {
    if (!t) {
        return -1;
    }
    if (t->x == x) {
        return t->x;
    }
    if (x < t->x) {
        return getValue(t->left, x);
    }
    return getValue(t->right, x);
}
 
node * insert(node * t, int x) {
    node *t1, *t2, *t3;
    split(t, x, t1, t2);
    split(t2, x + 1, t2, t3);
    return merge(merge(t1, new node{ x, rand(), x }), t3);
}
 
long long sum(node * &t, int l, int r) {
    node * t1, *t2, *t3;
    split(t, l, t1, t2);
    split(t2, r + 1, t2, t3);
    long long res = getSum(t2);
    t = merge(t1, merge(t2, t3));
    return res;
}
 
int main() {
    node * root = nullptr;
    int n;
    scanf("%d\n", &n);
    char command;
    long long x, y;
    long long t = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%c", &command);
        if (command == '+') {
            scanf("%lld\n", &x);
            root = insert(root, (x + t) % 1000000000);
            t = 0;
        }
        else {
            scanf("%lld%lld\n", &x, &y);
            t = sum(root, x, y);
            printf("%lld\n", t);
            t %= 1000000000;
        }
    }
    return 0;
}