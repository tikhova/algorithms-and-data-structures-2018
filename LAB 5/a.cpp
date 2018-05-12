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
    node * parent = nullptr;
};
 
node * minimum(node * x) {
    if (x->left == nullptr) {
        return x;
    }
    return minimum(x->left);
}
 
node * insert(node * x, int value) {
    if (x == nullptr) {
        return new node{ value, nullptr, nullptr, nullptr };
    }
    if (value < x->key) {
        x->left = insert(x->left, value);
        x->left->parent = x;
    }
    else if (value > x->key) {
        x->right = insert(x->right, value);
        x->right->parent = x;
    }
    return x;
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
    return x;
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