#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = 1e9+5;
const int P = 1000000007;
const ll LLINF = (ll)1e18+5;

struct DisjointSet {
    int n;
    vector<int> parent;
    vector<int> rank;
    DisjointSet(int n) : n(n) {
        parent.resize(n);
        for (int i=0; i<n; ++i) {
            parent[i] = i;
        }
        rank.resize(n, 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return find(parent[x]);
    }

    void merge(int u, int v) {
        if (find(u) == find(v)) return;
        u = find(u);
        v = find(v);
        if (rank[u] > rank[v]) swap(u, v);
        parent[u] = v;
        if (rank[u] == rank[v]) rank[v]++;
    }
};

vector<int> comps[200001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> nums(n);
    vector<int> ds;
    for (int i=0; i<n; ++i) {
        int m;
        cin >> m;
        for (int j=0; j<m; ++j) {
            int x;
            cin >> x;
            nums[i].push_back(x);
            ds.push_back(x);
        }
    }
    sort(ds.begin(), ds.end());
    ds.erase(unique(ds.begin(), ds.end()), ds.end());

    for (int i=0; i<n; ++i) {
        for (int x: nums[i]) {
            int newx = lower_bound(ds.begin(), ds.end(), x) - ds.begin();
            comps[newx].push_back(i);
        }
    }

    DisjointSet dsu(n);
    vector<tuple<int, int, int>> ans;
    for (int i=0; i<200001; ++i) {
        for (int j=0; j+1<comps[i].size(); ++j) {
            if (dsu.find(comps[i][j]) != dsu.find(comps[i][j+1])) {
                dsu.merge(comps[i][j], comps[i][j+1]);
                ans.push_back({comps[i][j], comps[i][j+1], ds[i]});
                // cout << comps[i][j] << ' ' << comps[i][j+1] << ' ' << ds[i] << '\n';
            }
        }
    }
    if (ans.size() != n-1) {
        cout << "impossible";
    } else {
        for (int i=0; i<ans.size(); ++i) {
            cout << get<0>(ans[i])+1 << ' ' << get<1>(ans[i])+1 << ' ' << get<2>(ans[i]) << '\n';
        }
    }

    return 0;
}