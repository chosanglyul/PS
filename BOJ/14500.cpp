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
istream& operator>>(istream& is, vector<T>& v) { for(auto &i : v) is >> i; return is; }
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

typedef function<pii(pii)> func;

pii fx(pii a) { return {-a.fi, a.se}; }
pii fy(pii a) { return {a.fi, -a.se}; }

pii r0(pii a) { return {a.fi, a.se}; }
pii r1(pii a) { return {a.se, -a.fi}; }
pii r2(pii a) { return {-a.fi, -a.se}; }
pii r3(pii a) { return {-a.se, a.fi}; }

pii d1(pii a) { return {-a.se, -a.fi}; }
pii d2(pii a) { return {a.se, a.fi}; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<vector<int>> A(n, vector<int>(m));
    for(auto &i : A) for(auto &j : i) cin >> j;
    const vector<vector<pii>> B = {
        {{0, 0}, {0, 1}, {0, 2}, {0, 3}},
        {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
        {{0, 0}, {1, 0}, {2, 0}, {2, 1}},
        {{0, 0}, {1, 0}, {1, 1}, {2, 1}},
        {{0, 0}, {0, 1}, {0, 2}, {1, 1}}
    };
    const vector<func> F = { fx, fy, r0, r1, r2, r3, d1, d2 };
    int ans = 0;
    for(int x = -10; x <= n+10; x++) {
        for(int y = -10; y <= m+10; y++) {
            for(auto &f : F) {
                for(auto T : B) {
                    int tmp = 0;
                    for(auto &i : T) {
                        i = f(i); i.fi += x, i.se += y;
                        if(i.fi < 0 || i.fi >= n || i.se < 0 || i.se >= m) {
                            tmp = 0;
                            break;
                        } else tmp += A[i.fi][i.se];
                    }
                    ans = max(ans, tmp);
                }
            }
        }
    }
    cout << ans << "\n";
    return 0;
}
