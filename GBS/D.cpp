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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll a, d; cin >> a >> d;
    int q; cin >> q;
    while(q--) {
        ll t, l, r; cin >> t >> l >> r; --l;
        if(t == 1) {
            cout << (2*a+(l+r-1)*d)*(r-l)/2;
        } else {
            if(l+1 == r) cout << a+d*l;
            else cout << __gcd(a, d);
        }
        cout << "\n";
    }
    return 0;
}