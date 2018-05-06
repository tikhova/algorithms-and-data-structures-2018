#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <string>
#include <vector>
using namespace std;
 
int main() {
    freopen("hemoglobin.in", "r", stdin);
    freopen("hemoglobin.out", "w", stdout);
    int n, k;
    int size = 0, sum;
    char operation;
    scanf("%i", &n);
    vector <int> queue;
    queue.reserve(50000);
    scanf("%c", &operation);
    for (int i = 0; i < n; i++) {
        scanf("%c", &operation);
        if (operation == '+') {
            scanf("%i", &k);
            queue.push_back(k);
            size++;
        }
        if (operation == '?') {
            scanf("%i", &k);
            sum = 0;
            for (int j = size - k; j < size; j++) {
                sum += queue.at(j);
            }
            printf("%i\n", sum);
        }
        if (operation == '-') {
            printf("%i\n", queue.back());
            queue.pop_back();
            size--;
        }
        scanf("%c", &operation);
    }
    return 0;
}
