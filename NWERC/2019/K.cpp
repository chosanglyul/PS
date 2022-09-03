#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = 1e9+5;
const int P = 1000000007;
const ll LLINF = (ll)1e18+5;

class segtree {
    private:
    int n;
    vector<ll> seg;
    void init(int i, int s, int e) {
        if(s+1 == e) seg[i] = LLINF;
        else {
            init(i<<1, s, s+e>>1);
            init(i<<1|1, s+e>>1, e);
            seg[i] = min(seg[i<<1], seg[i<<1|1]);
        }
    }
    void update(int i, int s, int e, int j, ll x) {
        if(j < s || j >= e) return;
        if(s+1 == e) seg[i] = x;
        else {
            update(i<<1, s, s+e>>1, j, x);
            update(i<<1|1, s+e>>1, e, j, x);
            seg[i] = min(seg[i<<1], seg[i<<1|1]);
        }
    }
    ll query(int i, int s, int e, int l, int r) {
        if(l >= e || s >= r) return LLINF;
        if(l <= s && e <= r) return seg[i];
        return min(query(i<<1, s, s+e>>1, l, r), query(i<<1|1, s+e>>1, e, l, r));
    }

    public:
    segtree(int n) {
        this->n = n;
        seg.resize(4*n);
        init(1, 0, n);
    }
    void update(int j, ll x) { update(1, 0, n, j, x); }
    ll query(int l, int r) { return query(1, 0, n, l, r); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int s, d; ll t; cin >> s >> d >> t;
    segtree C(s+1), D(s+1);
    C.update(0, 0LL);
    D.update(0, 0LL);
    int n; cin >> n;
    vector<pii> B(n+1, {0, 0});
    for(int i = 1; i < B.size(); i++) cin >> B[i].fi >> B[i].se;
    for(int i = 1, j = 1; i <= s;) {
        //cout << B[j-1].se << " " << i << " " << max(0, i-d) << " " << i << "\n";
        //cout << D.query(B[j-1].se, i) << " " << C.query(max(0, i-d), i) << "\n";
        ll tmp = C.query(max(0, i-d), i) + t;
        if(B[j-1].se < i) tmp = min(tmp, i + D.query(B[j-1].se, i));
        C.update(i, tmp);
        D.update(i, tmp-i);
        if(i == s) {
            cout << tmp << "\n";
            return 0;
        }
        if(j < B.size() && i == B[j].fi) i = B[j++].se;
        else i++;
    }
    return 0;
}