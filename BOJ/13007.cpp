#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 1000000007;
const ll LLINF = (ll)1e18+1;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
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
ll inv(ll a, ll m) {
    ll x, y; ll g = ext_gcd(a, m, x, y);
    if(g > 1) return -1;
    return mod(x, m);
}

class ncr {
    private:
    vector<ll> A, B;

    void init() {
        A[0] = 1LL;
        for(int i = 1; i < A.size(); i++) A[i] = (A[i-1]*i)%P;
        B[B.size()-1] = inv(A[A.size()-1], P);
        for(int i = B.size()-1; i >= 1; i--) B[i-1] = (B[i]*i)%P;
    }

    public:
    ll query(int n, int k) {
        if(n < k) return 0LL;
        return ((A[n]*B[k])%P*B[n-k])%P;
    }

    ncr(int n) {
        A.resize(n), B.resize(n);
        init();
    }
};



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ncr Q(1010101);
    ll ans = 0LL;
    int s, a, b, c; cin >> s >> a >> b >> c;
    for(int i = 0; i <= s; i++) {
        ll tmp = ((s-i)%2 ? -1LL : 1LL) * Q.query(s, i);
        tmp = mod(tmp*Q.query(i, a), P);
        tmp = mod(tmp*Q.query(i, b), P);
        tmp = mod(tmp*Q.query(i, c), P);
        ans = mod(ans+tmp, P);
    }
    cout << ans << "\n";
    return 0;
}