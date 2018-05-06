#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
using namespace std;
 
int indexOf(long long a, vector <long long> dp) {
    int l = -1, r = dp.size(), m;
    while (l < r - 1) {
        m = (l + r) / 2;
        if (dp.at(m) < a) {
            l = m;
        }
        else {
            r = m;
        }
    }
    return r;
}
 
int main() {
    int n;
    long long t;
    scanf("%i", &n);
 
    vector <long long> a, index, prev, dp;
    index.reserve(n + 1);
    prev.reserve(n);
    dp.reserve(n + 1);
    a.reserve(n);
    dp.push_back(LLONG_MIN);
    for (int i = 0; i <= n; i++) {
        index.push_back(-1);
    }
 
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &t);
        a.push_back(t);
        prev.push_back(-1);
        t = indexOf(t, dp);
        if (dp.at(t - 1) < a.back() && (t >= dp.size() || dp.at(t) > a.back())) {
            if (t < dp.size()) {
                dp.at(t) = a.back();
            }
            else {
                dp.push_back(a.back());
            }
            index.at(t) = i;
            prev.at(i) = index.at(t - 1);
        }
    }
 
    printf("%i\n", dp.size() - 1);
    t = index.at(dp.size() - 1);
    index.clear();
    while (t > -1) {
        index.push_back(a.at(t));
        t = prev.at(t);
    }
    for (int i = index.size() - 1; i >= 0; --i) {
        printf("%lld ", index.at(i));
    }
    return 0;
}
