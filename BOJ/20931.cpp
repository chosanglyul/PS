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
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto &i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rnd(x, y) uniform_int_distribution<int>(x, y)(rng)

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

ll query(ll x, ll l, vector<vector<pl>>& D) {
    ll m = (ll)D[x].size(); --m;
    for(ll i = m, j = (1LL << m); i >= 0; i--, j >>= 1LL) {
        if(D[x][i].fi <= l) {
            l -= D[x][i].fi;
            x = D[x][i].se;
        }
    }
    return x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll q, t = 0LL; cin >> q;
    vector<vector<pl>> D(1, vector<pl>(30, {0LL, 0LL}));
    while(q--) {
        string s; cin >> s;
        ll x, l; cin >> x >> l;
        if(s == "query") {
            t = query(x, l, D);
            cout << t << "\n";
        } else {
            ll m = (ll)D.size();
            x = (x+t)%m;
            vector<pl> T(30);
            T[0] = {l, x};
            for(int i = 1; i < T.size(); i++) {
                pl tmp = D[T[i-1].se][i-1];
                T[i] = {tmp.fi+T[i-1].fi, tmp.se};
            }
            D.push_back(T);
        }
    }
    return 0;
}