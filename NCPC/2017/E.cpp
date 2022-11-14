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

const int MAX_N = 250000 + 1;

int conn[MAX_N];
int root;

struct DisjointSet {
    int n;
    vector<vector<int>> group;
    vector<int> parent, rank, max_val;
    DisjointSet(int _n) : n(_n) {
        group.resize(n);
        for (int i=0; i<n; ++i) group[i].push_back(i);
        parent.resize(n);
        for (int i=0; i<n; ++i) parent[i] = i;
        rank.resize(n, 0);
        max_val.resize(n, -1234567);
    }

    int find(int x) {
        return parent[x] = (x == parent[x] ? x : find(parent[x]));
    }

    void merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;

        int val = max(max_val[u], max_val[v]);
        if (u == find(root)) swap(u, v);
        if (v == find(root)) {
            for (int x: group[u]) {
                conn[x] = val;
            }
        }

        if (rank[u] > rank[v]) swap(u, v);
        parent[u] = v;
        max_val[v] = val;
        for (int x: group[u]) group[v].push_back(x);
        group[u].clear();
        if (rank[u] == rank[v]) rank[v]++;
    }
};

const pii v[8] = {
    {1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int h, w;
    cin >> h >> w;
    vector<vector<int>> board(h, vector<int>(w));
    vector<tuple<int, int, int>> arr;
    DisjointSet dsu(h*w);
    for (int i=0; i<h; ++i) {
        for (int j=0; j<w; ++j) {
            int x;
            cin >> x;
            board[i][j] = x;
            arr.push_back({ x, i, j });
            dsu.max_val[w*i+j] = x;
        }
    }
    sort(arr.begin(), arr.end());

    int r, c;
    cin >> r >> c;
    r--; c--;
    root = w*r+c;
    conn[root] = board[r][c];

    for (int i=0; i<arr.size(); ++i) {
        int x = get<1>(arr[i]);
        int y = get<2>(arr[i]);
        for (pii dv: v) {
            int dx = x + dv.first;
            int dy = y + dv.second;
            if (0 <= dx && dx < h && 0 <= dy && dy < w && board[dx][dy] <= board[x][y]) {
                dsu.merge(w*dx+dy, w*x+y);
            }
        }
        // if (x == r && y == c) break;
    }

    ll ans = 0;
    for (int i=0; i<h; ++i) {
        for (int j=0; j<w; ++j) {
            //cout << conn[w*i+j] << ' ';
            if (conn[w*i+j] < 0) {
                ans += min(-board[r][c], -conn[w*i+j]);
            }
        }
    }
    //cout << endl;
    cout << ans;

    return 0;
}