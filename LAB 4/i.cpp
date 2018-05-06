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
    int l;
    int r;
    int count;
    long long max = 0;
    long long total = 0;
    node * left = nullptr;
    node * right = nullptr;
    bool resetFlag = true;
};
 
void push(node &v) {
    if (v.left == nullptr && v.right == nullptr) {
        v.left = new node{ v.l, (v.r + v.l) / 2, (v.r + v.l) / 2 - v.l + 1, 0, 0, nullptr, nullptr, true };
        v.right = new node{ (v.r + v.l) / 2 + 1, v.r, v.r - ((v.r + v.l) / 2 + 1) + 1, 0, 0, nullptr, nullptr, true };
    }
    if (v.resetFlag) {
        (*v.left).max = (*v.left).total = v.total * (*v.left).count / v.count;
        (*v.right).max = (*v.right).total = v.total - (*v.left).total;
        v.resetFlag = false;
        (*v.left).resetFlag = true;
        (*v.right).resetFlag = true;
    }
    return;
}
 
void set(node &v, int a, int b, long long value) {
    if (a > b) {
        return;
    }
 
    if (v.l == a && v.r == b) {
        v.resetFlag = true;
        v.max = v.total = value * (v.r - v.l + 1);
        return;
    }
 
    push(v);
 
    int cm = (v.l + v.r) / 2;
    set(*v.left, a, min(b, cm), value);
    set(*v.right, max(a, cm + 1), b, value);
 
    v.total = (*v.left).total + (*v.right).total;
    v.max = max((*v.left).max, (*v.left).total + (*v.right).max);
}
 
long long sum(node &v, long long h) {
    if (v.r == v.l) {
        if (v.max <= h) {
            return v.l + 1;
        }
        return v.l;
    }
 
    push(v);
 
    if ((*v.left).max > h) {
        return sum((*v.left), h);
    }
 
    return sum((*v.right), h - (*v.left).total);
}
 
int main() {
    //freopen("rmq.in", "r", stdin);
    int n;
    int a, b;
    long long v;
    char command;
    scanf("%d\n", &n);
    node root = { 0, n - 1, n, 0, 0, nullptr, nullptr };
    do {
        scanf("%c", &command);
        switch (command) {
        case 'Q': scanf("%lld\n", &v);
            printf("%lld\n", sum(root, v));
            break;
        case 'I': scanf("%d%d%lld\n", &a, &b, &v);
            set(root, a - 1, b - 1, v);
        }
    } while (command != 'E');
    return 0;
}