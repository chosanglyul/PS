#include <bits/stdc++.h>
using namespace std;
typedef double ll;
typedef pair<int, ll> pil;
typedef pair<pil, ll> piil;
#define fi first
#define se second
const ll eps = 1e-7;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto &i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }
ll myabs(ll t) { return (t < 0 ? -t : t); }

vector<vector<int>> VV;
vector<vector<piil>> EE;
vector<ll> X;

bool solve(int idx, vector<ll>& B, vector<ll>& C) {
    vector<piil> A = EE[idx];
    bool chk = false, can = true; ll x = 0.0;
    for(auto &i : A) {
        ll bmp = B[i.fi.fi]+B[i.fi.se];
        ll cmp = C[i.fi.fi]+C[i.fi.se];
        if(myabs(bmp) > eps) {
            ll y = (i.se-cmp)/bmp;
            if(!chk) { x = y; chk = true; }
            else if(myabs(x - y) > eps) can = false;
        } else if(myabs(cmp - i.se) > eps) can = false;
    }
    if(!chk) {
        vector<ll> D;
        for(auto i : VV[idx]) D.push_back(-B[i]*C[i]);
        sort(D.begin(), D.end());
        x = D[D.size()>>1];
    }
    X.push_back(x);
    return can;
}

void dfs(int x, ll b, ll c, vector<bool>& vis, vector<int>& V, 
        vector<vector<pil>>& E, vector<ll>& B, vector<ll>& C) {
    if(vis[x]) return;
    VV.back().push_back(x);
    V[x] = EE.size()-1;
    vis[x] = true; B[x] = b, C[x] = c;
    for(auto &i : E[x]) {
        EE.back().push_back({{x, i.fi}, i.se});
        dfs(i.fi, -b, i.se-c, vis, V, E, B, C);
    }
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m; cin >> n >> m;
    vector<piil> A(m);
    vector<vector<pil>> E(n);
    vector<int> V(n);
    for(auto &i : A) {
        cin >> i.fi.fi >> i.fi.se >> i.se;
        --i.fi.fi, --i.fi.se;
        E[i.fi.fi].emplace_back(i.fi.se, i.se);
        E[i.fi.se].emplace_back(i.fi.fi, i.se);
    }
    vector<ll> B(n), C(n);
    vector<bool> vis(n, false);
    for(int i = 0; i < n; i++) {
        if(vis[i]) continue;
        EE.push_back(vector<piil>());
        VV.push_back(vector<int>());
        dfs(i, 1.0, 0.0, vis, V, E, B, C);
    }
    bool can = true;
    for(int i = 0; i < EE.size(); i++)
        can = (can && solve(i, B, C));
    if(can) {
        cout << "YES\n";
        for(int i = 0; i < n; i++)
            cout << B[i]*X[V[i]]+C[i] << " ";
        cout << "\n";
    } else cout << "NO\n";
	return 0;
}
