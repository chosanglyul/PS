#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pl;
typedef pair<pl, ll> pll;
#define fi first
#define se second
const ll LLINF = 1e18+1;

vector<ll> djik(int s, int n, vector<vector<pl>>& E) {
    vector<ll> D(n, LLINF);
    priority_queue<pl, vector<pl>, greater<pl>> Q;
    Q.push({0LL, s});
    D[s] = 0LL;
    while(Q.size()) {
        pl tmp = Q.top();
        Q.pop();
        if(tmp.fi > D[tmp.se]) continue;
        for(auto &i : E[tmp.se]) {
            if(D[i.fi] > D[tmp.se]+i.se) {
                D[i.fi] = D[tmp.se]+i.se;
                Q.push({D[i.fi], i.fi});
            }
        }
    }
    return D;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    while(t--) {
        int n, d, c; cin >> n >> d >> c;
        vector<vector<pl>> E(n);
        for(int i = 0; i < d; i++) {
            pll tmp; cin >> tmp.fi.fi >> tmp.fi.se >> tmp.se;
            E[--tmp.fi.se].push_back({--tmp.fi.fi, tmp.se});
        }
        vector<ll> D = djik(--c, n, E);
        ll cnt = 0LL, ma = 0LL;
        for(auto i : D) {
            if(i < LLINF) {
                cnt++;
                ma = max(ma, i);
            }
        }
        cout << cnt << " " << ma << "\n";
    }
    return 0;
}