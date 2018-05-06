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
    int n, k;
    int min_value = 300000, min_index = 0;
    vector <int> a, days;
    scanf("%i", &n);
    if (n == 0) {
        printf("0\n0 0\n");
        return 0;
    }
    a.reserve(n);
    int ** b = new int *[n];
    for (int i = 0; i < n; i++) {
        scanf("%i", &k);
        a.push_back(k);
        b[i] = new int[n + 1];
        for (int j = 0; j <= n; ++j) {
            b[i][j] = 300000;
        }
    }
    if (a[0] > 100) {
        b[0][1] = a.at(0);
    }
    else {
        b[0][0] = a.at(0);
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (a.at(i) <= 100) {
                b[i][j] = min(j < n ? b[i - 1][j + 1] : 300000, b[i - 1][j] + a.at(i));
            }
            else {
                b[i][j] = min(j < n ? b[i - 1][j + 1] : 300000, j > 0 ? b[i - 1][j - 1] + a.at(i) : 300000);
            }           
        }
    }
    for (int j = 0; j <= n; ++j) {
        if (b[n - 1][j] <= min_value) {
            min_value = b[n - 1][j];
            min_index = j;
        }
    }
    k = min_index;
    for (int i = n - 1; i > 0; --i) {
        if (k > 0 && a.at(i) > 100 && b[i][k] == b[i - 1][k - 1] + a.at(i)) {
            --k;
        }
         
        else {
            if (!(a.at(i) <= 100 && b[i][k] == b[i - 1][k] + a.at(i))) {
                days.push_back(i + 1);
                ++k;
            }           
        }
    }
    printf("%i\n%i %i\n", min_value, min_index, days.size());
    for (int i = days.size() - 1; i >= 0; --i) {
        printf("%i\n", days.at(i));
    }
    return 0;
}
