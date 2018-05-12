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
using namespace std;

const int MOD = 1000000007;

struct node {
	node * parent;
	set<int> children;
	int positionInVtx = -1;
};

struct stNode {
	int index = -1;
	int value = 0;
};

vector<node *> tree;
vector<int> depth;
vector<int> vtx;
stNode * stTree;

void dfs(int x, int d) {
	if (tree.at(x)->children.size() == 0) {
		depth.push_back(d);
		vtx.push_back(x + 1);
		tree.at(x)->positionInVtx = vtx.size() - 1;
		vtx.push_back(x + 1);
		depth.push_back(d);
	}
	for (set<int>::iterator it = tree.at(x)->children.begin();
		it != tree.at(x)->children.end(); ++it) {
		depth.push_back(d);
		vtx.push_back(x + 1);
		if (tree.at(x)->positionInVtx == -1) {
			tree.at(x)->positionInVtx = vtx.size() - 1;
		}
		dfs(*it, d + 1);
		vtx.push_back(x + 1);
		depth.push_back(d);
	}
}

void build(stNode * tree, int v, int cl, int cr) {
	if (cl == cr) {
		tree[v].value = depth.at(cl);
		tree[v].index = cl;
	}
	else {
		int cm = (cl + cr) / 2;
		build(tree, (v << 1) + 1, cl, cm);
		build(tree, (v << 1) + 2, cm + 1, cr);
		tree[v].value = min(tree[(v << 1) + 1].value, tree[(v << 1) + 2].value);
		tree[v].index = tree[v].value == tree[(v << 1) + 1].value ?
			tree[(v << 1) + 1].index : tree[(v << 1) + 2].index;
	}
}

int rmq(int v, int l, int r, int cl, int cr) {
	if (l > r)
		return -1;

	if (l == cl && r == cr)
		return v;

	int cm = (cl + cr) / 2;
	int xValue, yValue;
	int x = rmq((v << 1) + 1, l, min(r, cm), cl, cm);
	if (x == -1) {
		xValue = INT_MAX;
	}
	else {
		xValue = stTree[x].value;
	}
	int y = rmq((v << 1) + 2, max(l, cm + 1), r, cm + 1, cr);
	if (y == -1) {
		yValue = INT_MAX;
	}
	else {
		yValue = stTree[y].value;
	}
	return xValue <= yValue ? x : y;
}

int lca(int x, int y, int n) {
	x = tree.at(x)->positionInVtx;
	y = tree.at(y)->positionInVtx;
	if (x > y) {
		swap(x, y);
	}
	int k = rmq(0, x, y, 0, n - 1);
	return vtx.at(stTree[k].index);
}

int main() {
	int n, m, x, y;

	scanf("%d", &n);

	tree.push_back(new node);
	for (int i = 1; i < n; ++i) {
		scanf("%d", &x);
		tree.push_back(new node{ tree.at(x - 1) });
		tree.at(x - 1)->children.insert(i);
	}


	dfs(0, 0);
	stTree = new stNode[4 * depth.size()];
	build(stTree, 0, 0, depth.size() - 1);

	scanf("%d", &m);

	for (int i = 0; i < m; ++i) {
		scanf("%d%d", &x, &y);
		printf("%d\n", lca(x - 1, y - 1, depth.size()));
	}
	return 0;
}