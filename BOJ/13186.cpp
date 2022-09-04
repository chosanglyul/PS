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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, k; cin >> n >> k;
    ll inv2 = inv(2LL, P);
    vector<ll> A(n+1LL, 1LL);
    for(int i = 1; i < A.size(); i++) A[i] = (A[i-1]*k)%P;
    ll ans = 0LL;
    for(int i = 1; i <= n; i++) {
        if(i&1) ans = (ans+A[i+1>>1])%P;
        else ans = (ans+(A[i+2>>1]+A[i>>1])*inv2)%P;
    }
    vector<ll> S(n+1, 0LL), C(A);
    vector<vector<int>> E(n+1, vector<int>(64));
    for(auto &i : E) i.clear();
    for(int i = 1; i <= n; i++)
        for(int j = i; j <= n; j += i)
            E[j].push_back(i);
    for(int i = 1; i <= n; i++) {
        C[i] = mod(C[i], P);
        for(int j = i; j <= n; j += i)
            if(j != i) C[j] -= C[i];
    }
    for(int i = n; i > 0; i--) {
        ll in = inv(i, P);
        for(auto j : E[i]) {
            S[j] = (S[j]+in)%P;
            ans = (ans+S[j]*C[j])%P;
        }
    }
    cout << (ans*inv2+1LL)%P << "\n";
    return 0;
}