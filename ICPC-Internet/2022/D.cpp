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

const int MAX = 1e5+1;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> A(n);
    for(auto &i : A) cin >> i;
    vector<ll> B(MAX*3);
    for(int i = 0; i < B.size(); i++) B[i] = (ll)i*(i+1)/2LL + 1LL;

    ll d = 0LL;
    while(true) {
        ll x = 0LL;
        int k = upper_bound(B.begin(), B.end(), d+A[0]) - B.begin() - 1;
        for(int i = ((k/2)*2)+1; i <= 3+k+MAX/max(k, 1); i += 2) {
            auto iter = lower_bound(A.begin(), A.end(), B[i]-d);
            if(iter == A.end()) break;
            ll mv = (*iter)+d;
            if(B[i+1] > mv) x = max(x, B[i+1] - mv);
        }
        if(x == 0LL) break;
        d += x;
    }
    cout << d << "\n";
    return 0;
}