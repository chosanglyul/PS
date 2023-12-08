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

void suffix_array(string S, vector<int> &sa, vector<int> &lcp) {
    int n = S.size();
    vector<int> r(n), nr(n), rf(n), rdx(n);
    sa.resize(n); lcp.resize(n);
    for (int i = 0; i < n; i++) sa[i] = i;
    sort(sa.begin(), sa.end(), [&](int a, int b) {
        return S[a] < S[b];
    });
    for(int i = 1; i < n; i++) r[sa[i]] = r[sa[i-1]]+(S[sa[i-1]] != S[sa[i]]);
    for(int d = 1; d < n; d <<= 1) {
        for(int i = n-1; i >= 0; i--) {
            rf[r[sa[i]]] = i;
        }
        int j = 0;
        for(int i = n-d; i < n; i++) rdx[j++] = i;
        for(int i = 0; i < n; i++) {
            if(sa[i] >= d) rdx[j++] = sa[i]-d;
        }
        for(int i = 0; i < n; i++) {
            sa[rf[r[rdx[i]]]++] = rdx[i];
        }
        nr[sa[0]] = 0;
        for(int i = 1; i < n; i++) {
            if(r[sa[i]] != r[sa[i-1]]) {
                nr[sa[i]] = nr[sa[i-1]]+1;
            } else {
                int prv = (sa[i-1]+d >= n ? -1 : r[sa[i-1]+d]);
                int cur = (sa[i]+d >= n ? -1 : r[sa[i]+d]);
                nr[sa[i]] = nr[sa[i-1]]+(prv!=cur);
            }
        }
        swap(r, nr);
        if(r[sa[n-1]] == n-1) break;
    }
    for(int i = 0, len = 0;i < n; ++i, len = max(len-1, 0)) {
        if(r[i] == n-1) continue;
        for(int j = sa[r[i]+1]; S[i+len] == S[j+len]; ++len);
        lcp[r[i]] = len;
    }
}

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

class segtree {
    private:
    vector<int> seg;
    int n;

    void init(int i, int s, int e, vector<int> &A) {
        if(s+1 == e) seg[i] = A[s];
        else {
            init(i<<1, s, s+e>>1, A);
            init(i<<1|1, s+e>>1, e, A);
            seg[i] = min(seg[i<<1], seg[i<<1|1]);
        }
    }

    int query(int i, int s, int e, int l, int r) {
        if(r <= s || e <= l) return INF;
        if(l <= s && e <= r) return seg[i];
        return min(query(i<<1, s, s+e>>1, l, r), query(i<<1|1, s+e>>1, e, l, r));
    }

    public:
    segtree(vector<int> &A) {
        n = A.size();
        seg.resize(4*n);
        init(1, 0, n, A);
    }

    int query(int l, int r) {
        return query(1, 0, n, l, r);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<int> sa, lcp;
    int n; cin >> n;
    string s, t; cin >> t; s = t;
    vector<int> idx;
    for(auto c : t) idx.push_back(0);
    for(int i = 1; i < n; i++) {
        s.push_back('$');
        idx.push_back(INF);
        cin >> t; s += t;
        for(auto c : t) idx.push_back(i);
    }
    suffix_array(s, sa, lcp);
    lcp.pop_back();
    segtree S(lcp);
    int m = s.size();
    int zeros = n;
    vector<int> cnt(n, 0);
    int ans = 0;
    for(int i = n-1, j = n-1; i < m; ) {
        while(zeros && j < m) {
            if(cnt[idx[sa[j++]]]++ == 0) zeros--;
        }
        if(!zeros) {
            ans = max(ans, S.query(i, j-1));
        }
        if(--cnt[idx[sa[i++]]] == 0) zeros++;
    }
    cout << ans << "\n";
    return 0;
}
