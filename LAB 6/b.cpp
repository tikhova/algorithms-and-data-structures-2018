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

int l;

struct node {
	int index;
	node * parent;
	int length = INT_MAX;
	set<int> children;
	int depth = 0;
};

vector<node *> tree;
int ** dp;
int ** dm;
int depth = 0;

void dfs(int v) {
	tree.at(v)->depth = ++depth;

	dp[v][0] = tree.at(v)->parent->index;
	dm[v][0] = tree.at(v)->length;
	for (int i = 1; i < l; ++i) {
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
		dm[v][i] = min(dm[v][i - 1], dm[dp[v][i - 1]][i - 1]);
	}
		
	for (set<int>::iterator it = tree.at(v)->children.begin();
		it != tree.at(v)->children.end(); ++it) {
		dfs(*it);
	}

	--depth;
}

int lca(int x, int y) {
	int m = INT_MAX;
	if (tree.at(x)->depth > tree.at(y)->depth) {
		swap(x, y);
	}

	int d;
	while (d = tree.at(y)->depth - tree.at(x)->depth) {
		d = log(d) / log(2);
		m = min(m, dm[y][d]);
		y = dp[y][d];
	}
	if (x == y) {
		return m;
	}
	for (int i = l - 1; i >= 0; --i) {
		if (dp[x][i] != dp[y][i]) {
			m = min(m, dm[y][i]);
			m = min(m, dm[x][i]);
			x = dp[x][i];
			y = dp[y][i];
		}
	}
	m = min(m, dm[x][0]);
	m = min(m, dm[y][0]);
	return m;
}

int main() {
	freopen("minonpath.in", "r", stdin);
	freopen("minonpath.out", "w", stdout);

	int n, m, x, y;

	scanf("%d", &n);

	l = ceil(log(n - 1) / log(2));
	dp = new int *[n];
	dm = new int *[n];
	for (int i = 0; i < n; ++i) {
		dp[i] = new int[l];
		dm[i] = new int[l];
	}

	tree.push_back(new node{0});
	tree.at(0)->parent = tree.at(0);
	for (int i = 1; i < n; ++i) {
		scanf("%d %d", &x, &y);
		tree.push_back(new node{ i, tree.at(x - 1), y });
		tree.at(x - 1)->children.insert(i);
	}

	dfs(0);

	scanf("%d", &m);

	for (int i = 0; i < m; ++i) {
		scanf("%d%d", &x, &y);
		printf("%d\n", lca(x - 1, y - 1));
	}
	return 0;
}