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

const ll LICHAO_INF = (ll)4e18;
const ll LICHAO_X_INF = (ll)1e12 + 10;

struct LiChao {
    struct Line {
        ll a, b;
        ll at(ll x) { return a * x + b; }
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
    ll _query(ll x, Node *p, ll s, ll e) {
        if (!p || x < s || x >= e) return -LICHAO_INF;
        ll mid = (s + e) / 2;
        return max({ p->line.at(x), _query(x, p->l, s, mid), _query(x, p->r, mid, e) });
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    LiChao lc;
    int n; cin >> n;
    vector<pii> T;
    while(n--) {
        int t; cin >> t;
        if(t == 1) {
            ll a, b; cin >> a >> b;
            lc.update({a, b});
        } else {
            ll x; cin >> x;
            cout << lc.query(x) << "\n";
        }
    }
    return 0;
}