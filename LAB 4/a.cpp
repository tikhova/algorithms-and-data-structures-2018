#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
 
#include <cstdio>
#include <fstream>
#include <cstring>
#include <iostream>
using namespace std;
 
const long long MOD16 = (1 << 16) - 1;
const long long MOD30 = (1 << 30) - 1;
 
 
int main() {
    freopen("sum0.in", "r", stdin);
    freopen("sum0.out", "w", stdout);
 
    int n, m;
    long long x, y, temp;
 
    scanf("%d%lld%lld%lld", &n, &x, &y, &temp);
    long long * a = new long long[n];
    long long * prefixSum = new long long[n + 1];
    a[0] = prefixSum[1] = temp;
    prefixSum[0] = 0;
    for (int i = 1; i < n; i++) {
        a[i] = (x * a[i - 1] + y) & MOD16;
        prefixSum[i + 1] = prefixSum[i] + a[i];
    }
 
    scanf("%d%d%lld%lld", &m, &x, &y, &temp);
    long long * b = new long long[2*m + 1];
    b[0] = temp;
    for (int i = 1; i <= 2 * m; i++) {
        b[i] = (x * b[i - 1] + y) & MOD30;
    }
    for (int i = 0; i <= 2 * m; i++) {
        b[i] %= n;
    }
 
    x = 0;
    for (int i = 0; i < m; i++) {
        if (b[2 * i] > b[2 * i + 1]) {
            swap(b[2 * i], b[2 * i + 1]);
        }
        x += prefixSum[b[2 * i + 1] + 1] - prefixSum[b[2 * i]];
    }
    printf("%lld", x);
    return 0;
}