#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 1000000007;
const ll LLINF = (ll)1e18+1;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }

bool dfs(int x, vector<vector<int>>& G, vector<bool>& chk, vector<bool>& fin) {
    if(chk[x]) return !fin[x];
    chk[x] = true, fin[x] = false;
    for(auto i : G[x]) if(dfs(i, G, chk, fin)) return true;
    fin[x] = true;
    return false;
}

vector<int> topo(int n, vector<vector<pi>>& E, vector<vector<int>>& G, vector<int> D) {
    queue<int> Q;
    vector<int> F(3*n, 0);
    for(auto &i : G) for(auto j : i) F[j]++;
    for(int i = 0; i < F.size(); i++) if(!F[i]) Q.push(i);
    while(Q.size()) {
        int hre = Q.front(); Q.pop();
        for(auto nxt : G[hre]) {
            D[nxt] = max(D[nxt], D[hre]+1);
            if(--F[nxt] == 0) Q.push(nxt);
        }
        pi tmp = {hre/n, hre%n};
        for(auto nxtp : E[tmp.se]) {
            int nxt = nxtp.fi + hre - tmp.se;
            D[nxt] = max(D[nxt], D[hre]);
        }
    }
    return D;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    for(int _t = 0; _t < t; _t++) {
        cout << "Case #" << _t+1 << endl;
        int n, m, k; cin >> n >> m >> k;
        vector<vector<pi>> E(n);
        vector<vector<int>> G(3*n);
        for(int i = 0; i < m; i++) {
            int x, y, z; char c;
            cin >> x >> y >> c; z = c-'A';
            E[--x].push_back({--y, z});
            G[n*z+x].push_back(n*((z+1)%3)+y);
        }
        vector<bool> chk(3*n, false), fin(3*n, false);
        bool cycle = false;
        for(int i = 0; i < G.size(); i++) if(dfs(i, G, chk, fin)) cycle = true;
        if(cycle) cout << -1 << endl;
        else {
            if(k == -1) {
                vector<int> F(3*n, 0);
                for(auto &i : G) for(auto j : i) F[j]++;
                vector<int> I = topo(n, E, G, vector<int>(3*n, 0));
                vector<int> J = topo(n, E, G, I);
                bool end = false;
                for(int i = 0; i < 3*n; i++) {
                    if((G[i].size() || F[i]) && (I[i] != J[i]))
                        end = true;
                }
                if(!end) cout << *max_element(J.begin(), J.end()) << endl;
                else cout << -1 << endl;
            } else {
                queue<int> Q;
                vector<vector<int>> D(3*n, vector<int>(k+1, 0));
                for(int tt = 0; tt <= k; tt++) {
                    vector<int> F(3*n, 0);
                    for(auto &i : G) for(auto j : i) F[j]++;
                    for(int i = 0; i < F.size(); i++) if(!F[i]) Q.push(i);
                    while(Q.size()) {
                        int hre = Q.front(); Q.pop();
                        for(auto nxt : G[hre]) {
                            for(int j = 0; j <= k; j++) D[nxt][j] = max(D[nxt][j], D[hre][j]+1);
                            if(--F[nxt] == 0) Q.push(nxt);
                        }
                        pi tmp = {hre/n, hre%n};
                        for(auto nxtp : E[tmp.se]) {
                            int nxt = nxtp.fi + hre - tmp.se;
                            for(int j = 0; j < k; j++) D[nxt][j+1] = max(D[nxt][j+1], D[hre][j]);
                        }
                    }
                }
                int ans = 0;
                for(auto &i : D) for(auto j : i) ans = max(ans, j);
                cout << ans << endl;
            }
        }
    }
    return 0;
}