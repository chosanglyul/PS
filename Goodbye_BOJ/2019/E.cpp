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
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto &i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }

ll solve(int n, vector<pl>& A, vector<pl>& B) {
    ll ans = -LLINF, su = 0LL, mis = 0LL;
    for(int i = 0; i < n; i++) {
        su += B[i].fi - A[i].fi;
        if(B[i].se - A[i].se) {
            ans = max(ans, su - mis);
            mis = min(mis, su);
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m = 0; cin >> n;
    for(int i = 1; i <= n; m++) i <<= 1;
    vector<vector<pl>> A(m+1, vector<pl>(n, {0, 0}));
    for(int i = 1, j = 1, k = n>>1;
        i <= m; i++, j <<= 1, k >>= 1) {
        for(int t = k; t < n; t += 2*(k+1)) {
            cin >> A[i][t].fi;
            A[i][t].se++;
        }
        for(int j = 0; j < A[0].size(); j++) {
            A[i][j].fi += A[i-1][j].fi;
            A[i][j].se += A[i-1][j].se;
        }
    }
    ll ans = -LLINF;
    for(int i = 0; i < m; i++)
        for(int j = i+1; j <= m; j++)
            ans = max(ans, solve(n, A[i], A[j]));
    cout << ans << "\n";
    return 0;
}