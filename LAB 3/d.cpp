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
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    string a, b;
    cin >> a >> b;
    int ** dp = new int *[a.length() + 1];
    for (int i = 0; i <= a.length(); ++i) {
        dp[i] = new int[b.length() + 1];
        dp[i][0] = i;
    }
    for (int j = 0; j <= b.length(); ++j) {
        dp[0][j] = j;
    }
    for (int i = 1; i <= a.length(); ++i) {
        for (int j = 1; j <= b.length(); ++j) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else {
                dp[i][j] = min(dp[i][j - 1], dp[i - 1][j]);
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);
                dp[i][j]++;
            }
        }
    }
    printf("%i", dp[a.length()][b.length()]);
    return 0;
}
