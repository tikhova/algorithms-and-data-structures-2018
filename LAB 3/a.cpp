#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
using namespace std;
 
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, k, t, max;
    scanf("%i%i", &n, &k);
    vector <int> a, index;
    a.reserve(n);
    index.reserve(n);
    a.push_back(0);
    index.push_back(-1);
    for (int i = 1; i < n; i++) {
        max = i - 1;
        if (i < n - 1) {
            scanf("%i", &t);
        }
        else {
            t = 0;
        }
        for (int j = i - 2; j >= 0 && j >= i - k; j--) {
            if (a.at(j) > a.at(max)) {
                max = j;
            }
        }
        a.push_back(t + a.at(max));
        index.push_back(max);
    }
    printf("%i\n", a.back());
    a.clear();
    t = n - 1;
    while(t >= 0) {
        a.push_back(t);
        t = index.at(t);
    }
    printf("%i\n", a.size() - 1);
    for (int i = a.size() - 1; i >= 0; i--) {
        printf("%i ", a.at(i) + 1);
    }
    return 0;
}
