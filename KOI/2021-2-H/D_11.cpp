#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<pi, int> pii;
#define fi first
#define se second

void dfs(int x, int d, int& y, vector<vector<int>>& E) {
    if(d < 0 || ((1<<x)&y)) return;
    y |= (1<<x);
    for(auto i : E[x]) dfs(i, d-1, y, E);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m; cin >> n >> m;
    vector<vector<int>> E(n);
    for(int i = 0; i < n-1; i++) {
        int x, y; cin >> x >> y; --x, --y;
        E[x].push_back(y); E[y].push_back(x);
    }
    vector<pii> A(m);
    vector<int> B(m, 0);
    for(int i = 0; i < m; i++) {
        cin >> A[i].fi.fi >> A[i].fi.se >> A[i].se;
        dfs(--A[i].fi.fi, A[i].fi.se, B[i], E);
    }
    ll ans = 0LL;
    for(int i = 0; i < (1<<m); i++) {
        int x = 0; ll y = 0LL;
        bool can = true;
        for(int j = 0, k = 1; j < m; j++, k <<= 1) {
            if(k&i) {
                if(x&B[j]) can = false;
                else {
                    x |= B[j];
                    y += A[j].se;
                }
            }
        }
        if(can) ans = max(ans, y);
    }
    cout << ans << "\n";
	return 0;
}
