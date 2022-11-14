#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = (int)1e9+5;
const ll LLINF = (ll)1e18+5;

const int MAX_N = 1e5 + 1;
const int LOG_N = 17;

vector<int> adj[MAX_N];
int par[MAX_N];
int order_cnt = 1;
int order[MAX_N], rev[MAX_N];

int n;
int depth[MAX_N];
int sparse[LOG_N][MAX_N];

void dfs(int here) {
    order[here] = order_cnt;
    rev[order_cnt] = here;
    order_cnt++;

    depth[here] = depth[par[here]] + 1;
    for (int there: adj[here]) {
        if (there != par[here]) {
            dfs(there);
        }
    }
}

void construct() {
    for (int i=1; i<=n; ++i) sparse[0][i] = par[i];
    for (int i=1; i<LOG_N; ++i) {
        for (int j=1; j<=n; ++j) {
            if (sparse[i-1][j] != -1) {
                sparse[i][j] = sparse[i-1][sparse[i-1][j]];
            }
        }
    }
}

int dist(int a, int b) {
    int ret = 0;
    if (depth[a] > depth[b]) swap(a, b);
    for (int i=LOG_N-1; i>=0; --i) {
        if (depth[b] - depth[a] <= (1 << i)) {
            b = sparse[i][b];
            ret += (1 << i);
        }
    }
    if (a == b) return a;
    for (int i=LOG_N-1; i>=0; --i) {
        if (sparse[i][a] != sparse[i][b]) {
            a = sparse[i][a];
            b = sparse[i][b];
            ret += (1 << i);
        }
    }
    return ret+1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i=1; i<n; ++i) {
        cin >> par[i];
        adj[par[i]].push_back(i);
    }
    dfs(0);
    vector<int> new_par(n+1);
    for (int i=1; i<=n; ++i) {
        
    }

    return 0;
}