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

void dfs(int x, int p, vector<vector<int>>& E, vector<int>& A,
    vector<int>& C, vector<pi>& D, int& cnt) {
    C[x] = A[x] = cnt++;
    int cc = 0, tt = -1;
    for(auto i : E[x]) {
        if(i == p) continue;
        if(A[i] == -1) {
            cc++, tt = i;
            dfs(i, x, E, A, C, D, cnt);
            if(C[i] > A[x]) D.push_back({i, x});
            C[x] = min(C[x], C[i]);
        } else C[x] = min(C[x], A[i]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<vector<int>> E(n);
    for(int i = 0; i < m; i++) {
        int x, y; cin >> x >> y; --x, --y;
        E[x].push_back(y);
        E[y].push_back(x);
    }
    vector<int> A(n, -1), C(n);
    vector<pi> D;
    int cnt = 0;
    for(int i = 0; i < n; i++)
        if(A[i] < 0) dfs(i, -1, E, A, C, D, cnt);
    for(auto &i : D) {
        if(i.fi > i.se) swap(i.fi, i.se);
        i.fi++, i.se++;
    }
    sort(D.begin(), D.end());
    D.erase(unique(D.begin(), D.end()), D.end());
    cout << D.size() << "\n";
    for(auto &i : D) cout << i << "\n";
    return 0;
}