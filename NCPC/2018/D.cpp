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

    ll dist[1001][1001];

    int main() {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
        
        int n, m;
        cin >> n >> m;
        for (int i=1; i<=n; ++i) {
            for (int j=1; j<=n; ++j) {
                dist[i][j] = 1e18;
            }
        }
        for (int i=0; i<m; ++i) {
            int u, v, d;
            cin >> u >> v >> d;
            dist[u][v] = d;
            dist[v][u] = d;
        }
        for (int i=1; i<=n; ++i) dist[i][i] = 0;
        for (int k=1; k<=n; ++k) {
            for (int i=1; i<=n; ++i) {
                for (int j=1; j<=n; ++j) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }

        int k;
        cin >> k;
        vector<ll> prefix(k+1, 0);
        vector<tuple<ll,ll,ll> > orders(k+1);
        for (int i=1; i<=k; ++i) {
            int s, u, t;
            cin >> s >> u >> t;
            orders[i] = {s,u,t};
            if (i >= 2) {
                prefix[i] = prefix[i-1] + dist[get<1>(orders[i-1])][get<1>(orders[i])];
            }
        }
        
        ll low = 0, high = 1e18;
        while (low < high) {
            ll mid = (low + high) / 2;

            vector<bool> possible(k+1, false);
            vector<ll> dp(k+1, 1e18);
            possible[0] = true;
            dp[0] = 0;
            for (int i=1; i<=k; ++i) {
                ll max_waiting = 0;
                for (int j=i-1; j>=0; --j) {
                    ll min_start = max(dp[j], get<2>(orders[i]));
                    if (j == i-1) {
                        max_waiting = min_start + dist[1][get<1>(orders[j+1])] - get<0>(orders[j+1]);
                    } else {
                        ll from_start = max(dp[j+1], get<2>(orders[i]));
                        ll delta = min_start - from_start;
                        max_waiting = max(max_waiting + delta - dist[1][get<1>(orders[j+2])] + dist[1][get<1>(orders[j+1])] + prefix[j+2] - prefix[j+1], 
                                        min_start + dist[1][get<1>(orders[j+1])] - get<0>(orders[j+1]));
                    }
                    //cout << " " << i << " " << j << " " << min_start << " " << max_waiting << "\n";
                    if (max_waiting > mid) continue;
                    if (possible[j]) {
                        possible[i] = true;
                        dp[i] = min(dp[i], min_start + prefix[i]-prefix[j+1] + dist[1][get<1>(orders[j+1])] + dist[get<1>(orders[i])][1]);
                    }
                }
            }
            //cout << low << ' ' << mid << ' ' << high << '\n';
            //cout << dp;
            if (possible[k]) {
                high = mid;
            } else {
                low = mid+1;
            }
        }
        cout << low;
        
        return 0;
    }