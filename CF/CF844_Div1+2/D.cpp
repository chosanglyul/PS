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
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> A(n);
        for(auto &i : A) cin >> i;
        vector<vector<pll>> B(n);
        for(int i = 0; i < n; i++) {
            for(int j = i+1; j < n; j++) {
                int tmp = A[j]-A[i];
                for(int k = 1; k*k <= tmp; k++) {
                    if(tmp%k == 0) {
                        int xx = k, yy = tmp/k;
                        if((xx+yy)&1) continue;
                        int a = (yy-xx)>>1, b = (xx+yy)>>1;
                        ll x = (ll)b*b-A[j];
                        if(x < 0LL) continue;
                        B[j].push_back({i, x});
                    }
                }
            }
        }
        
        vector<map<ll, int>> M(n);
        int ans = 1;
        for(int i = 0; i < n; i++) {
            for(auto &j : B[i]) {
                if(M[j.fi].find(j.se) == M[j.fi].end()) M[i][j.se] = max(M[i][j.se], 2);
                else M[i][j.se] = max(M[i][j.se], M[j.fi][j.se]+1);
                ans = max(ans, M[i][j.se]);
            }
        }
        cout << ans << "\n";
    }
    return 0;
}