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
    int q; cin >> q;
    vector<int> A(64, 0);
    while(q--) {
        char c; ll x, tmp = 1LL; cin >> c >> x;
        if(x) {
            int ans = 0;
            while(tmp != x) ans++, tmp <<= 1;
            if(c == '+') A[ans]++;
            else A[ans]--;
        }
        vector<int> B(A);
        for(int i = 1; i < B.size(); i++) {
            B[i] += B[i-1]/2;
            B[i-1] %= 2;
        }
        if(*max_element(B.begin(), B.end()) == 0) {
            cout << 0 << "\n";
        } else {
            for(int i = B.size(); i > 0; i--) {
                if(B[i-1]) {
                    cout << (1LL<<(i-1)) << "\n";
                    break;
                }
            }
        }
    }
    return 0;
}