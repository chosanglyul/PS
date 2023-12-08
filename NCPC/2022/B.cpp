#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX_N = 3e5 + 1;

vector<int> adj[MAX_N];
int depth[MAX_N];

void dfs(int here, int par = 0) {
    depth[here] = depth[par] + 1;
    for (int there: adj[here]) {
        if (there != par) {
            dfs(there, here);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i=0; i<n-1; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int b = 1;
    for (int i=2; i<=n; ++i) {
        if (adj[i].size() > adj[b].size()) b = i;
    }
    if (adj[b].size() == n-1) {
        cout << "NO";
        return 0;
    }
    int c = -1;
    for (int x: adj[b]) {
        if (adj[x].size() >= 2) {
            c = x;
            break;
        }
    }
    // cout << "b: " << b << endl;
    dfs(b);
    // for (int i=1; i<=n; ++i) cout << depth[i] << ' ';
    // cout << endl;

    vector<pair<int, int>> arr(n);
    for (int i=1; i<=n; ++i) arr[i-1] = { depth[i], i };
    sort(arr.begin(), arr.end());
    if (arr[1].second == c) {
        assert(arr[2].second != c);
        swap(arr[1], arr[2]);
    }

    cout << "YES\n";
    cout << b << ' ';
    for (int i=1; i<n; ++i) cout << arr[i].second << ' ';

    return 0;
}