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

void ad(int x, vector<int>& C, vector<int>& D, int& ans) {
    D[C[x]]--;
    if(C[x] == ans && D[C[x]+1] == 0) ans++;
    D[++C[x]]++;
}

void su(int x, vector<int>& C, vector<int>& D, int& ans) {
    D[C[x]]--;
    if(C[x] == ans && D[C[x]] == 0) ans--;
    D[--C[x]]++;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    int sq = sqrt(n);
    vector<int> A(n);
    for(auto &i : A) cin >> i;
    vector<int> T(A);
    sort(T.begin(), T.end());
    T.erase(unique(T.begin(), T.end()), T.end());
    for(auto &i : A) i = lower_bound(T.begin(), T.end(), i) - T.begin();
    int m; cin >> m;
    vector<pii> B(m);
    for(int i = 0; i < m; i++) {
        B[i].fi = i;
        cin >> B[i].se.fi >> B[i].se.se;
        B[i].se.fi--;
    }
    sort(B.begin(), B.end(), [&](pii a, pii b) {
       pi ta = {a.se.fi/sq, a.se.se}, tb = {b.se.fi/sq, b.se.se};
       if(ta == tb) return a.fi < b.fi;
       return ta < tb;
    });
    int ans = 0, l = B[0].se.fi, r = B[0].se.se;
    vector<int> C(T.size(), 0), D(n+1, 0), E(m);
    D[0] = T.size();
    for(int i = l; i < r; i++) ad(A[i], C, D, ans);
    E[B[0].fi] = ans;
    for(int i = 1; i < B.size(); i++) {
        while(l > B[i].se.fi) ad(A[--l], C, D, ans);
        while(r < B[i].se.se) ad(A[r++], C, D, ans);
        while(l < B[i].se.fi) su(A[l++], C, D, ans);
        while(r > B[i].se.se) su(A[--r], C, D, ans);
        E[B[i].fi] = ans;
    }
    for(auto i : E) cout << i << "\n";
    return 0;
}