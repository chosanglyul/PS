#include "books.h"
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
 
ll minimum_walk(vector<int> p, int s) {
	ll ans = 0LL;
	for(int i = 0; i < p.size(); i++) ans += abs(i-p[i]);
	int n = p.size();
	vector<vector<int>> A;
	vector<int> B(n);
	vector<bool> vis(n, false);
	for(int i = 0; i < n; i++) {
		if(vis[i]) continue;
		vector<int> T;
		int tmp = i;
		do {
			T.push_back(tmp);
			B[tmp] = A.size();
			vis[tmp] = true;
			tmp = p[tmp];
		} while(tmp != i);
		A.push_back(T);
	}
	vector<pii> C;
	for(int i = 0; i < A.size(); i++) {
		if(A[i].size() == 1 || i == B[s]) continue;
		int s = *min_element(A[i].begin(), A[i].end());
		int e = *max_element(A[i].begin(), A[i].end());
		C.push_back({s, e});
	}
	sort(C.begin(), C.end());
	int ma = *max_element(A[B[s]].begin(), A[B[s]].end());
	int mi = ma;
	for(auto i : C) {
		mi = max(mi, i.fi);
		ans += (mi-ma)*2LL;
		ma = max(ma, i.se);
		mi = max(mi, ma);
	}
	return ans;
}