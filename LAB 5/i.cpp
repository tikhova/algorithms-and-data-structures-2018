#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
 
#include <cstdio>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
 
struct node {
    int y;
    int c;
    int value;
    node * left = nullptr;
    node * right = nullptr;
    node * parent = nullptr;
    bool cycle = false;
};
 
vector<node *> cities;
 
int getC(node * t) {
    if (t) {
        return t->c;
    }
    return 0;
}
 
int getIndex(node * t) {
    int index = getC(t->left);
    while (t) {
        if (t->parent && t->parent->right == t) {
            index += getC(t->parent->left) + 1;
        }
        t = t->parent;
    }
     
    return index;
}
 
node * getRoot(node * t) {
    while (t->parent) {
        t = t->parent;
    }
    return t;
}
 
void fix(node * t) {
    if (!t) {
        return;
    }
    t->c = getC(t->left) + getC(t->right) + 1;
}
 
void split(node * t, int x, node *&t1, node *&t2) {
    if (!t) {
        t1 = t2 = nullptr;
        return;
    }
    int k = getC(t->left) + 1;
    if (k <= x) {
        split(t->right, x - k, t->right, t2);
        t1 = t;
        if (t->right) {
            t->right->parent = t;
        }
        if (t2) {
            t2->parent = nullptr;
        }
    }
    else {
        split(t->left, x, t1, t->left);
        t2 = t;
        if (t1) {
            t1->parent = nullptr;
        }
        if (t->left) {
            t->left->parent = t;
        }
    }
    fix(t);
}
 
void mirror(node * t) {
    if (!t) {
        return;
    }
    node * t1 = t->left;
    node * t2 = t->right;
    t->left = t2;
    t->right = t1;
    mirror(t1);
    mirror(t2);
}
 
node * merge(node *t1, node *t2) {
    if (t1 == nullptr) {
        return t2;
    }
    if (t2 == nullptr) {
        return t1;
    }
    if (t1->y > t2->y) {
        t1->right = merge(t1->right, t2);
        fix(t1); 
        t1->right->parent = t1;
        return t1;
    }
    else {
        t2->left = merge(t1, t2->left);
        fix(t2);
        t2->left->parent = t2;
        return t2;
    }
}
 
int nodesBetween(int x, int y) {
    if (x == y) {
        return 0;
    }
    node * rootX = getRoot(cities.at(x));
    node * rootY = getRoot(cities.at(y));
    if (rootX == rootY) {
        int distance = fabs(getIndex(cities.at(x)) - 
                           getIndex(cities.at(y)));
        if (rootX->cycle) {
            return min(distance, getC(rootX) - distance) - 1;
        }
        return distance - 1;
    }
    return -1;
}
 
node * moveToFront(node * t, int l, int r) {
    node * t1, *t2, *t3;
    split(t, l, t1, t2);
    split(t2, r + 1 - l, t2, t3);
    return merge(merge(t2, t1), t3);
}
 
void addLink(int x, int y) {
    node * rootX = getRoot(cities.at(x));
    node * rootY = getRoot(cities.at(y));
    if (rootX == rootY) { //cycle created
        rootX->cycle = true;
    }
    else {
        if (getIndex(cities.at(x)) == 0) {
            mirror(rootX);
        }
        if (getIndex(cities.at(y)) == getC(rootY) - 1) {
            mirror(rootY);
        }
        merge(rootX, rootY);
    }
}
 
void deleteLink(int x, int y) {
    node * rootX = getRoot(cities.at(x));
    node * rootY = getRoot(cities.at(y));
    if (rootX == rootY) {
        int xIndex = getIndex(cities.at(x));
        int yIndex = getIndex(cities.at(y));
        if (rootX->cycle) {
            if (abs(getIndex(cities.at(x)) - getIndex(cities.at(y))) == 1) {
                moveToFront(rootX, max(xIndex, yIndex), getC(rootX) - 1);
            }
            rootX->cycle = false;
        }
        else {
            node *t1 = nullptr, *t2 = nullptr;
            split(rootX, max(xIndex, yIndex), t1, t2);
        }
    }
}
 
void getArray(node * t) {
    if (!t) {
        return;
    }
    getArray(t->left);
    printf("%d ", t->value);
    getArray(t->right);
}
 
int main() {
    freopen("roads.in", "r", stdin);
    freopen("roads.out", "w", stdout);

    int n, m, q, x, y;
    char command;
 
    scanf("%d %d %d\n", &n, &m, &q);
 
    for (int i = 0; i < n; ++i) {
        cities.push_back(new node{ rand(), 1, i });
    }
 
    for (int i = 0; i < m; ++i) {
        scanf("%d %d\n", &x, &y);
        addLink(x - 1, y - 1);
    }
 
    for (int i = 0; i < q; ++i) {
        scanf("%c %d %d\n", &command, &x, &y);
        switch (command) {
            case '?':
                printf("%d\n", nodesBetween(x - 1, y - 1));
                break;
            case '-':
                deleteLink(x - 1, y - 1);
                break;
            case '+':
                addLink(x - 1, y - 1);
        }
    }
    return 0;
}