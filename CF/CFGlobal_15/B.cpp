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

bool cmp(vector<int>& a, vector<int>& b) {
    int cnt = 0;
    for(int i = 0; i < 5; i++)
        if(a[i] > b[i]) cnt++;
    return cnt > 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<vector<int>> A(n, vector<int>(5));
        vector<bool> can(n, true);
        for(auto &i : A) for(auto &j : i) cin >> j;
        for(int i = 1, j = 0; i < n && j < n;) {
            if(cmp(A[j], A[i])) {
                can[j] = false;
                while(j < n && !can[j]) j++;
            } else {
                can[i] = false;
                while(i < n && !can[i]) i++;
            }
            if(i == j) i++;
        }
        int ans = -1;
        for(int i = 0; i < n; i++) {
            if(can[i]) {
                for(int j = 0; j < n; j++) {
                    if(i == j) continue;
                    if(cmp(A[i], A[j])) can[i] = false;
                }
                if(can[i]) ans = i+1;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}