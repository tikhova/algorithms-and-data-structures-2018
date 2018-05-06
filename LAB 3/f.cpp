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
    string a;
    cin >> a;
    int n = a.size();
    int ** dp = new int *[n];
    for (int i = 0; i < n; i++) {
        dp[i] = new int[n];
        for (int j = 0; j < i; ++j) {
            dp[i][j] = 0;
        }
        dp[i][i] = 1;
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n - i; ++j) {
            dp[j][j + i] = min(dp[j][j + i - 1] + 1, dp[j + 1][j + i] + 1);
            dp[j][j + i] = min(dp[j][j + i], dp[j + 1][j + i - 1] + 2);     
            for (int k = j; k < j + i; ++k) {
                dp[j][j + i] = min(dp[j][j + i], dp[j][k] + dp[k + 1][j + i]);
            }
            if (a[j] == '(' && a[j + i] == ')' ||
                a[j] == '[' && a[j + i] == ']' || 
                a[j] == '{' && a[j + i] == '}') {
                dp[j][j + i] = min(dp[j][j + i], dp[j + 1][j + i - 1]);
            }
        }
    }
    printf("%i", n - dp[0][n - 1]);
    return 0;
}
