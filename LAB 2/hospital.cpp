#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <string>
#include <vector>
using namespace std;
 
int main() {
    freopen("hospital.in", "r", stdin);
    freopen("hospital.out", "w", stdout);
    int n, k;
    int begin = 0, size = 0;
    string operation;
    scanf("%i", &n);
    vector <int> queue;
    queue.reserve(100000);
    for (int i = 0; i < n; i++) {
        cin >> operation;
        if (operation == "+") {
            scanf("%i", &k);
            queue.push_back(k);
            size++;
        }
        if (operation == "*") {
            scanf("%i", &k);
            queue.insert(queue.begin() + (size + 1) / 2 + begin, k);
            size++;
        }
        if (operation == "-") {
            printf("%i\n", queue.at(begin));
            begin++;
            size--;
        }
    }
    return 0;
}
