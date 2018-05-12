#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
 
#include <cstdio>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
 
 
struct myElement {
    int x;
    int y;
    int number;
};
 
struct node {
    myElement a;
    node * left = nullptr;
    node * right = nullptr;
    node * parent = nullptr;
};
 
bool operator <(myElement a, myElement b) {
    if (a.x < b.x) {
        return true;
    }
    return false;
}
 
int getNumber(node * x) {
    if (x) {
        return x->a.number;
    }
    return 0;
}
 
node * search(node * x, int value) {
    if (x == nullptr || x->a.x == value) {
        return x;
    }
    if (value < x->a.x) {
        return search(x->left, value);
    }
    return search(x->right, value);
}
 
void printTreap(node ** b, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d %d %d\n", getNumber(b[i]->parent), getNumber(b[i]->left), getNumber(b[i]->right));
    }
}
 
int main() {
    int n;
    scanf("%d", &n);
    myElement * a = new myElement[n];
    node ** b = new node * [n];
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &a[i].x, &a[i].y);
        a[i].number = i + 1;
    }
    sort(a, a + n);
    node * last = nullptr;
    node * root = nullptr;
    for (int i = 0; i < n; ++i) {
        if (!last) {
            root = new node{ a[i] };
            b[a[i].number - 1] = last = root;
            continue;
        }
        else {
            while (last->parent && last->a.y > a[i].y) {
                last = last->parent;
            }
            if (last == root && last->a.y > a[i].y) {
                root = new node{ a[i], last, nullptr, nullptr};
                root->left->parent = root;
                b[a[i].number - 1] = last = root;
                continue;
            }
            else {
                node * t = last->right;
                last->right = new node{ a[i], t, nullptr, last };
                if (t) {
                    t->parent = last->right;
                }
                b[a[i].number - 1] = last = last->right;
                continue;
            }
        }
    }
    printf("YES\n");
    printTreap(b, n);
    return 0;
}