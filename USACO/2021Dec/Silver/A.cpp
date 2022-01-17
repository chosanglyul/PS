#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
typedef pair<int, ll> pil;
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int k, m, n; cin >> k >> m >> n;
    vector<pil> A(k);
    for(auto &i : A) cin >> i.fi >> i.se;
    sort(A.begin(), A.end());
    vector<int> B(m);
    for(auto &i : B) cin >> i;
    sort(B.begin(), B.end());
    vector<vector<pil>> C(m+1);
    for(int i = 0, j = 0; i < k; i++) {
        while(j < m && A[i].fi > B[j]) j++;
        C[j].push_back(A[i]);
    }
    vector<ll> D, E(m+1, 0), F(m+1, 0);
    for(int i = 0; i <= m; i++)
        for(auto j : C[i])
            E[i] += j.se;
    F[0] = E[0], F[m] = E[m];
    for(int i = 1; i < m; i++) {
        vector<ll> T(C[i].size()+1, 0);
        for(int j = 1; j < T.size(); j++) T[j] = T[j-1]+C[i][j-1].se;
        int tmp = B[i]-B[i-1];
        tmp = (tmp+1)/2;
        for(int l = 0, r = 0; l < C[i].size(); l++) {
            while(r < C[i].size() && C[i][r].fi-C[i][l].fi < tmp) r++;
            F[i] = max(F[i], T[r]-T[l]);
        }
    }
    for(int i = 0; i <= m; i++) {
        D.push_back(F[i]);
        D.push_back(E[i]-F[i]);
    }
    sort(D.begin(), D.end());
    reverse(D.begin(), D.end());
    ll ans = 0LL;
    for(int i = 0; i < n; i++) ans += D[i];
    cout << ans << "\n";
    return 0;
}