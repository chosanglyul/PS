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

void solve(int idx, int jdx, vector<int> &A, vector<int> &B, vector<int> &cnt) {
    if(idx == 0) {
        for(auto i : B) cout << A[i] << " ";
        cout << "\n";
        return;
    }
    for(int i = jdx; i < A.size(); i++) {
            B.push_back(i);
            solve(idx-1, i, A, B, cnt);
            B.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<int> A(n), B, cnt;
    for(auto &i : A) cin >> i;
    sort(A.begin(), A.end());
    vector<int> C(A);
    C.erase(unique(C.begin(), C.end()), C.end());
    cnt.resize(C.size(), 0);
    for(auto i : A) cnt[lower_bound(C.begin(), C.end(), i) - C.begin()]++;
    solve(m, 0, C, B, cnt);
    return 0;
}
