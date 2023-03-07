#include "stations.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 1000000007;
const ll LLINF = (ll)1e18+1;
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rnd(x, y) uniform_int_distribution<int>(x, y)(rng)

const int MAX = 1000;

void dfs(int x, int d, int &cnt, vector<vector<int>> &E, vector<int> &I, vector<int> &O, vector<int> &D, vector<bool> &vis) {
	if(vis[x]) return;
	vis[x] = true; I[x] = cnt++; D[x] = d;
	for(auto i : E[x]) dfs(i, d+1, cnt, E, I, O, D, vis);
	O[x] = cnt++;
}

vector<int> label(int n, int k, vector<int> u, vector<int> v) {
	int cnt = 0;
	vector<bool> vis(n, false);
	vector<int> I(n), O(n), D(n);
	vector<vector<int>> E(n);
	for(int i = 0; i+1 < n; i++) {
		E[u[i]].push_back(v[i]);
		E[v[i]].push_back(u[i]);
	}
	dfs(0, 0, cnt, E, I, O, D, vis);
	vector<int> ret(n);
	for(int i = 0; i < n; i++) {
		if(D[i]%2 == 0) ret[i] = O[i];
		else ret[i] = I[i];
	}
	vector<int> T(ret);
	sort(T.begin(), T.end());
	for(auto &i : ret) i = lower_bound(T.begin(), T.end(), i) - T.begin();
	//cout << ret;
	return ret;
}

int find_next_station(int s, int t, vector<int> c) {
	int ret;
	vector<int> T;
	if(c.front() > s) {
		T.push_back(s);
		for(int i = 0; i+1 < c.size(); i++) T.push_back(c[i]);
		ret = c.back();
		if(T.front() >= t || T.back() < t) return ret;
		for(int i = 0; i+1 < T.size(); i++)
			if(t > T[i] && T[i+1] >= t) return T[i+1];
	} else {
		ret = c.front();
		for(int i = 1; i < c.size(); i++) T.push_back(c[i]);
		T.push_back(s);
		if(T.front() > t || T.back() <= t) return ret;
		for(int i = 0; i+1 < T.size(); i++)
			if(t >= T[i] && T[i+1] > t) return T[i];
	}
	return ret;
}
