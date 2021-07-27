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

bool chk(pi a, pi b) {
    if(a.fi > a.se) swap(a.fi, a.se);
    if(b.fi > b.se) swap(b.fi, b.se);
    if(a.fi > b.fi) swap(a, b);
    return a.se > b.fi && b.se > a.se;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n, k; cin >> n >> k;
        vector<pi> A(k);
        vector<bool> C(2*n, false);
        for(auto &i : A) {
            cin >> i.fi >> i.se;
            C[--i.fi] = true;
            C[--i.se] = true;
        }
        vector<int> B;
        for(int i = 0; i < 2*n; i++)
            if(!C[i]) B.push_back(i);
        for(int i = 0; i < n-k; i++)
            A.push_back({B[i], B[n-k+i]});
        int cnt = 0;
        for(int i = 0; i < n; i++)
            for(int j = i+1; j < n; j++)
                if(chk(A[i], A[j])) { cnt++; }
        cout << cnt << "\n";
    }
    return 0;
}