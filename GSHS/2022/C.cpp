#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128_t lll;
typedef pair<ll, ll> pll;
typedef pair<lll, lll> plll;
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

const lll LICHAO_INF = (lll)4e30;
const ll LICHAO_X_INF = (ll)1e15 + 10;

struct LiChao {
    struct Line {
        lll a, b;
        lll at(ll x) { return a * x + b; }
    };
    struct Node {
        Node *l, *r;
        Line line;
    } *root;

    LiChao() {
        root = new Node {nullptr, nullptr, {0, -LICHAO_INF}};
    }
    void update(Line line) {
        _update(line, root, -LICHAO_X_INF, LICHAO_X_INF);
    }
    void _update(Line line, Node *p, ll s, ll e) {
        Line l1 = p->line, l2 = line;
        if (l1.at(s) > l2.at(s)) swap(l1, l2);
        if (l1.at(e - 1) <= l2.at(e - 1)) {
            p->line = l2;
            return;
        }
        ll mid = (s + e) / 2;
        if (l1.at(mid) >= l2.at(mid)) {
            p->line = l1;
            if (!p->l) p->l = new Node {nullptr, nullptr, l2};
            _update(l2, p->l, s, mid);
        }
        else {
            p->line = l2;
            if (!p->r) p->r = new Node {nullptr, nullptr, l1};
            _update(l1, p->r, mid, e);
        }
    }
    ll query(ll x) {
        return _query(x, root, -LICHAO_X_INF, LICHAO_X_INF);
    }
    lll _query(ll x, Node *p, ll s, ll e) {
        if (!p || x < s || x >= e) return -LICHAO_INF;
        ll mid = (s + e) / 2;
        return max({ p->line.at(x), _query(x, p->l, s, mid), _query(x, p->r, mid, e) });
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k; cin >> n >> k;
    k = min(n, k);
    vector<ll> A(n);
    for(auto &i : A) cin >> i;
    vector<ll> B = {0LL};
    for(auto &i : A) B.push_back(B.back()+i);
    vector<vector<ll>> dp(k+1, vector<ll>(n+1, 0LL));
    fill(dp[0].begin(), dp[0].end(), 1LL);
    for(int i = 1; i <= k; i++) {
        LiChao cht1, cht2;
        cht1.update({-dp[i-1][i-1], (lll)dp[i-1][i-1]*B[i-1]});
        cht2.update({dp[i-1][i-1], -(lll)dp[i-1][i-1]*B[i-1]});
        for(int j = i; j <= n; j++) {
            //cout << i << " " << j << ", query : " << B[j] << "\n";
            dp[i][j] = max(dp[i][j-1], max(abs(cht1.query(B[j])), abs(cht2.query(B[j]))));
            cht1.update({-dp[i-1][j], (lll)dp[i-1][j]*B[j]});
            cht2.update({dp[i-1][j], -(lll)dp[i-1][j]*B[j]});
        }
    }
    //cout << " " << dp;
    ll ans = 0LL;
    for(int i = 1; i <= k; i++) ans = max(ans, dp[i].back());
    cout << ans << "\n";
    return 0;
}