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

int solve(vector<int> A, vector<int> B, vector<int> C) {
    for(auto c : C) {
        int idx = abs(c)-1;
        if(c < 0) {
            for(int i = idx+1; i < (int)B.size(); i++)
                B[i-1] = B[i];
            B[(int)B.size()-1] = 0;
        }
        if(c > 0) {
            for(int i = (int)B.size()-1; i > idx; i--)
                B[i] = B[i-1];
            B[idx] = 0;
        }
    }
    int ans = 0;
    for(int i = 0; i < A.size(); i++)
        ans += (A[i] == B[i]);
    return ans;
}

int dfs(int n, int m, vector<int> &A, vector<int> &B, vector<int> &C) {
    if(m == C.size()) return solve(A, B, C);
    int ans = 0;
    for(int i = -n; i <= n; i++) {
        C[m] = i;
        ans = max(ans, dfs(n, m+1, A, B, C));
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k; cin >> n >> k;
    vector<int> A(n), B(n), C(k);
    for(auto &i : A) cin >> i;
    for(auto &i : B) cin >> i;
    cout << dfs(n, 0, A, B, C) << "\n";
    return 0;
}