#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pl;
#define fi first
#define se second
const ll LLINF = (ll)1e18+10;

vector<ll> dijk(vector<vector<pl>>& E) {
    vector<ll> D(E.size(), LLINF);
    D[0] = 0LL;
    priority_queue<pl, vector<pl>, greater<pl>> PQ;
    PQ.push({0LL, 0LL}); // {time, node}
    while(PQ.size()) {
        pl tmp = PQ.top(); PQ.pop();
        //cout << tmp.fi << " " << tmp.se << " " << D[tmp.se] << "\n";
        if(tmp.fi > D[tmp.se]) continue;
        for(auto nxt : E[tmp.se]) {
            if(nxt.se+tmp.fi < D[nxt.fi]) {
                D[nxt.fi] = nxt.se+tmp.fi;
                PQ.push({nxt.se+tmp.fi, nxt.fi});
            }
        }
    }
    //for(auto i : D) cout << i << " ";
    //cout << "\n";
    return D;
}

void dfs(int x, vector<vector<pl>>& E, vector<bool>& chk) {
    if(chk[x]) return;
    chk[x] = true;
    for(auto i : E[x]) dfs(i.fi, E, chk);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<vector<pl>> E(n);
    for(int i = 0; i < m; i++) {
        int u, v, a, b; cin >> u >> v >> a >> b; --u, --v;
        E[u].push_back({v, a+b});
        E[v].push_back({u, a+b});
    }
    ll t; cin >> t; t *= 2LL;
    vector<bool> chk(n, false);
    dfs(0, E, chk);
    bool mi = false;
    for(int i = 0; i < n; i++) {
        if(!chk[i]) continue;
        for(auto j : E[i]) if(j.se < 0) mi = true;
    }
    vector<int> T;
    if(mi) {
        for(int i = 1; i < n; i++)
            if(chk[i]) T.push_back(i);
    } else {
        vector<ll> D = dijk(E);
        for(int i = 1; i < n; i++)
            if(D[i] <= t) T.push_back(i);
    }
    cout << T.size() << "\n";
    for(auto i : T) cout << i+1 << " ";
    cout << "\n";
    return 0;
}