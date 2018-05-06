#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <string>
#include <list>
#include <iterator>
using namespace std;
 
int main() {
    freopen("dsu.in", "r", stdin);
    freopen("dsu.out", "w", stdout);
    int n, i, j;
    string s;
    scanf("%i", &n);
    int * parent = new int[n + 1];
    int * min = new int[n + 1];
    int * max = new int[n + 1];
    int * count = new int[n + 1];
    for (int k = 1; k <= n; k++) {
        parent[k] = k;
        min[k] = k;
        max[k] = k;
        count[k] = 1;
    }
    while (cin >> s) {
        if (s == "union") {
            scanf("%i%i", &i, &j);
            while (i != parent[i]) {
                i = parent[i];
            }
            while (j != parent[j]) {
                j = parent[j];
            }
            if (i != j) {
                if (count[i] < count[j]) {
                    swap(i, j);
                }
                parent[j] = i;
                count[i] += count[j];
                min[i] = min[i] < min[j] ? min[i] : min[j];
                max[i] = max[i] > max[j] ? max[i] : max[j];
            }
        }
        if (s == "get") {
            scanf("%i", &i);
            while (i != parent[i]) {
                i = parent[i];
            }
            printf("%i %i %i\n", min[i], max[i], count[i]);
        }
    }
    return 0;
}
