#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, ll> pil;
typedef pair<pil, ll> piil;
#define fi first
#define se second

void dfs(int x, ll b, ll c, vector<bool>& vis,
        vector<vector<pil>>& E, vector<ll>& B, vector<ll>& C) {
    if(vis[x]) return;
    vis[x] = true; B[x] = b, C[x] = c;
    for(auto &i : E[x]) dfs(i.fi, -b, i.se-c, vis, E, B, C);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m; cin >> n >> m;
    vector<piil> A(m);
    vector<vector<pil>> E(n);
    for(auto &i : A) {
        cin >> i.fi.fi >> i.fi.se >> i.se;
        --i.fi.fi, --i.fi.se;
        E[i.fi.fi].emplace_back(i.fi.se, i.se);
        E[i.fi.se].emplace_back(i.fi.fi, i.se);
    }
    vector<ll> B(n), C(n);
    vector<bool> vis(n, false);
    dfs(0, 1LL, 0LL, vis, E, B, C);
    /*
    for(auto i : B) cout << i << " ";
    cout << "\n";
    for(auto i : C) cout << i << " ";
    cout << "\n";
    */
    bool chk = false, can = true; ll x = 0LL;
    for(auto &i : A) {
        ll bmp = B[i.fi.fi]+B[i.fi.se];
        ll cmp = C[i.fi.fi]+C[i.fi.se];
        if(bmp) {
            ll y = i.se-cmp;
            if(y%bmp) can = false;
            else {
                y /= bmp;
                if(!chk) { x = y; chk = true; }
                else if(x != y) can = false;
            }
        } else if(cmp != i.se) can = false;
    }
    if(can) {
        cout << "Yes\n";
        if(!chk) {
            vector<ll> D(n);
            for(int i = 0; i < n; i++) D[i] = -B[i]*C[i];
            sort(D.begin(), D.end());
            x = D[n>>1];
        }
        for(int i = 0; i < n; i++)
            cout << B[i]*x+C[i] << " ";
        cout << "\n";
    } else cout << "No\n";
	return 0;
}
