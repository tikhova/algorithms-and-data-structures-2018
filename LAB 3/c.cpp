#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
using namespace std;
 
int main() {
    int n;
    long long sum = 0;
    scanf("%i", &n);
    vector <long long> last;
    vector <long long> current;
    last.reserve(10);
    current.reserve(10);
    for (int i = 0; i < 10; i++) {
        last.push_back(1);
        current.push_back(1);
    }
    last.at(0) = last.at(8) = 0;
    for (int i = 1; i < n; i++) {
        current.at(1) = (last.at(6) + last.at(8)) % 1000000000;
        current.at(2) = (last.at(7) + last.at(9)) % 1000000000;
        current.at(3) = (last.at(4) + last.at(8)) % 1000000000;
        current.at(4) = (last.at(3) + last.at(9) + last.at(0)) % 1000000000;
        current.at(5) = 0;
        current.at(6) = (last.at(1) + last.at(7) + last.at(0)) % 1000000000;
        current.at(7) = (last.at(2) + last.at(6)) % 1000000000;
        current.at(8) = (last.at(1) + last.at(3)) % 1000000000;
        current.at(9) = (last.at(2) + last.at(4)) % 1000000000;
        current.at(0) = (last.at(4) + last.at(6)) % 1000000000;
        last = current;
    }
    for (int i = 0; i < 10; ++i) {
        sum += last.at(i);
        sum %= 1000000000;
    }
    printf("%lld", sum);
    return 0;
}
