#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<pi, pi> pii;
#define fi first
#define se second
const int INF = 1e9+1;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto &i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }

int su(pi a) { return a.fi+a.se; }

bool cmp(pii a, pii b) {
    if(su(a.se) == su(b.se)) return a.fi.se < b.fi.se;
    else return su(a.se) < su(b.se);
}

int dfs(int x, vector<vector<int>>& G, vector<int>& H, vector<bool>& vis) {
    if(vis[x]) return H[x];
    vis[x] = true;
    int cnt = 1;
    for(auto &i : G[x]) cnt += dfs(i, G, H, vis);
    return H[x] = cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<pii> A(n);
    vector<int> B(n, INF), C(n), D(n, -1), E(n), F(n), H(n);
    vector<vector<int>> G(n);
    vector<bool> vis(n, false);
    for(int i = 0; i < n; i++) {
        char c; cin >> c;
        if(c == 'E') A[i].fi.fi = 0;
        else A[i].fi.fi = 1;
        A[i].fi.se = i;
        cin >> A[i].se.fi >> A[i].se.se;
    }
    sort(A.begin(), A.end(), cmp);

    for(int i = n-1; i >= 0; i--) {
        for(int j = i+1; j < n; j++) {
            if(su(A[i].se) == su(A[j].se)) continue;
            pi tar = {-1, -1};
            if(A[i].fi.fi) tar = {A[i].se.fi, A[j].se.se};
            else tar = {A[j].se.fi, A[i].se.se};
            if(A[j].fi.fi) {
                if(tar.fi != A[j].se.fi) continue;
                if(tar.se > A[j].se.se+B[j] || tar.se < A[j].se.se) continue;
            } else {
                if(tar.se != A[j].se.se) continue;
                if(tar.fi > A[j].se.fi+B[j] || tar.fi < A[j].se.fi) continue;
            }
            if(A[i].fi.fi) {
                if(B[i] > tar.se-A[i].se.se)  {
                    B[i] = tar.se-A[i].se.se;
                    D[i] = j;
                }
            } else {
                if(B[i] > tar.fi-A[i].se.fi) {
                    B[i] = tar.fi-A[i].se.fi;
                    D[i] = j;
                }
            }
            if(B[i] <= 0) exit(1);
        }
    }
    for(int i = 0; i < n; i++) C[A[i].fi.se] = i;
    for(int i = 0; i < n; i++) {
        E[i] = B[C[i]];
        F[i] = D[C[i]];
        if(F[i] >= 0) G[A[F[i]].fi.se].push_back(i);
        //F[i] = A[F[i]].fi.se;
    }
    for(int i = 0; i < n; i++) {
        if(!vis[i]) dfs(i, G, H, vis);
    }
    for(auto i : H) cout << i-1 << "\n";
    return 0;
}