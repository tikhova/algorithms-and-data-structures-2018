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
    string ** s = new string *[n];
    for (int i = 0; i < n; i++) {
        dp[i] = new int[n];
        s[i] = new string[n];
        for (int j = 0; j < i; ++j) {
            dp[i][j] = 0;
            s[i][j] = "";
        }
        dp[i][i] = 1;
        s[i][i] =  "";
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n - i; ++j) {
            if (dp[j][j + i - 1] < dp[j + 1][j + i]) {
                s[j][j + i] = s[j][j + i - 1];
                dp[j][j + i] = dp[j][j + i - 1] + 1;
            }
            else {
                s[j][j + i] = s[j + 1][j + i];
                dp[j][j + i] = dp[j + 1][j + i] + 1;
            }
            if (dp[j][j + i] > dp[j + 1][j + i - 1] + 2) {
                dp[j][j + i] = dp[j + 1][j + i - 1] + 2;
                s[j][j + i] = s[j + 1][j + i - 1];
            }   
            for (int k = j; k < j + i; ++k) {
                if (dp[j][j + i] > dp[j][k] + dp[k + 1][j + i]) {
                    dp[j][j + i] = dp[j][k] + dp[k + 1][j + i];
                    s[j][j + i] = s[j][k] + s[k + 1][j + i];
                }
            }
            if ((a[j] == '(' && a[j + i] == ')' ||
                a[j] == '[' && a[j + i] == ']' || 
                a[j] == '{' && a[j + i] == '}') && 
                dp[j][j + i] > dp[j + 1][j + i - 1]) {
                dp[j][j + i] = dp[j + 1][j + i - 1];
                if (a[j] == '(') {
                    s[j][j + i] = "(" + s[j + 1][j + i - 1] + ")";
                }
                if (a[j] == '[') {
                    s[j][j + i] = "[" + s[j + 1][j + i - 1] + "]";
                }
                if (a[j] == '{') {
                    s[j][j + i] = "{" + s[j + 1][j + i - 1] + "}";
                }
            }
        }
    }
    cout << s[0][n - 1]; 
    return 0;
}
