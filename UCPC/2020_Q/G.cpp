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
    int n; cin >> n;
    vector<vector<int>> A(n);
    for(auto &i : A) {
        int x; cin >> x;
        while(x) {
            i.push_back(--x);
            cin >> x;
        }
    }
    int m; cin >> m;
    vector<int> B(m), C(n, -1), D(n);
    for(auto &i : B) { cin >> i; i--; }
    for(int i = 0; i < n; i++) D[i] = (A[i].size()+1)/2;
    queue<pi> Q;
    for(auto i : B) {
        Q.push({i, 0});
        D[i] = -1;
    }
    while(Q.size()) {
        pi tmp = Q.front(); Q.pop();
        C[tmp.fi] = tmp.se;
        for(auto nxt : A[tmp.fi])
            if(--D[nxt] == 0)
                Q.push({nxt, tmp.se+1});
    }
    cout << C;
    return 0;
}