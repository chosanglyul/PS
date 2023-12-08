#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define fi first
#define se second

const int INF = (int)1e9+5;
const ll LLINF = (ll)1e18+5;

const int MAX_N = 21 * 360 + 1;

vector<int> adj[MAX_N];
vector<int> adj2[MAX_N];
vector<int> adj3[MAX_N];

void solve() {
    for (int i=0; i<MAX_N; ++i) {
        adj2[i].clear();
        adj3[i].clear();
    }

    for (int r=0; r<20; ++r) {
        for (int t=0; t<360; ++t) {
            int a = 360 * r + t;
            int b = 360 * (r+1) + t;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
    }
    for (int r=0; r<=20; ++r) {
        for (int t=0; t<360; ++t) {
            int a = 360 * r + t;
            int b = 360 * r + (t == 359 ? 0 : t+1);
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
    }

    int n;
    cin >> n;
    for (int i=0; i<n; ++i) {
        char ch;
        cin >> ch;
        if (ch == 'C') {
            int r, t1, t2;
            cin >> r >> t1 >> t2;
            if (t1 > t2) t2 += 360;
            for (int t=t1; t<t2; ++t) {
                int tt = t % 360;
                int a = 360 * (r-1) + tt;
                int b = 360 * r + tt;
                adj2[a].push_back(b);
                adj2[b].push_back(a);
            }
        } else {
            int r1, r2, t;
            cin >> r1 >> r2 >> t;
            int pt = (t == 0 ? 359 : t-1);
            for (int r=r1; r<r2; ++r) {
                int a = 360 * r + pt;
                int b = 360 * r + t;
                adj2[a].push_back(b);
                adj2[b].push_back(a);
            }
        }
    }

    for (int i=0; i<MAX_N; ++i) {
        for (int j: adj[i]) {
            if (find(adj2[i].begin(), adj2[i].end(), j) == adj2[i].end()) {
                adj3[i].push_back(j);
            }
        }
    }

    queue<int> q;
    vector<int> visited(MAX_N, 0);
    for (int i=0; i<360; ++i) {
        q.push(i);
        visited[i] = 1;
    }
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int y: adj3[x]) {
            if (!visited[y]) {
                q.push(y);
                visited[y] = 1;
            }
        }
    }

    for (int i=0; i<360; ++i) {
        int a = 360 * 20 + i;
        if (visited[a]) {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int cases;
    cin >> cases;
    while (cases--) solve();

    return 0;
}