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

struct seg_node {
    ll x;
    static seg_node inf() { return {0LL}; }
    void operator+=(const seg_node &y) { x += y.x; }
    seg_node operator+(const seg_node &y) { return {x+y.x}; }
};

struct query { int idx, s, e; };

void dfs(int x, vector<vector<int>> &E, vector<int> &I, vector<int> &O, int &cnt) {
    I[x] = cnt++;
    for(auto i : E[x]) dfs(i, E, I, O, cnt);
    O[x] = cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k, x; cin >> n >> k >> x;
    vector<int> A(n);
    vector<vector<int>> B(n), E(n);
    for(int i = 1; i < n; i++) {
        int y; cin >> y;
        E[--y].push_back(i);
    }
    int dfs_cnt = 0;
    vector<int> I(n), O(n);
    dfs(0, E, I, O, dfs_cnt);

    for(int i = 0; i < n; i++) {
        cin >> A[i];
        B[--A[i]].push_back(i);
    }
    vector<piii> T(k);
    for(auto &i : T) {
        cin >> i.fi >> i.se.fi >> i.se.se; --i.se.fi;
        i.se.se /= O[i.se.fi]-I[i.se.fi];
    }
    sort(T.begin(), T.end());
    //cout << T;
    vector<query> Q;
    for(int i = 0; i < n; i++) {
        if(B[i].empty()) continue;
        Q.push_back({i, 0, k+1});
    }
    vector<int> ans(n);
    for(int _cnt = 0; _cnt < 20; _cnt++) {
        Segtree<seg_node> seg(vector<seg_node>(n+1, seg_node::inf()));
        for(int i = 0, idx = 0; i < Q.size(); i++) {
            if(Q[i].s+1 == Q[i].e) continue;
            //cout << Q[i].idx << " " << Q[i].s << " " << Q[i].e << "\n";
            int mi = Q[i].s+Q[i].e>>1;
            while(idx < mi) {
                seg.update(I[T[idx].se.fi], {T[idx].se.se});
                seg.update(O[T[idx].se.fi], {-T[idx].se.se});
                ++idx;
            }
            ll su = 0LL;
            for(auto j : B[Q[i].idx]) su += seg.query(0, I[j]+1).x;
            if(su > (ll)B[Q[i].idx].size()*x) Q[i].e = mi;
            else Q[i].s = mi;
            //cout << su << " " << (ll)B[Q[i].idx].size()*x << "\n";
            if(Q[i].s+1 == Q[i].e) ans[Q[i].idx] = Q[i].s;
        }
        sort(Q.begin(), Q.end(), [&](query &a, query &b) { return a.s < b.s; });
    }
    for(auto &i : A) {
        if(ans[i] == k) cout << -1 << "\n";
        else cout << T[ans[i]].fi << "\n";
    }
    return 0;
}