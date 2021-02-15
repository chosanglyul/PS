#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<string, int> psi;
#define fi first
#define se second
const int INF = 1e9+1;

typedef struct Node {
    int l, r, cnt;
    vector<pi> E;
    Node(int tl, int tr, int tcnt) { l = tl, r = tr, cnt = tcnt; }
} Node;

vector<vector<Node>> V;
int N, dp[55][55];
bool visit[55][55];

int dfs(int n, int x, int depth) {
    //cout << n << " " << x << endl;
    //depth += V[n][x].cnt;

    if(V[n][x].E.size()) {
        if(visit[n][x]) return dp[n][x];
        visit[n][x] = true;
        int maxd = -INF;
        for(auto &i : V[n][x].E) {
            int tmp = dfs(n+1, i.fi, depth);
            if(tmp > maxd) {
                maxd = tmp;
                swap(V[n][x].E[0], i);
            }
        }
        return dp[n][x] = maxd+V[n][x].cnt;
    } else {
        if(V[n][x].r == N && n == N-1) return V[n][x].cnt;
        else return -INF;
    }
}

string ans;

void answer(int n, pi x) {
    string s;
    cout << n << endl;
    for(int i = 0; i < x.se-V[n][x.fi].l; i++) s += 'L';
    for(int i = 0; i < V[n][x.fi].r-V[n][x.fi].l-1; i++) s += 'R';
    if(n < N-1) {
        for(int i = 0; i < V[n][x.fi].r-V[n][x.fi].E[0].se-1; i++) s += 'L';
        s += 'D';
    }
    ans += s;
    if(n < N-1) answer(n+1, V[n][x.fi].E[0]);
}

int main() {
    cin >> N; V.resize(N);
    for(int i = 0; i < N; i++) {
        int cnt = 0, l = 0;
        for(int j = 0; j < N; j++) {
            char c; cin >> c;
            if(c == 'U') {
                if(l < j) V[i].emplace_back(l, j, cnt);
                cnt = 0;
                l = j+1;
            } else if(c == 'D') cnt++;
        }
        if(l < N) V[i].emplace_back(l, N, cnt);
    }
    cout << "HI" << endl;

    for(int i = 0; i < N-1; i++)
        for(int j = 0; j < V[i].size(); j++)
            for(int k = 0; k < V[i+1].size(); k++)
                if(V[i+1][k].l < V[i][j].r && V[i][j].l < V[i+1][k].r)
                    V[i][j].E.emplace_back(k, max(V[i+1][k].l, V[i][j].l));
    cout << "HI" << endl;

    cout << dfs(0, 0, 0) << endl;
    cout << "HI" << endl;

    answer(0, {0, 0});
    cout << ans << endl;
    return 0;
}