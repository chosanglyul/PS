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
    ll mm = 404050LL;
    vector<ll> A(mm), B(mm);
    A[0] = 1LL;
    for(ll i = 1LL; i < mm; i++) A[i] = (A[i-1]*i)%P;
    B[mm-1] = inv(A.back(), P);
    for(ll i = mm-1LL; i > 0LL; i--) B[i-1] = (B[i]*i)%P;
    ll m = 202020LL;
    vector<ll> C(m);
    for(ll i = 0LL; i < m; i++) C[i] = (((A[2LL*i]*B[i])%P*B[i])%P*inv(i+1LL, P))%P;

    string s; cin >> s;
    ll ans = 1LL; char c = '?';
    vector<int> D;
    for(int i = 0, j = 0; i < s.size(); i++) {
        if(s[i] == '?') {
            if(c == '?') D.push_back(0);
            D[(int)D.size()-1]++;
            c = '?';
        } else if(s[i] == ':') {
            if(c == ':') {
                ans = (ans*C[D.back()])%P;
                D.pop_back();
            }
            c = ':';
        }
    }
    if(D.size() != 1) return 1;
    for(auto i : D) ans = (ans*C[i])%P;
    cout << ans << "\n";
    return 0;
}