#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define fi first
#define se second

const int MAX_N = 50000 + 1;

vector<int> adj[MAX_N];
vector<int> gbadj[MAX_N];
int gb[MAX_N];

void dfs(int here, int par, vector<int>& nodes) {
    nodes.push_back(here);
    for (int there: gbadj[here]) {
        if (there != par) {
            dfs(there, here, nodes);
        }
    }
}

struct perm {
    int a, b;
    perm(int _a, int _b): a(_a), b(_b) {
        a = _a;
        b = _b;
    }

    int pop() {
        if (a == b) return a;
        if (a < b) return a++;
        else return a--;
    }

    void swap() {
        int c = a;
        a = b;
        b = c;
    }
};

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
    for (int i=1; i<=n; ++i) gb[i] = (adj[i].size() != 1);
    for (int i=1; i<=n; ++i) {
        for (int j: adj[i]) {
            if (gb[i] && gb[j]) {
                gbadj[i].push_back(j);
            }
        }
    }

    vector<int> gb_nodes;
    for (int i=1; i<=n; ++i) {
        if (gb[i] && gbadj[i].size() <= 1) { // n=3 exception
            dfs(i, -1, gb_nodes);
            break;
        }
    }
    
    vector<int> ans(n+1, 0);
    perm p(1, n);
    for (int i=0; i<gb_nodes.size(); ++i) {
        int x = gb_nodes[i];
        ans[x] = p.pop();
        p.swap();
        for (int y: adj[x]) {
            if (!gb[y]) {
                ans[y] = p.pop();
            }
        }
    }
    for (int i=1; i<=n; ++i) cout << ans[i] << ' ';

    return 0;
}