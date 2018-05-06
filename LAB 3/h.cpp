#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <algorithm> 
using namespace std;
 
int l(int n, vector<int> * children, int * prel) {
    if (prel[n] != -1) {
        return prel[n];
    }
    int ch = 0, grch = 0, k;
    for (int i = 0; i < children[n].size(); ++i) {
        k = children[n].at(i);
        ch += prel[k] == - 1 ? l(k, children, prel) : prel[k];
        for (int j = 0; j < children[k].size(); ++j) {
            grch += prel[children[k].at(j)] == -1 ? l(children[k].at(j), children, prel) : prel[children[k].at(j)];
        }
    }
    prel[n] = max(ch, grch + 1);
    return prel[n];
}
 
int main() {
    int n, k;
    scanf("%i", &n);
    vector<int> * children = new vector<int>[n + 1];
    int * prel = new int[n + 1];
    for (int i = 0; i < n; ++i) {
        scanf("%i", &k);
        children[k].push_back(i + 1);
        prel[i + 1] = -1;
    }
    printf("%i", l(children[0].front(), children, prel));
    return 0;
}
