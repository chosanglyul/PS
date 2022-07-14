#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MAX_V = 1100 + 2;

vector<int> adj[MAX_V];
int capa[MAX_V][MAX_V];
int level[MAX_V];
int cache[MAX_V];

bool bfs(int s, int t) {
    queue<int> q;
    q.push(s);
    fill(level, level+MAX_V, -1);
    level[s] = 0;
    while (!q.empty()) {
        int here = q.front();
        q.pop();
        for (int there: adj[here]) {
            if (level[there] == -1 && capa[here][there] > 0) {
                level[there] = level[here] + 1;
                q.push(there);
            }
        }
    }
    return level[t] != -1;
}

int dfs(int here, int t, int extra_capa) {
    if (here == t) return extra_capa;
    for (int& i=cache[here]; i<adj[here].size(); ++i) {
        int there = adj[here][i];
        if (level[there] == level[here] + 1 && capa[here][there] > 0) {
            int bottleneck = min(extra_capa, capa[here][there]);
            int f = dfs(there, t, bottleneck);
            if (f > 0) {
                capa[here][there] -= f;
                capa[there][here] += f;
                // cout << here << ' ' << there << endl;
                return f;
            }
        }
    }
    return 0;
}

int max_flow(int s, int t) {
    int ret = 0;
    while (bfs(s, t)) {
        fill(cache, cache+MAX_V, 0);
        while (true) {
            int f = dfs(s, t, INF);
            // cout << endl;
            if (f == 0) break;
            ret += f;
        }
    }
    return ret;
}

void add_edge(int u, int v, int c) {
    adj[u].push_back(v);
    adj[v].push_back(u);
    capa[u][v] = c;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<int> group(m, 0);
    vector<vector<int> > cow_attended(n);
    for (int i=0; i<m; ++i) {
        int cnt;
        cin >> cnt;
        group[i] = cnt;
        for (int j=0; j<cnt; ++j) {
            int x;
            cin >> x;
            cow_attended[x-1].push_back(i);
        }
    }

    vector<int> cow_capa(n, 0);
    for (int i=0; i<n; ++i) {
        double tmp = 0.0;
        for (int g: cow_attended[i]) {
            tmp += 1.0 / group[g];
        }
        cow_capa[i] = (int)(ceil(tmp - 0.00000001));
    }
    
    for (int i=0; i<n; ++i) {
        for (int g: cow_attended[i]) {
            add_edge(i, n+g, 1);
        }
    }
    for (int i=0; i<n; ++i) {
        add_edge(n+m, i, cow_capa[i]);
    }
    for (int i=0; i<m; ++i) {
        add_edge(n+i, n+m+1, 1);
    }

    int mf = max_flow(n+m, n+m+1);
    if (mf < m) {
        cout << -1;
        return 0;
    }

    for (int i=0; i<m; ++i) {
        for (int j=0; j<n; ++j) {
            if (capa[j][n+i] == 0 && capa[n+i][j] > 0) {
                cout << j+1 << '\n';
                break;
            }
        }
    }
}