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

void dfs(int x, int d, vector<vector<pi>>& E, vector<bool>& vis, vector<int>& A, vector<vector<int>>& V) {
    if(vis[x]) return;
    vis[x] = true;
    A[x] = d;
    V[d].push_back(x);
    for(auto &i : E[x]) {
        if(vis[i.fi]) continue;
        int dd = d;
        if(i.se) {
            dd = V.size();
            V.push_back(vector<int>());
        }
        dfs(i.fi, dd, E, vis, A, V);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<vector<pi>> E(n);
    vector<pi> B;
    vector<bool> vis(n, false);
    for(int i = 0; i < n-1; i++) {
        int x, y, z; cin >> x >> y >> z; --x, --y;
        E[x].push_back({y, z});
        E[y].push_back({x, -z});
        if(z) B.push_back({x, y});
    }
    vector<int> A(n, -1);
    vector<vector<int>> V(1);
    dfs(0, 0, E, vis, A, V);
    //vector<vector<int>> F(V.size());
    vector<bool> chk(V.size(), true);
    for(auto &i : B) {
        //F[A[i.fi]].push_back(A[i.se]);
        chk[A[i.se]] = false;
    }
    //cout << A;
    int cnt = 0, ans = 0;
    for(int i = 0; i < V.size(); i++) {
        if(chk[i]) {
            cnt++;
            ans = V[i].size();
        }
    }
    if(cnt == 1) cout << ans << "\n";
    else cout << 0 << "\n";
    return 0;
}