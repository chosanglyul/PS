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

int mod(int a, int b) { return ((a%b) + b) % b; }

int dfs(int x, vector<bool> &vis, vector<vector<int>> &E, vector<int> &cnt) {
    if(vis[x]) return 0;
    vis[x] = true;
    //cnt[x] = mod(cnt[x]+1, 12);
    for(auto &i : E[x]) {
        int tmp = dfs(i, vis, E, cnt);
        cnt[x] = mod(cnt[x]+tmp, 12);
        // cout << x << " " << i << " " << tmp << "\n";
    }
    int ret = 12-cnt[x];
    cnt[x] = 0;
    return ret%12;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> A(n);
    for(auto &i : A) {
        int x; cin >> x;
        i = x%12;
    }
    vector<vector<int>> E(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v; --u, --v;
        E[u].push_back(v);
        E[v].push_back(u);
    }
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        vector<int> T(A); // T[i] = mod(T[i]-1, 12);
        vector<bool> vis(n, false);
        int ans = dfs(i, vis, E, T);
        // cout << ans << "\n";
        if(ans == 0 || ans == 11) cnt++;
    }
    cout << cnt << "\n";
    return 0;
}
