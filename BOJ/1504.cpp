#include <bits/stdc++.h>
using namespace std;
const int INF = 5e8+1;
typedef pair<int, int> pi;
#define fi first
#define se second

vector<int> dijk(int s, vector<vector<pi>>& E) {
    vector<int> D(E.size(), INF);
    priority_queue<pi, vector<pi>, greater<pi>> Q;
    Q.push({0, s});
    D[s] = 0;
    while(Q.size()) {
        pi tmp = Q.top();
        Q.pop();
        if(D[tmp.se] < tmp.fi) continue;
        for(auto &i : E[tmp.se]) {
            if(D[i.fi] > D[tmp.se]+i.se) {
                D[i.fi] = D[tmp.se]+i.se;
                Q.push({D[i.fi], i.fi});
            }
        }
    }
    return D;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, e; cin >> n >> e;
    vector<vector<pi>> E(n);
    for(int i = 0; i < e; i++) {
        int a, b, c; cin >> a >> b >> c;
        --a, --b;
        E[a].push_back({b, c});
        E[b].push_back({a, c});
    }
    int u, v; cin >> u >> v;
    vector<int> A = dijk(--u, E);
    vector<int> B = dijk(--v, E);
    int tmp = min(A.front()+B.back(), A.back()+B.front())+A[v];
    if(tmp >= INF) cout << -1 << "\n";
    else cout << tmp << "\n";
    return 0;
}