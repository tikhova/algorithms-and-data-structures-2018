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
 
struct node {
    int key;
    node * left = nullptr;
    node * right = nullptr;
    int height = 1;
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
 
void fixHeight(node * x) {
    if (x == nullptr) {
        return;
    }
    x->height = max(height(x->left), height(x->right)) + 1;
}
 
node * rotateLeft(node * x) {
    node * y = x->right;
    x->right = y->left;
    y->left = x;
    fixHeight(x);
    fixHeight(y);
    return y;
}
 
node * rotateRight(node * x) {
    node* y = x->left;
    x->left = y->right;
    y->right = x;
    fixHeight(x);
    fixHeight(y);
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
    fixHeight(x);
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
 
node * minimum(node * x) {
    if (x->left == nullptr) {
        return x;
    }
    return minimum(x->left);
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
 
node * search(node * x, int value) {
    if (x == nullptr || x->key == value) {
        return x;
    }
    if (value < x->key) {
        return search(x->left, value);
    }
    return search(x->right, value);
}
 
node * next(node * root, int x) {
    node * current = root;
    node * answer = nullptr;
    while (current != nullptr) {
        if (current->key > x) {
            answer = current;
            current = current->left;
        }
        else {
            current = current->right;
        }
    }   
    return answer;
}
 
node * prev(node * root, int x) {
    node * current = root;
    node * answer = nullptr;
    while (current != nullptr) {
        if (current->key < x) {
            answer = current;
            current = current->right;
        }
        else {
            current = current->left;
        }
    }
    return answer;
}
 
int main() {
    //freopen("permutation.in", "r", stdin);
    //freopen("permutation.out", "w", stdout);
    string command;
    int x;
    node * root = nullptr;
    node * a;
    while (cin >> command >> x) {
        if (command.compare("insert") == 0) {
            root = insert(root, x);
        }
        else if (command.compare("delete") == 0) {
            root = deleteNode(root, x);
        }
        else if (command.compare("exists") == 0) {
            if (search(root, x) != nullptr) {
                printf("true\n");
            }
            else {
                printf("false\n");
            }
        }
        else if (command.compare("next") == 0) {
            a = next(root, x);
            if (a == nullptr) {
                printf("none\n");
            }
            else {
                printf("%d\n", a->key);
            }
        }
        else if (command.compare("prev") == 0) {
            a = prev(root, x);
            if (a == nullptr) {
                printf("none\n");
            }
            else {
                printf("%d\n", a->key);
            }
        }
    }
    return 0;
}