#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, int> pli;
#define fi first
#define se second
const ll LLINF = (ll)1e18+5;

vector<ll> dijk(vector<vector<pli>> &E) {
    vector<ll> D(E.size(), LLINF);
    priority_queue<pli, vector<pli>, greater<pli>> PQ;
    PQ.push({0LL, 0}); D[0] = 0LL;
    PQ.push({0LL, (int)E.size()/2}); D[(int)E.size()/2] = 0LL;
    while(PQ.size()) {
        auto [c, hre] = PQ.top(); PQ.pop();
        if(c > D[hre]) continue;
        for(auto &[w, nxt] : E[hre]) {
            if(c+w >= D[nxt]) continue;
            D[nxt] = c+w;
            PQ.push({c+w, nxt});
        }
    }
    return D;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k; cin >> n >> m >> k;
    vector<vector<pli>> EE(n);
    for(int i = 0; i < m; i++) {
        int x, y, z; cin >> x >> y >> z; --x, --y;
        EE[x].push_back({z, y});
    }
    vector<vector<pli>> E(2*n);
    vector<vector<int>> P(k);
    vector<bool> F(n, false), B(n, false);
    vector<int> PN(n, -1);
    for(auto &T : P) {
        int l; cin >> l;
        T.resize(l);
        for(auto &i : T) { cin >> i; --i; }
        F[T.front()] = true;
        B[T.back()] = true;
        for(int i = 1; i < l; i++)
            PN[T[i-1]] = T[i];
    }
    for(int i = 0; i < n; i++) {
        for(auto [w, j] : EE[i]) {
            if(PN[i] == j) {
                if(F[i] && B[j]) {
                    continue;
                } else if(F[i]) {
                    E[i].push_back({w, j+n});
                    E[i+n].push_back({w, j+n});
                } else if(B[j]) {
                    E[i].push_back({w, j});
                    E[i].push_back({w, j+n});
                } else {
                    E[i].push_back({w, j});
                    E[i].push_back({w, j+n});
                    E[i+n].push_back({w, j+n});
                }
            } else {
                E[i].push_back({w, j});
                E[i].push_back({w, j+n});
                E[i+n].push_back({w, j});
                E[i+n].push_back({w, j+n});
            }
        }
    }

    vector<ll> D = dijk(E);
    for(int i = 0; i < n; i++) {
        ll tmp = min(D[i], D[i+n]);
        if(tmp >= LLINF) cout << -1 << " ";
        else cout << tmp << " ";
    }
    cout << "\n";
    return 0;
}
