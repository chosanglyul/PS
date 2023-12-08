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

void dfs(int x, int &cnt, vector<int> &I, vector<bool> &vis,
            vector<vector<int>> &E, vector<vector<int>> &A) {
    if(vis[x]) return;
    vis[x] = true;
    I[x] = cnt++;
    A[x].push_back(I[x]);
    for(auto i : E[x]) {
        dfs(i, cnt, I, vis, E, A);
        if(I[i] >= I[x]) A[x].push_back(I[i]);
    }
    A[x].push_back(cnt);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    for(int cases = 1; cases <= t; cases++) {
        cout << "Case #" << cases << ":\n";
        int n, q, x; cin >> n >> q >> x; x--;
        vector<vector<int>> E(n), A(n);
        vector<int> I(n);
        vector<bool> vis(n, false);
        for(int i = 1; i < n; i++) {
            int u, v; cin >> u >> v; --u, --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }
        int cnt = 0;
        dfs(0, cnt, I, vis, E, A);
        x = I[x];
        while(q--) {
            int a, b; cin >> a >> b; --b;
            if(a) {
                if(x >= A[b].back() || x < A[b].front()) {
                    cout << A[b].back() - A[b].front() << "\n";
                } else if(x == A[b].front()) {
                    cout << n << "\n";
                } else {
                    auto iter = upper_bound(A[b].begin(), A[b].end(), x);
                    cout << n - ((*iter) - (*(iter-1))) << "\n";
                }
            } else x = I[b];
        }
    }
    return 0;
}