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
 
void build(long long * tree, long long * a, int n) {
    for (int i = 0; i < n; ++i) {
        tree[n - 1 + i] = a[i];
    }
    for (int i = n - 2; i >= 0; --i) {
        tree[i] = min(tree[(i << 1) + 1], tree[(i << 1) + 2]);
    }
}
 
long long ans(long long * tree, int l, int r) {
    long long leftRes = LLONG_MAX;
    long long rightRes = LLONG_MAX;
    while (l < r) {
        if (l % 2 == 0) {
            leftRes = min(leftRes, tree[l]);
        }
        l /= 2;
        if (r % 2 == 1) {
            rightRes = min(rightRes, tree[r]);
        }
        r = r / 2 - 1;
    }
    if (l == r) {
        leftRes = min(leftRes, tree[l]);
    }
    return min(leftRes, rightRes);
}
 
int main() {
    freopen("sparse.in", "r", stdin);
    freopen("sparse.out", "w", stdout);
 
    int n, m;
    scanf("%d%d", &n, &m);
    long long * a = new long long[n];
    long long * tree = new long long[n * 4];
 
    scanf("%lld", &a[0]);
    for (int i = 1; i < n; i++) {
        a[i] = (23 * a[i - 1] + 21563) % 16714589;
    }
    for (int i = 0; i < n * 4; i++) {
        tree[i] = LLONG_MAX;
    }
    build(tree, a, n);
     
    int u, v;
    long long answer;
    scanf("%d%d", &u, &v);
    answer = ans(tree, n - 2 + min(u, v), n - 2 + max(u, v));
    for (int i = 1; i < m; i++) {
        u = ((17 * u + 751 + answer + 2 * i) % n) + 1;
        v = ((13 * v + 593 + answer + 5 * i) % n) + 1;
        answer = ans(tree, n - 2 + min(u, v), n - 2 + max(u, v));
    }
    printf("%d %d %lld", u, v, answer);
    return 0;
}