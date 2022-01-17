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

int bin(ll x, ll t, vector<ll>& C) {
    int l = 0, r = C.size();
    while(l+1 < r) {
        int mi = l+r>>1;
        ll tmp = (t/C[mi])*C[mi]-mi;
        //cout << l << " " << r << " " << tmp << " " << mi << "\n";
        if(tmp > x) l = mi;
        else r = mi;
    }
    ll tmp = (t/C[l])*C[l]-l;
    if(tmp <= x) --l;
    return l;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q; cin >> n >> q;
    vector<ll> A(n);
    for(auto &i : A) cin >> i;
    vector<pll> B(q);
    for(auto &i : B) cin >> i.fi >> i.se.fi >> i.se.se;
    vector<ll> C(n+1);
    C[0] = 1LL;
    for(int i = 1; i <= n; i++) {
        ll tmp = A[i-1]/C[i-1];
        if(A[i-1]%C[i-1]) tmp++;
        C[i] = tmp*C[i-1];
    }
    for(auto i : B) {
        int l = bin(i.se.fi-1LL, i.fi, C);
        int r = bin(i.se.se, i.fi, C);
        //cout << l << " " << r << "\n";
        cout << l-r << "\n";
    }
    return 0;
}