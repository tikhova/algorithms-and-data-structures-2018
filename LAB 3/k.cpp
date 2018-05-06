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
    freopen("nice.in", "r", stdin);
    freopen("nice.out", "w", stdout);
    int n, m, black, white;
    int nice;
    scanf("%i%i", &n, &m);
    vector <int> current, last;
    if (n > m) {
        swap(n, m);
    }
    for (int i = 0; i < (1 << n); ++i) {
        last.push_back(1);
        current.push_back(0);
    }
    for (int t = 1; t < m; ++t) {
        for (int i = 0; i < (1 << n); ++i) {
            current.at(i) = 0;
            for (int j = 0; j < (1 << n); ++j) {
                black = i & j;
                white = (~(i | j));
                nice = 1;
                for (int k = 0; k <= n - 2; ++k) {
                    if ((black & (3 << k)) == (3 << k) || (white & (3 << k)) == (3 << k)) {
                        nice = 0;
                        break;
                    }
                }
                current.at(i) += last.at(j) * nice;
            }
        }
        last = current;
    }
 
    long long answer = 0;
    for (int i = 0; i < (1 << n); ++i) {
        answer += last.at(i);
    }
    printf("%lld", answer);
    return 0;
}
