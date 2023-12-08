#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 2e5 + 1;
vector<int> adj[MAX_N];
vector<int> tadj[MAX_N];
int sz[MAX_N];
bool visited[MAX_N];

int div_sz[2];
array<vector<int>, 2> divs;
array<vector<int>, 2> divs_cpy;
vector<int> mom_path;

void dfs1(int here) {
    visited[here] = true;
    for (int there: adj[here]) {
        if (!visited[there]) {
            // cout << here << ' ' << there << endl;
            tadj[here].push_back(there);
            dfs1(there);
        }
    }
}

int dfs2(int here) {
    int ret = 1;
    for (int there: tadj[here]) {
        ret += dfs2(there);
    }
    sz[here] = ret;
    return ret;
}

void dfs3(int here) {
    mom_path.push_back(here);
    if (tadj[here].size() == 1) {
        if (abs(div_sz[0]-div_sz[1]) == sz[here]-1) {
            divs[(div_sz[0] > div_sz[1] ? 1 : 0)].push_back(tadj[here][0]);
            return;
        } else {
            dfs3(tadj[here][0]);
        }
    } else if (tadj[here].size() >= 2) {
        vector<pair<int, int>> subtrees;
        for (int there: tadj[here]) {
            subtrees.push_back({ sz[there], there });
        }
        sort(subtrees.begin(), subtrees.end());
        int nxt = subtrees.back().second;
        subtrees.pop_back();
        while (!subtrees.empty()) {
            auto[sub_sz, chd] = subtrees.back();
            subtrees.pop_back();
            if (div_sz[0] > div_sz[1]) {
                div_sz[1] += sub_sz;
                divs[1].push_back(chd);
            } else {
                div_sz[0] += sub_sz;
                divs[0].push_back(chd);
            }
        }
        if (abs(div_sz[0]-div_sz[1]) == sz[nxt]) {
        // if (sz[nxt] == 1 && abs(div_sz[0]-div_sz[1]) == 1) {
            divs[(div_sz[0] > div_sz[1] ? 1 : 0)].push_back(nxt);
            return;
        } else {
            dfs3(nxt);
        }
    }
}

void dfs4(int here, int div) {
    divs_cpy[div].push_back(here);
    for (int there: tadj[here]) dfs4(there, div);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    for (int i=0; i<m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs1(1);
    dfs2(1);
    dfs3(1);

    cout << mom_path.size() << ' ' << (n - mom_path.size()) / 2 << '\n';
    for (int x: mom_path) cout << x << ' ';
    cout << '\n';
    for (int x: divs[0]) dfs4(x, 0);
    for (int x: divs[1]) dfs4(x, 1);
    for (int x: divs_cpy[0]) cout << x << ' ';
    cout << '\n';
    for (int x: divs_cpy[1]) cout << x << ' ';
    cout << '\n';

    return 0;
}