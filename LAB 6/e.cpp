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
#include <map>
#include <set>
#include <math.h>
using namespace std;

struct node {
	int index;
	node * parent = nullptr;
	set<int> children;
	int s = 1;
};

vector<node *> tree;
int t;

void makeParent(int x) {
	for (set<int>::iterator it = tree.at(x)->children.begin();
		it != tree.at(x)->children.end(); ++it) {
		tree.at(*it)->parent = tree.at(x);
		tree.at(*it)->children.erase(x);
		makeParent(*it);
		tree.at(x)->s += tree.at(*it)->s;
	}
}

int findCenter(int index) {
	int k = -1;
	for (set<int>::iterator it = tree.at(index)->children.begin();
		it != tree.at(index)->children.end(); ++it) {
		if ((k == -1 ||	tree.at(k)->s < tree.at(*it)->s) &&
			tree.at(*it)->s > t / 2) {
			k = *it;
		}
	}
	if (k == -1) {
		return index;
	}
	return findCenter(k);
}

void hangNode(int index) {
	if (tree.at(index)->parent) {
		hangNode(tree.at(index)->parent->index);

		tree.at(index)->parent->s -= tree.at(index)->s;
		tree.at(index)->s += tree.at(index)->parent->s;

		tree.at(index)->children.insert(tree.at(index)->parent->index);
		tree.at(index)->parent->children.erase(index);
		tree.at(index)->parent->parent = tree.at(index);
		tree.at(index)->parent = nullptr;
	}

}

int decompose(int index) {
	int root = findCenter(index);
	hangNode(root);
	set<int> new_children;
	for (set<int>::iterator it = tree.at(root)->children.begin();
		it != tree.at(root)->children.end(); ++it) {
		tree.at(*it)->parent = nullptr;
		t = tree.at(*it)->s;
		int k = decompose(*it);
		new_children.insert(k);
		tree.at(k)->parent = tree.at(root);
	}
	tree.at(root)->children = new_children;
	return root;
}

int main() {
	int n, x, y;
	scanf("%d", &n);

	for (int i = 0; i < n; ++i) {
		tree.push_back(new node{ i });
	}

	for (int i = 1; i < n; ++i) {
		scanf("%d %d", &x, &y);
		--x;
		--y;
		tree.at(x)->children.insert(y);
		tree.at(y)->children.insert(x);
	}

	makeParent(0);
	t = n;
	decompose(0);

	for (int i = 0; i < n; ++i) {
		printf("%d ", tree.at(i)->parent ? tree.at(i)->parent->index + 1 : 0);
	}

	return 0;
}