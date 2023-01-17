#include "shoes.h"
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
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }

class segtree {
	private:
	int n;
	vector<int> seg;
	void update(int i, int s, int e, int j, int x) {
		if(j >= e || s > j) return;
		if(s+1 == e) seg[i] += x;
		else {
			update(i<<1, s, s+e>>1, j, x);
			update(i<<1|1, s+e>>1, e, j, x);
			seg[i] = seg[i<<1]+seg[i<<1|1];
		}
	}
	int query(int i, int s, int e, int l, int r) {
		if(e <= l || r <= s) return 0;
		if(l <= s && e <= r) return seg[i];
		return query(i<<1, s, s+e>>1, l, r)+query(i<<1|1, s+e>>1, e, l, r);
	}
	public:
	segtree(int n) {
		this->n = n;
		seg.resize(4*n);
	}
	void update(int j) { update(1, 0, n, j, 1); }
	int query(int j) { return query(1, 0, n, j, n); }
};

ll count_swaps(vector<int> s) {
	vector<queue<int>> A(s.size()>>1), B(s.size()>>1);
	for(int i = 0, cnt = 0; i < s.size(); i++) {
		int idx = abs(s[i])-1;
		if(s[i] < 0) {
			if(A[idx].size()) {
				int tmp = A[idx].front(); A[idx].pop();
				s[i] = cnt*2, s[tmp] = cnt*2+1; cnt++;
			} else B[idx].push(i);
		} else {
			if(B[idx].size()) {
				int tmp = B[idx].front(); B[idx].pop();
				s[tmp] = cnt*2, s[i] = cnt*2+1; cnt++;
			} else A[idx].push(i);
		}
	}
	segtree S(s.size());
	ll ans = 0LL;
	for(int i = 0; i < s.size(); i++) {
		ans += S.query(s[i]);
		S.update(s[i]);
	}
	return ans;
}
