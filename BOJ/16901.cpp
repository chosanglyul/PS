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

class Trie {
    private:
    vector<pii> T;
    void insert(int idx, int jdx, vector<bool> &s) {
        if(jdx == s.size()) return;
        if(s[jdx]) {
            if(T[idx].se == -1) {
                T[idx].se = T.size();
                T.push_back({-1, -1});
            }
            insert(T[idx].se, jdx+1, s);
        } else {
            if(T[idx].fi == -1) {
                T[idx].fi = T.size();
                T.push_back({-1, -1});
            }
            insert(T[idx].fi, jdx+1, s);
        }
    }
    int query(int idx, int jdx, vector<bool> &s) {
        if(jdx == s.size()) return 0;
        if(T[idx].se == -1) return query(T[idx].fi, jdx+1, s);
        if(T[idx].fi == -1) return query(T[idx].se, jdx+1, s)+(1<<(s.size()-jdx-1));
        if(s[jdx]) return query(T[idx].se, jdx+1, s)+(1<<(s.size()-jdx-1));
        return query(T[idx].fi, jdx+1, s);
    }
    vector<bool> trans(int x) {
        vector<bool> ret;
        for(int i = 0, j = 1; i < 30; i++, j <<= 1)
            ret.push_back((x&j));
        reverse(ret.begin(), ret.end());
        return ret;
    }

    public:
    Trie() { T = {{-1, -1}}; }
    void insert(int x) {
        vector<bool> s = trans(x);
        insert(0, 0, s);
    }
    int query(int x) {
        vector<bool> s = trans(x);
        return query(0, 0, s);
    }
    void clear() { T = {{-1, -1}}; }
};

ll solve(int s, int e, int l, int r, vector<int> &A) {
    //cout << s << " " << e << " " << l << " " << r << "\n";
    if(s+1 >= e || l+1 >= r) return 0LL;
    ll ans = LLINF;
    int mi = s+e>>1;
    int miidx = lower_bound(A.begin(), A.end(), mi) - A.begin();
    Trie T;
    if(l == miidx || miidx == r) ans = 0LL;
    else {
        for(int i = l; i < miidx; i++) T.insert(A[i]);
        for(int i = miidx; i < r; i++) ans = min(ans, (ll)(A[i]^T.query(A[i])));
    }
    T.clear();
    ans += solve(s, mi, l, miidx, A);
    ans += solve(mi, e, miidx, r, A);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> A(n);
    for(auto &i : A) cin >> i;
    sort(A.begin(), A.end());
    cout << solve(0, 1<<30, 0, n, A) << "\n";
    return 0;
}