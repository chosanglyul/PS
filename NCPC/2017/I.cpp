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

const int MAX_N = 500 + 1;

int adj[MAX_N][MAX_N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<string> files(n);
    for (string& s: files) cin >> s;
    map<string, int> mp;
    for (string s: files) mp[s] = mp.size();

    for (int i=0; i<n; ++i) {
        for (int j=0; j<n; ++j) {
            adj[i][j] = INF;
        }
    }
    vector<pii> edges;
    for (int i=0; i<n; ++i) {
        string s;
        int k;
        cin >> s >> k;
        int here = mp[s];
        cin.ignore();
        for (int j=0; j<k; ++j) {
            string line;
            getline(cin, line);
            // cout << line << endl;
            line = line.substr(7);

            int pos = 0;
            while (pos < line.size()) {
                int idx = find(line.begin() + pos, line.end(), ',') - line.begin();
                string file = line.substr(pos, idx-pos);
                if (here == mp[file]) {
                    cout << files[here];
                    return 0;
                }
                adj[here][mp[file]] = 1;
                edges.push_back({ here, mp[file] });
                pos = idx+2;
            }
        }
    }

    for (int k=0; k<n; ++k) {
        for (int i=0; i<n; ++i) {
            for (int j=0; j<n; ++j) {
                if (adj[i][j] > adj[i][k] + adj[k][j]) {
                    adj[i][j] = adj[i][k] + adj[k][j];
                }
            }
        }
    }

    int min_dist = INF;
    for (int i=0; i<edges.size(); ++i) {
        min_dist = min(min_dist, adj[edges[i].second][edges[i].first]);
    }
    if (min_dist == INF) {
        cout << "SHIP IT";
        return 0;
    }
    int x, y;
    for (int i=0; i<edges.size(); ++i) {
        if (adj[edges[i].second][edges[i].first] == min_dist) {
            x = edges[i].first;
            y = edges[i].second;
            break;
        }
    }

    // path y to x
    vector<vector<int>> gadj(n);
    for (int i=0; i<edges.size(); ++i) {
        gadj[edges[i].first].push_back(edges[i].second);
    }
    queue<int> q;
    vector<bool> visited(n, false);
    vector<int> from(n, -1);
    q.push(y);
    visited[y] = true;
    while (!q.empty()) {
        int here = q.front();
        q.pop();

        for (int there: gadj[here]) {
            if (!visited[there]) {
                q.push(there);
                visited[there] = true;
                from[there] = here;
            }
        }
    }

    vector<string> path;
    int curr = x;
    while (curr != y) {
        curr = from[curr];
        path.push_back(files[curr]);
    }
    cout << files[x] << ' ';
    while (!path.empty()) {
        cout << path.back() << ' ';
        path.pop_back();
    }

    return 0;
}