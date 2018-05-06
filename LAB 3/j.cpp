#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <algorithm> 
using namespace std;
 
long long shortestLength(long long ** dp, long long ** d, int n, int i, int mask) {
    if (dp[i][mask] != 130000000) {
        return dp[i][mask];
    }
    for (int j = 0; j < n; j++) {
        if (mask & (1 << j)) {
            dp[i][mask] = min(dp[i][mask], shortestLength(dp, d, n, j, mask - (1 << j)) + d[i][j]);
        }
    }
    return dp[i][mask];
}
 
int main() {
    int n, k, minind = 0;
    long long min = LLONG_MAX;
    scanf("%i", &n);
    int mask = (1 << n) - 1;
    vector<int> answer;
    answer.reserve(n);
    long long ** d = new long long *[n];
    long long ** dp = new long long *[n];
    for (int i = 0; i < n; i++) {
        d[i] = new long long[n];
        dp[i] = new long long[mask + 1];
        for (int j = 0; j < n; j++) {
            scanf("%i", &k);
            d[i][j] = k;
        }
        dp[i][0] = 0;
        for (int j = 1; j <= mask; j++) {
            dp[i][j] = 130000000;
        }
    }
    for (int i = 0; i < n; i++) {
        shortestLength(dp, d, n, i, mask - (1 << i));
        if (dp[i][mask - (1 << i)] <= min) {
            min = dp[i][mask - (1 << i)];
            minind = i;
        }
    }
    printf("%lld\n%i ", min, minind + 1);
    mask -= (1 << minind);
    for (int j = 0; j < n && mask; j++) {
            if (mask & (1 << j) &&
                dp[minind][mask] == dp[j][mask - (1 << j)] + d[minind][j]) {
                printf("%i ", j + 1);
                mask -= (1 << j);
                minind = j;
                j = -1;
            }
        }
    return 0;
}
