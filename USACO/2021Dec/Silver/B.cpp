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
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rnd(x, y) uniform_int_distribution<int>(x, y)(rng)

void dfs(int x, int y, vector<vector<int>>& E, vector<bool>& chk, vector<int>& A, vector<int>& B) {
    if(chk[x]) return;
    chk[x] = true; A.push_back(x); B[x] = y;
    for(auto i : E[x]) dfs(i, y, E, chk, A, B);
}

vector<ll> getD(int n, vector<int>& A, vector<int>& B) {
    vector<ll> ans(n, LLINF);
    for(int i = 0, j = -1; i < B.size(); i++) {
        if(j+1 < A.size() && A[j+1] == i) j++;
        if(j == -1) ans[B[i]] = min(ans[B[i]], (ll)(A.front()-i));
        else if(j+1 < A.size()) ans[B[i]] = min(ans[B[i]], (ll)min(A[j+1]-i, i-A[j]));
        else ans[B[i]] = min(ans[B[i]], (ll)(i-A.back()));
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n, m; cin >> n >> m;
        vector<vector<int>> E(n), A;
        for(int i = 0; i < m; i++) {
            int x, y; cin >> x >> y; --x, --y;
            E[x].push_back(y);
            E[y].push_back(x);
        }
        vector<bool> chk(n, false);
        vector<int> B(n);
        for(int i = 0; i < n; i++) {
            if(chk[i]) continue;
            vector<int> T;
            dfs(i, A.size(), E, chk, T, B);
            sort(T.begin(), T.end());
            A.push_back(T);
        }
        if(B[n-1] == 0) {
            cout << 0 << "\n";
            continue;
        }
        vector<ll> C = getD(A.size(), A[0], B);
        vector<ll> D = getD(A.size(), A[B[n-1]], B);
        ll a = C[B[n-1]]/2; ll b = C[B[n-1]]-a; ll ans = a*a+b*b;
        for(int i = 0; i < A.size(); i++) ans = min(ans, C[i]*C[i]+D[i]*D[i]);
        cout << ans << "\n";
    }
    return 0;
}