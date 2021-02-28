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
    int n, m, k; cin >> n >> m >> k;
    vector<vector<pi>> E(n);
    vector<priority_queue<int>> dist(n);
    for(int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        E[a].emplace_back(c, b);
    }
    priority_queue<pi, vector<pi>, greater<pi>> Q;
    Q.push({0, 0});
    while(Q.size()) {
        pi top = Q.top(); Q.pop();
        //cout << top << " " << dist[top.se].size() << " " << (dist[top.se].size() ? dist[top.se].top() : 0) << endl;
        if(dist[top.se].size() == k && dist[top.se].top() <= top.fi) continue;
        if(dist[top.se].size() == k) dist[top.se].pop();
        dist[top.se].push(top.fi);
        for(auto &i : E[top.se]) {
            if(dist[i.se].size() == k && dist[i.se].top() <= i.fi+top.fi) continue;
            Q.emplace(i.fi+top.fi, i.se);
        }
    }
    for(auto &i : dist) {
        if(i.size() < k) cout << -1 << "\n";
        else cout << i.top() << "\n";
    }
    return 0;
}