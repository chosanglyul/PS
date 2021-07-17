#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<pi> d = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    int n;
    for(int pcnt = 1; ; pcnt++) {
        cin >> n;
        if(n == 0) break;
        vector<vector<int>> A(n, vector<int>(n));
        vector<vector<bool>> chk(n, vector<bool>(n, false));
        for(auto &i : A) for(auto &j : i) cin >> j;
        priority_queue<pii, vector<pii>, greater<pii>> Q;
        Q.push({A[0][0], {0, 0}});
        while(Q.size()) {
            pii tmp = Q.top();
            Q.pop();
            if(chk[tmp.se.fi][tmp.se.se]) continue;
            chk[tmp.se.fi][tmp.se.se] = true;
            if(tmp.se.fi == n-1 && tmp.se.se == n-1) {
                cout << "Problem " << pcnt << ": " << tmp.fi << "\n";
                break;
            }
            for(auto &i : d) {
                pi nxt = {tmp.se.fi+i.fi, tmp.se.se+i.se};
                if(nxt.fi < 0 || nxt.fi >= n || nxt.se < 0 || nxt.se >= n || chk[nxt.fi][nxt.se]) continue;
                Q.push({tmp.fi+A[nxt.fi][nxt.se], nxt});
            }
        }
    }
    return 0;
}