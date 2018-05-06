#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
int main() {
    freopen("bureaucracy.in", "r", stdin);
    freopen("bureaucracy.out", "w", stdout);
    vector <long long int> a;
    vector <long long int> ans;
    int n, m, k, max = INT_MIN;
    scanf("%i%i", &n, &m);
    a.reserve(n);
    for (int i = 0; i < n; i++) {
        scanf("%i", &k);
        a.push_back(k);
        if (k > max) {
            max = k;
        }
    }
    int l = 0, r = max + 1, mid;
    long long int sum;
    while (l < r - 1) {
        mid = (l + r) / 2;
        sum = 0;
        for (int i = 0; i < n; i++) {
            sum += a.at(i) < mid ? a.at(i) : mid;
        }
        if (m >= sum) {
            l = mid;
        }
        else {
            r = mid;
        }
    }
    for (int i = 0; i < a.size(); i++) {
        if (a.at(i) <= l) {
            m -= a.at(i);
            a.at(i) = 0;
            n--;
        }
        else {
            a.at(i) -= l;
            m -= l;
        }
    }
    k = 0;
    for (; k < a.size() && m > 0; k++) {
        if (a.at(k) > 0) {
            a.at(k)--;
            m--;
            if (a.at(k) == 0) {
                n--;
            }
        }
    }
    if (n > 0) {
        printf("%i\n", n);
        for (; k < a.size(); k++) {
            if (a.at(k) > 0) {
                printf("%i ", a.at(k));
                n--;
            }
        }
        for (k = 0; k < a.size(), n > 0; k++) {
            if (a.at(k) > 0) {
                printf("%i ", a.at(k));
                n--;
            }
        }   
    }
    else {
        printf("-1");
    }
    return 0;
}
