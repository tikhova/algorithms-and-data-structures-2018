#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
int main() {
    freopen("saloon.in", "r", stdin);
    freopen("saloon.out", "w", stdout);
    vector <int> hour;
    vector <int> minutes;
    vector <int> hour_ans;
    vector <int> minutes_ans;
    int n, h, m, k;
    scanf("%i", &n);
    for (int i = 0; i < n; i++) {
        scanf("%i%i%i", &h, &m, &k);
        while (!hour.empty() && hour.front() * 60 + minutes.front() <= h * 60 + m) {
            hour.erase(hour.begin());
            minutes.erase(minutes.begin());
        }
        if (hour.size() <= k) {
            if (hour.empty()) {
                hour.push_back(h);
                minutes.push_back(m + 20);
            }
            else {
                hour.push_back(hour.back());
                minutes.push_back(minutes.back() + 20);
            }
            hour_ans.push_back(hour.back());
            minutes_ans.push_back(minutes.back());
        }
        else {
            hour_ans.push_back(h);
            minutes_ans.push_back(m);
        }
    }
    for (int i = 0; i < n; i++) {
        printf("%i %i\n", hour_ans.at(i) + minutes_ans.at(i) / 60, minutes_ans.at(i) % 60);
    }
    return 0;
}
