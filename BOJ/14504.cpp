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
    int n; cin >> n;
    vector<int> A(n);
    for(auto &i : A) cin >> i;
    int sq = sqrt(n)+1;
    vector<vector<int>> S(sq);
    for(int i = 0; i < sq; i++) {
        for(int j = sq*i; j < min(n, sq*(i+1)); j++) S[i].push_back(A[j]);
        sort(S[i].begin(), S[i].end());
    }
    int m; cin >> m;
    for(int i = 0; i < m; i++) {
        int t; cin >> t;
        if(t == 1) {
            int l, r, v; cin >> l >> r >> v; l--;
            int lsq = l/sq, rsq = r/sq;
            int ans = 0;
            if(lsq != rsq) {
                for(int i = l; i < (lsq+1)*sq; i++) ans += A[i] > v;
                for(int i = lsq+1; i < rsq; i++)
                    ans += S[i].end() - upper_bound(S[i].begin(), S[i].end(), v);
                for(int i = rsq*sq; i < r; i++) ans += A[i] > v;
            } else {
                for(int i = l; i < r; i++) ans += A[i] > v;
            }
            cout << ans << "\n";
        } else {
            int j, v; cin >> j >> v; j--;
            vector<int> &T = S[j/sq];
            T.erase(find(T.begin(), T.end(), A[j]));
            A[j] = v;
            auto iter = T.begin();
            while(iter != T.end() && *iter < A[j]) iter++;
            T.insert(iter, A[j]);
        }
    }
    return 0;
}