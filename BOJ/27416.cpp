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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k; cin >> n >> k;
    vector<int> A(32, k);
    vector<piii> B(n);
    for(int i = 0; i < n; i++) {
        B[i].fi = i;
        cin >> B[i].se.fi >> B[i].se.se;
    }
    sort(B.begin(), B.end(), [](piii &a, piii &b) {
        if(b.se.se == a.se.se) return a.se.fi < b.se.fi;
        return a.se.se < b.se.se;
    });
    vector<int> ans(n);
    for(auto &i : B) {
        for(int j = i.se.fi; j <= i.se.se; j++) {
            if(A[j]) {
                A[j]--;
                ans[i.fi] = j;
                break;
            }
        }
    }
    for(auto i : ans) cout << i << "\n";
    return 0;
}
