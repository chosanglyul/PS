#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX_N = 3000 + 1;

vector<int> adj[MAX_N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    for (int i=0; i<m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int ans = 0x3f3f3f3f;
    ll ans_cnt;
    for (int s=1; s<=n; ++s) {
        for (int t: adj[s]) { // iterate every edge
            queue<int> q;
            vector<int> visited(n+1, 0);
            vector<int> dist(n+1, 0x3f3f3f3f);
            vector<ll> pcnt(n+1, 0); // shortest path count
            q.push(s);
            visited[s] = 1;
            dist[s] = 0;
            pcnt[s] = 1;
            while (!q.empty()) {
                int x = q.front();
                q.pop();
                if (x == t) break;
                for (int y: adj[x]) {
                    if (!(x == s && y == t)) {
                        if (!visited[y]) {
                            q.push(y);
                            visited[y] = 1;
                            dist[y] = dist[x] + 1;
                            pcnt[y] += pcnt[x];
                        } else if (dist[y] == dist[x] + 1) {
                            pcnt[y] += pcnt[x];
                        }
                    }
                }
            }
            // cout << s << ' ' << t << ' ' << dist[t] << ' ' << pcnt[t] << endl;
            if (ans > dist[t]) {
                ans = dist[t];
                ans_cnt = pcnt[t];
            } else if (ans == dist[t]) {
                ans_cnt += pcnt[t];
            }
        }
    }
    cout << ans_cnt / (2ll * (ans+1));

    return 0;
}