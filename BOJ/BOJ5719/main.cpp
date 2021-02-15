#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second
const int INF = 1e9;
const ll LLINF = 1e18;

int dist[2][505];

void bfs(int d, vector<vector<bool>>& chk, vector<vector<pi>>& I) {
    vector<bool> visit(I.size(), false);
    queue<int> Q;
    Q.push(d);
    while(Q.size()) {
        int x = Q.front();
        Q.pop();
        for(auto &y : I[x]) {
            if(dist[0][x] == y.se+dist[0][y.fi]) {
                chk[y.fi][x] = true;
                if(!visit[y.fi]) {
                    visit[y.fi] = true;
                    Q.push(y.fi);
                }
            }
        }
    }
}

void djik(int i, int idx, vector<vector<pi>>& V, vector<vector<bool>>& chk) {
    priority_queue<pi, vector<pi>, greater<pi>> Q;
    Q.push({0, i});
    while(Q.size()) {
        pi tmp = Q.top(); Q.pop();
        if(dist[idx][tmp.se] < tmp.fi) continue;
        dist[idx][tmp.se] = tmp.fi;
        for(auto &j : V[tmp.se]) {
            if(chk[tmp.se][j.fi]) continue;
            if(dist[idx][j.fi] > tmp.fi+j.se) {
                Q.push({tmp.fi+j.se, j.fi});
                dist[idx][j.fi] = tmp.fi+j.se;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    while(1) {
        int n, m, s, d;
        cin >> n >> m;
        if(n == 0 && m == 0) break;
        cin >> s >> d;
        vector<vector<pi>> V(n, vector<pi>()), I(n, vector<pi>());
        vector<vector<bool>> chk(n, vector<bool>(n, false));
        for(int i = 0; i < n; i++) dist[0][i] = dist[1][i] = INF;
        for(int i = 0; i < m; i++) {
            int x, y, z;
            cin >> x >> y >> z;
            I[y].push_back({x, z});
            V[x].push_back({y, z});
        }
        djik(s, 0, V, chk);
        bfs(d, chk, I);
        djik(s, 1, V, chk);
        if(dist[1][d] == INF) cout << "-1\n";
        else cout << dist[1][d] << "\n";
    }
    return 0;
}
