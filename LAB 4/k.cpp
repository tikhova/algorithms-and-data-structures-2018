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
 
long long binpow(long a, long n) {
    long long result = 1;
    while (n > 0) {
        if (n & 1)
            result *= a;
        a *= a;
        n >>= 1;
    }
    return result;
}
 
void set(long long * tree, int cur, int tl, int tr, int pos, long long x) {
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
    tree[cur] = tree[(cur << 1) + 2] + tree[(cur << 1) + 1];
}
 
void buildSum(long long * a, long long * t, int cur, int tl, int tr) {
    if (tl == tr) {
        t[cur] = a[tl];
        return;
    }
    int tm = (tl + tr) / 2;
    buildSum(a, t, cur * 2 + 1, tl, tm);
    buildSum(a, t, cur * 2 + 2, tm + 1, tr);
    t[cur] = t[cur * 2 + 2] + t[cur * 2 + 1];
}
 
long long getSum(long long * tree, int cur, int tl, int tr, int l, int r) {
    if (l > r)
        return 0;
    if (l == tl && r == tr)
        return tree[cur];
 
    int tm = (tl + tr) / 2;
    return getSum(tree, (cur << 1) + 1, tl, tm, l, min(r, tm)) +
           getSum(tree, (cur << 1) + 2, tm + 1, tr, max(l, tm + 1), r);
}
 
int main() {
    freopen("permutation.in", "r", stdin);
    freopen("permutation.out", "w", stdout);
    int n, m, t;
    int x, y;
    long long subSum;
    long long subHashSum;
    scanf("%d\n", &n);
    long long* array = new long long[n];
    long long * hashArray = new long long[n];
    long long * sum = new long long[n];
    long long * hashSum = new long long[n];
    long long * treeSum = new long long[n * 4];
    long long * treeHashSum = new long long[n * 4];
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &array[i]);
        hashArray[i] = binpow(11, array[i]);
        if (i == 0) {
            hashSum[i] = 11;
            sum[i] = 1;
        }
        else {
            hashSum[i] = hashSum[i - 1] + binpow(11, i + 1);
            sum[i] = sum[i - 1] + i + 1;
        }
    }
    buildSum(array, treeSum, 0, 0, n - 1);
    buildSum(hashArray, treeHashSum, 0, 0, n - 1);
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%d", &t, &x, &y);
        switch (t) {
        case 1: 
            set(treeSum, 0, 0, n - 1, x - 1, y);
            set(treeHashSum, 0, 0, n - 1, x - 1, binpow(11, y));
            break;
        case 2: 
            subSum = getSum(treeSum, 0, 0, n - 1, x - 1, y - 1);
            subHashSum = getSum(treeHashSum, 0, 0, n - 1, x - 1, y - 1);
            if (subSum == sum[y - x] && subHashSum == hashSum[y - x]) {
                printf("YES\n");
            }
            else {
                printf("NO\n");
            }
        }
    }
    return 0;
}