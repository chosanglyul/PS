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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k, p; cin >> n >> k >> p;
    int x = n, y;
    vector<ll> A = {1LL, 1LL};
    while(A.back() < INF) A.push_back(A.back()*A.size());
    A.pop_back();

    int ans;
    if(n == 2) {
        ans = 2;
    } else if(k == 2) {
        if(n >= A.size()) ans = INF;
        else ans = A[n];
        if(ans >= p) {
            ans = 0;
        } else if(n == 12) {
            ll tmp = 1LL;
            for(int i = p-1; i > ans; i--) tmp = (tmp*i)%p;
            tmp = inv(tmp, p);
            ans = (int)mod(-tmp, p);
        } else {
            ll tmp = 1LL;
            for(int i = 1; i <= ans; i++) tmp = (tmp*i)%p;
            ans = tmp;
        }
    } else if(n == 3 && k == 3) {
        ll tmp = 1LL;
        for(int i = 1; i <= 720; i++) tmp = (tmp*i)%p;
        ans = tmp;
    } else {
        ans = 0;
    }
    cout << ans%p << "\n";
    return 0;
}