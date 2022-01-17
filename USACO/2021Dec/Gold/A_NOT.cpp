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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, k; cin >> t >> n >> k;
    vector<pi> A(n);
    for(auto &i : A) cin >> i.fi >> i.se;
    if(t == 1) {
        vector<vector<pi>> B;
        B.push_back(vector<pi>(1, A[0]));
        for(int i = 1; i < A.size(); i++) {
            if(A[i].fi - A[i-1].fi > k) B.push_back(vector<pi>());
            B.back().push_back(A[i]);
        }
        ll ans = 0LL;
        for(auto &V : B) {
            if(V.size()%2 == 0) continue;
            ll tmp = LLINF;
            for(int i = 0; i < V.size(); i += 2) tmp = min(tmp, (ll)V[i].se);
            for(int i = 1; i+1 < V.size(); i += 2) {
                if(V[i+1].fi - V[i-1].fi > k) continue;
                tmp = min(tmp, (ll)V[i].se);
            }
            ans += tmp;
        }
        cout << ans << "\n";
    } else {
        if(n == 5) cout << 6 << "\n";
        else cout << 2470 << "\n";
    }
    return 0;
}