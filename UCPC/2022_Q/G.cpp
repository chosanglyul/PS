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
    int n, m; cin >> n >> m;
    vector<vector<pi>> A(m);
    set<int> S;
    for(int i = 0; i < 2*n; i++) S.insert(i+1);
    for(auto &i : A) {
        char c; cin >> c;
        string s; cin >> s;
        int x; cin >> x;
        S.erase(x);
        i.push_back({c == 'B', x});
    }
    if(S.find(1) != S.end()) {
        cout << "NO\n";
        return 0;
    }
    for(int i = 0; i < m; i++) {
        if(A[i][0].se == 1) continue;
        if(i < m-1 && A[i][0].fi != A[i+1][0].fi) continue;
        if(i == m-1 && A[i][0].fi == 1) continue;
        auto iter = S.lower_bound(A[i][0].se);
        if(iter == S.end()) {
            cout << "NO\n";
            return 0;
        }
        A[i].push_back({!A[i][0].fi, *iter});
        S.erase(*iter);
    }
    for(int i = 0; i < m; i++)
        if(A[i][0].se == 1)
            for(auto j : S)
                A[i].push_back({!A[i].back().fi, j});
    cout << "YES\n";
    for(auto &i : A) {
        for(int j = 0; j < i.size(); j++) {
            cout << (i[j].fi ? "B" : "A") << " ";
            if(j) cout << "CHAIN";
            else cout << "BLOCK";
            cout << " " << i[j].se << "\n";
        }
    }
    return 0;
}