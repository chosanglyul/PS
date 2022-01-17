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
const ll LLINF = 1e18+1;
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
    int t; cin >> t;
    for(int tt = 1; tt <= t; tt++) {
        int n; cin >> n;
        vector<int> A(n);
        for(auto &i : A) { cin >> i; i--; }
        vector<vector<int>> B;
        vector<bool> chk(n, false);
        for(int i = 0; i < n; i++) {
            if(chk[i]) continue;
            B.push_back(vector<int>());
            int tmp = i;
            while(!chk[tmp]) {
                chk[tmp] = true;
                B.back().push_back(tmp);
                tmp = A[tmp];
            }
        }
        int ans = 0;
        for(auto &i : B) {
            if(i.size() == 1) continue;
            ans += i.size();
        }
        cout << "Case #" << tt << ": " << ans << ".000000\n";

    }
    return 0;
}