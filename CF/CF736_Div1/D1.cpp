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

int solve(int i, int j) {
    int x = (j&1)-(i&1), y = (j>>1)-(i>>1);
    if(x < 0) x = -x;
    if(y < 0) y = -y;
    return x | y;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    ll cnt[2][2] = {0, };
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        x >>= 1, y >>= 1;
        cnt[x%2][y%2]++;
    }
    ll ans = 0LL;
    for(int i = 0; i < 4; i++) {
        for(int j = i; j < 4; j++) {
            for(int k = j; k < 4; k++) {
                int tmp = solve(i, j)+solve(j, k)+solve(k, i);
                if(tmp%2) continue;
                vector<int> A = {i, j, k};
                sort(A.begin(), A.end());
                if(A[0] == A[1] && A[1] == A[2]) {
                    ll c = cnt[A[0]&1][A[0]>>1];
                    ans += c*(c-1LL)*(c-2LL)/6LL;
                } else if(A[0] == A[1]) {
                    ll c = cnt[A[0]&1][A[0]>>1];
                    ans += c*(c-1LL)*cnt[A[2]&1][A[2]>>1]/2LL;
                } else if(A[1] == A[2]) {
                    ll c = cnt[A[1]&1][A[1]>>1];
                    ans += c*(c-1LL)*cnt[A[0]&1][A[0]>>1]/2LL;
                } else ans += cnt[A[0]&1][A[0]>>1]*cnt[A[1]&1][A[1]>>1]*cnt[A[2]&1][A[2]>>1];
            }
        }
    }
    cout << ans << "\n";
    return 0;
}