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
const ll P = 1000000007LL;
const ll LLINF = (ll)1e18+1;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto &i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }

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
    vector<ll> A(n);
    for(auto &i : A) cin >> i;
    sort(A.begin(), A.end());
    ll ans = 0LL, tmp = 0LL, inve = inv(2LL, P);
    vector<ll> M(n);
    M[0] = 1LL;
    for(int i = 1; i < n; i++) M[i] = (M[i-1]*2)%P;
    for(int i = 0; i < n; i++) tmp = (tmp+(A[i]*M[i])%P)%P;
    for(int i = 0; i < n; i++) {
        tmp = (mod((tmp-A[i]), P)*inve)%P;
        ans = (ans+mod(tmp-(A[i]*(M[n-i-1]-1LL))%P, P))%P;
    }
    cout << ans << "\n";
    return 0;
}