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
 
int r;
 
struct matrix {
    long long value[2][2];
};
 
matrix E;
matrix Z;
 
matrix multiply(matrix a, matrix b) {
    matrix m = Z;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                m.value[i][j] = (m.value[i][j] + a.value[i][k] * b.value[k][j]) % r;
            }
        }
    }
    return m;
}
 
void printMatrix(matrix a) {
    printf("%lld %lld\n", a.value[0][0], a.value[0][1]);
    printf("%lld %lld\n\n", a.value[1][0], a.value[1][1]);
}
 
void build(matrix * tree, matrix * a, int v, int cl, int cr) {
    if (cl == cr)
        tree[v] = a[cl];
    else {
        int cm = (cl + cr) / 2;
        build(tree, a, (v << 1) + 1, cl, cm);
        build(tree, a, (v << 1) + 2, cm + 1, cr);
        tree[v] = multiply(tree[(v << 1) + 1], tree[(v << 1) + 2]);
    }
}
 
matrix mul(matrix * tree, int v, int cl, int cr, int l, int r) {
    if (l > r)
        return E;
    if (l == cl && r == cr)
        return tree[v];
 
    int cm = (cl + cr) / 2;
    return multiply(mul(tree, (v << 1) + 1, cl, cm, l, min(r, cm)),
                    mul(tree, (v << 1) + 2, cm + 1, cr, max(l, cm + 1), r));
}
 
int main() {
    freopen("crypto.in", "r", stdin);
    freopen("crypto.out", "w", stdout);
 
    int n, m;
    scanf("%d%d%d\n", &r, &n, &m);
    int minBorder = INT16_MAX;
    int maxBorder = INT16_MIN;
    matrix * a = new matrix[n];
    matrix * tree = new matrix[n * 4];
 
    E.value[0][0] = E.value[1][1] = 1;
    E.value[0][1] = E.value[1][0] = 0;
 
    Z.value[0][0] = Z.value[1][1] = 0;
    Z.value[0][1] = Z.value[1][0] = 0;
 
    for(int i = 0; i < n; ++i) {
        scanf("%lld%lld\n%lld%lld\n", &a[i].value[0][0], &a[i].value[0][1],
                              &a[i].value[1][0], &a[i].value[1][1]);
    }
    for (int i = 0; i < 4 * n; ++i) {
        tree[i] = E;
    }
    build(tree, a, 0, 0, n - 1);
    int i, j;
    for (int k = 0; k < m; ++k) {
        scanf("%d%d", &i, &j);
        printMatrix(mul(tree, 0, 0, n - 1, --i, --j));
    }
    return 0;
}