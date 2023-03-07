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

int L(int x) { return (x/1000)+(x%1000)*10; }
int R(int x) { return (x/10)+(x%10)*1000; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int x, y; cin >> x >> y;
        vector<bool> vis(10000, false);
        queue<pair<int, string>> Q; Q.push({x, ""});
        while(Q.front().fi != y) {
            auto tmp = Q.front(); Q.pop();
            int d = (2*tmp.fi)%10000, s = (tmp.fi-1+10000)%10000;
            int l = L(tmp.fi), r = R(tmp.fi);
            if(!vis[d]) Q.push({d, tmp.se+'D'}), vis[d] = true;
            if(!vis[s]) Q.push({s, tmp.se+'S'}), vis[s] = true;
            if(!vis[l]) Q.push({l, tmp.se+'L'}), vis[l] = true;
            if(!vis[r]) Q.push({r, tmp.se+'R'}), vis[r] = true;
        }
        cout << Q.front().se << "\n";
    }
    return 0;
}