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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    int sq = sqrt(n);
    vector<int> A(n);
    for(auto &i : A) cin >> i;
    vector<int> B(A);
    sort(B.begin(), B.end());
    B.erase(unique(B.begin(), B.end()), B.end());
    for(auto &i : A) i = lower_bound(B.begin(), B.end(), i) - B.begin();
    int q; cin >> q;
    vector<pii> Q(q);
    for(int i = 0; i < q; i++) {
        Q[i].fi = i;
        cin >> Q[i].se.fi >> Q[i].se.se;
        Q[i].se.fi--, Q[i].se.se--;
    }
    sort(Q.begin(), Q.end(), [&](pii a, pii b) {
        pi ta = {a.se.fi/sq, a.se.se}, tb = {b.se.fi/sq, b.se.se};
        if(ta == tb) return a.fi < b.fi;
        return ta < tb;
    });
    vector<int> C(B.size(), 0), D(q, -1);
    int s = Q[0].se.fi, e = Q[0].se.se, ans = 0;
    for(int i = s; i <= e; i++) if(C[A[i]]++ == 0) ans++;
    D[Q[0].fi] = ans;
    for(int i = 1; i < q; i++) {
        while(s > Q[i].se.fi) if(C[A[--s]]++ == 0) ans++;
        while(e < Q[i].se.se) if(C[A[++e]]++ == 0) ans++;
        while(s < Q[i].se.fi) if(--C[A[s++]] == 0) ans--;
        while(e > Q[i].se.se) if(--C[A[e--]] == 0) ans--;
        D[Q[i].fi] = ans;
    }
    for(auto i : D) cout << i << "\n";
    return 0;
}