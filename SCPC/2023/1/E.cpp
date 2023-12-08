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
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }

/* https://github.com/justiceHui/AlgorithmImplement/blob/master/Math/ExtendGCD.cpp */
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

double inter(pl& a, pl& b) { return (double)(a.se-b.se)/(b.fi-a.fi); }

void add(vector<pl> &A, pl x) {
    while(A.size() > 1 && inter(A[A.size()-2], A.back()) > inter(A.back(), x)) A.pop_back();
    A.push_back(x);
}

ll search(vector<pl> &A, ll x) {
    int s = 0, e = A.size();
    while(s+1 < e) {
        int mi = s+e>>1;
        if(inter(A[mi-1], A[mi]) < x) s = mi;
        else e = mi;
    }
    return A[s].fi*x+A[s].se;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t; cin >> t;
    for(int _t = 0; _t < t; _t++) {
        cout << "Case #" << _t+1 << endl;
        int n; cin >> n;
        ll ans = 0LL;
        vector<ll> R(n), D(n);
        for(int i = 0; i < n; i++) cin >> R[i] >> D[i];
        int m; cin >> m;
        vector<ll> P(m), W(m);
        for(auto &i : P) cin >> i;
        for(auto &i : W) cin >> i;
        for(int i = 0; i < n; i++)
            ans += (D[i]-R[i])*P[0];
        vector<pl> A;
        for(int i = 0; i < m; i++) add(A, {P[i], W[i]});
        for(int i = 1; i < n; i++) ans += search(A, R[i]-D[i-1]);
        cout << ans;
        cout << endl;
    }
    return 0;
}
