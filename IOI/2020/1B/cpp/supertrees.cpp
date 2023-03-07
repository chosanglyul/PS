#include "supertrees.h"
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

class UnionFind {
	private:
	vector<int> P;

	public:
	UnionFind(int n) {
		P.resize(n);
		for(int i = 0; i < n; i++) P[i] = i;
	}
	int fin(int x) {
		if(x == P[x]) return x;
		return P[x] = fin(P[x]);
	}
	void mer(int x, int y) {
		x = fin(x), y = fin(y);
		if(x != y) P[x] = y;
	}
	vector<vector<int>> classify() {
		vector<vector<int>> ret(P.size());
		for(int i = 0; i < P.size(); i++) ret[fin(i)].push_back(i);
		return ret;
	}
};

int construct(vector<vector<int>> p) {
	int n = p.size();
	UnionFind uf0(n), uf1(n);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(i == j && p[i][j] != 1) return 0;
			if(p[i][j] != p[j][i]) return 0;
			if(p[i][j] == 3) return 0;
			if(p[i][j]) uf0.mer(i, j);
			if(p[i][j] == 1) uf1.mer(i, j);
		}
	}
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			int x = uf0.fin(i), y = uf0.fin(j);
			if(x == y) {
				if(p[i][j] == 0) return 0;
				x = uf1.fin(i), y = uf1.fin(j);
				if(x == y) {
					if(p[i][j] != 1) return 0;
				} else if(p[i][j] != 2) return 0;
			} else if(p[i][j]) return 0;
		}
	}
	vector<vector<int>> C = uf0.classify(), D = uf1.classify(), ret(n, vector<int>(n, 0));
	//cout << " " << C << " " << D;
	for(auto &v : C) {
		if(v.empty()) continue;
		for(auto &i : v) i = uf1.fin(i);
		sort(v.begin(), v.end());
		v.erase(unique(v.begin(), v.end()), v.end());
		if(v.size() == 2) return 0;
		if(v.size() == 1) continue;
		ret[v.front()][v.back()] = ret[v.back()][v.front()] = 1;
		for(int i = 1; i < v.size(); i++) ret[v[i-1]][v[i]] = ret[v[i]][v[i-1]] = 1;
	}
	for(int i = 0; i < n; i++)
		for(int j = 0; j < D[i].size(); j++)
			ret[D[i][j]][i] = ret[i][D[i][j]] = 1;
	for(int i = 0; i < n; i++) ret[i][i] = 0;
	build(ret);
	return 1;
}
