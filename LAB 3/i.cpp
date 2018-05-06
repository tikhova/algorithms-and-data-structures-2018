#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <algorithm> 
using namespace std;
 
 
int main() {
    freopen("skyscraper.in", "r", stdin);
    freopen("skyscraper.out", "w", stdout);
    int n, w, s;
    scanf("%i%i", &n, &w);
    vector <int> answer;
    int * a = new int[n];
    int * dp = new int [n + 1];
    vector <int> sum;
    dp[0] = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%i", &a[i]);
    }
    for (int j = 0; j < 1 << n; ++j) {
        s = 0;
        for (int i = 0; i < n; ++i) {
            if (j & (1 << i)) {
                s += a[i];
            }
        }
        sum.push_back(s);
    }
    for (int i = 1; i <= n; ++i) {
        dp[i] = 0;
        for (int j = 1; j < 1 << n; ++j) {
            if (sum[j] > sum[dp[i]] && sum[j] - sum[dp[i - 1]] <= w && (j | dp[i - 1]) == j) {
                dp[i] = j;
            }
        }
        if (dp[i] == (1 << n) - 1) {
            printf("%i", i);
            while (dp[i]) {
                w = dp[i--] ^ dp[i - 1];
                for (int k = 0; k < n; ++k) {
                    if (w & (1 << k)) {
                        answer.push_back(k + 1);
                    }
                }
                printf("\n%i ", answer.size());
                for (int k = 0; k < answer.size(); ++k) {
                    printf("%i ", answer.at(k));
                }
                answer.clear();
            }
            break;
        }
    }
    return 0;
}
