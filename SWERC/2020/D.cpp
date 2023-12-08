#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, int> pli;
typedef pair<int, int> pii;
#define fi first
#define se second
const int INF = (int)1e9+5;
const ll LLINF = (ll)1e18+5;

vector<int> dijk(vector<vector<pii>> &E) {
    vector<int> D(E.size(), INF); D[0] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> Q;
    Q.push({0, 0});

    while(Q.size()) {
        pii tmp = Q.top(); Q.pop();
        if(tmp.fi > D[tmp.se]) continue;
        for(auto &nxt : E[tmp.se]) {
            if(nxt.fi+tmp.fi >= D[nxt.se]) continue;
            D[nxt.se] = nxt.fi+tmp.fi;
            Q.push({nxt.fi+tmp.fi, nxt.se});
        }
    }

    return D;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, l, r; cin >> n >> m >> l >> r;
    vector<vector<pii>> E(n);
    for(int i = 0; i < m; i++) {
        int x, y, c; cin >> x >> y >> c;
        E[x].push_back({c, y});
        E[y].push_back({c, x});
    }
    vector<int> D = dijk(E);
    vector<pii> ans;
    for(int i = 0; i < n; i++)
        if(D[i]*2 < r)
            for(auto &nxt : E[i])
                ans.push_back({i, nxt.se});
    for(auto &i : ans)
        if(i.fi > i.se)
            swap(i.fi, i.se);
    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());
    cout << ans.size() << "\n";
    return 0;
}