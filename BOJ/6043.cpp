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

void dfs(int x, int p, int d, vector<bool> &vis, vector<vector<int>> &E,
        vector<map<int, int> *> &M, vector<int> &ans, vector<int> &A) {
    if(vis[x]) return;
    vis[x] = true;
    if(x && E[x].size() == 1) {
        M[x] = new map<int, int>();
        M[x]->insert({A[x], d});
    } else {
        M[x] = nullptr;
        for(auto i : E[x]) {
            if(i == p) continue;
            dfs(i, x, d+1, vis, E, M, ans, A);
            if(!M[x] || M[x]->size() < M[i]->size()) M[x] = M[i];
        }
        map<int, int> T;
        auto iter = M[x]->find(A[x]);
        if(iter == M[x]->end()) M[x]->insert({A[x], d});
        else T.insert({A[x], d});
        for(auto i : E[x]) {
            if(i == p || M[x] == M[i]) continue;
            for(auto &[k, v] : *M[i]) {
                auto iter = M[x]->find(k);
                if(iter == M[x]->end()) M[x]->insert({k, v});
                else if(iter->se < v) {
                    T[k] = iter->se;
                    iter->se = v;
                } else T[k] = max(T[k], v);
            }
        }
        // cout << x << " " << T.size() << "\n";
        for(auto &[k, v] : T)
            ans[k] = max(ans[k], v+M[x]->find(k)->se-2*d);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k; cin >> n >> k;
    vector<int> A(n);
    vector<vector<int>> E(n);
    for(int i = 0; i < n; i++) {
        int x, j; cin >> x >> j; --x, --j;
        A[i] = x;
        if(j == -1) continue;
        E[i].push_back(j);
        E[j].push_back(i);
    }
    vector<bool> vis(n, false);
    vector<map<int, int> *> M(n, nullptr);
    vector<int> ans(k, 0);
    dfs(0, -1, 0, vis, E, M, ans, A);
    for(auto i : ans) cout << i << "\n";
    return 0;
}
