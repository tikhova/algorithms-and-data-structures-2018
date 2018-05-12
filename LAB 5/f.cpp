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
    int key;
    int c = 1;
    int height = 1;
    node * left = nullptr;
    node * right = nullptr;
};
 
int height(node * x) {
    return x ? x->height : 0;
}
 
int diff(node * x) {
    if (x == nullptr) {
        return 0;
    }
    return height(x->left) - height(x->right);
}
 
int getC(node * x) {
    if (x) {
        return x->c;
    }
    return 0;
}
 
void fix(node * x) {
    if (x == nullptr) {
        return;
    }
    x->height = max(height(x->left), height(x->right)) + 1;
    x->c = getC(x->left) + getC(x->right) + 1;
}
 
node * rotateLeft(node * x) {
    node * y = x->right;
    x->right = y->left;
    y->left = x;
    fix(x);
    fix(y);
    return y;
}
 
node * rotateRight(node * x) {
    node* y = x->left;
    x->left = y->right;
    y->right = x;
    fix(x);
    fix(y);
    return y;
}
 
node * bigRotateLeft(node * x) {
    x->right = rotateRight(x->right);
    return rotateLeft(x);
}
 
node * bigRotateRight(node * x) {
    x->left = rotateLeft(x->left);
    return rotateRight(x);
}
 
node * balance(node * x) {
    fix(x);
    if (diff(x) == -2) {
        int b = diff(x->right);
        if (b > 0) {
            return bigRotateLeft(x);
        }
        else {
            return rotateLeft(x);
        }
    }
    else if (diff(x) == 2) {
        int b = diff(x->left);
        if (b < 0) {
            return bigRotateRight(x);
        }
        else {
            return rotateRight(x);
        }
    }
    return x;
}
 
node * insert(node * x, int value) {
    if (x == nullptr) {
        return new node{ value };
    }
    if (value < x->key) {
        x->left = insert(x->left, value);
    }
    else if (value > x->key) {
        x->right = insert(x->right, value);
    }
    return balance(x);
}
 
node * minimum(node * x) {
    if (x->left == nullptr) {
        return x;
    }
    return minimum(x->left);
}
 
node * deleteNode(node * x, int value) {
    if (x == nullptr) {
        return x;
    }
    if (value < x->key) {
        x->left = deleteNode(x->left, value);
    }
    else if (value > x->key) {
        x->right = deleteNode(x->right, value);
    }
    else if (x->left != nullptr && x->right != nullptr) {
        x->key = minimum(x->right)->key;
        x->right = deleteNode(x->right, x->key);
    }
    else {
        if (x->left != nullptr) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    return balance(x);
}
 
int maxNode(node * t, int k) {
    if (!t) {
        return INT_MIN;
    }
    int n = getC(t->right) + 1;
    if (k == n) {
        return t->key;
    }
    if (k < n) {
        return maxNode(t->right, k);
    }
    else {
        return maxNode(t->left, k - n);
    }
}
 
int main() {
    node * root = nullptr;
    int n, x, y;
 
    scanf("%d\n", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &x, &y);
        if (x == 1) {
            root = insert(root, y);
        }
        else if(x == -1) {
            root = deleteNode(root, y);
        }
        else {
            printf("%d\n", maxNode(root, y));
        }
    }
    return 0;
}