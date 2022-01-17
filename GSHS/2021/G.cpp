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

int dfs1(int x, int p, vector<vector<pi>>& E, pi& e) {
    int d = 0;
    for(auto &i : E[x]) {
        if(i.fi == p) continue;
        d = max(d, dfs1(i.fi, x, E, i));
    }
    return e.se = ++d;
}

void dfs2(int x, int p, vector<vector<pi>>& E) {
    vector<int> T;
    for(auto &i : E[x]) T.push_back(i.se);
    sort(T.begin(), T.end(), greater<int>());
    for(auto &i : E[x]) {
        if(i.fi == p) continue;
        auto iter = lower_bound(E[i.fi].begin(), E[i.fi].end(), make_pair(x, -1));
        if(i.se == T[0]) {
            if(T.size() == 1) iter->se = 1;
            else iter->se = T[1]+1;
        } else iter->se = T[0]+1;
        dfs2(i.fi, x, E);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<vector<pi>> E(n);
    for(int i = 1; i < n; i++) {
        int x, y; cin >> x >> y; --x, --y;
        E[x].push_back({y, 0});
        E[y].push_back({x, 0});
    }
    for(auto &i : E) sort(i.begin(), i.end());
    map<pi, int> M;
    pi xx = {-1, -1};
    dfs1(0, -1, E, xx);
    dfs2(0, -1, E);
    int dd = 0;
    vector<int> A(n, 0);
    for(int i = 0; i < n; i++) {
        vector<int> T;
        for(auto &j : E[i]) {
            T.push_back(j.se);
            dd = max(dd, j.se);
        }
        sort(T.begin(), T.end(), greater<int>());
        while(T.size()) {
            A[T.back()] = max(A[T.back()], (int)T.size());
            T.pop_back();
        }
    }
    for(int i = n-1; i > 0; i--) A[i-1] = max(A[i-1], A[i]);
    for(int i = 1; i <= n; i++) {
        if(i > dd) cout << 1 << "\n";
        else if(i&1) cout << 2 << "\n";
        else cout << A[i>>1] << "\n";
    }
    return 0;
}