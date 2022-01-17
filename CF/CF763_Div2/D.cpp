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

vector<ll> calc(int n, int b, int d) {
    vector<ll> A;
    if(d >= b) A.push_back(d-b);
    else A.push_back(n-b+n+d);
    A.push_back(n-b+n-d);
    return A;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    ll in = inv(100, P);
    while(t--) {
        ll n, m, rb, cb, rd, cd, p;
        cin >> n >> m >> rb >> cb >> rd >> cd >> p;
        vector<ll> A = calc(n, rb, rd), B = calc(m, cb, cd), C;
        for(ll i = 0; i < m; i++) for(auto j : A) C.push_back(j+2*(n-1)*i);
        for(ll i = 0; i < n; i++) for(auto j : B) C.push_back(j+2*(m-1)*i);
        for(auto &i : C) i = i%(2*(m-1)*(n-1));
        sort(C.begin(), C.end());
        C.erase(unique(C.begin(), C.end()), C.end());
        vector<ll> V(C.size()+1, 1LL);
        for(int i = 0; i < C.size(); i++) V[i+1] = mod(V[i]*in*(100-p), P);
        ll ans = 0LL;
        for(int i = 0; i < C.size(); i++) {
            ll t = mod(V[i]*C[i], P);
            ans = mod(ans+t*mod(p*in, P), P);
        }
        ll inq = inv(1-V.back(), P);
        inq = mod(inq*inq, P);
        ll b = mod(inq*V.back(), P);
        b = mod(b*2*(m-1)*(n-1), P);
        cout << mod(ans+b, P) << "\n";
    }
    return 0;
}