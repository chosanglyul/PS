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

int g(int i, int j, vector<ll>& B, vector<ll>& C) {
    if(!j) return 0;
    i = i+(--j);
    ll tmp = B[i];
    tmp = (((B[i]*C[j])%P)*C[i-j])%P;
    return (int)tmp;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> A(n+1);
    for(auto &i : A) cin >> i;
    A.push_back(0);
    vector<ll> B(1, 1LL), C;
    /*
    for(ll i = 1LL; i < B.size(); i++) {
        B[i] = (B[i-1]*i)%P;
        C[i] = (C[i-1]*inv(i, P))%P;
    }
    */
    for(ll i = 1LL; i < 1010101; i++) B.push_back((B.back()*i)%P);
    C.push_back(inv(B.back(), P));
    for(ll i = (ll)B.size()-1; i > 0; i--) C.push_back((C.back()*i)%P);
    reverse(C.begin(), C.end());
    int ans = 0;
    for(int i = 1; i < A.size(); i++) {
        for(int j = A[i-1]; j > A[i]; j--) ans = (ans+g(i-1, j, B, C))%P;
        ans = (ans+g(i, A[i], B, C))%P;
    }
    cout << ans << "\n";
    return 0;
}