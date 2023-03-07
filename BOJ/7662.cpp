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
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
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
    int t; cin >> t;
    while(t--) {
        multiset<int> S;
        int q; cin >> q;
        while(q--) {
            char c; int x; cin >> c >> x;
            if(c == 'I') S.insert(x);
            else {
                if(x == -1) {
                    auto iter = S.begin();
                    if(iter != S.end()) S.erase(iter);
                } else {
                    auto iter = S.end();
                    if(iter != S.begin()) S.erase(--iter);
                }
            }
        }
        if(S.empty()) cout << "EMPTY\n";
        else {
            auto iter = S.end();
            cout << *--iter << " ";
            iter = S.begin();
            cout << *iter << "\n";
        }
    }
    return 0;
}