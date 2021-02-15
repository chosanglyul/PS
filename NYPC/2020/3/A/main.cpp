#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second

pi A[18][1<<18];
pii C[18][1<<18];
vector<vector<bool>> B, E;

void inttov(int n, vector<bool>& D) {
    for(int i = 1; i <= D.size(); i++) {
        D[D.size()-i] = n & 1;
        n >>= 1;
    }
}

int vtoint(vector<bool>& D) {
    int ans = 0;
    for(int i = 0; i < D.size(); i++) {
        ans <<= 1;
        if(D[i]) ans |= 1;
    }
    return ans;
}

void solve(int n) {
    vector<bool> D(n);
    for(int i = 0; i < n; i++) {
        int on = vtoint(B[i]);
        for(int j = 0; j < (1<<n); j++) {
            if(on & j) continue;
            inttov(j, D);
            bool nope = false;
            for(int k = 1; k < n; k++)
                if(D[k] && D[k-1]) nope = true;
            if(nope) continue;
            if(i) A[i][j] = C[i-1][vtoint(E[j])].se;
            for(auto k : D) if(k) A[i][j].fi++;
        }
        for(int j = 0; j < (1<<n); j++) {
            C[i][j].se = A[i][j];
            C[i][j].fi = j;
            swap(C[i][j].fi, C[i][j].se.se);
            for(int k = 0, x = 1; k < n; k++, x <<= 1) {
                if(!(j & x)) continue;
                int tmp = j^x;
                if(C[i][j].se.fi < C[i][tmp].se.fi)
                    C[i][j] = C[i][tmp];
            }
        }
    }
}

void btr(int x, int y, vector<pi>& D, int n) {
    if(x) btr(x-1, C[x][y].fi, D, n);
    vector<bool> F(n);
    inttov(C[x][y].se.se, F);
    for(int i = 0; i < n; i++) {
        if(F[i]) D.push_back({x+1, i+1});
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, k; cin >> n >> k;
    B.resize(n);
    for(int i = 0; i < n; i++) B[i].resize(n);
    for(int i = 0; i < k; i++) {
        int x, y; cin >> x >> y;
        B[--x][--y] = true;
    }
    E.resize(1<<n);
    for(int i = 0; i < (1<<n); i++) {
        E[i].resize(n);
        vector<bool> D(n);
        inttov(i, D);
        for(int j = 0; j < n; j++) E[i][j] = true;
        for(int j = 0; j < n; j++) {
            E[i][j] = E[i][j] && ((j==0) || (!D[j-1]));
            E[i][j] = E[i][j] && ((j==n-1) || (!D[j+1]));
            E[i][j] = E[i][j] && (!D[j]);
        }
    }
    solve(n);
    pi ma = {A[n-1][0].fi, 0};
    for(int i = 1; i < (1<<n); i++)
        if(ma.fi < A[n-1][i].fi)
            ma = {A[n-1][i].fi, i};
    cout << ma.fi << "\n";
    vector<pi> D;
    btr(n-1, ma.se, D, n);
    for(auto &i : D) cout << i.fi << " " << i.se << "\n";
    return 0;
}