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
    int n, m; cin >> n >> m;
    vector<pii> E(m);
    vector<ll> dist(n, LLINF);
    dist[0] = 0;
    for(auto &i : E) {
        cin >> i.se.fi >> i.se.se >> i.fi;
        i.se.fi--, i.se.se--;
    }
    for(int i = 0; i < n; i++) {
        for(auto &j : E) {
            if(dist[j.se.fi]+j.fi < dist[j.se.se]) {
                if(i == n-1 && dist[j.se.se] < INF) {
                    cout << -1 << "\n";
                    return 0;
                }
                dist[j.se.se] = dist[j.se.fi]+j.fi;
            }
        }
    }
    for(int i = 1; i < n; i++) {
        if(dist[i] >= INF) cout << -1 << "\n";
        else cout << dist[i] << "\n";
    }
    return 0;
}