#include <stack>
using namespace std;
int main() {
freopen("stack-min.in", "r", stdin);
freopen("stack-min.out", "w", stdout);
stack <int> min;
    int n, k;
    scanf("%i", &n);
    for (int i = 0; i < n; i++) {
        scanf("%i", &k);
        switch (k) {
            case 1:
                scanf("%i", &k);
                if (min.empty() || min.top() >= k) {
                    min.push(k);
                } else {
                    min.push(min.top());
                }
                break;
            case 2:
                min.pop();
                break;
            case 3:
            printf("%i\n", min.top());
                break;
                }
            }
    return 0;
}
