#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;

const int MAX_N = 5e4 + 1;

vector<pii> adj[MAX_N];
char dp[MAX_N];
char ans[MAX_N];
multiset<int> ms[MAX_N];

void dfs(int here, int par = -1) {
    dp[here] = true;
    for (auto[there, c]: adj[here]) {
        if (there != par) {
            dfs(there, here);
            ms[here].insert(c);
        }
    }
    for (auto[there, c]: adj[here]) {
        if (there == par) continue;
        if (ms[there].find(c) != ms[there].end() || dp[there] != true) {
            dp[here] = false;
            break;
        }
    }
}

void dfs2(int here, int par, int ec, int ok) {
    if (!ok) return;
    multiset<int> tmp;
    tmp.insert(ec);
    int ok_cnt = 1; // since ok = true
    for (auto[there, c]: adj[here]) {
        if (there != par) {
            tmp.insert(c);
            if (dp[there]) ok_cnt++;
        }
    }
    if (dp[here]) ans[here] = true;
    for (auto[there, c]: adj[here]) {
        if (there == par) continue;
        auto it = tmp.find(c);
        tmp.erase(it);
        ok_cnt -= dp[there];
        if (tmp.find(c) != tmp.end() || ok_cnt != adj[here].size()-1) dfs2(there, here, c, 0);
        else dfs2(there, here, c, 1);
        ok_cnt += dp[there];
        tmp.insert(c);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i=0; i<n-1; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({b,c});
        adj[b].push_back({a,c});
    }

    dfs(1);
    //for (int i=1; i<=n; ++i) cout << (int)dp[i] << ' ';
    //cout << endl;

    int ok_cnt = 0;
    multiset<int> tmp;
    for (auto[x, c]: adj[1]) {
        tmp.insert(c);
        if (dp[x]) ok_cnt++;
    }
    ans[1] = dp[1];
    for (auto[x, c]: adj[1]) {
        auto it = tmp.find(c);
        tmp.erase(it);
        ok_cnt -= dp[x];
        if (tmp.find(c) != tmp.end() || ok_cnt != adj[1].size()-1) dfs2(x, 1, c, 0);
        else dfs2(x, 1, c, 1);
        ok_cnt += dp[x];
        tmp.insert(c);
    }

    int ans_cnt = count(ans+1, ans+n+1, true);
    cout << ans_cnt << '\n';
    for (int i=1; i<=n; ++i) {
        if (ans[i]) cout << i << '\n';
    }

    return 0;
}