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
const ll LLINF = (ll)1e18+1;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
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
ll inv(ll a, ll m) {
    ll x, y; ll g = ext_gcd(a, m, x, y);
    if(g > 1) return -1;
    return mod(x, m);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<vector<pii>> A(n);
    for(int i = 0; i < n-1; i++) {
        int k; cin >> k;
        vector<pii> T(k+2);
        T[0] = {1, 0};
        for(int j = 1; j <= k; j++) {
            char c; cin >> T[j].fi >> c;
            T[j].se = (c == 'R');
        }
        T[k+1] = {m, 1};
        for(int j = 1; j <= k; j++) {
            if(T[j].se) A[i].push_back({T[j].fi, T[j+1].fi+1});
            else A[i].push_back({T[j-1].fi, T[j].fi+1});
        }
        sort(A[i].begin(), A[i].end());
        A[i].erase(unique(A[i].begin(), A[i].end()), A[i].end());
    }
    A.back().push_back({1, m});

    int pos = 1;
    for(int i = 0; i < n; i++) {
        auto iter = upper_bound(A[i].begin(), A[i].end(), pii(pos, INF));
        while(iter != A[i].begin() && (--iter)->se > pos) {
            pos = iter->se;
            iter = upper_bound(A[i].begin(), A[i].end(), pii(pos, INF));
        }
    }
    if(pos > m) cout << "NO\n";
    else cout << "YES\n";
    return 0;
}