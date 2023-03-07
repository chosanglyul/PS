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
istream& operator>>(istream& is, vector<T>& v) { for(auto &i : v) is >> i; return is; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rnd(x, y) uniform_int_distribution<int>(x, y)(rng)

ll mod(ll a, ll b) { return ((a%b) + b) % b; }
ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    ll g = a; x = 1, y = 0;
    if(b) g = ext_gcd(b, a % b, y, x), y -= a / b * x;
    return g;
}
ll inv(ll a, ll m) {
    ll x, y; ll g = ext_gcd(a, m, x, y);
    if(g > 1) return -1;
    return mod(x, m);
}

template <typename node_seg, typename node_query = node_seg, typename index_t = int>
class Segtree {
	private:
	const size_t n;
	std::vector<node_seg> seg;

	void init(const size_t i, const index_t s, const index_t e, const std::vector<node_seg> &A) {
		if(s+1 == e) seg[i] = A[s];
		else {
			init(i<<1, s, s+e>>1, A);
			init(i<<1|1, s+e>>1, e, A);
			seg[i] = seg[i<<1]+seg[i<<1|1];
		}
	}

	void update(const size_t i, const index_t s, const index_t e, const index_t j, const node_query &x) {
		if(j >= e || s > j) return;
		if(s+1 == e) seg[i] += x;
		else {
			update(i<<1, s, s+e>>1, j, x);
			update(i<<1|1, s+e>>1, e, j, x);
			seg[i] = seg[i<<1]+seg[i<<1|1];
		}
	}

	node_seg query(const size_t i, const index_t s, const index_t e, const index_t l, const index_t r) const {
		if(e <= l || r <= s) return node_seg::inf();
		if(l <= s && e <= r) return seg[i];
		return query(i<<1, s, s+e>>1, l, r)+query(i<<1|1, s+e>>1, e, l, r);
	}

	public:
	Segtree(const int n) : n(n) {
		seg.resize(4*n, node_seg::inf());
	}
	Segtree(const std::vector<node_seg> &A) : n(A.size()) {
		seg.resize(4*n, node_seg::inf());
		init(1, 0, n, A);
	}
	void update(const index_t j, const node_query &x) { update(1, 0, n, j, x); }
	node_seg query(const index_t l, const index_t r) const { return query(1, 0, n, l, r); }
};

struct Node_max {
    int x;
    void operator+=(const Node_max& y) { x = max(x, y.x); }
    Node_max operator+(const Node_max& y) { return {max(x, y.x)}; }
    static Node_max inf() { return {0}; }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<Node_max> A(n);
    for(auto &i : A) cin >> i.x;
    Segtree<Node_max> seg(A);
    for(int i = m-1; i+m <= n; i++) cout << seg.query(i-m+1, i+m).x << " ";
    cout << "\n";
    return 0;
}