#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
 
int main() {
    freopen("kenobi.in", "r", stdin);
    freopen("kenobi.out", "w", stdout);
    vector <int> lightsabers;
    string s;
    int n, k;
    scanf("%i", &n);
    for (int i = 0; i < n; i++) {
        cin >> s;
        if (s == "add") {
            scanf("%i", &k);
            lightsabers.push_back(k);
        }
        else if (s == "take") {
            if (!lightsabers.empty()) {
                lightsabers.pop_back();
            }
        }
        else {
            rotate(lightsabers.begin(), lightsabers.begin() + lightsabers.size() / 2, lightsabers.end());
        }
    }
    printf("%i\n", lightsabers.size());
    for (int i : lightsabers) {
        printf("%i ", i);
    }
    return 0;
}
