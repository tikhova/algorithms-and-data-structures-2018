#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <string>
using namespace std;
 
int main() {
    freopen("formation.in", "r", stdin);
    freopen("formation.out", "w", stdout);
    int n, i, j;
    string s = "";
    scanf("%i", &n);
    int * l = new int[n + 1];
    int * r = new int[n + 1];
    l[0] = r[0] = -1;
    l[1] = r[1] = 0;
    scanf("%i", &n);
    for (int k = 0; k < n; k++) {
        cin >> s;
        if (s == "left") {
            scanf("%i%i", &j, &i);
            r[l[i]] = j;
            r[j] = i;
            l[j] = l[i];
            l[i] = j;           
        }
        if (s == "right") {
            scanf("%i%i", &j, &i);
            l[r[i]] = j;
            l[j] = i;
            r[j] = r[i];
            r[i] = j;
        }
        if (s == "leave") {
            scanf("%i", &i);
            r[l[i]] = r[i];
            l[r[i]] = l[i];
            l[i] = r[i] = -1;
        }
        if (s == "name") {
            scanf("%i", &i);
            printf("%i %i\n", l[i], r[i]);
        }
    }
    return 0;
}
