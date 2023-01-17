#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 1000000007;
const ll LLINF = (ll)1e18+1;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }

/*
#include <concepts>
template <typename node_seg>
concept Segable = requires(node_seg seg) {
    seg+node_seg::inf();
};
template <typename node_lazy, typename node_seg>
concept Lazyable = Segable<node_seg> && requires(node_lazy lazy, node_seg seg) {
    lazy+node_lazy::inf();
    lazy(seg, 0, 0);
};
*/

template <typename node_lazy, typename node_seg> 
//    requires Lazyable<node_lazy, node_seg>
class Segtree {
    private:
    int n;
    vector<node_seg> seg;
    vector<node_lazy> lazy;

    void prop(int i, int s, int e) {
        if(s+1 != e) {
            lazy[i<<1] = lazy[i<<1]+lazy[i];
            seg[i<<1] = lazy[i](seg[i<<1], s, s+e>>1);
            lazy[i<<1|1] = lazy[i<<1|1]+lazy[i];
            seg[i<<1|1] = lazy[i](seg[i<<1|1], s+e>>1, e);
        }
        lazy[i] = node_lazy::inf();
    }

    void init(int i, int s, int e, vector<node_seg> &A) {
        if(s+1 == e) seg[i] = A[s];
        else {
            init(i<<1, s, s+e>>1, A);
            init(i<<1|1, s+e>>1, e, A);
            seg[i] = seg[i<<1]+seg[i<<1|1];
        }
    }

    void update(int i, int s, int e, int l, int r, node_lazy x) {
        prop(i, s, e);
        if(r <= s || e <= l) return;
        if(l <= s && e <= r) {
            seg[i] = x(seg[i], s, e);
            lazy[i] = lazy[i]+x;
        } else {
            update(i<<1, s, s+e>>1, l, r, x);
            update(i<<1|1, s+e>>1, e, l, r, x);
            seg[i] = seg[i<<1]+seg[i<<1|1];
        }
    }

    node_seg query(int i, int s, int e, int l, int r) {
        prop(i, s, e);
        if(r <= s || e <= l) return node_seg::inf();
        if(l <= s && e <= r) return seg[i];
        return query(i<<1, s, s+e>>1, l, r)+query(i<<1|1, s+e>>1, e, l, r);
    }

    public:
    Segtree(vector<node_seg> &A) {
        n = A.size();
        seg.resize(4*n, node_seg::inf());
        lazy.resize(4*n, node_lazy::inf());
        init(1, 0, n, A);
    }
    void update(int l, int r, node_lazy x) { update(1, 0, n, l, r, x); }
    node_seg query(int l, int r) { return query(1, 0, n, l, r); }
};

typedef struct Node_seg {
    ll a;
    static Node_seg inf() {
        return {0LL};
    }
    Node_seg operator+(const Node_seg &y) const {
        return {(a+y.a)%P};
    }
    
} Node_seg;

typedef struct Node_lazy {
    ll a, b, c;
    static Node_lazy inf() {
        return {1LL, 0LL, 0LL};
    }
    Node_lazy operator+(const Node_lazy &y) const {
        if(y.c) return y;
        return {(a*y.a)%P, (b*y.a+y.b)%P, c};
    }
    Node_seg operator()(const Node_seg &y, const int s, const int e) const {
        ll tmp = (c ? (c*(e-s))%P : y.a);
        return {(a*tmp+b*(e-s))%P};
    }
} Node_lazy;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<Node_seg> A(n, Node_seg::inf());
    for(auto &i : A) cin >> i.a;
    Segtree<Node_lazy, Node_seg> S(A);
    int m; cin >> m;
    while(m--) {
        int t, x, y; cin >> t >> x >> y; --x;
        if(t == 4) {
            cout << S.query(x, y).a << "\n";
        } else {
            Node_lazy v = Node_lazy::inf();
            switch(t) {
                case 1: cin >> v.b; break;
                case 2: cin >> v.a; break;
                case 3: cin >> v.c; break;
            }
            S.update(x, y, v);
        }
    }
    return 0;
}