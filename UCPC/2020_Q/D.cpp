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

ll mod(ll a, ll b) { return ((a%b) + b) % b; }
ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    ll g = a; x = 1, y = 0;
    if(b) g = ext_gcd(b, a % b, y, x), y -= a / b * x;
    return g;
}
ll inv(ll a, ll m) { //return x when ax mod m = 1, fail -> -1
    ll x, y; ll g = ext_gcd(a, m, x, y);
    if(g > 1) return -1;
    return mod(x, m);
}

pl dfs(int x, vector<vector<int>>& A, vector<pl>& B, vector<bool>& chk) {
    chk[x] = true;
    pl ans = {0LL, 0LL};
    for(auto i : A[x]) {
        if(chk[i]) continue;
        pl tmp = dfs(i, A, B, chk);
        ans.fi += tmp.fi; ans.se += tmp.se;
        B[x].fi++; B[x].se += B[i].fi;
        ans.fi += B[i].se;
        ans.se += B[i].fi*(B[i].fi-1LL)/2LL;
    }
    ans.fi += B[x].se*(B[x].fi-1LL);
    ans.se += B[x].fi*(B[x].fi-1LL)*(B[x].fi-2LL)/6LL;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<vector<int>> A(n);
    for(int i = 1; i < n; i++) {
        int x, y; cin >> x >> y; --x, --y;
        A[x].push_back(y);
        A[y].push_back(x);
    }
    vector<bool> chk(n, false);
    vector<pl> B(n, {0LL, 0LL});
    pl ans = dfs(0, A, B, chk);
    if(ans.fi > 3*ans.se) cout << "D\n";
    else if(ans.fi < 3*ans.se) cout << "G\n";
    else cout << "DUDUDUNGA\n";
    return 0;
}