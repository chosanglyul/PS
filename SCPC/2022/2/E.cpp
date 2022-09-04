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
const int P = 998244353;
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t; cin >> t;
    for(int _t = 0; _t < t; _t++) {
        cout << "Case #" << _t+1 << endl;
        int n, k; cin >> n >> k;
        vector<int> A(n);
        for(auto &i : A) cin >> i;
        if(n > 10) {
            cout << 0 << endl;
            continue;
        }
        ll ans = 0LL;
        vector<ll> B(1<<n, 0LL);
        B[0] = 1LL;
        for(int i = 0; i < k; i++) {
            vector<ll> T(1<<n, 0LL);
            for(int j = 0; j < T.size(); j++)
                for(int x = 0, y = 1; x < n; x++, y <<= 1)
                    T[j|y] = (T[j|y]+B[j]*A[x])%P;
            B = T;
            ll tmp = 0LL;
            for(int j = 0; j < B.size(); j++)
                tmp += __builtin_popcount(j) * B[j];
            ans ^= tmp%P;
        }
        cout << ans << endl;
    }
    return 0;
}