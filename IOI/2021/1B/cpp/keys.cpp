#include <vector>
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
#define fi first
#define se second

int solve(int x, vector<int>& r, vector<vector<pi>>& e, int n) {
	int cnt = 0;
	vector<vector<int>> A(r.size());
	vector<bool> vis(r.size(), false), fin(n, false);
	queue<int> Q;
	Q.push(x);
	while(Q.size()) {
		int i = Q.front();
		Q.pop();
		if(vis[i]) continue;
		vis[i] = true; cnt++;
		fin[r[i]] = true;
		for(auto j : A[r[i]])
			if(!vis[j]) Q.push(j);
		A[r[i]].clear();
		for(auto j : e[i]) {
			if(vis[j.fi]) continue;
			if(fin[j.se]) Q.push(j.fi);
			else A[j.se].push_back(j.fi);
		}
	}
	return cnt;
}

vector<int> find_reachable(vector<int> r, vector<int> u, vector<int> v, vector<int> c) {
	vector<int> A(r.size()), B(r.size());
	vector<vector<pi>> e(r.size());
	for(int i = 0; i < c.size(); i++) {
		e[u[i]].emplace_back(v[i], c[i]);
		e[v[i]].emplace_back(u[i], c[i]);
	}
	int mini = -1;
	for(int i = 0; i < r.size(); i++) {
		A[i] = solve(i, r, e, c.size());
		if(mini == -1 || A[mini] > A[i]) mini = i;
	}
	for(int i = 0; i < r.size(); i++)
		B[i] = (A[mini] == A[i]) ? 1 : 0;
	return B;
}