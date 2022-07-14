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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n, m; cin >> n >> m;
        vector<vector<int>> A(n, vector<int>(m));
        for(auto &i : A) for(auto &j : i) cin >> j;
        vector<vector<int>> B(A);
        for(auto &i : A) sort(i.begin(), i.end());
        int l = -1, r = -1;
        bool can = true;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(A[i][j] != B[i][j]) {
                    if(l == j || r == j) continue;
                    else if(l == -1) l = j;
                    else if(r == -1) r = j;
                    else can = false;
                }
            }
        }
        if(can) {
            if(l == -1) cout << "1 1\n";
            else {
                for(auto &i : A) swap(i[l], i[r]);
                for(int i = 0; i < n; i++)
                    for(int j = 0; j < m; j++)
                        if(A[i][j] != B[i][j]) can = false;
                if(can) cout << ++l << " " << ++r << "\n";
                else cout << "-1\n";
            }
        } else cout << "-1\n";
    }
    return 0;
}