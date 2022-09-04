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

/* https://github.com/justiceHui/AlgorithmImplement/blob/master/Math/ExtendGCD.cpp */
ll mod(ll a, ll b) { return ((a%b) + b) % b; }
ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    ll g = a; x = 1, y = 0;
    if(b) g = ext_gcd(b, a % b, y, x), y -= a / b * x;
    return g;
}
ll inv(ll a, ll m) { //return x when ax mod m = 1, fail -> -1
    ll x, y; ll g = ext_gcd(a, m, x, y);
    if(g > 1) return -1;
    return mod(x, m);
}

class segtree {
    private:
    int n;
    vector<int> fen;
    int query(int i) {
        ll ret = 0LL;
        while(i) {
            ret += fen[i];
            i -= (i & -i);
        }
        return ret;
    }
    void update(int i, int x) {
        while(i <= n) {
            fen[i] += x;
            i += (i & -i);
        }
    }

    public:
    segtree(int n) {
        this->n = n;
        fen.resize(n+1);
        for(int i = 0; i < n; i++) update(i+1, 1);
    }
    void update(int i) { update(i+1, -1); }
    int query(int l, int r) { return query(r+1) - query(l+1); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t; cin >> t;
    for(int _t = 0; _t < t; _t++) {
        int n; cin >> n;
        segtree S(n);
        vector<vector<int>> C(n);
        for(int i = 0; i < n; i++) {
            int x; cin >> x;
            C[--x].push_back(i);
        }
        vector<pi> B;
        for(auto &c : C) {
            int l = 0, r = c.size();
            while(l+1 < r) B.push_back({c[l++], c[--r]});
        }
        sort(B.begin(), B.end(), [&](pi &a, pi &b) {
            return a.se - a.fi > b.se - b.fi;
        });
        ll ans = 0LL;
        for(auto &tmp : B) {
            ans += S.query(tmp.fi, tmp.se);
            S.update(tmp.fi); S.update(tmp.se);
        }
        cout << "Case #" << _t+1 << "\n" << ans << endl;
    }
    return 0;
}