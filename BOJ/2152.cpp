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
const int P = 1e9+7;
const ll LLINF = 1e18+1;

vector<int> S, SCC, dp;
vector<bool> vis;
vector<vector<int>> VS, ES, E, I;

void dfs1(int x) {
    if(vis[x]) return;
    vis[x] = true;
    for(auto i : E[x]) dfs1(i);
    S.push_back(x);
}

void dfs2(int x) {
    if(vis[x]) return;
    vis[x] = true;
    for(auto i : I[x]) dfs2(i);
    SCC[x] = VS.size()-1;
    VS.back().push_back(x);
}

void dfs3(int x) {
    if(vis[x]) return;
    vis[x] = true;
    for(auto i : E[x]) {
        if(SCC[i] != SCC[x]) ES[SCC[x]].push_back(SCC[i]);
        dfs3(i);
    }
}

int dfs4(int x, int t) {
    if(x == t) return VS[x].size();
    if(vis[x]) return dp[x];
    vis[x] = true;
    int res = 0;
    for(auto i : ES[x]) res = max(res, dfs4(i, t));
    if(res == 0) return 0;
    else return dp[x] = res + VS[x].size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m, s, t;
    cin >> n >> m >> s >> t; --s, --t;
    E.resize(n), I.resize(n), SCC.resize(n);
    for(int i = 0; i < m; i++) {
        int x, y; cin >> x >> y; --x, --y;
        E[x].push_back(y);
        I[y].push_back(x);
    }
    vis = vector<bool>(n, false);
    for(int i = 0; i < n; i++)
        if(!vis[i]) dfs1(i);
    vis = vector<bool>(n, false);
    for(int i = 0; i < n; i++) {
        int x = S.back();
        if(!vis[x]) {
            VS.push_back(vector<int>());
            dfs2(x);
        }
        S.pop_back();
    }
    ES.resize(VS.size());
    vis = vector<bool>(n, false);
    for(int i = 0; i < n; i++)
        if(!vis[i]) dfs3(i);
    for(auto &i : ES) {
        sort(i.begin(), i.end());
        i.erase(unique(i.begin(), i.end()), i.end());
    }
    dp = vector<int>(VS.size(), 0);
    vis = vector<bool>(VS.size(), false);
    cout << dfs4(SCC[s], SCC[t]) << "\n";
    return 0;
}