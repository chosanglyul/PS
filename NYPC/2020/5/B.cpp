#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pi;
typedef pair<pi, ll> pii;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 1e9+7;
const ll LLINF = 1e18+1;

bool chk1[505050], chk2[505050];
vector<int> V[505050], R[505050], S;
int scc[505050], indeg[505050];

void dfs1(int x) {
    if(chk1[x]) return;
    chk1[x] = true;
    for(auto i : V[x]) dfs1(i);
    S.push_back(x);
}

void dfs2(int x, int cnt) {
    if(chk2[x]) return;
    chk2[x] = true;
    for(auto i : R[x]) dfs2(i, cnt);
    scc[x] = cnt;
}

void mkgraph(vector<pii>& A, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i == j) continue;
            if(A[i].fi.fi == A[j].fi.fi) {
                if(abs(A[i].fi.se-A[j].fi.se) <= A[i].se) {
                    V[i].push_back(j);
                    R[j].push_back(i);
                }
            } else if(A[i].fi.se == A[j].fi.se) {
                if(abs(A[i].fi.fi-A[j].fi.fi) <= A[i].se) {
                    V[i].push_back(j);
                    R[j].push_back(i);
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, cnt = 0; cin >> n;
    string s; cin >> s;
    vector<pii> A(n);
    for(auto &i : A) cin >> i.fi.fi >> i.fi.se >> i.se;
    mkgraph(A, n);
    for(int i = 0; i < n; i++) dfs1(i);
    while(S.size()) {
        int i = S.back();
        S.pop_back();
        if(chk2[i]) continue;
        dfs2(i, cnt++);
    }
    if(s == "max") {
        cout << cnt << endl;
    } else {
        for(int i = 0; i < n; i++)
            for(auto j : V[i])
                if(scc[j] != scc[i]) indeg[scc[j]]++;
        int scnt = 0;
        for(int i = 0; i < cnt; i++)
            if(indeg[i] == 0) scnt++;
        cout << scnt << endl;
    }
    return 0;
}